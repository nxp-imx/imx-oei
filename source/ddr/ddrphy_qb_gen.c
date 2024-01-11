// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2023 NXP
 */
#include "crc.h"
#include "ddr/qb_p230_rldb4.h"
#include "time.h"

static u8 ddrphy_read_mb_u8(u32 offset)
{
	u8 ret;
	u16 val;
	u32 addr  = (offset / 2);
	bool high = (offset % 2);

	addr += DMEM_OFFSET_ADDR;
	val = dwc_ddrphy_apb_rd(addr);

	if (high)
		val = (val & 0xFF00) >> 8;
	else
		val = (val & 0x00FF);

	ret = (u8) val;

	return ret;
}

void ddrphy_qb_save(void)
{
	u32 i, addr, mux, ucc, size;
	ddrphy_qb_state *qb_state = (ddrphy_qb_state *) QB_STATE_MEM;

	/* enable the ddrphy apb */
	mux = dwc_ddrphy_apb_rd(0xd0000);
	ucc = dwc_ddrphy_apb_rd(0xc0080);
	udelay(1);
	dwc_ddrphy_apb_wr(0xd0000, 0x0);
	dwc_ddrphy_apb_wr(0xc0080, 0x3);

	/* Save trained values from Message Block area */
#if defined(DDR4x)
	qb_state->TrainedVREFCA_A0 = ddrphy_read_mb_u8(0x4b);
	qb_state->TrainedVREFCA_A1 = ddrphy_read_mb_u8(0x4c);
	qb_state->TrainedVREFCA_B0 = ddrphy_read_mb_u8(0x7e);
	qb_state->TrainedVREFCA_B1 = ddrphy_read_mb_u8(0x7f);

	qb_state->TrainedVREFDQ_A0 = ddrphy_read_mb_u8(0x4d);
	qb_state->TrainedVREFDQ_A1 = ddrphy_read_mb_u8(0x4e);
	qb_state->TrainedVREFDQ_B0 = ddrphy_read_mb_u8(0x80);
	qb_state->TrainedVREFDQ_B1 = ddrphy_read_mb_u8(0x81);
#elif defined(DDR5)
	qb_state->TrainedVREFCA_A0 = ddrphy_read_mb_u8(0x33);
	qb_state->TrainedVREFCA_A1 = ddrphy_read_mb_u8(0x34);
	qb_state->TrainedVREFCA_B0 = ddrphy_read_mb_u8(0x4e);
	qb_state->TrainedVREFCA_B1 = ddrphy_read_mb_u8(0x4f);

	qb_state->TrainedVREFDQ_A0 = ddrphy_read_mb_u8(0x35);
	qb_state->TrainedVREFDQ_A1 = ddrphy_read_mb_u8(0x36);
	qb_state->TrainedVREFDQ_B0 = ddrphy_read_mb_u8(0x50);
	qb_state->TrainedVREFDQ_B1 = ddrphy_read_mb_u8(0x51);

	qb_state->TrainedVREFDQU_A0 = ddrphy_read_mb_u8(0xd0);
	qb_state->TrainedVREFDQU_A1 = ddrphy_read_mb_u8(0xd5);
	qb_state->TrainedVREFDQU_B0 = ddrphy_read_mb_u8(0xda);
	qb_state->TrainedVREFDQU_B1 = ddrphy_read_mb_u8(0xdf);

	qb_state->TrainedDRAMDFE_A0 = ddrphy_read_mb_u8(0xd1);
	qb_state->TrainedDRAMDFE_A1 = ddrphy_read_mb_u8(0xd6);
	qb_state->TrainedDRAMDFE_B0 = ddrphy_read_mb_u8(0xdb);
	qb_state->TrainedDRAMDFE_B1 = ddrphy_read_mb_u8(0xe0);

	qb_state->TrainedDRAMDCA_A0 = ddrphy_read_mb_u8(0xd2);
	qb_state->TrainedDRAMDCA_A1 = ddrphy_read_mb_u8(0xd7);
	qb_state->TrainedDRAMDCA_B0 = ddrphy_read_mb_u8(0xdc);
	qb_state->TrainedDRAMDCA_B1 = ddrphy_read_mb_u8(0xe1);
#endif

	qb_state->QBPllUPllProg0 = dwc_ddrphy_apb_rd(0x58098);
	qb_state->QBPllUPllProg1 = dwc_ddrphy_apb_rd(0x58099);
	qb_state->QBPllUPllProg2 = dwc_ddrphy_apb_rd(0x5809a);
	qb_state->QBPllUPllProg3 = dwc_ddrphy_apb_rd(0x5809b);
	qb_state->QBPllCtrl1 = dwc_ddrphy_apb_rd(0x5809c);
	qb_state->QBPllCtrl4 = dwc_ddrphy_apb_rd(0x5809d);
	qb_state->QBPllCtrl5 = dwc_ddrphy_apb_rd(0x5809e);

	/* Save CSRs */
	for (i = 0; i < DDRPHY_QB_CSR_SIZE; i++)
		qb_state->csr[i] = dwc_ddrphy_apb_rd(ddrphy_csr_cfg[i]);

	/**
	 * Read ACSM SRAM area and save it to non-volatile storage.
	 * Psuedo code provided to save ACSM SRAM as follows:
	 * where ACSM_SRAM_BASE_ADDR is 0x41000
	 */
	for (i = 0, addr = ACSM_SRAM_BASE_ADDR; i < DDRPHY_QB_ACSM_SIZE; i++, addr++)
		qb_state->acsm[i] = dwc_ddrphy_apb_rd(addr);

	/**
	 * Read PState SRAM area and save it to non-volatile storage only
	 * if there is more than 2 PState. Psuedo code provide to save
	 * PState SRAM as follows, where PSTATE_SRAM_BASE_ADDR is 0xA0000
	 */
	for (i = 0, addr = PSTATE_SRAM_BASE_ADDR; i < DDRPHY_QB_PST_SIZE; i++, addr++)
		qb_state->pst[i] = dwc_ddrphy_apb_rd(addr);

	size = sizeof(ddrphy_qb_state) - sizeof(u32);
	qb_state->crc = crc32(&qb_state->TrainedVREFCA_A0, size);

	/* restore mux */
	dwc_ddrphy_apb_wr(0xc0080, ucc);
	dwc_ddrphy_apb_wr(0xd0000, mux);
}
