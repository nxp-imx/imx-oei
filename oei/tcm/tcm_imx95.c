// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright 2023-2024 NXP
 */
#include "stdbool.h"
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


/**
 * Checks and powers up M7MIX.
 *
 * CM33/CA55 bootrom powers up M7 mix when container image
 * includes M7 firmware to be loaded in M7 TCM. In such case
 * M7 TCM is zeroed, but M7MIX power must remain on.
 *
 * @return true if M7MIX was powered-up by OEI,
 *         false if M7MIX was already powered-up by ROM
 */
static bool Power_Up_M7mix(void)
{
    if (*(volatile unsigned int *)SRC_M7MIX_SLICE_SW_CTRL != 0) {
        *(volatile unsigned int *)SRC_M7MIX_SLICE_SW_CTRL = 0U;
        while (*(volatile unsigned int *)SRC_M7MIX_SLICE_FUNC_STAT & 0x10);

        return true;
    }

    return false;
}

/**
 * Checks and powers down M7MIX
 */
static void Power_Down_M7mix(void)
{
    if (*(volatile unsigned int *)SRC_M7MIX_SLICE_SW_CTRL == 0) {
        *(volatile unsigned int *)SRC_M7MIX_SLICE_SW_CTRL |= SW_CTRL_PDN_SOFT_MASK;
        while (!*(volatile unsigned int *)SRC_M7MIX_SLICE_FUNC_STAT & 0x1);
    }
}

/**
 * Puts the M7 TCM in retention mode
 */
static void Tcm_Retention(void)
{
    *(volatile unsigned int *)SRC_M7MIX_SLICE_MEM_CTRL |= MEM_CTRL_LP_MODE_MASK;
}

/**
 * Initialise the M7 TCM using EDMA
 */
static int Tcm_Init_By_Dma(void)
{
    int ret = -1;
    uint32_t i = 0;
    bool pup;
    mem_tbl tcm_tbl[] =
    {
        {CM7_ITCM_START_ADDR, CM7_ITCM_END_ADDR},
        {CM7_DTCM_START_ADDR, CM7_DTCM_END_ADDR}
    };
    unsigned int transfer_size = 0;

    pup = Power_Up_M7mix();
    for (i = 0; i < sizeof(tcm_tbl) / sizeof(mem_tbl); i++)
    {
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

    /* The M7MIX will be powered down if the M7MIX is powered up by OEI */
    if (pup)
    {
        Tcm_Retention();
        Power_Down_M7mix();
    }

    return ret;
}

/**
 * TCM init wrapper for tcm_init_by_dma
 */
int Tcm_Init(void)
{
    return Tcm_Init_By_Dma();
}
