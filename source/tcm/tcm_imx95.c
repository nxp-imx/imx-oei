// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2023-2024 NXP
 */
#include <asm/arch/ccm_regs.h>
#include <asm/arch/clock.h>
#include <asm/types.h>
#include "edma.h"

typedef struct
{
	unsigned int start_addr;
	unsigned int end_addr;
} mem_tbl;

void power_up_m7mix(void)
{
	/* Do we need power up m7 mix? actually cm33 bootrom/ca55 bootrom will power up m7 mix when contaimer image include m7 firmware */
	if (*(volatile unsigned int *)SRC_M7MIX_SLICE_SW_CTRL != 0) {
		*(volatile unsigned int *)SRC_M7MIX_SLICE_SW_CTRL = 0U;
		while (*(volatile unsigned int *)SRC_M7MIX_SLICE_FUNC_STAT & 0x10);
	}
}

static int tcm_init_by_dma(void)
{
	int ret = -1;
/*	unsigned int itcm_size = CM7_ITCM_END_ADDR -  CM7_ITCM_START_ADDR + 1;
	unsigned int dtcm_size = CM7_DTCM_END_ADDR -  CM7_DTCM_START_ADDR + 1; */
	u32 i = 0;
	u32 j = 0;
	mem_tbl tcm_tbl[] = {
					{CM7_ITCM_START_ADDR, CM7_ITCM_END_ADDR},
					{CM7_DTCM_START_ADDR, CM7_DTCM_END_ADDR}
				};
	unsigned int transfer_size = 0;

	power_up_m7mix();
	for (i = 0; i < sizeof(tcm_tbl) / sizeof(mem_tbl); i++)
	{
		for (j = tcm_tbl[i].start_addr; ;)
		{
			if (j + OCRAM_SOURCE_DATA_SIZE <=  tcm_tbl[i].end_addr)
			{
				transfer_size = OCRAM_SOURCE_DATA_SIZE;
			}
			else
			{
				transfer_size = tcm_tbl[i].end_addr - j + 1;
			}
			edma_ops.en_master_rep(EDMA2_BASE_ADDR, EDMA_CH0);
			ret = edma_ops.configure(EDMA2_BASE_ADDR, EDMA_CH0 ,OCRAM_START_ADDR, 8, j, 8, transfer_size, 2);
			if (ret != 0)
			{
				goto exit;
			}
			edma_ops.set_tbytes(EDMA2_BASE_ADDR, EDMA_CH0, 8, 8);
			edma_ops.start_transfer(EDMA2_BASE_ADDR, EDMA_CH0);
			ret = edma_ops.wait_transfer(EDMA2_BASE_ADDR, EDMA_CH0);
			if (ret != 0)
			{
				goto exit;
			}
			edma_ops.clr_tcd(EDMA2_BASE_ADDR, EDMA_CH0);
			j += transfer_size;
			if ( j == tcm_tbl[i].end_addr + 1)
			{
				break;
			}
		}
	}

exit:
	edma_ops.clr_tcd(EDMA2_BASE_ADDR, EDMA_CH0);
	
	return ret;
}

int tcm_init(void)
{
	return tcm_init_by_dma();
}
