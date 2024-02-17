/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */
#include <asm/io.h>
#include <asm/types.h>
#include <asm/arch/soc_memory_map.h>
#include <asm/arch/syscounter.h>
#include <time.h>

/* generic timer come from system counter which is running on 24MHz */
#define TICKS_TO_USEC(ticks)	(uint32_t)(((uint32_t)ticks) / 24UL)
#define USEC_TO_TICKS(usec)	((uint64_t)(usec) * 24UL)

#define SYSCNT_CTRL_BASE_ADDR	SYSCTRL_CTL_RBASE

void timer_enable(void)
{
	struct sctr_regs *sctr = (struct sctr_regs *)SYSCNT_CTRL_BASE_ADDR;

	clrsetbits_le32(&sctr->cntcr, SC_CNTCR_FREQ0 | SC_CNTCR_FREQ1,
			SC_CNTCR_FREQ0 | SC_CNTCR_ENABLE | SC_CNTCR_HDBG);
}

bool timer_is_enabled(void)
{
	struct sctr_regs *sctr = (struct sctr_regs *)SYSCNT_CTRL_BASE_ADDR;

	return (sctr->cntcr & BIT(SC_CNTCR_ENABLE)) ? true : false;
}

uint64_t timer_tick(void)
{
	struct sctr_regs *sctr = (struct sctr_regs *)SYSCNT_CTRL_BASE_ADDR;
	uint32_t ls, ms, ms2;
	uint64_t ticks;

	/* Do consecutive reads to guard against ripple */
	do {
		ms  = sctr->cntcv1;
		ls  = sctr->cntcv0;
		ms2 = sctr->cntcv1;
	} while (ms != ms2);

	ticks = ms;
	ticks = (ticks << 32U) | ls;

	return ticks;
}

uint32_t timer_get_us(void)
{
	return TICKS_TO_USEC(timer_tick());
}

bool time_after(uint32_t us, uint32_t timeout)
{
	return (timer_get_us() + timeout > us);
}

void udelay(uint32_t us)
{
	uint64_t startTicks = timer_tick();
	uint64_t delayTicks = USEC_TO_TICKS(us);

	while ((timer_tick() - startTicks) < delayTicks)
	{
		;
	}
}
