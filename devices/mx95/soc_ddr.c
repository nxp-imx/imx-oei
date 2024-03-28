// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2024 NXP
 */
#include "crc.h"
#include "soc_ddr.h"
#include "soc_rom.h"

static u32 get_dev_offset(u32 *offset)
{
	void *buf = (void *)QB_STATE_LOAD_ADDR;
	struct container_hdr *phdr;
	struct boot_img_t *img_entry;
	u32 ctn_off, img_end, readsize;
	u8 i = 0;
	int ret;

	ret = rom_api_query_boot_info(QUERY_IMG_OFF, &ctn_off);
	if (ret != ROM_API_OKAY)
		return ret;

	/** third container offset */
	ctn_off += 2 * CONTAINER_HDR_ALIGNMENT;
	readsize = rom_api_read(ctn_off, CONTAINER_HDR_ALIGNMENT, buf);
	if (readsize != CONTAINER_HDR_ALIGNMENT)
		return ROM_API_ERR_INV_PAR;

	phdr = (struct container_hdr *)buf;
	if (phdr->tag != 0x87 || phdr->version != 0x0) {
		return ROM_API_ERR_INV_PAR;
	}

	img_entry = (struct boot_img_t *)((u32)buf + sizeof(struct container_hdr));
	for (i = 0; i < phdr->num_images; i++) {
		img_end = img_entry->offset + img_entry->size;
		if (i + 1 < phdr->num_images) {
			img_entry++;
			if (img_end + QB_STATE_LOAD_SIZE == img_entry->offset) {
				/** hole detected */
				(*offset) = ctn_off + img_end;
				return ROM_API_OKAY;
			}
		}
	}

	return ROM_API_ERR_INV_PAR;
}

u32 get_training_data_offset(u32 *offset)
{
	u32 boot;
	enum boot_dev_type boot_type;
	u32 ret = ROM_API_OKAY;

	rom_api_set_ready();
	ret |= rom_api_query_boot_info(QUERY_BT_DEV, &boot);
	if (ret != ROM_API_OKAY)
		return ret;

	boot_type = boot >> 16;
	switch (boot_type) {
		case BT_DEV_TYPE_SD:
		case BT_DEV_TYPE_MMC:
		case BT_DEV_TYPE_FLEXSPINOR:
			ret = get_dev_offset(offset);
			break;
		case BT_DEV_TYPE_NAND:
		case BT_DEV_TYPE_SPI_NOR:
		case BT_DEV_TYPE_FLEXSPINAND:
		case BT_DEV_TYPE_USB:
		default:
			(*offset) = 0;
			break;
	}

	return ret;
}

bool ddr_training_data_check(void)
{
	ddrphy_qb_state *qb_state;
	u32 size, crc;

	qb_state = (ddrphy_qb_state *)(QB_STATE_LOAD_ADDR);

	size = sizeof(ddrphy_qb_state) - sizeof(u32);
	crc = crc32(&qb_state->TrainedVREFCA_A0, size);

	return (crc == qb_state->crc);
}
