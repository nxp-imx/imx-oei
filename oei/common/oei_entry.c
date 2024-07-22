/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2024 NXP
 */
#include <stdint.h>
#include "board.h"
#include "oei.h"

extern char __START_BSS[], __END_BSS[];
extern char __StackTop[], __StackLimit[];

/**
 * OEI entry is the interface between SYSROM and some specific OEI implementation.
 *
 * Its purpose is to handle common OEI functions such as BSS and stack management,
 * and ensure proper values are returned to ROM.
 */
#if defined(CONFIG_DUMMY_TRAIN_DATA_SUPPORT)
uint32_t __attribute__((section(".entry"))) oei_entry(uint32_t *args)
#else
uint32_t __attribute__((section(".entry"))) oei_entry(void)
#endif
{
	int ret = 0;
	uint32_t msp, msplim;

	memset(__START_BSS, 0, (uint32_t)__END_BSS - (uint32_t)__START_BSS);
	memset(__StackLimit, 0, (uint32_t)__StackTop - (uint32_t)__StackLimit);

	/** Save MSP and MSPLIM */
	msp    = __get_MSP();
	msplim = __get_MSPLIM();

	/** Switch to OEI stack */
	__set_MSP((uint32_t)__StackTop);
	__set_MSPLIM((uint32_t)__StackLimit);

#if defined(CONFIG_DUMMY_TRAIN_DATA_SUPPORT)
	ret = oei_main(OEI_ARG_LEN_IN_WORD, args);
#else
	ret = oei_main(0, 0);
#endif

	/** Restore SYSROM stack */
	__set_MSP(msp);
	__set_MSPLIM(msplim);

	return (ret == 0 ? OEI_SUCCESS_FREE_MEM : OEI_FAIL);
}
