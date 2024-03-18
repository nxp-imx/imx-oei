// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018 NXP
 */
#include <asm/io.h>
#include <errno.h>
#include "ddr.h"
#include "ddr_retention.h"

static char _end[0] __attribute__((section(".__end")));

#if !defined(CONFIG_DDR_QBOOT)
static void check_cfg_id(struct dram_fsp_msg *fsp_msg, u32 reg, u32 *cfg_id, u16 *val)
{
	struct ddrphy_cfg_param *cfg = fsp_msg->fsp_phy_msgh_cfg;
	u32 cfg_num = fsp_msg->fsp_phy_msgh_cfg_num;
	u32 id = (*cfg_id);

	/**
	 * Point the config ID to the position where the current register
	 * (reg) is less or equal to the config register (cfg[id].reg)
	 * The assumption is that the registers in "fsp_phy_msgh_cfg" are
	 * in ascending order
	 */
	while (id < cfg_num && ((cfg[id].reg & 0xff000) != DMEM_OFFSET_ADDR || reg > cfg[id].reg))
		id++;

	*val = (id == cfg_num || reg < cfg[id].reg ? 0 : cfg[id].val);
	*cfg_id = id;
}
#endif

struct ddr_fw_header {
	u32 imem_size;
	u32 dmem_size;
};

u32 ddr_get_qb_state_addr(void)
{
	struct ddr_fw_header *header = (struct ddr_fw_header *)((void *)&_end);
	u32 header_size = sizeof(struct ddr_fw_header);
	u32 fw;

	fw = (u32)&_end + header_size + header->imem_size + header->dmem_size;

	return fw;
}

void ddr_load_train_firmware(struct dram_fsp_msg *fsp_msg, enum mem_type type)
{
	u16 val;
	u32 fw_num, i;
	unsigned long fw, pr_to32;
	struct ddr_fw_header *header = (struct ddr_fw_header *)((void *)&_end);
	u32 header_size = sizeof(struct ddr_fw_header);
#if !defined(CONFIG_DDR_QBOOT)
	u32 cfg_id;
#endif

	switch (type) {
	case IMEM:
		fw      = (unsigned long)&_end + header_size;
		fw_num  = header->imem_size / sizeof(val);
		pr_to32 = IMEM_OFFSET_ADDR;
		break;
	case DMEM:
		fw      = (unsigned long)&_end + header_size + header->imem_size;
		fw_num  = header->dmem_size / sizeof(val);
		pr_to32 = DMEM_OFFSET_ADDR;
		break;
	default:
		/* No error given function signature */
		return;
	}

	i = 0;
#if !defined(CONFIG_DDR_QBOOT)
	if (type == DMEM && fsp_msg != NULL && fsp_msg->fsp_phy_msgh_cfg != NULL) {
		cfg_id = 0;
		for ( ; i < DDRPHY_QB_MSB_SIZE; i++, pr_to32++) {
			check_cfg_id(fsp_msg, pr_to32, &cfg_id, &val);
			writew(val, IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(pr_to32));
			fw += sizeof(val);
		}
	}
#endif
	for ( ; i < fw_num; i++, pr_to32++) {
		val = readw(fw);
		writew(val, IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(pr_to32));
		fw += sizeof(val);
	}
}

#if defined(CONFIG_DDR_QBOOT)
void ddr_load_DMEM(u16 *msg_blk, ddrphy_qb_state *qb_state)
{
	struct ddr_fw_header *header = (struct ddr_fw_header *)((void *)&_end);
	u32 header_size = sizeof(struct ddr_fw_header);
	unsigned long fw, pr_to32;
	u32 fw_num, i, j;
	u16 val;

	fw      = (unsigned long)&_end + header_size + header->imem_size;
	fw_num  = header->dmem_size / sizeof(val);
	pr_to32 = DMEM_OFFSET_ADDR;

	for (i = 0; i < DDRPHY_QB_MSB_SIZE; i++, pr_to32++) {
		val = msg_blk[i];
		writew(val, IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(pr_to32));
		fw += sizeof(val);
	}

	/* save CSRs to address starting with 0x58200 */
	for (j = 0; j < DDRPHY_QB_CSR_SIZE; j++, i++, pr_to32++) {
		val = qb_state->csr[j];
		writew(val, IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(pr_to32));
		fw += sizeof(val);
	}

	for ( ; i < fw_num; i++, pr_to32++) {
		val = readw(fw);
		writew(val, IP2APB_DDRPHY_IPS_BASE_ADDR(0) + ddrphy_addr_remap(pr_to32));
		fw += sizeof(val);
	}
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
