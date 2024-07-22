// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright 2018, 2023-2024 NXP
 */

#include <stddef.h>
#include <stdio.h>
#include "ddr.h"
#include "fsl_sysctr.h"
#include "time.h"

static void Ddr_Phy_Delay40(unsigned int drate)
{
#ifndef CONFIG_EMUL
    unsigned int udelays = 40 * 8;

    udelays /= drate;

    if (udelays == 0) { udelays = 1; }

    /* wait 40 DfiClks */
    SystemTimeDelay(udelays);
#endif
}

int Ddr_Cfg_Phy(struct dram_timing_info *dtiming)
{
    struct dram_fsp_msg *fsp_msg;
    unsigned int i;
    int ret;
#ifdef DEBUG
    uint64_t ts, te;
#endif

    /* initialize PHY configuration */
    /* config phy common reg */
    Ddr_Phy_Cfg_Set(dtiming->ddrphy_cfg, dtiming->ddrphy_cfg_num);

#ifdef DEBUG
    ts = SYSCTR_GetUsec64();
#endif

    if (!dtiming->skip_fw)
    {
        /** 3.2.4 Step D Load QuickBoot IMEM */
        phy_ops.ddr_pre_load_firmware(NULL, IMEM, DDRFW_TRAINING);
        phy_ops.ddr_do_load_firmware(IMEM);
    }

    /* load the frequency setpoint message block config */
    fsp_msg = dtiming->fsp_msg;
    for (i = 0; i < dtiming->fsp_msg_num; i++)
    {
        /* If NumPStates more than 2, StartPsloop "DMA reload" prepare no action required */
        /* config phy pstate reg */
        Ddr_Phy_Cfg_Set(fsp_msg->fsp_phy_cfg, fsp_msg->fsp_phy_cfg_num);

        /* If NumPStates more than 2, stopPsloop "DMA reload" prepare
         * action is included in end of fsp_phy_cfg  */

        if (dtiming->prog_csr)
        {
            /* prog_csr for one time */
            if (i == 0)
            {
                Ddr_Phy_Cfg_Set(dtiming->ddrphy_prog_csr, dtiming->ddrphy_prog_csr_num);
            }

            /* prog_csr ps */
            Ddr_Phy_Cfg_Set(fsp_msg->fsp_phy_prog_csr_ps_cfg, fsp_msg->fsp_phy_prog_csr_ps_cfg_num);
            /* If NumPStates more than 2, stopPsloop "DMA reload" prepare
             * action is included in end of fsp_phy_prog_csr_ps_cfg  */
        }

        if (i == 0 && !dtiming->skip_fw)
        {
            phy_ops.ddr_post_load_firmware(IMEM);
        }

        if (!dtiming->skip_fw)
        {
            /* set dram PHY input clocks to desired frequency */
            Ddr_Phy_Init_Set_Dfi_Clk(fsp_msg->drate);

            /* load the dram training firmware image */
            phy_ops.ddr_pre_load_firmware(fsp_msg, DMEM, DDRFW_TRAINING);
            phy_ops.ddr_do_load_firmware(DMEM);
            phy_ops.ddr_post_load_firmware(DMEM);
#ifdef DEBUG
            te = SYSCTR_GetUsec64() - ts;
            if (i == 0)
            {
                printf("DDR OEI: IMEM + DMEM load in %u us\n", (uint32_t)te);
            }
            else
            {
                printf("DDR OEI: DMEM load in %u us\n", (uint32_t)te);
            }
            ts = SYSCTR_GetUsec64();
#endif
            /*
             * -------------------- excute the firmware --------------------
             * Running the firmware is a simply process to taking the
             * PMU out of reset and stall, then the firwmare will be run
             * 1. reset the PMU;
             * 2. begin the excution;
             * 3. wait for the training done;
             * 4. read the message block result.
             * -------------------------------------------------------------
             */
            Dwc_Ddrphy_Apb_Wr(0xd0000, 0x1); /* CSR bus: MCU/PIE/DMA++,TDR/APB-- */
            Dwc_Ddrphy_Apb_Wr(0xd0099, 0x9);
            Dwc_Ddrphy_Apb_Wr(0xd0099, 0x1);
            Dwc_Ddrphy_Apb_Wr(0xd0099, 0x0);

            /* Wait for the training firmware to complete */
            ret = Wait_Ddr_Phy_Training_Complete();
            if (ret) { return ret; }

            /* Halt the microcontroller. */
            Dwc_Ddrphy_Apb_Wr(0xd0099, 0x1);
            Ddr_Phy_Delay40(fsp_msg->drate);
            Dwc_Ddrphy_Apb_Wr(0xd0000, 0x0); /* CSR bus: MCU--,PIE/DMA/TDR/APB++ */
#ifdef DEBUG
            te = SYSCTR_GetUsec64() - ts;
            printf("DDR OEI: TRAINING complete in %u us\n", (uint32_t)te);
            ts = SYSCTR_GetUsec64();
#endif

            /* Read the Message Block results */
            Ddr_Phy_Init_Read_Msg_Block();
        }

        /* If NumPStates more than 2, resumePsloop "DMA reload" prepare resume, no action */
        /* config PIE pstate reg */
        Ddr_Phy_Cfg_Set(fsp_msg->fsp_phy_pie_cfg, fsp_msg->fsp_phy_pie_cfg_num);
        /* If NumPStates more than 2, "DMA reload" prepare end, prepare Xlat Table for this PState */
        /* action is included in end of fsp_phy_pie_cfg */
        fsp_msg++;
    }

    /* Load PHY Init Engine Image */
    Ddr_Phy_Cfg_Set(dtiming->ddrphy_pie, dtiming->ddrphy_pie_num);

    Dwc_Ddrphy_Apb_Wr(0xd0000, 0x1); /* CSR bus: MCU/PIE/DMA++,TDR/APB-- */

    return 0;
}
