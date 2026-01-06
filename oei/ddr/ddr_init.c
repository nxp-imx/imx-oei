// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright 2022-2025 NXP
 */
#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include "crc.h"
#include "common.h"
#include "fsl_common.h"
#include "oei.h"
#include "soc_ddr.h"

/* Local Functions */

#if (!defined(DDR_NO_PHY))
static uint32_t DDR_SimpleDivRound(uint32_t val, uint32_t denom);
#endif

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
        if (dtiming->fsp_table[i] == dtiming->fsp_msg[fsp_id].drate)
        {
            break;
        }
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

static void Ddr_MixPowerUp(void)
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
}

static void Ddr_PhyColdReset(void)
{
    /* set RESET_N LOW, already LOW if function called after Ddr_MixPowerUp */
    SRC_XSPR_DDRMIX->IRST_REQ_CTRL |= SRC_XSPR_IRST_REQ_CTRL_RSTR_1_IRST_1_MASK;
    /* Reset duration is min 64 DfiClk, this time shall include 16 APBCLK below */
    SystemTimeDelay(8);
    /* set PRESETN LOW */
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

enum sdram_type Ddrc_Get_Sdram_Type(void)
{
    struct dram_timing_info *dtiming = &dram_timing;
    uint32_t i, num = dtiming->ddrc_cfg_num, reg, ddr_dram_cfg;
    struct ddrc_cfg_param *ddrc_cfg;
    enum sdram_type type = SDRAM_LPDDR5; /* default value */

    ddrc_cfg = dtiming->ddrc_cfg;
    ddr_dram_cfg  = (uint32_t)&DDRC->DDR_SDRAM_CFG;
    ddr_dram_cfg &= ~(1U << 28U); /* Clean (S) bit */

    /* Get SDRAM type from DDRC timing config */
    for (i = 0; i < num; i++, ddrc_cfg++)
    {
        reg = (ddrc_cfg->reg & ~(1U << 28U)); /* Clean (S) bit */
        if (reg == ddr_dram_cfg)
        {
            type = (ddrc_cfg->val & DDRC_DDR_SDRAM_CFG_SDRAM_TYPE_MASK)
                    >> DDRC_DDR_SDRAM_CFG_SDRAM_TYPE_SHIFT;
            break;
        }
    }

    return type;
}

int Ddrc_Init(struct dram_timing_info *dtiming, uint32_t img_id)
{
    int ret = 0;
    uint32_t fsp_id, drate;
#if (!defined(DDR_NO_PHY))
    int qb_ret = 0;
    uint32_t acg;
#endif

    /** Power up DDRMIX, prepare resets */
    Ddr_MixPowerUp();

    /** Start DfiClk and APBCLK
     *
     * FSP ID must point to the last trained FSP
     * so that the proper DDRC config - for the
     * last trained FSP - is loaded. This fits
     * both training and quick boot flows.
     */
    fsp_id = dtiming->fsp_msg_num - 1;
    drate = dtiming->fsp_msg[fsp_id].drate;
    /* default to the last frequency point clock */
    Ddr_Phy_Init_Set_Dfi_Clk(drate, dtiming->fsp_msg[fsp_id].ssc);

    /** Reset DDR PHY */
    Ddr_PhyColdReset();

#if (!defined(DDR_NO_PHY))
    /** Try to configure PHY in QuickBoot mode */
    qb_ret = Ddr_Cfg_Phy_Qb(dtiming, fsp_id, img_id);
    if (qb_ret < 0)
    {
        /** QuckBoot flow failure, return error */
        return qb_ret;
    }
    else if (qb_ret > 0)
    {
        /** QuickBoot flow signals inappropriate flow context, run Training flow */

        /* Move obtaining the Pathphase init values from SM to OEI after
           training perform this before Ddr_Phy_Qb_Save()
         */
        /*! PathPhase select */
        uint16_t pathsel[4];
        uint32_t idx;
        uint32_t sumpathphase = 0;
        uint16_t count = 128;
        uint16_t loop = count;
        uint32_t dbytes;
        uint16_t init = 0;
        uint32_t addr = 0;
        ddrphy_qb_state *qb_state;
        uint32_t size;

        /** Reset DDR PHY */
        Ddr_PhyColdReset();

        /*
         * Start PHY initialization and training by
         * accessing relevant PUB registers
         */
        ret = Ddr_Cfg_Phy(dtiming);
        if (ret) { return ret; }

        /* CSR bus: MCU/PIE/DMA++,TDR/APB-- */
        Dwc_Ddrphy_Apb_Wr(0xd0000, 0x0);

        /* Initial training of baseline RxReplica receive delay line values
         * used by RxReplcia SW method. If the HW PHY methof of RxReplica
         * is used, then do not execute this. To check if the HW method is
         * used, read RxClkCntl1[EnRxClkCor]: if set, then HW mthod is used.
         */
        if (((uint16_t)Dwc_Ddrphy_Apb_Rd(0x10057U) & 0x1U) == 0x0U)
        {
            /* Detect how many bytes are used in the DDR interface.
               Cannot retrieve this information from the DDRC since
               it has not been configured yet. Instead, we can get
               this information from the DDR PHY CSR AcLnDisable. This tells
               us which CA bus signals are disabled for each channel. For
               channel B, this CSR address is 0x310ac. If any of the CA bus
               signals are disabled (denoted by setting it to "1"), then this
               implies this channel is disabled indicating we are in 16-bit
               (2 byte) mode.
               This CSR definition changes depending on LP4 or LP5 mode, but
               in either mode, bit[0] indicates CA0.
               Hence, for simplicity, we can just read bit[0] which is ChB_CA0
               and if it returns "1", it means ChB is disabled.
             */
            if (((uint16_t)Dwc_Ddrphy_Apb_Rd(0x310acU) & 0x1U) == 0x1U)
            {
                dbytes = 2U;
            }
            else
            {
                dbytes = 4U;
            }

            /* Obtain the baseline RxReplica receive delay line values by
               taking 128 samples and averaging it, per byte lane, then store
               this in RxReplicaCtl03.
             */
            for (idx = 0U; idx < dbytes; idx++)
            {
                sumpathphase = 0U;
                loop = count;

                /* Get path select */
                /* RxReplicaCtl01: Specify which of the five
                 * RxReplicaPathPhase[0..4]
                 * to use for computing RxReplicaRatioNow.
                 */
                addr = 0x100adU + (idx << 12U);
                pathsel[idx] = (uint16_t)(Dwc_Ddrphy_Apb_Rd(addr));

                /* Obtain 128 samples of the receive delay line (pathphase)
                   from the RxReplica circuit
                 */
                while (loop-- != 0U)
                {
                    addr = 0x100d0U + (idx << 12U) + pathsel[idx];
                    sumpathphase += (uint16_t)Dwc_Ddrphy_Apb_Rd(addr);
                }

                /* Got Pathphase init values*/
                init = (uint16_t)(DDR_SimpleDivRound(sumpathphase, count));
                /* Store the receive dealy line (pathphase) baseline to
                   RxReplicaCtl03
                 */
                addr = 0x100afU + (idx << 12U);
                Dwc_Ddrphy_Apb_Wr(addr, init);
            }
        }

        Dwc_Ddrphy_Apb_Wr(0xd0000U, 0x1U);

        /** Collect training data */
        Ddr_Phy_Qb_Save();

        /** Sign collected training data */
        Ddr_Training_Data_Sign(img_id);

        /**
         * Compute CRC32 over Training Data + Signature to
         * be able to check the integrity of the data in
         * the bootloader, before saving to NVM.
         */
        qb_state = (ddrphy_qb_state *)QB_STATE_SAVE_ADDR;

        size = sizeof(ddrphy_qb_state) - sizeof(qb_state->crc);
        qb_state->crc = CRC_Crc32((uint8_t *)qb_state->mac, size);
    }
#endif

    /* save the ddr info for retention */
    Ddr_Cfg_Save(dtiming);

#if (!defined(DDR_NO_PHY))
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

    if (qb_ret > 0)
    {
        uint8_t max_tsize = 128; /* bytes */
        uint64_t size;

        /** Round size to a multiple of 128, so
          * the maximum eDMA transfer size (128 bytes)
          * can be used.
          */
        size = ALIGN(sizeof(ddrphy_qb_state), max_tsize);
        size = MIN(size, QB_STATE_STORAGE_SIZE);

        /** Copy qb data from NPU SRAM to DRAM,
          * for bootloader to save to NVM.
          */
        Edma_Copy_Data(QB_STATE_SAVE_ADDR, max_tsize,
                       QB_STATE_DDR_ADDR,  max_tsize, size);
    }

    /* Indicate that the RxReplica pathPhase initialization was performed
       in the OEI by writing a special code key to DDRC DDR_MTP0 (register
       not used during normal operations).
     */
    DDRC->DDR_MTP[0] = 0x0C0DE0E1U;

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

#if (!defined(DDR_NO_PHY))
/*--------------------------------------------------------------------------*/
/* Divide and round (up or down) function                                   */
/*--------------------------------------------------------------------------*/
static uint32_t DDR_SimpleDivRound(uint32_t val, uint32_t denom)
{
    uint32_t oneOrZero;
    uint32_t absV;

    oneOrZero = ((val % denom) >= (denom / 2U)) ? 1U : 0U;

    /*
     * False Positive: The variable oneOrZero can only have values 0 or 1.
     * There is a theoretical wraparound scenario when val equals UINT32_MAX
     * and denom is 1. However, the count variable is always either 128 or 100,
     * which ensures that wrapping cannot occur.
     * Therefore, this is a false positive.
     */
    // coverity[cert_int30_c_violation]
    absV = (val / denom) + oneOrZero;

    return absV;
}
#endif
