/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023-2024 NXP
 */
#include <asm/arch/clock.h>
#include <time.h>
#include "oei.h"
#include "debug.h"
#include "lpuart.h"
#include "pinmux.h"

extern int tcm_init(void);

uint32_t __attribute__((section(".entry"))) oei_entry(void)
{
	int ret = 0;
#ifdef DEBUG
	unsigned int ts, te;
#endif

	if (!timer_is_enabled())
		timer_enable();

	clock_init();
	pinmux_config();
	lpuart32_serial_init();

	printf("\n\n** TCM OEI: start **\n");
#ifdef DEBUG
	ts = timer_get_us();
#endif
	ret = tcm_init();

#ifdef DEBUG
	te = timer_get_us() - ts;
	printf("** TCM INIT: %u us **\n", te);
#endif
	printf("\n\n** TCM OEI: end ret = 0x%x **\n", ret);

	return (ret == 0 ? OEI_SUCCESS_FREE_MEM : OEI_FAIL);
}
