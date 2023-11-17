// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2022 NXP
 */
#include <asm/arch/soc_memory_map.h>
#include <asm/arch/ccm_regs.h>
#include <asm/arch/clock.h>
#include <asm/arch/imx-regs.h>
#include <asm/io.h>
#include <errno.h>
#include <time.h>

#if defined(CA55)
#define ANATOP_BASE_ADDR	ANATOP_NS_RBASE
#elif defined(CM33)
#define ANATOP_BASE_ADDR	ANATOP_RBASE
#else
#error "Please specify either -DCA55 or -DCM33 !"
#endif

static struct anatop_reg *ana_regs = (struct anatop_reg *)ANATOP_BASE_ADDR;

struct imx_fracpll_rate_table imx9_fracpll_tbl[] = {
	FRAC_PLL_RATE(1066666666U, 1, 133, 3, 1, 3), /* 1066.(6)Mhz */
	FRAC_PLL_RATE(1000000000U, 1, 166, 4, 2, 3), /* 1000Mhz */
	FRAC_PLL_RATE(933333333U, 1, 155, 4, 5, 9), /* 933.(3)Mhz */
	FRAC_PLL_RATE(933000000U, 1, 155, 4, 1, 2), /* 933.(0)Mhz */
	FRAC_PLL_RATE(800000000U, 1, 200, 6, 0, 1), /* 800Mhz */
	FRAC_PLL_RATE(700000000U, 1, 145, 5, 5, 6), /* 700Mhz */
	FRAC_PLL_RATE(600000000U, 1, 200, 8, 0, 1), /* 600Mhz */
	FRAC_PLL_RATE(533333333U, 1, 133, 6, 1, 3), /* 533.(3)Mhz */
	FRAC_PLL_RATE(484000000U, 1, 121, 6, 0, 1),
	FRAC_PLL_RATE(466666666U, 1, 155, 8, 5, 9), /* 466.(6)Mhz */
	FRAC_PLL_RATE(466000000U, 1, 155, 8, 1, 3), /* 466.(0)Mhz */
	FRAC_PLL_RATE(400000000U, 1, 200, 12, 0, 1), /* 400Mhz */
	FRAC_PLL_RATE(300000000U, 1, 150, 12, 0, 1),
	FRAC_PLL_RATE(266666666U, 1, 177, 16, 7, 9), /* 266.(6)Mhz */
	FRAC_PLL_RATE(233333333U, 1, 155, 16, 5, 9), /* 233.(3)Mhz */
	FRAC_PLL_RATE(233000000U, 1, 174, 18, 3, 4), /* 233.(0)Mhz */
	FRAC_PLL_RATE(200000000U, 1, 200, 24, 0, 1), /* 200Mhz */
	FRAC_PLL_RATE(100000000U, 1, 200, 48, 0, 1), /* 100Mhz */
	FRAC_PLL_RATE(0U, 0, 0, 0, 0, 0)
};

/**
 * Fractional mode.
 * Set the output clock frequency for a fractional PLL.
 * The equations are:
 *      Fvco_clk = Fref / DIV[RDIV] * (DIV[MFI] + DENOMINATOR[MFN] / NUMERATOR[MFD])
 *      Fclko_odiv = Fvco_clk / DIV[ODIV]
 * RDIV, MFI, MFN, MFD, ODIV are provided in imx9_fracpll_tbl.
 */
int configure_fracpll(enum ccm_clk_src pll, u32 freq)
{
	struct imx_fracpll_rate_table *rate;
	struct ana_pll_reg *reg;
	u32 i, pll_status;

	for (i = 0; i < ARRAY_SIZE(imx9_fracpll_tbl); i++) {
		if (freq == imx9_fracpll_tbl[i].rate)
			break;
	}

	if (i == ARRAY_SIZE(imx9_fracpll_tbl)) {
/*		debug("No matched freq table %u\n", freq); */
		return -EINVAL;
	}

	rate = &imx9_fracpll_tbl[i];

	switch (pll) {
	case SYS_PLL_PG:
		reg = &ana_regs->sys_pll;
		break;
	case DRAM_PLL_CLK:
		reg = &ana_regs->dram_pll;
		break;
	case VIDEO_PLL_CLK:
		reg = &ana_regs->video_pll;
		break;
#ifdef CONFIG_IMX95
	case AUDIO_PLL_CLK:
		reg = &ana_regs->audio_pll;
		break;
	case AUDIO_PLL2_CLK:
		reg = &ana_regs->audio_pll2;
		break;
#endif
	default:
		return -EPERM;
	}

	/* Bypass the PLL to ref */
	writel(PLL_CTRL_CLKMUX_BYPASS, &reg->ctrl.reg_set);

	/* disable pll and output */
	writel(PLL_CTRL_CLKMUX_EN | PLL_CTRL_POWERUP, &reg->ctrl.reg_clr);

	/* Program the ODIV, RDIV, MFI */
	writel((rate->odiv & GENMASK(7, 0)) | ((rate->rdiv << 13) & GENMASK(15, 13)) |
	       ((rate->mfi << 16) & GENMASK(24, 16)), &reg->div.reg);

	/* Set SPREAD_SPECRUM enable to 0 */
	writel(PLL_SS_EN, &reg->ss.reg_clr);

	/* Program NUMERATOR and DENOMINATOR */
	writel((rate->mfn << 2), &reg->num.reg);
	writel((rate->mfd & GENMASK(29, 0)), &reg->denom.reg);

#ifndef CONFIG_IMX95_EMU
	/* wait 5us */
	udelay(5);
#endif

	/* power up the PLL and wait lock (max wait time 100 us) */
	writel(PLL_CTRL_POWERUP, &reg->ctrl.reg_set);

#ifndef CONFIG_IMX95_EMU
	udelay(100);
#endif

	pll_status = readl(&reg->pll_status);
	if (pll_status & PLL_STATUS_PLL_LOCK) {
		writel(PLL_CTRL_CLKMUX_EN, &reg->ctrl.reg_set);

		/* check the MFN is updated */
		pll_status = readl(&reg->pll_status);
		if ((pll_status & ~0x3) != (rate->mfn << 2)) {
/*			debug("MFN update not matched, pll_status 0x%x, mfn 0x%x\n",
			      pll_status, rate->mfn); */
#ifndef CONFIG_IMX95_EMU
			return -EIO;
#endif
		}

		/* clear bypass */
		writel(PLL_CTRL_CLKMUX_BYPASS, &reg->ctrl.reg_clr);

	} else {
/*		debug("Fail to lock PLL %u\n", pll); */
		return -EIO;
	}

	return 0;
}

void dram_pll_init(ulong pll_val)
{
	configure_fracpll(DRAM_PLL_CLK, pll_val);
}

void dram_enable_bypass(ulong clk_val)
{
	switch (clk_val) {
	case MHZ(625):
		ccm_clk_root_cfg(DRAM_ALT_CLK_ROOT, SYS_PLL_PFD2, 1);
		break;
	case MHZ(400):
		ccm_clk_root_cfg(DRAM_ALT_CLK_ROOT, SYS_PLL_PFD1, 2);
		break;
	case MHZ(333):
		ccm_clk_root_cfg(DRAM_ALT_CLK_ROOT, SYS_PLL_PFD0, 3);
		break;
	case MHZ(200):
		ccm_clk_root_cfg(DRAM_ALT_CLK_ROOT, SYS_PLL_PFD1, 4);
		break;
	case MHZ(100):
		ccm_clk_root_cfg(DRAM_ALT_CLK_ROOT, SYS_PLL_PFD1, 8);
		break;
	default:
/*		printf("No matched freq table %lu\n", freq); */
		return;
	}

	/* Set DRAM APB to 133Mhz */
	ccm_clk_root_cfg(DRAM_APB_CLK_ROOT, SYS_PLL_PFD1_DIV2, 3);
	/* Switch from DRAM  clock root from PLL to CCM */
	ccm_shared_gpr_set(SHARED_GPR_DRAM_CLK, SHARED_GPR_DRAM_CLK_SEL_CCM);
}

void dram_disable_bypass(void)
{
	/* Set DRAM APB to 133Mhz */
	ccm_clk_root_cfg(DRAM_APB_CLK_ROOT, SYS_PLL_PFD1_DIV2, 3);
	/* Switch from DRAM  clock root from CCM to PLL */
	ccm_shared_gpr_set(SHARED_GPR_DRAM_CLK, SHARED_GPR_DRAM_CLK_SEL_PLL);
}
