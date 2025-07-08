/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2023,2024 NXP
 */
#include <stdint.h>
#include <stdio.h>

#include "clock.h"
#include "oei.h"
#include "board.h"
#include "rom_api.h"
#include "soc_ddr.h"
#include "time.h"
#include "build_info.h"

#include "fsl_sysctr.h"

#ifdef  DDR_MEM_TEST
#define DDR_MEM_BASE    0x80000000
#define SIZE_512M       0x20000000
static uint32_t mem_test(uint32_t addr, uint32_t val, uint32_t index, uint32_t len)
{
    uint32_t read_data, fail = 0, i, j;
    uint32_t dest;

    for (i=index, j=val; i<len; i++, j++)
    {
        dest = addr + 0x4*i;
        Write32(dest, j);
    }

    for (i=index, j=val; i<len; i++, j++)
    {
        dest = addr + 0x4*i;
        read_data = Read32(dest);
        if (read_data != j)
            fail = fail+1;
    }

    return fail;
}
#endif

/**
 * Load training data needed for quick boot flow from container
 *
 * @param offset    training data offset within the container
 *            = 0 if ROM has no support for dummy entry, non-zero otherwise
 *
 * @return        ROM_API_OKAY if data of expected size was loaded
 *            ROM_API_ERR_INV_PAR otherwise
 */
static uint32_t Ddr_Load_Training_Data(uint32_t offset)
{
    void *dest = (void *)QB_STATE_LOAD_ADDR;
    uint32_t size, off = offset;
    uint32_t lsize;

#if (defined(DDR_NO_PHY))
    /** No need to load training data */
    return ROM_API_OKAY;
#endif

    if (!off && Get_Training_Data_Offset(&off) != ROM_API_OKAY)
    {
        return ROM_API_ERR_INV_PAR;
    }

    /**
     * For stream devices such as USB the stream must point
     * to the following image body when OEI returns control to
     * ROM, therefore the loaded data size must be the entire
     * space allocated for DDR training data.
     *
     * For all other devices the optimal size of loaded data
     * is the size of ddrphy_qb_state structure.
     */
    lsize = Rom_Api_Boot_Dev_Is_Stream() ? QB_STATE_STORAGE_SIZE : sizeof(ddrphy_qb_state);
    size = Rom_Api_Read(off, lsize, dest);

    return (size == lsize ? ROM_API_OKAY : ROM_API_ERR_INV_PAR);
}

int oei_main(uint32_t argc, uint32_t *argv)
{
    int ret = 0;
#ifdef DDR_MEM_TEST
    int fail = 0;
#endif
    uint32_t offset = 0, id = 0;

    if (!timer_is_enabled())
        timer_enable();

    Clock_Init();
#ifdef DEBUG
    BOARD_InitPins();
    BOARD_InitDebugConsole();
#endif

    printf("\nDDR OEI: (Build %lu, Commit %08lx, %s %s)\n\n",
        OEI_BUILD, OEI_COMMIT, OEI_DATE, OEI_TIME);

    printf("DDR OEI: SOC %s, Board %s\n", OEI_DEVICES, OEI_BOARD);
    /**
     * Pass offset = 0 for iMX95 A0 since there is no ROM support
     * for training data dummy entry
     */
    if (argc >= 3 && argv[0] == OEI_ARG_TYPE_IN_IMG_OFF)
    {
        offset = argv[1];
        id = argv[2];
    }

    ret = Ddr_Load_Training_Data(offset);
    if (ret != ROM_API_OKAY)
    {
        return OEI_FAIL;
    }

    ret = Ddrc_Init(&dram_timing, id);

#ifdef  DDR_MEM_TEST
    if (ret == 0)
    {
        fail = fail + mem_test(DDR_MEM_BASE, 0xfabeface, 0, 10);
        fail = fail + mem_test(DDR_MEM_BASE, 0xdeadbeef, 10, 0x100);

        fail = fail + mem_test(DDR_MEM_BASE + SIZE_512M, 0x98760000, 0, 10);
        fail = fail + mem_test(DDR_MEM_BASE + SIZE_512M, 0xabcd0000, 10, 0x100);
        if (fail)
        {
            printf("DDR OEI: memtest fails: %u\n", fail);
        }
        else
        {
            printf("DDR OEI: memtest pass!\n");
        }
    }
#endif
    printf("DDR OEI: done, err = 0x%x\n", ret);

    return ret;
}
