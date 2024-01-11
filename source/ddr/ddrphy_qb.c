// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2022 NXP
 */

#include <errno.h>
#include "crc.h"
#include "ddr.h"
#include "debug.h"
#include "time.h"
#if defined(DDR4x)
#include "ddr/msb_ddr4x.h"
#elif defined(DDR5)
#include "ddr/msb_ddr5.h"
#endif

static void ddrphy_delay40(unsigned int drate)
{
#ifndef CONFIG_IMX95_EMU
	unsigned int udelays = 40 * 8;

	udelays /= drate;

	if (udelays == 0)
		udelays = 1;

	/* wait 40 DfiClks */
	udelay(udelays);
#endif
}

static void ddrphy_prepare_mb(u16 *mb, struct dram_fsp_msg *fsp_msg)
{
	u32 i, idx;
	struct ddrphy_cfg_param *cfg;

	if (fsp_msg == NULL || fsp_msg->fsp_phy_msgh_cfg == NULL)
		return;

	cfg = fsp_msg->fsp_phy_msgh_cfg;
	for (i = 0; i < fsp_msg->fsp_phy_msgh_cfg_num; i++, cfg++) {
		if ((cfg->reg & 0xff000) != DMEM_OFFSET_ADDR)
			continue;
		idx = (cfg->reg & 0xfff);
		if (idx >= DDRPHY_QB_MSB_SIZE)
			continue;
		mb[idx] = cfg->val;
	}
}

static int ddrphy_qb_restore(u16 *mb, struct dram_fsp_msg *fsp_msg, ddrphy_qb_state *qb_state)
{
	u32 i;
#if defined(DDR4x)
	MSB_DDR4X_t *msb = (MSB_DDR4X_t *)(mb);
#elif defined(DDR5)
	MSB_DDR5_t *msb = (MSB_DDR5_t *)(mb);
#endif
	for (i = 0; i < DDRPHY_QB_MSB_SIZE; i++)
		mb[i] = 0;

	ddrphy_prepare_mb(mb, fsp_msg);

	msb->SequenceCtrl = 0x01; /* SequenceCtrl = 0x1 (DevInit Only)*/
	msb->Quickboot    = 0x01; /* Quickboot    = 0x1 */

	msb->QBPllUPllProg0 = qb_state->QBPllUPllProg0;
	msb->QBPllUPllProg1 = qb_state->QBPllUPllProg1;
	msb->QBPllUPllProg2 = qb_state->QBPllUPllProg2;
	msb->QBPllUPllProg3 = qb_state->QBPllUPllProg3;
	msb->QBPllCtrl1 = qb_state->QBPllCtrl1;
	msb->QBPllCtrl4 = qb_state->QBPllCtrl4;
	msb->QBPllCtrl5 = qb_state->QBPllCtrl5;

#if (defined(DDR4x) || defined(DDR5))
	msb->MR12_A0 = qb_state->TrainedVREFCA_A0;
	msb->MR12_A1 = qb_state->TrainedVREFCA_A1;
	msb->MR12_B0 = qb_state->TrainedVREFCA_B0;
	msb->MR12_B1 = qb_state->TrainedVREFCA_B1;

	msb->MR14_A0 = qb_state->TrainedVREFDQ_A0;
	msb->MR14_A1 = qb_state->TrainedVREFDQ_A1;
	msb->MR14_B0 = qb_state->TrainedVREFDQ_B0;
	msb->MR14_B1 = qb_state->TrainedVREFDQ_B1;
#endif

#if (defined(DDR5))
	msb->MR15_A0 = qb_state->TrainedVREFDQU_A0;
	msb->MR15_A1 = qb_state->TrainedVREFDQU_A1;
	msb->MR15_B0 = qb_state->TrainedVREFDQU_B0;
	msb->MR15_B1 = qb_state->TrainedVREFDQU_B1;

	msb->MR24_A0 = qb_state->TrainedDRAMDFE_A0;
	msb->MR24_A1 = qb_state->TrainedDRAMDFE_A1;
	msb->MR24_B0 = qb_state->TrainedDRAMDFE_B0;
	msb->MR24_B1 = qb_state->TrainedDRAMDFE_B1;

	msb->MR30_A0 = qb_state->TrainedDRAMDCA_A0;
	msb->MR30_A1 = qb_state->TrainedDRAMDCA_A1;
	msb->MR30_B0 = qb_state->TrainedDRAMDCA_B0;
	msb->MR30_B1 = qb_state->TrainedDRAMDCA_B1;
#endif
	return 0;
}

#define PUB2_xx	1
#define PUB2_30	1

int ddr_cfg_phy_qb(struct dram_timing_info *dtiming, int fsp_id)
{
	struct dram_fsp_msg *fsp_msg;
	ddrphy_qb_state *qb_state;
	u32 qb_state_addr;
	unsigned int i;
	int ret;
	u32 to_addr, size, crc;
	u16 *mb;
#ifdef DEBUG
	unsigned int ts, te;
#endif

	mb = (u16 *) QB_STATE_MEM;
	fsp_msg = &dtiming->fsp_msg[fsp_id];
	qb_state_addr = ddr_get_qb_state_addr();
	qb_state = (ddrphy_qb_state *)(qb_state_addr);

	size = sizeof(ddrphy_qb_state) - sizeof(u32);
	crc = crc32(&qb_state->TrainedVREFCA_A0, size);

	if (crc != qb_state->crc)
		return -1;

	/** 3.2.2 MemReset Toggle */
	ddrphy_delay40(fsp_msg->drate);
	dwc_ddrphy_apb_wr(0xd0000, 0x0);
	dwc_ddrphy_apb_wr(0xd0031, 0x1);
	dwc_ddrphy_apb_wr(0xc0080, 0x3); /** 3.2.2.1 Low Speed PMU clock */
	dwc_ddrphy_apb_wr(0xc0086, 0x0); /** 3.2.3   SRAM ECC Initialization off */
	dwc_ddrphy_apb_wr(0x3F0A2, 0x0F00);
	dwc_ddrphy_apb_wr(0x3F042, 0x0F0F);
	dwc_ddrphy_apb_wr(0x3F043, 0x0F0F);
	dwc_ddrphy_apb_wr(0x3F0A3, 0x0800);
#if (defined(PUB1_02) || defined(PUB1_04) || defined(PUB1_05) || defined(PUB2_00))
	dwc_ddrphy_apb_wr(0x3F0AC, 0x07FF);
	dwc_ddrphy_apb_wr(0x1F00F, 0x0006);
	dwc_ddrphy_apb_wr(0x200F8, 0x0000);
#endif
	/** Need to wait 30 DFI cycles since PtrInit works after some pipeline. */
	udelay(1);
	dwc_ddrphy_apb_wr(0x20090, 0x0001);
	dwc_ddrphy_apb_wr(0x20060, 0x0003);

#ifdef DEBUG
	ts = timer_get_us();
#endif
	/** 3.2.4 Step D Load QuickBoot IMEM */
	ddr_load_train_firmware(NULL, IMEM);
#ifdef DEBUG
	te = timer_get_us() - ts;
	printf("** DDR OEI: IMEM load in %u us **\n", te);
	ts = timer_get_us();
#endif
	/** 3.2.5 Step F Load QuickBoot DMEM */
	ddrphy_qb_restore(mb, fsp_msg, qb_state);
	ddr_load_DMEM(mb, qb_state);
#ifdef DEBUG
	te = timer_get_us() - ts;
	printf("** DDR OEI: DMEM load in %u us **\n", te);
	ts = timer_get_us();
#endif
	/* excute the firmware */
	dwc_ddrphy_apb_wr(0xd0000, 0x1); /* CSR bus: MCU/PIE/DMA++,TDR/APB-- */
	dwc_ddrphy_apb_wr(0xd0099, 0x9);
	dwc_ddrphy_apb_wr(0xd0099, 0x1);
	dwc_ddrphy_apb_wr(0xd0099, 0x0);

	/* Wait for the quick boot firmware to complete */
	ret = wait_ddrphy_training_complete();
	if (ret)
		return ret;

	/* Halt the microcontroller. */
	dwc_ddrphy_apb_wr(0xd0099, 0x1);
	ddrphy_delay40(fsp_msg->drate);
	dwc_ddrphy_apb_wr(0xd0000, 0x0); /* CSR bus: MCU--,PIE/DMA/TDR/APB++ */
#ifdef DEBUG
	te = timer_get_us() - ts;
	printf("** DDR OEI: Quickboot FW run complete in %u us **\n", te);
	ts = timer_get_us();
#endif
	/** 3.2.7 Step H Restore SRAM data */
	for (i = 0, to_addr = ACSM_SRAM_BASE_ADDR; i < DDRPHY_QB_ACSM_SIZE; i++, to_addr++)
		dwc_ddrphy_apb_wr(to_addr, qb_state->acsm[i]);
#ifdef DEBUG
	te = timer_get_us() - ts;
	printf("** DDR OEI: ACSM SRAM restore in %u us **\n", te);
	ts = timer_get_us();
#endif
	for (i = 0, to_addr = PSTATE_SRAM_BASE_ADDR; i < DDRPHY_QB_PST_SIZE; i++, to_addr++)
		dwc_ddrphy_apb_wr(to_addr, qb_state->pst[i]);
#ifdef DEBUG
	te = timer_get_us() - ts;
	printf("** DDR OEI: PSTATE SRAM restore in %u us **\n", te);
#endif
	/** 3.2.8 Step I Configure PHY for Hardware */
#if defined(PUB1_xx)
	dwc_ddrphy_apb_wr(0xd00e7, 0x400);
#elif defined(PUB2_xx)
	dwc_ddrphy_apb_wr(0xd00e7, 0x600);
#endif
	dwc_ddrphy_apb_wr(0xc0080, 0x2);
	dwc_ddrphy_apb_wr(0xd0000, 0x1);

	return 0;
}
