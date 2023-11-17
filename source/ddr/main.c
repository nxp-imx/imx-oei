/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */
#include "ddr.h"
#include <asm/arch/clock.h>
#include <time.h>
#include "oei.h"
#include "debug.h"
#include "lpuart.h"
#include "pinmux.h"
#include "build_info.h"

#ifdef  DDR_MEM_TEST
#define DDR_MEM_BASE	0x80000000
#define SIZE_1G		0x40000000
static u32 mem_test(ulong addr, u32 val, u32 index, u32 len)
{
	u32 read_data, fail = 0, i, j;
	ulong dest;

	for (i=index, j=val; i<len; i++, j++) {
		dest = addr + 0x4*i;
		W32(dest, j);
	}

	for (i=index, j=val; i<len; i++, j++) {
		dest = addr + 0x4*i;
		R32(dest, read_data);
		if (read_data != j)
			fail = fail+1;
	}

	return fail;
}
#endif

uint32_t __attribute__((section(".entry"))) oei_entry(void)
{
	int ret;
#ifdef DDR_MEM_TEST
	int fail = 0;
#endif
	if (!timer_is_enabled())
		timer_enable();

	clock_init();
	pinmux_config();
	lpuart32_serial_init();

#ifdef	CONFIG_DDR_QBOOT
	printf("\n\n** DDR OEI: QuickBoot, commit: %08x **\n", OEI_COMMIT);
#else
	printf("\n\n** DDR OEI: Training, commit: %08x **\n", OEI_COMMIT);
#endif

	ret = ddr_init(&dram_timing);

#ifdef  DDR_MEM_TEST
	if (ret == 0) {
		fail = fail + mem_test(DDR_MEM_BASE, 0xfabeface, 0, 10);
		fail = fail + mem_test(DDR_MEM_BASE, 0xdeadbeef, 10, 0x100);

		fail = fail + mem_test(DDR_MEM_BASE + SIZE_1G, 0x98760000, 0, 10);
		fail = fail + mem_test(DDR_MEM_BASE + SIZE_1G, 0xabcd0000, 10, 0x100);
		if (fail)
			printf("** DDR OEI: memtest fails: %u **\n", fail);
		else
			printf("** DDR OEI: memtest pass! **\n");
	}
#endif
	printf("** DDR OEI: done, err=%d **\n", ret);

	return (ret == 0 ? OEI_SUCCESS_FREE_MEM : OEI_FAIL);
}
