/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2022 NXP
 */

#ifndef __CLOCK_IMX9__
#define __CLOCK_IMX9__

#include "asm/types.h"

#define MHZ(x)	((x) * 1000000UL)

enum ccm_clk_src {
#if defined(CONFIG_IMX95)
	EXT_CLK,
	OSC_32K_CLK,
	OSC_24M_CLK,
	FRO_CLK,
	SYS_PLL_PG,
	SYS_PLL_PFD0,
	SYS_PLL_PFD0_DIV2,
	SYS_PLL_PFD1,
	SYS_PLL_PFD1_DIV2,
	SYS_PLL_PFD2,
	SYS_PLL_PFD2_DIV2,
	AUDIO_PLL_CLK,
	AUDIO_PLL2_CLK,
	VIDEO_PLL_CLK,
	ARM_PLL_CLK,
	DRAM_PLL_CLK,
	HSIO_PLL_CLK,
	LDB_PLL_CLK,
	ARM_PLL_PFD0,
	ARM_PLL_PFD1,
	ARM_PLL_PFD2,
	ARM_PLL_PFD3,
	OSCPLL_END,
#endif
};

struct ccm_gpr {
	u32 gpr;
	u32 gpr_set;
	u32 gpr_clr;
	u32 gpr_tog;
	u32 authen;
	u32 authen_set;
	u32 authen_clr;
	u32 authen_tog;
};

struct ccm_lpcg_oscpll {
	u32 direct;
	u32 lpm_status0;
	u32 lpm_status1;
	u32 reserved0;
	u32 lpm0;
	u32 lpm1;
	u32 reserved1;
	u32 lpm_cur;
	u32 status0;
	u32 status1;
	u32 reserved2[2];
	u32 authen;
	u32 reserved3[3];
};

struct ccm_root {
	u32 control;
	u32 control_set;
	u32 control_clr;
	u32 control_tog;
	u32 reserved[4];
	u32 status0;
	u32 reserved1[3];
	u32 authen;
	u32 reserved2[19];
};

#if defined(CONFIG_IMX95)
struct ccm_reg {
	struct ccm_root clk_roots[128];		/* 0x0000 */
	u32 reserved_0[512];
	struct ccm_gpr clk_shared_gpr[8];	/* 0x4800 */
	u32 reserved_1[192];
	struct ccm_gpr clk_private_gpr[16];	/* 0x4c00 */
	u32 reserved_2[128];
	struct ccm_lpcg_oscpll clk_oscplls[32];	/* 0x5000 */
	u32 reserved_3[2560];
	struct ccm_lpcg_oscpll clk_lpcgs[256];	/* 0x8000 */
};
#endif

struct ana_pll_reg_elem {
	u32 reg;
	u32 reg_set;
	u32 reg_clr;
	u32 reg_tog;
};

struct ana_pll_dfs {
	struct ana_pll_reg_elem dfs_ctrl;
	struct ana_pll_reg_elem dfs_div;
};

struct ana_pll_reg {
	struct ana_pll_reg_elem ctrl;
	struct ana_pll_reg_elem ana_prg;
	struct ana_pll_reg_elem test;
	struct ana_pll_reg_elem ss; /* Spread spectrum */
	struct ana_pll_reg_elem num; /* numerator */
	struct ana_pll_reg_elem denom; /* demoninator */
	struct ana_pll_reg_elem div;
	struct ana_pll_dfs dfs[4];
	u32 pll_status;
	u32 dfs_status;
	u32 reserved[2];
};

#if defined(CONFIG_IMX95)
struct anatop_reg {
	u32 osc_ctrl;
	u32 osc_state;
	u32 reserved_0[510];
	u32 chip_version;
	u32 reserved_1[511];
	struct ana_pll_reg sys_pll;
	struct ana_pll_reg audio_pll;
	struct ana_pll_reg audio_pll2;
	struct ana_pll_reg video_pll;
	struct ana_pll_reg res[2];
	struct ana_pll_reg arm_pll;
	struct ana_pll_reg dram_pll;
};
#endif

#define PLL_CTRL_HW_CTRL_SEL BIT(16)
#define PLL_CTRL_CLKMUX_BYPASS BIT(2)
#define PLL_CTRL_CLKMUX_EN BIT(1)
#define PLL_CTRL_POWERUP BIT(0)

#define PLL_STATUS_PLL_LOCK BIT(0)
#define PLL_DFS_CTRL_ENABLE BIT(31)
#define PLL_DFS_CTRL_CLKOUT BIT(30)
#define PLL_DFS_CTRL_CLKOUT_DIV2 BIT(29)
#define PLL_DFS_CTRL_BYPASS BIT(23)

#define PLL_SS_EN BIT(15)

struct imx_fracpll_rate_table {
	u32 rate; /*khz*/
	u32 rdiv;
	u32 mfi;
	u32 odiv;
	u32 mfn;
	u32 mfd;
};

#define FRAC_PLL_RATE(_rate, _r, _m, _o, _n, _d)			\
	{							\
		.rate	=	(_rate),			\
		.rdiv	=	(_r),				\
		.mfi	=	(_m),				\
		.odiv	=	(_o),				\
		.mfn	=	(_n),				\
		.mfd	=	(_d),				\
	}

struct clk_root_map {
	u32 clk_root_id;
	u32 mux_type;
};

int clock_init(void);
void dram_pll_init(ulong pll_val);
void dram_enable_bypass(ulong clk_val);
void dram_disable_bypass(void);

#ifdef CONFIG_IMX95
int configure_fracpll(enum ccm_clk_src clksrc, u32 freq);
#endif
int ccm_clk_root_cfg(u32 clk_root_id, enum ccm_clk_src src, u32 div);
int ccm_shared_gpr_set(u32 gpr, u32 val);
#endif
