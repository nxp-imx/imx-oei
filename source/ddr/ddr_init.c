// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2022-2024 NXP
 */
#include <asm/io.h>
#include "time.h"
#include "iopoll.h"
#include "soc_ddr.h"

#define MAX(a, b)	(((a) > (b)) ? (a) : (b))

#if defined(CA55)
#define SRC_BASE	SRC_RBASE
#elif defined(CM33)
#define SRC_BASE	SRC_RBASE
#else
#error "Please specify either -DCA55 or -DCM33 !"
#endif

#define SRC_DDRMIX_PRS_BASE_ADDR	SRC_BASE + 0x3400U
#define SRC_DDRMIX_PRS_SLICE_SW_CTRL	SRC_DDRMIX_PRS_BASE_ADDR + 0x20U
#define SRC_DDRMIX_PRS_IRST_REQ_CTRL	SRC_DDRMIX_PRS_BASE_ADDR + 0x24U
#define SRC_DDRMIX_PRS_FUNC_STAT	SRC_DDRMIX_PRS_BASE_ADDR + 0xb4U

#define SRC_DDRMIX_PRM_BASE_ADDR	SRC_BASE + 0x3500U

static void check_ddrc_idle(void)
{
	u32 regval;

	do {
		regval = readl(REG_DDRDSR_2);
		if (regval & BIT(31))
			break;
	} while (1);
}

static void check_dfi_init_complete(void)
{
	u32 regval;

	do {
		regval = readl(REG_DDRDSR_2);
		if (regval & BIT(2))
			break;
	} while (1);
	setbits_le32(REG_DDRDSR_2, BIT(2));
}

int ddrc_config(struct dram_timing_info *dtiming, uint32 fsp_id)
{
	uint32_t i = 0, num = dtiming->ddrc_cfg_num;
	struct ddrc_cfg_param *ddrc_cfg;

	ddrc_cfg = dtiming->ddrc_cfg;

	/* common DDRC config */
	for (i = 0; i < num; i++, ddrc_cfg++)
		writel(ddrc_cfg->val, ddrc_cfg->reg);

	if (dtiming->fsp_cfg == NULL || fsp_id >= dtiming->fsp_cfg_num)
		return -EINVAL;

	/**
	 * FSP specific DDRC config
	 *
	 * Pstate DDRC specific configuration
	 * index must be correlated with the index of
	 * the corresponding drate in fsp_table.
	 */
	for (i = 0; i < dtiming->fsp_msg_num; i++) {
		if (dtiming->fsp_table[i] == dtiming->fsp_msg[fsp_id].drate)
			break;
	}

	if (i < dtiming->fsp_cfg_num) {
		ddrc_cfg = dtiming->fsp_cfg[i].ddrc_cfg;
		num      = dtiming->fsp_cfg[i].ddrc_cfg_num;

		for (i = 0; i < num; i++, ddrc_cfg++)
			writel(ddrc_cfg->val, ddrc_cfg->reg);
	}

	return 0;
}

static void ddrphy_coldreset(void)
{
	/**
	 * BIT(8) => src_ipc_ddrphy_presetn, PRESETN
	 * BIT(9) => src_ipc_ddrphy_reset_n, RESET_N
	 *
	 * DfiClk is 790MHz in waveform ~= 800MHz ?
	 * APBCLK is 200MHz in waveform
	 */
	u32 stat;

	/**
	 * for some reason BIT(8)=1 at this point, so PRESETN go LOW after power-up
	 * Ensure PRESETN go HIGH after power-up
	 * Ensure RESET_N go LOW  after power-up
	 */
	clrbits_le32(SRC_DDRMIX_PRS_IRST_REQ_CTRL, BIT(8));
	setbits_le32(SRC_DDRMIX_PRS_IRST_REQ_CTRL, BIT(9));

	/* Disable IPs isolation in DDRMIX */
	clrbits_le32(SRC_DDRMIX_PRS_SLICE_SW_CTRL, 0x7f000000);
	/* Power-up DDRMIX */
	clrbits_le32(SRC_DDRMIX_PRS_SLICE_SW_CTRL, BIT(31));
	/* Wait resets to be released => BIT(2) being set */
	readl_poll_timeout(SRC_DDRMIX_PRS_FUNC_STAT, stat, (stat & BIT(2)), 0);
	/* sleep for a while, just random */
	udelay(8);
	/* set PRESETN LOW after power-up */
	setbits_le32(SRC_DDRMIX_PRS_IRST_REQ_CTRL, BIT(8));
	/* The delay below must be at least 16 APBCLK
	 * APBCLK is @200MHz in waveform. Timer clock is @24MHz =>
	 * => (16 * 24.000.000 / 200.000.000) = 1.92us minimum
	 * => set x4 = 8us */
	udelay(8);
	/* set PRESETN HIGH */
	clrbits_le32(SRC_DDRMIX_PRS_IRST_REQ_CTRL, BIT(8));
	/* The delay below shall be 0 according to PHY PUB, set 8 just in case */
	udelay(8);
	/* set RESET_N HIGH */
	clrbits_le32(SRC_DDRMIX_PRS_IRST_REQ_CTRL, BIT(9));
	/* The duration for the delay below is not mentioned in PHY PUB, set 8 just in case */
	udelay(8);
}

int ddr_init(struct dram_timing_info *dtiming)
{
	int ret;
	u32 fsp_id, drate, acg;

	/* reset ddrphy */
	ddrphy_coldreset();

	/**
	 * FSP ID must point to the last trained FSP
	 * so that the proper DDRC config - for the
	 * last trained FSP - is loaded. This fits
	 * both training and quick boot flows.
	 */
	fsp_id = dtiming->fsp_msg_num - 1;
	drate = dtiming->fsp_msg[fsp_id].drate;
	/* default to the last frequency point clock */
	ddrphy_init_set_dfi_clk(drate);

	if (ddr_training_data_check()) {
		/* Configure PHY in QuickBoot mode */
		ret = ddr_cfg_phy_qb(dtiming, fsp_id);
		if (ret)
			return ret;
	} else {
		/*
		 * Start PHY initialization and training by
		 * accessing relevant PUB registers
		 */
		ret = ddr_cfg_phy(dtiming);
		if (ret)
			return ret;

		ddrphy_qb_save();
	}

	/* save the ddr info for retention */
	ddr_cfg_save(dtiming);

	/* save the ddr PHY trained CSR for retention */
	ddrphy_trained_csr_save();

	/* program the ddrc registers */
	ddrc_config(dtiming, fsp_id);

	check_dfi_init_complete();

	setbits_le32(REG_DDR_SDRAM_CFG, BIT(31)); /* |= 0x80000000 */

	check_ddrc_idle();

	while (readl(REG_DDR_MTCR) & 0x80000000);

	/**
	 * Enable auto clock gating feature
	 * By default gate all options except GATE_DDRPHY_DFICLK
	 */
	acg  = HWFFC_ACG_FORCE_B | AUTO_CG_ENA | SSI_IDLE_STRAP;
	acg |= GATE_DDRPHY_APBCLK | GATE_DDRC_IPS_CLK | GATE_DDRC_CLK;

	setbits_le32(REG_AUTO_CG_CTRL, acg);

	/** Set SR_FAST_WK_EN in REG_DDR_SDRAM_CFG_3 */
	setbits_le32(REG_DDR_SDRAM_CFG_3, SR_FAST_WK_EN);

	return 0;
}
