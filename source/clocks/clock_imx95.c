// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2022-2023 NXP
 */

#include <asm/arch/ccm_regs.h>
#include <asm/arch/clock.h>
#include <asm/arch/imx-regs.h>
#include <asm/io.h>
#include <errno.h>

struct imx95_ccm_clk_root_cfg {
	u32 clk_root_id;
	enum ccm_clk_src clk_src_id;
	u32 div;
};

static struct imx95_ccm_clk_root_cfg clk_root_cfgs[] = {
	{ DRAM_APB_CLK_ROOT, SYS_PLL_PFD1_DIV2, 3 }, /* 400MHz / 3 = 133.(3) MHz */
#ifdef DEBUG
#if (DEBUG_UART_INSTANCE == 1)
	{ LPUART1_CLK_ROOT, OSC_24M_CLK, 1}, /* 24MHz */
#elif (DEBUG_UART_INSTANCE == 2)
	{ LPUART2_CLK_ROOT, OSC_24M_CLK, 1}, /* 24MHz */
#endif
#endif
};

int clock_init(void)
{
	unsigned int i = 0;
	struct imx95_ccm_clk_root_cfg *cfg = NULL;

	for (i = 0; i < ARRAY_SIZE(clk_root_cfgs); i++) {
		cfg = &clk_root_cfgs[i];
		ccm_clk_root_cfg(cfg->clk_root_id, cfg->clk_src_id, cfg->div);
	}

	return 0;
}
