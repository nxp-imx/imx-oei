/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */

#include "asm/types.h"

#ifndef ASM_IO
#define ASM_IO

#define BIT(x)		(1 << x)
#define BITS_PER_INT	32
#define GENMASK(h, l)	(((~0UL) << (l)) & (~0UL >> (BITS_PER_INT - 1 - (h))))

#define readw(addr)		(*(volatile unsigned short *)(addr))
#define readl(addr)		(*(volatile unsigned int   *)(addr))
#define writew(val, addr)	*((volatile unsigned short *)(addr)) = (val)
#define writel(val, addr)	*((volatile unsigned int   *)(addr)) = (val)
#define clrw(msk, addr)		*((volatile unsigned short *)(addr)) &= ~(msk)
#define clrl(msk, addr)		*((volatile unsigned int   *)(addr)) &= ~(msk)
#define setw(msk, addr)		*((volatile unsigned short *)(addr)) |= (msk)
#define setl(msk, addr)		*((volatile unsigned int   *)(addr)) |= (msk)

#define setbits_le32(addr, val)		setl(val, addr)
#define clrbits_le32(addr, val)		clrl(val, addr)
#define clrsetbits_le32(addr, clr, set)	do { clrl(clr, addr); setl(set, addr); } while(0)

#define W32(addr, value)	writel(value, addr)
#define R32(addr, value)	do { value = readl(addr); } while(0)

#endif
