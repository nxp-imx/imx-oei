// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright 2023-2024 NXP
 */
#include "fsl_sysctr.h"
#include "qb_p230_rldb4.h"
#include "soc_ddr.h"

static uint8_t Ddr_Phy_Read_Mb_U8(uint32_t offset)
{
    uint8_t ret;
    uint16_t val;
    uint32_t addr  = (offset / 2);
    bool high = (offset % 2);

    addr += DMEM_OFFSET_ADDR;
    val = Dwc_Ddrphy_Apb_Rd(addr);

    if (high)
        val = (val & 0xFF00) >> 8;
    else
        val = (val & 0x00FF);

    ret = (uint8_t) val;

    return ret;
}

void Ddr_Phy_Qb_Save(void)
{
    int i;
    uint32_t addr, mux, ucc;
    ddrphy_qb_state *qb_state = (ddrphy_qb_state *) QB_STATE_SAVE_ADDR;

    /* enable the ddrphy apb */
    mux = Dwc_Ddrphy_Apb_Rd(0xd0000);
    ucc = Dwc_Ddrphy_Apb_Rd(0xc0080);
    SystemTimeDelay(1);
    SYSCTR_TimeDelay(1);
    Dwc_Ddrphy_Apb_Wr(0xd0000, 0x0);
    Dwc_Ddrphy_Apb_Wr(0xc0080, 0x3);

    /* Save trained values from Message Block area */
#if defined(LPDDR4x)
    qb_state->TrainedVREFCA_A0 = Ddr_Phy_Read_Mb_U8(0x4b);
    qb_state->TrainedVREFCA_A1 = Ddr_Phy_Read_Mb_U8(0x4c);
    qb_state->TrainedVREFCA_B0 = Ddr_Phy_Read_Mb_U8(0x7e);
    qb_state->TrainedVREFCA_B1 = Ddr_Phy_Read_Mb_U8(0x7f);

    qb_state->TrainedVREFDQ_A0 = Ddr_Phy_Read_Mb_U8(0x4d);
    qb_state->TrainedVREFDQ_A1 = Ddr_Phy_Read_Mb_U8(0x4e);
    qb_state->TrainedVREFDQ_B0 = Ddr_Phy_Read_Mb_U8(0x80);
    qb_state->TrainedVREFDQ_B1 = Ddr_Phy_Read_Mb_U8(0x81);
#elif defined(LPDDR5)
    qb_state->TrainedVREFCA_A0 = Ddr_Phy_Read_Mb_U8(0x33);
    qb_state->TrainedVREFCA_A1 = Ddr_Phy_Read_Mb_U8(0x34);
    qb_state->TrainedVREFCA_B0 = Ddr_Phy_Read_Mb_U8(0x4e);
    qb_state->TrainedVREFCA_B1 = Ddr_Phy_Read_Mb_U8(0x4f);

    qb_state->TrainedVREFDQ_A0 = Ddr_Phy_Read_Mb_U8(0x35);
    qb_state->TrainedVREFDQ_A1 = Ddr_Phy_Read_Mb_U8(0x36);
    qb_state->TrainedVREFDQ_B0 = Ddr_Phy_Read_Mb_U8(0x50);
    qb_state->TrainedVREFDQ_B1 = Ddr_Phy_Read_Mb_U8(0x51);

    qb_state->TrainedVREFDQU_A0 = Ddr_Phy_Read_Mb_U8(0xd0);
    qb_state->TrainedVREFDQU_A1 = Ddr_Phy_Read_Mb_U8(0xd5);
    qb_state->TrainedVREFDQU_B0 = Ddr_Phy_Read_Mb_U8(0xda);
    qb_state->TrainedVREFDQU_B1 = Ddr_Phy_Read_Mb_U8(0xdf);

    qb_state->TrainedDRAMDFE_A0 = Ddr_Phy_Read_Mb_U8(0xd1);
    qb_state->TrainedDRAMDFE_A1 = Ddr_Phy_Read_Mb_U8(0xd6);
    qb_state->TrainedDRAMDFE_B0 = Ddr_Phy_Read_Mb_U8(0xdb);
    qb_state->TrainedDRAMDFE_B1 = Ddr_Phy_Read_Mb_U8(0xe0);

    qb_state->TrainedDRAMDCA_A0 = Ddr_Phy_Read_Mb_U8(0xd2);
    qb_state->TrainedDRAMDCA_A1 = Ddr_Phy_Read_Mb_U8(0xd7);
    qb_state->TrainedDRAMDCA_B0 = Ddr_Phy_Read_Mb_U8(0xdc);
    qb_state->TrainedDRAMDCA_B1 = Ddr_Phy_Read_Mb_U8(0xe1);
#endif

    qb_state->QBPllUPllProg0 = Dwc_Ddrphy_Apb_Rd(0x58098);
    qb_state->QBPllUPllProg1 = Dwc_Ddrphy_Apb_Rd(0x58099);
    qb_state->QBPllUPllProg2 = Dwc_Ddrphy_Apb_Rd(0x5809a);
    qb_state->QBPllUPllProg3 = Dwc_Ddrphy_Apb_Rd(0x5809b);
    qb_state->QBPllCtrl1 = Dwc_Ddrphy_Apb_Rd(0x5809c);
    qb_state->QBPllCtrl4 = Dwc_Ddrphy_Apb_Rd(0x5809d);
    qb_state->QBPllCtrl5 = Dwc_Ddrphy_Apb_Rd(0x5809e);

    /* Save CSRs */
    for (i = 0; i < DDRPHY_QB_CSR_SIZE; i++)
    {
        qb_state->csr[i] = Dwc_Ddrphy_Apb_Rd(ddrphy_csr_cfg[i]);
    }

    /**
     * Read ACSM SRAM area and save it to non-volatile storage.
     * Psuedo code provided to save ACSM SRAM as follows:
     * where ACSM_SRAM_BASE_ADDR is 0x41000
     */
    for (i = 0, addr = ACSM_SRAM_BASE_ADDR; i < DDRPHY_QB_ACSM_SIZE; i++, addr++)
    {
        qb_state->acsm[i] = Dwc_Ddrphy_Apb_Rd(addr);
    }

    /**
     * Read PState SRAM area and save it to non-volatile storage only
     * if there is more than 2 PState. Psuedo code provide to save
     * PState SRAM as follows, where PSTATE_SRAM_BASE_ADDR is 0xA0000
     */
    for (i = 0, addr = PSTATE_SRAM_BASE_ADDR; i < DDRPHY_QB_PST_SIZE; i++, addr++)
    {
        qb_state->pst[i] = Dwc_Ddrphy_Apb_Rd(addr);
    }

    /* restore mux */
    Dwc_Ddrphy_Apb_Wr(0xc0080, ucc);
    Dwc_Ddrphy_Apb_Wr(0xd0000, mux);
}
