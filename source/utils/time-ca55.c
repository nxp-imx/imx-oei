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
#define TICKS_TO_USEC(ticks)	((uint32_t)((uint64_t)(ticks) / 24UL))
#define USEC_TO_TICKS(usec)	((uint64_t)(usec) * 24UL)
#define CNTP_CTL_EL0_ENABLE_MSK (0x01ULL << 0)

#define SYSCNT_CTRL_BASE_ADDR   SYSCTRL_CTL_NS_RBASE 

void timer_enable(void)
{
	struct sctr_regs *sctr = (struct sctr_regs *)SYSCNT_CTRL_BASE_ADDR;
	unsigned long freq = readl(&sctr->cntfid0);

	// Update with accurate clock frequency
	asm volatile("msr cntfrq_el0, %0" : : "r" (freq) : "memory");

	clrsetbits_le32(&sctr->cntcr, SC_CNTCR_FREQ0 | SC_CNTCR_FREQ1,
			SC_CNTCR_FREQ0 | SC_CNTCR_ENABLE | SC_CNTCR_HDBG);
}

bool timer_is_enabled(void)
{
	uint64_t cntp_ctrl_el0 = 0ULL;

	asm volatile ("mrs %0, CNTP_CTL_EL0":"=r" (cntp_ctrl_el0));

	return CNTP_CTL_EL0_ENABLE_MSK == (cntp_ctrl_el0 & CNTP_CTL_EL0_ENABLE_MSK);
}

uint64_t timer_tick(void)
{
	uint64_t retValue;

	asm volatile ("mrs %0, cntpct_el0":"=r" (retValue));

	return retValue;
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
