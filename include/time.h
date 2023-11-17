/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */
#ifndef __TIME_H
#define __TIME_H

#include <asm/types.h>

bool timer_is_enabled(void);
void timer_enable(void);
uint64_t timer_tick(void);
uint32_t timer_get_us(void);
bool time_after(uint32_t us, uint32_t timeout);
void udelay(uint32_t us);

#define mdelay(x)	udelay(1000 * x)

#endif
