// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright 2022-2024 NXP
 */
#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include "oei.h"
#include "soc_ddr.h"

/*--------------------------------------------------------------------------*/
/* DDR Controller Idle status                                               */
/*--------------------------------------------------------------------------*/
static bool Check_DdrcIdle(uint32_t flag)
{
    while ((DDRC_CTRL->DDRDSR_2 & flag) != flag) {};

    /* Return status */
    return true;
}

/*--------------------------------------------------------------------------*/
/* Check status of DFI Init                                                 */
/*--------------------------------------------------------------------------*/
static bool Check_Dfi_Init_Complete(void)
{
    do
    {
        if ((Read32(&DDRC_CTRL->DDRDSR_2) &
                DDRC_DDRDSR_2_PHY_INIT_CMPLT_MASK) != 0U)
        {
            break;
        }
    } while (true);

    DDRC->DDRDSR_2 |= DDRC_DDRDSR_2_PHY_INIT_CMPLT_MASK;

    /* Return status */
    return true;
}

int Ddrc_Config(struct dram_timing_info *dtiming, uint32_t fsp_id)
{
    uint32_t i = 0, num = dtiming->ddrc_cfg_num;
    struct ddrc_cfg_param *ddrc_cfg;

    ddrc_cfg = dtiming->ddrc_cfg;

    /* common DDRC config */
    for (i = 0; i < num; i++, ddrc_cfg++)
    {
        Write32(ddrc_cfg->reg, ddrc_cfg->val);
    }

    if (dtiming->fsp_cfg == NULL || fsp_id >= dtiming->fsp_cfg_num)
    {
        return -EINVAL;
    }

    /**
     * FSP specific DDRC config
     *
     * Pstate DDRC specific configuration
     * index must be correlated with the index of
     * the corresponding drate in fsp_table.
     */
    for (i = 0; i < dtiming->fsp_msg_num; i++)
    {
        if (dtiming->fsp_table[i] == dtiming->fsp_msg[fsp_id].drate) { break; }
    }

    if (i < dtiming->fsp_cfg_num)
    {
        ddrc_cfg = dtiming->fsp_cfg[i].ddrc_cfg;
        num      = dtiming->fsp_cfg[i].ddrc_cfg_num;

        for (i = 0; i < num; i++, ddrc_cfg++)
        {
            Write32(ddrc_cfg->reg, ddrc_cfg->val);
        }
    }

    return 0;
}

static void Ddr_PhyColdReset(void)
{
    /**
     * BIT(8) => src_ipc_ddrphy_presetn, PRESETN
     * BIT(9) => src_ipc_ddrphy_reset_n, RESET_N
     *
     * DfiClk is 790MHz in waveform ~= 800MHz ?
     * APBCLK is 200MHz in waveform
     */

    /**
     * for some reason BIT(8)=1 at this point, so PRESETN go LOW after power-up
     * Ensure PRESETN go HIGH after power-up
     * Ensure RESET_N go LOW  after power-up
     */
    SRC_XSPR_DDRMIX->IRST_REQ_CTRL &= ~SRC_XSPR_IRST_REQ_CTRL_RSTR_1_IRST_0_MASK;
    SRC_XSPR_DDRMIX->IRST_REQ_CTRL |= SRC_XSPR_IRST_REQ_CTRL_RSTR_1_IRST_1_MASK;

    /* Disable IPs isolation in DDRMIX */
    SRC_XSPR_DDRMIX->SLICE_SW_CTRL &= ~0x7F000000;
    /* Power-up DDRMIX */
    SRC_XSPR_DDRMIX->SLICE_SW_CTRL &= ~SRC_XSPR_SLICE_SW_CTRL_PDN_SOFT_MASK;
    /* Wait resets to be released => BIT(2) being set */
    while (!(SRC_XSPR_DDRMIX->FUNC_STAT & SRC_XSPR_FUNC_STAT_RST_STAT_MASK));
    /* sleep for a while, just random */
    SystemTimeDelay(8);
    /* set PRESETN LOW after power-up */
    SRC_XSPR_DDRMIX->IRST_REQ_CTRL |= SRC_XSPR_IRST_REQ_CTRL_RSTR_1_IRST_0_MASK;
    /* The delay below must be at least 16 APBCLK
     * APBCLK is @200MHz in waveform. Timer clock is @24MHz =>
     * => (16 * 24.000.000 / 200.000.000) = 1.92us minimum
     * => set x4 = 8us */
    SystemTimeDelay(8);
    /* set PRESETN HIGH */
    SRC_XSPR_DDRMIX->IRST_REQ_CTRL &= ~SRC_XSPR_IRST_REQ_CTRL_RSTR_1_IRST_0_MASK;
    /* The delay below shall be 0 according to PHY PUB, set 8 just in case */
    SystemTimeDelay(8);
    /* set RESET_N HIGH */
    SRC_XSPR_DDRMIX->IRST_REQ_CTRL &= ~SRC_XSPR_IRST_REQ_CTRL_RSTR_1_IRST_1_MASK;
    /* The duration for the delay below is not mentioned in PHY PUB, set 8 just in case */
    SystemTimeDelay(8);
}

int Ddrc_Init(struct dram_timing_info *dtiming, uint32_t img_id)
{
    int ret = 0;
    uint32_t fsp_id, drate;
#if (!defined(DDR_NO_PHY))
    uint32_t acg;
    bool valid;
#endif

    /* reset ddrphy */
    Ddr_PhyColdReset();

    /**
     * FSP ID must point to the last trained FSP
     * so that the proper DDRC config - for the
     * last trained FSP - is loaded. This fits
     * both training and quick boot flows.
     */
    fsp_id = dtiming->fsp_msg_num - 1;
    drate = dtiming->fsp_msg[fsp_id].drate;
    /* default to the last frequency point clock */
    Ddr_Phy_Init_Set_Dfi_Clk(drate);

#if (!defined(DDR_NO_PHY))
    /** Verify training data loaded from non-volatile memory */
    valid = Ddr_Training_Data_Check();
    /** Release in read-write mode the memory used to load training data */
    Ddr_Training_Data_Release(img_id);

    if (valid)
    {
        /* Configure PHY in QuickBoot mode */
        ret = Ddr_Cfg_Phy_Qb(dtiming, fsp_id);
        if (ret) { return ret; }
    }
    else
    {
        /*
         * Start PHY initialization and training by
         * accessing relevant PUB registers
         */
        ret = Ddr_Cfg_Phy(dtiming);
        if (ret) { return ret; }

        /** Collect training data */
        Ddr_Phy_Qb_Save();

        /** Sign collected training data */
        Ddr_Training_Data_Sign();

        /**
         * Release in read-write mode the memory used
         * to save and sign training data
         */
        Ddr_Training_Data_Release(img_id);
    }

    /* save the ddr info for retention */
    Ddr_Cfg_Save(dtiming);

    /* save the ddr PHY trained CSR for retention */
    Ddr_Phy_Trained_Csr_Save();
#endif

    /* program the ddrc registers */
    Ddrc_Config(dtiming, fsp_id);

    Check_Dfi_Init_Complete();

    DDRC->DDR_SDRAM_CFG |= DDRC_DDR_SDRAM_CFG_MEM_EN_MASK; /* |= 0x80000000 */

    Check_DdrcIdle(DDRC_DDRDSR_2_IDLE_MASK);

    while (DDRC->DDR_MTCR & DDRC_DDR_MTCR_MT_EN_MASK);

#if (!defined(DDR_NO_PHY))
    /**
     * Enable auto clock gating feature
     * By default gate all options except GATE_DDRPHY_DFICLK
     */
    acg  = BLK_CTRL_DDRMIX_AUTO_CG_CTRL_HWFFC_ACG_FORCE_B_MASK |
           BLK_CTRL_DDRMIX_AUTO_CG_CTRL_AUTO_CG_ENA_MASK |
           BLK_CTRL_DDRMIX_AUTO_CG_CTRL_SSI_IDLE_STRAP(0x8000);
    acg |= BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_APBCLK_MASK |
           BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_IPS_CLK_MASK |
           BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_CLK_MASK;

    BLK_CTRL_DDRMIX->AUTO_CG_CTRL |= acg;

    /** Set SR_FAST_WK_EN in REG_DDR_SDRAM_CFG_3 */
    DDRC->DDR_SDRAM_CFG_3 |= DDRC_DDR_SDRAM_CFG_3_SR_FAST_WK_EN_MASK;
#endif

    return ret;
}
