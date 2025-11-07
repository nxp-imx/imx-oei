/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2024 NXP
 */

#include <stdint.h>

#include "fsl_sysctr.h"

void timer_enable(void)
{
	SYSCTR_Init();
}

bool time_after(uint32_t us, uint32_t timeout)
{
	return SYSCTR_GetUsec64() + timeout > us;
}

bool timer_is_enabled(void)
{
	uint32_t cntcr = SYS_CTR_CONTROL->CNTCR;

	return (cntcr & SYS_CTR_CONTROL_CNTCR_EN_MASK) ? true : false;
}

uint32_t timer_get_us(void)
{
	return (uint32_t)SYSCTR_GetUsec64();
}

void udelay(uint32_t us)
{
	SYSCTR_TimeDelay(us);
}

void SystemTimeDelay(uint32_t usec)
{
	SYSCTR_TimeDelay(usec);
}
