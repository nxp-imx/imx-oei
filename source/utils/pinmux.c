/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */
#include <asm/arch/soc_memory_map.h>
#include <asm/io.h>
#include <asm/types.h>
#include "pinmux.h"

#define IOMUXC_PAD_PD_MASK        0x400
#define IOMUXC_PAD_PD_SHIFT       10
#define IOMUXC_PAD_PD(x)          (((u32)(((u32)(x)) << IOMUXC_PAD_PD_SHIFT)) & IOMUXC_PAD_PD_MASK)
#define IOMUXC_PAD_DSE_MASK       0x7E
#define IOMUXC_PAD_DSE_SHIFT      1
#define IOMUXC_PAD_DSE(x)         (((u32)(((u32)(x)) << IOMUXC_PAD_DSE_SHIFT)) & IOMUXC_PAD_DSE_MASK)
#define IOMUXC_PAD_MUX_MODE_MASK  0x7
#define IOMUXC_PAD_MUX_MODE_SHIFT 0U
#define IOMUXC_PAD_MUX_MODE(x)    (((u32)(((u32)(x)) << IOMUXC_PAD_MUX_MODE_SHIFT)) & IOMUXC_PAD_MUX_MODE_MASK)
#define IOMUXC_PAD_SION_MASK      0x10
#define IOMUXC_PAD_SION_SHIFT     4
#define IOMUXC_PAD_SION(x)        (((u32)(((u32)(x)) << IOMUXC_PAD_SION_SHIFT)) & IOMUXC_PAD_SION_MASK)

#define IOMUXC_BASE	IOMUXC_RBASE
#define IOR(x)		(IOMUXC_BASE + x)

static const struct pinmux_cfg {
	u32 muxReg;
	u32 muxMode;
	u32 inReg;
	u32 inDaisy;
	u32 inOnFld;
	u32 confReg;
	u32 confVal;
} lpuart_pinmux_cfg[] = {
#ifdef DEBUG
	{ IOR(0x1D0), 0, IOR(0), 0, 0, IOR(0x3D4), IOMUXC_PAD_PD(1) },
	{ IOR(0x1D4), 0, IOR(0), 0, 0, IOR(0x3D8), IOMUXC_PAD_DSE(0xf) },
#endif
	{ 0, 0, 0, 0, 0, 0, 0 },
};

void pinmux_config(void)
{
	const struct pinmux_cfg *cfg;
	u32 muxVal;

	for (cfg = lpuart_pinmux_cfg; cfg->muxReg != 0; cfg++) {
		muxVal = IOMUXC_PAD_MUX_MODE(cfg->muxMode) | IOMUXC_PAD_SION(cfg->inOnFld);
		writel(muxVal, cfg->muxReg);
		writel(cfg->inDaisy, cfg->inReg);
		writel(cfg->confVal, cfg->confReg);
	}
}
