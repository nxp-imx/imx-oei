// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018, 2023-2024 NXP
 */
#include <errno.h>
#include "debug.h"
#include "ddr.h"
#include "ddr_retention.h"
#include "edma.h"
#include "soc_edma.h"

extern char s_code_end[0];

#if !defined(CONFIG_DDR_QBOOT)
/**
 * Point the config ID to the position where the current register
 * (reg) is less or equal to the config register (cfg[id].reg)
 * The assumption is that the registers in "fsp_phy_msgh_cfg" are
 * in ascending order
 *
 * @fsp_msg: ddr fsp traing info
 * @reg: IMEM/DMEM offset address
 * @cfg_id: config index
 * @val: ddrphy config parameter
 */
static void check_cfg_id(struct dram_fsp_msg *fsp_msg, u32 reg, u32 *cfg_id, u16 *val)
{
	struct ddrphy_cfg_param *cfg = fsp_msg->fsp_phy_msgh_cfg;
	u32 cfg_num = fsp_msg->fsp_phy_msgh_cfg_num;
	u32 id = (*cfg_id);

	while (id < cfg_num && ((cfg[id].reg & 0xff000) != DMEM_OFFSET_ADDR || reg > cfg[id].reg))
		id++;

	*val = (id == cfg_num || reg < cfg[id].reg ? 0 : cfg[id].val);
	*cfg_id = id;
}
#endif

/**
 * Get the QuickBoot data address offset
 */
u32 ddr_get_qb_state_addr(void)
{
	struct ddr_fw_header *header = (struct ddr_fw_header *)((void *)&s_code_end);
	u32 header_size = sizeof(struct ddr_fw_header);
	u32 fw;

	/* calculate the quick boot data address */
	fw = (u32)&s_code_end + header_size + header->imem_size + header->dmem_size;

	return fw;
}

/**
 * Wrapper function for waiting edma transfers
 *
 * @type: memory type IMEM/DMEM
 */
static void wait_edma_transfer(enum mem_type type)
{
	uint8_t edma_ch = (type == DMEM) ? EDMA_CH1 : EDMA_CH0;

	edma_ops.wait_transfer(EDMA2_BASE_ADDR, edma_ch);
}

/**
 * Wrapper function for starting edma transfer
 *
 * @type: memory type IMEM/DMEM
 */
static void start_edma_transfer(enum mem_type type)
{
	/* Use CH0 for IMEM and CH1 for DMEM loads. */
	uint8_t edma_ch = (type == DMEM) ? EDMA_CH1 : EDMA_CH0;

	edma_ops.start_transfer(EDMA2_BASE_ADDR, edma_ch);
	edma_ops.check_edma(EDMA2_BASE_ADDR, edma_ch);
}

/**
 * Configure EDMA channels for loading IMEM and DMEM.
 *
 * @fsp_msg: ddr fsp traing info
 * @type: memory type IMEM/DMEM
 */
static void edma_ddr_load_train_firmware(struct dram_fsp_msg *fsp_msg, enum mem_type type)
{
	int ret;
	u32 fw_num, edma_ch;
	unsigned long fw, pr_to32;
	struct ddr_fw_header *header = (struct ddr_fw_header *)((void *)&s_code_end);
	u32 header_size = sizeof(struct ddr_fw_header);
#if !defined(CONFIG_DDR_QBOOT)
	u16 val;
	u32 i, cfg_id;
#endif

	switch (type) {
	case IMEM:
		fw      = (unsigned long)&s_code_end + header_size;
		fw_num  = header->imem_size;
		pr_to32 = IMEM_OFFSET_ADDR;
		edma_ch = EDMA_CH0;
		break;
	case DMEM:
		fw      = (unsigned long)&s_code_end + header_size + header->imem_size;
		fw_num  = header->dmem_size;
		pr_to32 = DMEM_OFFSET_ADDR;
		edma_ch = EDMA_CH1;
		break;
	default:
		/* No error given function signature */
		return;
	}

#if !defined(CONFIG_DDR_QBOOT)
	i = 0;
	if (type == DMEM && fsp_msg != NULL && fsp_msg->fsp_phy_msgh_cfg != NULL) {
		cfg_id = 0;
		for ( ; i < DDRPHY_QB_MSB_SIZE; i++, pr_to32++) {
			check_cfg_id(fsp_msg, pr_to32, &cfg_id, &val);
			writew(val, IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(pr_to32));
			fw += sizeof(val);
		}
	}

	fw_num = fw_num - (i * sizeof(u16));
#endif
	edma_ops.en_master_rep(EDMA2_BASE_ADDR, edma_ch);
	edma_ops.set_tbytes(EDMA2_BASE_ADDR, edma_ch, 2, 2);
	ret = edma_ops.configure(EDMA2_BASE_ADDR, edma_ch, fw, 2,
			IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(pr_to32), 4, fw_num, 1);
	if (ret != 0)
		edma_ops.clr_tcd(EDMA2_BASE_ADDR, edma_ch);
}

#if defined(CONFIG_DDR_QBOOT)
/**
 * Load QuickBoot DMEM memory blocks.
 *
 * @msg_blks: message blocks
 * @qb_state: quick boot state data
 */
static void edma_ddr_load_DMEM(u16 *msg_blk, ddrphy_qb_state *qb_state)
{
	int ret;
	struct ddr_fw_header *header = (struct ddr_fw_header *)((void *)&s_code_end);
	u32 header_size = sizeof(struct ddr_fw_header);
	unsigned long fw, pr_to32;
	u32 fw_num, msg_blk_size, csr_size;

	fw      = (unsigned long)&s_code_end + header_size + header->imem_size;
	fw_num  = header->dmem_size;
	pr_to32 = DMEM_OFFSET_ADDR;
	msg_blk_size = (DDRPHY_QB_MSB_SIZE * sizeof(u16));
	csr_size = (DDRPHY_QB_CSR_SIZE * sizeof(u16));
	fw += msg_blk_size + csr_size;
	fw_num = fw_num - (msg_blk_size + csr_size);

	edma_ops.en_master_rep(EDMA2_BASE_ADDR, EDMA_CH1);
	edma_ops.set_tbytes(EDMA2_BASE_ADDR, EDMA_CH1 , 2, 2);

	/* load msg blocks */
	ret = edma_ops.configure(EDMA2_BASE_ADDR, EDMA_CH1, (unsigned int) msg_blk, 2,
		IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(pr_to32), 4, msg_blk_size, 1);
	if (ret != 0)
		goto exit;

	edma_ops.start_transfer(EDMA2_BASE_ADDR, EDMA_CH1);
	edma_ops.check_edma(EDMA2_BASE_ADDR, EDMA_CH1);

	edma_ops.wait_transfer(EDMA2_BASE_ADDR, EDMA_CH1);
	pr_to32 += DDRPHY_QB_MSB_SIZE;

	/* save CSRs to address starting */
	ret = edma_ops.configure(EDMA2_BASE_ADDR, EDMA_CH1, (unsigned int)&(qb_state->csr[0]),
		2, IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(pr_to32), 4, csr_size, 1);

	if (ret != 0)
		goto exit;

	edma_ops.start_transfer(EDMA2_BASE_ADDR, EDMA_CH1);
	edma_ops.check_edma(EDMA2_BASE_ADDR, EDMA_CH1);
	edma_ops.wait_transfer(EDMA2_BASE_ADDR, EDMA_CH1);
	pr_to32 += DDRPHY_QB_CSR_SIZE;

	/* transfer the remaining DMEM memory blocks */
	ret = edma_ops.configure(EDMA2_BASE_ADDR, EDMA_CH1, fw, 2,
			         IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(pr_to32), 4,
				 fw_num, 1);
	if (ret != 0)
		goto exit;

	start_edma_transfer(DMEM);
	return;

exit:
	edma_ops.clr_tcd(EDMA2_BASE_ADDR, EDMA_CH1);
}

/*
 * Execute ACSM SRAM restore using edma
 * qb_state - quick boot data
 */
static void edma_acsm_sram_restore(ddrphy_qb_state *qb_state)
{
	int ret;

	edma_ops.set_tbytes(EDMA2_BASE_ADDR, EDMA_CH0 , 2, 2);
	ret = edma_ops.configure(EDMA2_BASE_ADDR, EDMA_CH0, (unsigned int)&(qb_state->acsm[0]) , 2,
		      IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(ACSM_SRAM_BASE_ADDR), 4, DDRPHY_QB_ACSM_SIZE, 1);
	if (ret != 0)
	{
		printf("Failed to set edma - error %d\n", ret);
		edma_ops.clr_tcd(EDMA2_BASE_ADDR, EDMA_CH0);
	}
	edma_ops.start_transfer(EDMA2_BASE_ADDR, EDMA_CH0);
	edma_ops.check_edma(EDMA2_BASE_ADDR, EDMA_CH0);
	edma_ops.wait_transfer(EDMA2_BASE_ADDR, EDMA_CH0);
}
#endif

void ddr_cfg_save(struct dram_timing_info *dtiming)
{
	struct ddr_info* ddr = (struct ddr_info*)0x2001A000;
	unsigned int i, j;

	/* zero init the 64K buffer to avoid ECC errors */
	for (i = 0; i < 0xFFFF; i+=4) {
		writel(0, 0x2001A000 + i);
	}

	/* ddrc config next after the ddr_into struct */
	ddr->ddrc_cfg = (struct ddrc*)((unsigned int)ddr + sizeof(struct ddr_info));
	/* number of ddr registers */
	ddr->ddrc_cfg_num = dtiming->ddrc_cfg_num;

	/* save register address and value */
	for (i = 0; i < ddr->ddrc_cfg_num; i++) {
		ddr->ddrc_cfg[i].reg = dtiming->ddrc_cfg[i].reg;
		ddr->ddrc_cfg[i].val = dtiming->ddrc_cfg[i].val;
	}

	/* number of pstates */
	ddr->pstate_num = dtiming->fsp_cfg_num;
	/* pstate struct is after ddrc_cfg */
	ddr->pstate = (struct ddrc_pstate*)((unsigned int)ddr->ddrc_cfg + (ddr->ddrc_cfg_num * sizeof(struct ddrc)));

	for (j = 0; j < ddr->pstate_num; j++)
	{
		/* number of pstate specific ddrc registers */
		ddr->pstate[j].cfg_num = dtiming->fsp_cfg[j].ddrc_cfg_num;
		if (j > 0) {
			/* skip previous pstate structure */
			ddr->pstate[j].cfg = (struct ddrc*)((unsigned int)ddr->pstate[j-1].cfg + (ddr->pstate[j-1].cfg_num *sizeof(struct ddrc)));
		}
		else {
			/* first pstate cfg, skip no. of ddr_pstate structs */
			ddr->pstate[j].cfg = (struct ddrc*)((unsigned int)ddr->pstate + (sizeof(struct ddrc_pstate) * ddr->pstate_num));
		}

		/* save pstate specific register address and value */
		for (i = 0; i < ddr->pstate[j].cfg_num; i++) {
			ddr->pstate[j].cfg[i].reg = dtiming->fsp_cfg[j].ddrc_cfg[i].reg;
			ddr->pstate[j].cfg[i].val = dtiming->fsp_cfg[j].ddrc_cfg[i].val;
		}
	}

	/* save number of trained phy config registers */
	ddr->ddrphy_trained_csr_num = dtiming->ddrphy_trained_csr_num;
	/* skip last pstate struct */
	ddr->trained_csr = (struct ddrphy *)((unsigned int)ddr->pstate[ddr->pstate_num-1].cfg + (ddr->pstate[ddr->pstate_num-1].cfg_num * sizeof(struct ddrc)));

	/* save ddrphy trained csr registers only, value will be saved after phy training completes */
	for (i = 0; i < ddr->ddrphy_trained_csr_num; i++) {
		ddr->trained_csr[i].reg = dtiming->ddrphy_trained_csr[i].reg;
	}

	/* save pstate frequencies */
	for (i = 0; i < ddr->pstate_num; i++) {
		ddr->pstate_freq[i] = dtiming->fsp_table[i];
	}
}

void ddrphy_trained_csr_save(void)
{
	unsigned int i = 0;
	struct ddr_info* ddr = (struct ddr_info*)0x2001A000;

	/* enable the ddrphy apb */
	dwc_ddrphy_apb_wr(0xd0000, 0x0);
	dwc_ddrphy_apb_wr(0xc0080, 0x3);

	/* save ddrphy trained csr value */
        for (i = 0; i < ddr->ddrphy_trained_csr_num; i++) {
                ddr->trained_csr[i].val = dwc_ddrphy_apb_rd(ddr->trained_csr[i].reg);
        }

	/* save ZQ calibration codes */
	ddr->ZQCalCodePU = dwc_ddrphy_apb_rd(0x20326);
	ddr->ZQCalCodePD = dwc_ddrphy_apb_rd(0x20327);

	/* disable the ddrphy apb */
	dwc_ddrphy_apb_wr(0xc0080, 0x2);
	dwc_ddrphy_apb_wr(0xd0000, 0x1);
}

struct ddr_phy_ops phy_ops = {
	.ddr_pre_load_firmware = edma_ddr_load_train_firmware,
	.ddr_do_load_firmware = start_edma_transfer,
	.ddr_post_load_firmware = wait_edma_transfer,
#if defined(CONFIG_DDR_QBOOT)
	.ddr_load_DMEM = edma_ddr_load_DMEM,
	.acsm_sram_restore = edma_acsm_sram_restore,
#endif
};
