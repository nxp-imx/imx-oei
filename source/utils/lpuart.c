/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */
#include <asm/arch/clock.h>
#include <asm/arch/soc_memory_map.h>
#include <asm/io.h>
#include <asm/types.h>
#include "debug.h"
#include "iopoll.h"

#define UART_BASE			LPUART1_RBASE
#define UART_CLOCK			LPUART1_CLK_ROOT

#define LPUART_BAUD_BOTHEDGE_MASK	(0x20000)
#define LPUART_BAUD_OSR_MASK		(0x1F000000)
#define LPUART_BAUD_OSR_SHIFT		(24)
#define LPUART_BAUD_OSR(x)		((((u32)(x)) << 24) & 0x1F000000)
#define LPUART_BAUD_SBR_MASK		(0x1FFF)
#define LPUART_BAUD_SBR_SHIFT		(0U)
#define LPUART_BAUD_SBR(x)		(((u32)(x)) & 0x1FFF)
#define LPUART_BAUD_M10_MASK		(0x20000000U)
#define LPUART_BAUD_SBNS_MASK		(0x2000U)
#define LPUART_GLOBAL_RST_MASK		BIT(1)

#define US1_TDRE	BIT(7)
#define US1_RDRF	BIT(5)
#define US1_OR		BIT(3)
#define UC2_TE		BIT(3)
#define UC2_RE		BIT(2)
#define CFIFO_TXFLUSH	BIT(7)
#define CFIFO_RXFLUSH	BIT(6)
#define SFIFO_RXOF	BIT(2)
#define SFIFO_RXUF	BIT(0)

#define STAT_LBKDIF	BIT(31)
#define STAT_RXEDGIF	BIT(30)
#define STAT_TDRE	BIT(23)
#define STAT_RDRF	BIT(21)
#define STAT_IDLE	BIT(20)
#define STAT_OR		BIT(19)
#define STAT_NF		BIT(18)
#define STAT_FE		BIT(17)
#define STAT_PF		BIT(16)
#define STAT_MA1F	BIT(15)
#define STAT_MA2F	BIT(14)
#define STAT_FLAGS	(STAT_LBKDIF | STAT_RXEDGIF | STAT_IDLE | STAT_OR | \
			 STAT_NF | STAT_FE | STAT_PF | STAT_MA1F | STAT_MA2F)

#define CTRL_TE		BIT(19)
#define CTRL_RE		BIT(18)

#define FIFO_RXFLUSH		BIT(14)
#define FIFO_TXFLUSH		BIT(15)
#define FIFO_TXSIZE_MASK	0x70
#define FIFO_TXSIZE_OFF	4
#define FIFO_RXSIZE_MASK	0x7
#define FIFO_RXSIZE_OFF	0
#define FIFO_TXFE		0x80
#define FIFO_RXFE		0x40

#define WATER_TXWATER_OFF	0
#define WATER_RXWATER_OFF	16

#define LPUART_FLAG_REGMAP_32BIT_REG	BIT(0)
#define LPUART_FLAG_REGMAP_ENDIAN_BIG	BIT(1)

#ifdef CONFIG_IMX95_EMU
#define BAUD_RATE 4000000
#else
#define BAUD_RATE 115200
#endif

struct lpuart_fsl_reg32 {
	u32 verid;
	u32 param;
	u32 global;
	u32 pincfg;
	u32 baud;
	u32 stat;
	u32 ctrl;
	u32 data;
	u32 match;
	u32 modir;
	u32 fifo;
	u32 water;
};

enum lpuart_devtype {
	DEV_VF610 = 1,
	DEV_LS1021A,
	DEV_MX7ULP,
	DEV_IMX8,
	DEV_IMXRT,
};

static struct lpuart_serial_platdata {
	void *reg;
	enum lpuart_devtype devtype;
	unsigned long flags;
} platdata = {
	.reg = (void *)UART_BASE,
	.devtype = DEV_MX7ULP,
	.flags = LPUART_FLAG_REGMAP_32BIT_REG,
};

static void lpuart32_serial_setbrg_7ulp(int baudrate)
{
	struct lpuart_serial_platdata *plat = &platdata;
	struct lpuart_fsl_reg32 *base = plat->reg;
	u32 sbr, osr, baud_diff, tmp_osr, tmp_sbr, tmp_diff, tmp;
	u32 clk = MHZ(24);

	baud_diff = baudrate;
	osr = 0;
	sbr = 0;

	for (tmp_osr = 4; tmp_osr <= 32; tmp_osr++) {
		tmp_sbr = (clk / (baudrate * tmp_osr));

		if (tmp_sbr == 0)
			tmp_sbr = 1;

		/* calculate difference in actual buad w/ current values */
		tmp_diff = (clk / (tmp_osr * tmp_sbr));
		tmp_diff = tmp_diff - baudrate;

		/* select best values between sbr and sbr+1 */
		if (tmp_diff > (baudrate - (clk / (tmp_osr * (tmp_sbr + 1))))) {
			tmp_diff = baudrate - (clk / (tmp_osr * (tmp_sbr + 1)));
			tmp_sbr++;
		}

		if (tmp_diff <= baud_diff) {
			baud_diff = tmp_diff;
			osr = tmp_osr;
			sbr = tmp_sbr;
		}
	}

	/* Software reset */
	setl(LPUART_GLOBAL_RST_MASK, &base->global);
	clrl(LPUART_GLOBAL_RST_MASK, &base->global);

	tmp = readl(&base->baud);

	if ((osr > 3) && (osr < 8))
		tmp |= LPUART_BAUD_BOTHEDGE_MASK;

	tmp &= ~LPUART_BAUD_OSR_MASK;
	tmp |= LPUART_BAUD_OSR(osr-1);

	tmp &= ~LPUART_BAUD_SBR_MASK;
	tmp |= LPUART_BAUD_SBR(sbr);

	/* explicitly disable 10 bit mode & set 1 stop bit */
	tmp &= ~(LPUART_BAUD_M10_MASK | LPUART_BAUD_SBNS_MASK);

	writel(tmp, &base->baud);
}

static void lpuart32_serial_putc(struct lpuart_serial_platdata *plat, const char c)
{
	struct lpuart_fsl_reg32 *base = plat->reg;
	u32 stat;

	if (c == '\n')
		lpuart32_serial_putc(plat, '\r');

	readl_poll_timeout(&base->stat, stat, (stat & STAT_TDRE), 0);

	writel(c, &base->data);
}

int lpuart32_serial_init(void)
{
	struct lpuart_serial_platdata *plat = &platdata;
	struct lpuart_fsl_reg32 *base = (struct lpuart_fsl_reg32 *)plat->reg;
	u32 val, tx_fifo_size;

	val = readl(&base->ctrl);
	val &= ~CTRL_RE;
	val &= ~CTRL_TE;
	writel(val, &base->ctrl);

	writel(0, &base->modir);

	val = readl(&base->fifo);
	tx_fifo_size = (val & FIFO_TXSIZE_MASK) >> FIFO_TXSIZE_OFF;
	/* Set the TX water to half of FIFO size */
	if (tx_fifo_size > 1)
		tx_fifo_size = tx_fifo_size >> 1;

	/* Set RX water to 0, to be triggered by any receive data */
	writel((tx_fifo_size << WATER_TXWATER_OFF), &base->water);

	/* Enable TX and RX FIFO */
	val |= (FIFO_TXFE | FIFO_RXFE | FIFO_TXFLUSH | FIFO_RXFLUSH);
	writel(val, &base->fifo);

	writel(0, &base->match);

	lpuart32_serial_setbrg_7ulp(BAUD_RATE);

	writel(CTRL_RE | CTRL_TE,  &base->ctrl);

	return 0;
}

static int lpuart32_serial_getc(void)
{
	struct lpuart_serial_platdata *plat = &platdata;
	struct lpuart_fsl_reg32 *base = (struct lpuart_fsl_reg32 *)plat->reg;
	u32 stat, val;

	stat = readl(&base->stat);
	while ((stat & STAT_RDRF) == 0) {
		writel(STAT_FLAGS, &base->stat);
		stat = readl(&base->stat);
	}

	val = readl(&base->data);
	stat = readl(&base->stat);
	if (stat & STAT_OR)
		writel(STAT_OR, &base->stat);

	return val & 0x3ff;
}

int getc(void)
{
	return lpuart32_serial_getc();
}

void putc(const char c)
{
	lpuart32_serial_putc(&platdata, c);
}
