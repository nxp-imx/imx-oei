/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2023-2024 NXP
 */
#include <stdio.h>
#include <time.h>
#include "clock.h"
#include "fsl_sysctr.h"
#include "oei.h"
#include "board.h"

extern int Tcm_Init(void);

int oei_main(uint32_t argc, uint32_t *argv)
{
	int ret = 0;
#ifdef DEBUG
	uint64_t ts, te;
#endif

	if (!timer_is_enabled())
		timer_enable();

	Clock_Init();
	BOARD_InitPins();
	BOARD_InitDebugConsole();

	printf("\n\nTCM OEI: start\n");
#ifdef DEBUG
        ts = SYSCTR_GetUsec64();
#endif
	ret = Tcm_Init();

#ifdef DEBUG
	te = SYSCTR_GetUsec64() - ts;
	printf("TCM INIT: %u us\n", (uint32_t)te);
#endif
	printf("\n\nTCM OEI: end ret = 0x%x\n", ret);

	return ret;
}
