// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright 2022-2024 NXP
 */

#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#if defined(LPDDR4x)
#include "msb_ddr4x.h"
#elif defined(LPDDR5)
#include "msb_ddr5.h"
#endif
#include "fsl_sysctr.h"
#include "soc_ddr.h"

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

static void ddrphy_prepare_mb(uint16_t *mb, struct dram_fsp_msg *fsp_msg)
{
	uint32_t i, idx;
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

static int ddrphy_qb_restore(uint16_t *mb, struct dram_fsp_msg *fsp_msg, ddrphy_qb_state *qb_state)
{
	uint32_t i;
#if defined(LPDDR4x)
	MSB_DDR4X_t *msb = (MSB_DDR4X_t *)(mb);
#elif defined(LPDDR5)
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

#if (defined(LPDDR4x) || defined(LPDDR5))
	msb->MR12_A0 = qb_state->TrainedVREFCA_A0;
	msb->MR12_A1 = qb_state->TrainedVREFCA_A1;
	msb->MR12_B0 = qb_state->TrainedVREFCA_B0;
	msb->MR12_B1 = qb_state->TrainedVREFCA_B1;

	msb->MR14_A0 = qb_state->TrainedVREFDQ_A0;
	msb->MR14_A1 = qb_state->TrainedVREFDQ_A1;
	msb->MR14_B0 = qb_state->TrainedVREFDQ_B0;
	msb->MR14_B1 = qb_state->TrainedVREFDQ_B1;
#endif

#if (defined(LPDDR5))
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

int Ddr_Cfg_Phy_Qb(struct dram_timing_info *dtiming, int fsp_id)
{
	struct dram_fsp_msg *fsp_msg;
	ddrphy_qb_state *qb_state;
	int i, ret;
	uint32_t to_addr;
	uint16_t *mb;
#ifdef DEBUG
	unsigned int ts, te;
#endif

	mb = (uint16_t *) QB_STATE_SAVE_ADDR;
	fsp_msg = &dtiming->fsp_msg[fsp_id];
	qb_state = (ddrphy_qb_state *)(QB_STATE_LOAD_ADDR);

	/** 3.2.2 MemReset Toggle */
	Ddr_Phy_Delay40(fsp_msg->drate);
	Dwc_Ddrphy_Apb_Wr(0xd0000, 0x0);
	Dwc_Ddrphy_Apb_Wr(0xd0031, 0x1);
	Dwc_Ddrphy_Apb_Wr(0xc0080, 0x3); /** 3.2.2.1 Low Speed PMU clock */
	Dwc_Ddrphy_Apb_Wr(0xc0086, 0x0); /** 3.2.3   SRAM ECC Initialization off */
	Dwc_Ddrphy_Apb_Wr(0x3F0A2, 0x0F00);
	Dwc_Ddrphy_Apb_Wr(0x3F042, 0x0F0F);
	Dwc_Ddrphy_Apb_Wr(0x3F043, 0x0F0F);
	Dwc_Ddrphy_Apb_Wr(0x3F0A3, 0x0800);
#if (defined(PUB1_02) || defined(PUB1_04) || defined(PUB1_05) || defined(PUB2_00))
	Dwc_Ddrphy_Apb_Wr(0x3F0AC, 0x07FF);
	Dwc_Ddrphy_Apb_Wr(0x1F00F, 0x0006);
	Dwc_Ddrphy_Apb_Wr(0x200F8, 0x0000);
#endif
	/** Need to wait 30 DFI cycles since PtrInit works after some pipeline. */
	SystemTimeDelay(1);
	Dwc_Ddrphy_Apb_Wr(0x20090, 0x0001);
	Dwc_Ddrphy_Apb_Wr(0x20060, 0x0003);

#ifdef DEBUG
	ts = SYSCTR_GetUsec64();
#endif
	/** 3.2.4 Step D Load QuickBoot IMEM */
	phy_ops.ddr_pre_load_firmware(NULL, IMEM, DDRFW_QUICKBOOT);
	phy_ops.ddr_do_load_firmware(IMEM);

	/** 3.2.5 Step F Load QuickBoot DMEM */
	ddrphy_qb_restore(mb, fsp_msg, qb_state);
	phy_ops.ddr_load_DMEM(mb, qb_state);
	phy_ops.ddr_post_load_firmware(IMEM);
	phy_ops.ddr_post_load_firmware(DMEM);
#ifdef DEBUG
	te = SYSCTR_GetUsec64() - ts;
	printf("DDR OEI: IMEM + DMEM load in %u us\n", te);
	ts = SYSCTR_GetUsec64();
#endif

	/* excute the firmware */
	Dwc_Ddrphy_Apb_Wr(0xd0000, 0x1); /* CSR bus: MCU/PIE/DMA++,TDR/APB-- */
	Dwc_Ddrphy_Apb_Wr(0xd0099, 0x9);
	Dwc_Ddrphy_Apb_Wr(0xd0099, 0x1);
	Dwc_Ddrphy_Apb_Wr(0xd0099, 0x0);

	/* Wait for the quick boot firmware to complete */
	ret = Wait_Ddr_Phy_Training_Complete();
	if (ret)
		return ret;

	/* Halt the microcontroller. */
	Dwc_Ddrphy_Apb_Wr(0xd0099, 0x1);
	Ddr_Phy_Delay40(fsp_msg->drate);
	Dwc_Ddrphy_Apb_Wr(0xd0000, 0x0); /* CSR bus: MCU--,PIE/DMA/TDR/APB++ */
#ifdef DEBUG
	te = SYSCTR_GetUsec64() - ts;
	printf("DDR OEI: Quickboot FW run complete in %u us\n", te);
	ts = SYSCTR_GetUsec64();
#endif
	/** 3.2.7 Step H Restore SRAM data */
	phy_ops.acsm_sram_restore(qb_state);
#ifdef DEBUG
	te = SYSCTR_GetUsec64() - ts;
	printf("DDR OEI: ACSM SRAM restore in %u us\n", te);
	ts = SYSCTR_GetUsec64();
#endif
	for (i = 0, to_addr = PSTATE_SRAM_BASE_ADDR; i < DDRPHY_QB_PST_SIZE; i++, to_addr++)
		Dwc_Ddrphy_Apb_Wr(to_addr, qb_state->pst[i]);
#ifdef DEBUG
	te = SYSCTR_GetUsec64() - ts;
	printf("DDR OEI: PSTATE SRAM restore in %u us\n", te);
#endif
	/** 3.2.8 Step I Configure PHY for Hardware */
#if defined(PUB1_xx)
	Dwc_Ddrphy_Apb_Wr(0xd00e7, 0x400);
#elif defined(PUB2_xx)
	Dwc_Ddrphy_Apb_Wr(0xd00e7, 0x600);
#endif
	Dwc_Ddrphy_Apb_Wr(0xc0080, 0x2);
	Dwc_Ddrphy_Apb_Wr(0xd0000, 0x1);

	/**
	 * Invalidate the storage used by training flow
	 * to store training data
	 */
	Ddr_Training_Data_Invalidate();

	return 0;
}
