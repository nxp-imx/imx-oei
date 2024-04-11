// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2023-2024 NXP
 */
#include "debug.h"
#include "edma.h"
#include "soc_edma.h"

/**
 * struct mem_tbl - defined a memory block with start and end address
 *
 * @start_addr - start address of the memory block
 * @end_addr   - end address of the memory block
 */
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

void power_down_m7mix(void)
{
	/* power down m7 mix */
	if (*(volatile unsigned int *)SRC_M7MIX_SLICE_SW_CTRL == 0) {
		*(volatile unsigned int *)SRC_M7MIX_SLICE_SW_CTRL |= SW_CTRL_PDN_SOFT_MASK;
		while (!*(volatile unsigned int *)SRC_M7MIX_SLICE_FUNC_STAT & 0x1);
	}
}

void tcm_retention(void)
{
	*(volatile unsigned int *)SRC_M7MIX_SLICE_MEM_CTRL |= MEM_CTRL_LP_MODE_MASK;
}

static int tcm_init_by_dma(void)
{
	int ret = -1;
	u32 i = 0;
	mem_tbl tcm_tbl[] = {
					{CM7_ITCM_START_ADDR, CM7_ITCM_END_ADDR},
					{CM7_DTCM_START_ADDR, CM7_DTCM_END_ADDR}
				};
	unsigned int transfer_size = 0;

	power_up_m7mix();
	for (i = 0; i < sizeof(tcm_tbl) / sizeof(mem_tbl); i++){
		transfer_size = (tcm_tbl[i].end_addr - tcm_tbl[i].start_addr) + 1;
		edma_ops.en_master_rep(EDMA2_BASE_ADDR, EDMA_CH0);
		edma_ops.set_tbytes(EDMA2_BASE_ADDR, EDMA_CH0, 128, 128);
		ret = edma_ops.configure(EDMA2_BASE_ADDR, EDMA_CH0 , OCRAM_START_ADDR, 128, tcm_tbl[i].start_addr, 128, transfer_size, 1);
		if (ret != 0)
		{
			goto exit;
		}
		edma_ops.write_only(EDMA2_BASE_ADDR, EDMA_CH0);
		edma_ops.start_transfer(EDMA2_BASE_ADDR, EDMA_CH0);
		ret = edma_ops.check_edma(EDMA2_BASE_ADDR, EDMA_CH0);
		if (ret != 0)
		{
			goto exit;
		}
		edma_ops.wait_transfer(EDMA2_BASE_ADDR, EDMA_CH0);
	}

exit:
	edma_ops.clr_tcd(EDMA2_BASE_ADDR, EDMA_CH0);
	tcm_retention();
	power_down_m7mix();

	return ret;
}

int tcm_init(void)
{
	return tcm_init_by_dma();
}
