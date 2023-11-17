// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018 NXP
 */
#include <asm/io.h>
#include <errno.h>
#include "ddr.h"

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
