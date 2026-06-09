/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2025 NXP
 */
#include <stdio.h>
#include "board.h"
#include "fsl_ele.h"
#include "oei.h"

#define RNG_CHECK_CNT       1000U
#define RNG_DELAY_US        5U

static int rngRet;

void prepare_iee(void)
{
    /** Start the random number generator */
    rngRet = ELE_StartRng();
}

#define SIZE_64K    0x10000U
#define ALIGN_SIZE  SIZE_64K

int enable_iee(void)
{
    int ret = -1;

    /** Check if random number generator started ok */
    if (rngRet == ELE_SUCCESS_IND)
    {
        uint32_t cnt = 0U;
        ele_trng_state_t trng;
        ele_rnd_ctin_state_t rctin;
        int ieeRet;

        /** Wait random number generator to enter the state expected by IEE */
        do
        {
            ieeRet = ELE_GetTRngState(&trng, &rctin);
            if (trng == ELE_TRNG_ENTR_VLD && rctin == ELE_RND_CTIN_SUCC)
            {
                break;
            }
            SystemTimeDelay(RNG_DELAY_US);
            cnt++;
        } while ((ieeRet == ELE_SUCCESS_IND) && (cnt <= RNG_CHECK_CNT));

        if (cnt > RNG_CHECK_CNT)
        {
            printf("DDR OEI: IEE: RNG didn't started in %u us\n ", (RNG_CHECK_CNT * RNG_DELAY_US));
        }
        else if ((ieeRet == ELE_SUCCESS_IND) && (trng == ELE_TRNG_ENTR_VLD) &&
                 (rctin == ELE_RND_CTIN_SUCC))
        {
            ele_iee_inst_reg_state_t state = ELE_IEE_INST_REG_SUCCS;
            uint64_t startAddr;
            uint64_t endAddr;

            /**
             * Align down to 64KB boundary the start address so that
             * the required memory region is fully covered
             */
            startAddr = ALIGN_DOWN(DDR_IEE_REG_START, ALIGN_SIZE);

            /**
             * Align up to 64KB boundary the end address so that
             * the required memory region is fully covered.
             *
             * Substract 1 so that the address is the offset of
             * the latest byte in the encrypted region.
             */
            endAddr = ALIGN(DDR_IEE_REG_END, ALIGN_SIZE) - 1U;

            ieeRet = ELE_IeeInstallRegion(startAddr, endAddr, 0U, false, &state);

            if (ieeRet != ELE_SUCCESS_IND)
            {
                printf("DDR OEI: IEE enable failed: error=%d\n", ieeRet);
            }
            else if (state != ELE_IEE_INST_REG_SUCCS)
            {
                printf("DDR OEI: IEE enable failed: state=%04x\n", state);
            }
            else
            {
                printf("DDR OEI: IEE enabled on 0x%02x%08x..0x%02x%08x\n",
                       UINT64_H(startAddr), UINT64_L(startAddr),
                       UINT64_H(endAddr),   UINT64_L(endAddr));
                ret = 0;
            }
        }
    }
    else
    {
        printf("DDR OEI: RNG start failed: %d\n", rngRet);
    }

    return ret;
}
