/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 */

#ifndef _ASM_ARCH_SYSTEM_COUNTER_H
#define _ASM_ARCH_SYSTEM_COUNTER_H

/* System Counter */
struct sctr_regs {
	volatile u32 cntcr;
	volatile u32 cntsr;
	volatile u32 cntcv0;
	volatile u32 cntcv1;
	u32 resv1[4];
	volatile u32 cntfid0;
	volatile u32 cntfid1;
	volatile u32 cntfid2;
	u32 resv2[1001];
	volatile u32 counterid[1];
};

#define SC_CNTCR_ENABLE		(1 << 0)
#define SC_CNTCR_HDBG		(1 << 1)
#define SC_CNTCR_FREQ0		(1 << 8)
#define SC_CNTCR_FREQ1		(1 << 9)

#endif
