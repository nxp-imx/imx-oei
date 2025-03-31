/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "oei.h"
#include "config_board.h"
#include "fsl_ccm.h"
#include "fsl_clock.h"

struct clk_root_cfg {
	uint32_t clk_root_id;
	uint32_t clk_src_id;
	uint32_t div;
};

static struct clk_root_cfg clk_root_cfgs[] = {
	{ CLOCK_ROOT_DRAMAPB, CLOCK_SRC_SYSPLL1_PFD1_DIV2, 3 }, /* 400MHz / 3 = 133.(3) MHz */
#ifdef DEBUG
#if (BOARD_DEBUG_UART_INSTANCE == 1)
	{ CLOCK_ROOT_LPUART1, CLOCK_SRC_OSC24M, 1}, /* 24MHz */
#elif (BOARD_DEBUG_UART_INSTANCE == 2)
	{ CLOCK_ROOT_LPUART2, CLOCK_SRC_OSC24M, 1}, /* 24MHz */
#endif
#endif
};

int clk_root_set_rate_enable(uint32_t id, uint32_t src, uint32_t div, bool enable)
{
	(void) CCM_RootSetDiv(id, div);
	(void) CCM_RootSetParent(id, src);
	(void) CCM_RootSetEnable(id, enable);

	return 0;
}

int Clock_Init(void)
{
	unsigned int i = 0;
	struct clk_root_cfg *cfg = NULL;

	for (i = 0; i < ARRAY_SIZE(clk_root_cfgs); i++) {
		cfg = &clk_root_cfgs[i];
		clk_root_set_rate_enable(cfg->clk_root_id, cfg->clk_src_id, cfg->div, true);
	}

	return 0;
}

struct fracpll_rate_table {
	uint64_t vco;
	uint64_t rate;
};

struct fracpll_rate_table fracpll_tbl[] = {
	{ 4800000000ULL, 800000000ULL },
	{ 4800000000ULL, 600000000ULL },
	{ 4800000000ULL, 200000000ULL },
	{ 3199500000ULL, 533250000ULL },
	{ 4000000000ULL, 500000000ULL },
	{ 3733000000ULL, 466625000ULL },
	{ 3200000000ULL, 400000000ULL },
	{ 3199500000ULL, 266625000ULL },
	{ 3732000000ULL, 233250000ULL },
};

void Dram_PLL_Init(uint64_t pll_val, bool ssc)
{
	unsigned int i = 0;
	struct fracpll_rate_table *tbl = NULL;

	if ((CLOCK_SourceGetRate(CLOCK_SRC_DRAMPLL) == pll_val) &&
	    CLOCK_SourceGetEnable(CLOCK_SRC_DRAMPLL))
		return;

	for (i = 0; i < ARRAY_SIZE(fracpll_tbl); i++) {
		tbl = &fracpll_tbl[i];
		if (tbl->rate == pll_val) {
			uint64_t t_rate;

			if (ssc) {
				/* Configure Spread Spectrum Clocking to 0.5% spread, and 30kHz modFreq */
				(void) CLOCK_SourceSetSsc(CLOCK_SRC_DRAMPLL_VCO, 5U, 30000U, 1U);
			}
			(void) CLOCK_SourceSetRate(CLOCK_SRC_DRAMPLL_VCO, tbl->vco, CLOCK_ROUND_RULE_CLOSEST);
			(void) CLOCK_SourceSetRate(CLOCK_SRC_DRAMPLL, tbl->rate, CLOCK_ROUND_RULE_CLOSEST);
			t_rate = CLOCK_SourceGetRate(CLOCK_SRC_DRAMPLL);
			if (t_rate != tbl->rate) {
				printf("Clock rate req %lld but got %lld\n", tbl->rate, t_rate);
			}
			(void) CLOCK_SourceSetEnable(CLOCK_SRC_DRAMPLL_VCO, true);
			(void) CLOCK_SourceSetEnable(CLOCK_SRC_DRAMPLL, true);
			return;
		}
	}

	printf("Failed to set dram pll %llu\n", pll_val);
}

void Dram_Disable_Bypass(void)
{
	/* Set DRAM APB to 133Mhz */
	(void) CCM_RootSetDiv(CLOCK_ROOT_DRAMAPB, 3U);
	(void) CCM_RootSetParent(CLOCK_ROOT_DRAMAPB, CLOCK_SRC_SYSPLL1_PFD1_DIV2);
	(void) CCM_RootSetEnable(CLOCK_ROOT_DRAMAPB, 1);
	/* Switch from DRAM  clock root from CCM to PLL */
	(void) CCM_GprValSet(2, CCM_GPR_SHARED2_DRAM_PLL_BYPASS_MASK, 0);
}

void Dram_Enable_Bypass(uint64_t clk_val)
{
	printf("Not support dram bypass enable\n");
}
