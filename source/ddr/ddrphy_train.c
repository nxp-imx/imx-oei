// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018 NXP
 */

#include "ddr.h"
#include "debug.h"
#include "time.h"

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

int ddr_cfg_phy(struct dram_timing_info *dtiming)
{
	struct dram_fsp_msg *fsp_msg;
	unsigned int i;
	int ret;
#ifdef DEBUG
	unsigned int ts, te;
#endif

	/* initialize PHY configuration */
	/* config phy common reg */
	ddrphy_cfg_set(dtiming->ddrphy_cfg, dtiming->ddrphy_cfg_num);

	/* load training firmwrae iMEM */
#ifdef DEBUG
	ts = timer_get_us();
#endif
	ddr_load_train_firmware(NULL, IMEM);
#ifdef DEBUG
	te = timer_get_us() - ts;
	printf("** DDR OEI: IMEM load in %u us **\n", te);
#endif

	/* load the frequency setpoint message block config */
	fsp_msg = dtiming->fsp_msg;
	for (i = 0; i < dtiming->fsp_msg_num; i++) {
		/* If NumPStates more than 2, StartPsloop "DMA reload" prepare no action required */
		/* config phy pstate reg */
		ddrphy_cfg_set(fsp_msg->fsp_phy_cfg, fsp_msg->fsp_phy_cfg_num);

		/* If NumPStates more than 2, stopPsloop "DMA reload" prepare
		 * action is included in end of fsp_phy_cfg  */

		/* set dram PHY input clocks to desired frequency */
		ddrphy_init_set_dfi_clk(fsp_msg->drate);

		/* load the dram training firmware image */
#ifdef DEBUG
		ts = timer_get_us();
#endif
		ddr_load_train_firmware(fsp_msg, DMEM);
#ifdef DEBUG
		te = timer_get_us() - ts;
		printf("** DDR OEI: DMEM load in %u us **\n", te);
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
#ifdef DEBUG
		ts = timer_get_us();
#endif
		dwc_ddrphy_apb_wr(0xd0000, 0x1); /* CSR bus: MCU/PIE/DMA++,TDR/APB-- */
		dwc_ddrphy_apb_wr(0xd0099, 0x9);
		dwc_ddrphy_apb_wr(0xd0099, 0x1);
		dwc_ddrphy_apb_wr(0xd0099, 0x0);

		/* Wait for the training firmware to complete */
		ret = wait_ddrphy_training_complete();
		if (ret)
			return ret;

		/* Halt the microcontroller. */
		dwc_ddrphy_apb_wr(0xd0099, 0x1);
		ddrphy_delay40(fsp_msg->drate);
		dwc_ddrphy_apb_wr(0xd0000, 0x0); /* CSR bus: MCU--,PIE/DMA/TDR/APB++ */
#ifdef DEBUG
		te = timer_get_us() - ts;
		printf("** DDR OEI: TRAINING complete in %u us **\n", te);
#endif

		/* Read the Message Block results */
		ddrphy_init_read_msg_block();

		/* If NumPStates more than 2, resumePsloop "DMA reload" prepare resume, no action */
		/* config PIE pstate reg */
		ddrphy_cfg_set(fsp_msg->fsp_phy_pie_cfg,
			       fsp_msg->fsp_phy_pie_cfg_num);
		/* If NumPStates more than 2, "DMA reload" prepare end, prepare Xlat Table for this PState */
		/* action is included in end of fsp_phy_pie_cfg */
		fsp_msg++;
	}

	/* Load PHY Init Engine Image */
	ddrphy_cfg_set(dtiming->ddrphy_pie, dtiming->ddrphy_pie_num);

	dwc_ddrphy_apb_wr(0xd0000, 0x1); /* CSR bus: MCU/PIE/DMA++,TDR/APB-- */

	return 0;
}
