/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2024 NXP
 */
#ifndef __ROM_API_H
#define __ROM_API_H

#include <asm/types.h>

enum boot_device {
	WEIM_NOR_BOOT,
	ONE_NAND_BOOT,
	PATA_BOOT,
	SATA_BOOT,
	I2C_BOOT,
	SPI_NOR_BOOT,
	SD1_BOOT,
	SD2_BOOT,
	SD3_BOOT,
	SD4_BOOT,
	MMC1_BOOT,
	MMC2_BOOT,
	MMC3_BOOT,
	MMC4_BOOT,
	NAND_BOOT,
	QSPI_BOOT,
	FLEXSPI_BOOT,
	FLEXSPI_NAND_BOOT,
	USB_BOOT,
	USB2_BOOT,
	UNKNOWN_BOOT,
	BOOT_DEV_NUM = UNKNOWN_BOOT,
};

enum boot_dev_type {
	BT_DEV_TYPE_SD = 1,
	BT_DEV_TYPE_MMC = 2,
	BT_DEV_TYPE_NAND = 3,
	BT_DEV_TYPE_FLEXSPINOR = 4,
	BT_DEV_TYPE_SPI_NOR = 6,
	BT_DEV_TYPE_FLEXSPINAND = 8,
	BT_DEV_TYPE_USB = 0xE,
	BT_DEV_TYPE_MEM_DEV = 0xF,
	BT_DEV_TYPE_INVALID = 0xFF,
};

enum boot_stage_type {
	BT_STAGE_PRIMARY = 0x6,
	BT_STAGE_SECONDARY = 0x9,
	BT_STAGE_RECOVERY = 0xa,
	BT_STAGE_USB = 0x5,
};

#define QUERY_ROM_VER		1
#define QUERY_BT_DEV		2
#define QUERY_PAGE_SZ		3
#define QUERY_IVT_OFF		4
#define QUERY_BT_STAGE		5
#define QUERY_IMG_OFF		6
#define ROM_API_OKAY		0xF0
#define ROM_API_ERR_INV_PAR	0x1

#define ALIGN_MASK(x, m)	(((x) + (m)) & ~(m))
#define ALIGN(x, a)		ALIGN_MASK((x), (__typeof__(x))(a) - 1)

#define IV_MAX_LEN		32
#define HASH_MAX_LEN		64
#define CONTAINER_HDR_ALIGNMENT	0x400

struct container_hdr {
	u8 version;
	u8 length_lsb;
	u8 length_msb;
	u8 tag;
	u32 flags;
	u16 sw_version;
	u8 fuse_version;
	u8 num_images;
	u16 sig_blk_offset;
	u16 reserved;
} __attribute__ ((packed));

struct boot_img_t {
	u32 offset;
	u32 size;
	u64 dst;
	u64 entry;
	u32 hab_flags;
	u32 meta;
	u8 hash[HASH_MAX_LEN];
	u8 iv[IV_MAX_LEN];
} __attribute__ ((packed));

typedef u32 (*download_image_fn)(u8 *dest, u64 offset, u32 size, u32 xor);
typedef u32 (*query_boot_info_fn)(u32 info_type, u32 *info, u32 xor);
typedef void (*set_ready_fn)(void);

struct rom_api {
	download_image_fn   download_image;
	query_boot_info_fn  query_boot_info;
	set_ready_fn        set_ready;
};

u32  rom_api_query_boot_info(u32 info_type, u32 *info);
void rom_api_set_ready(void);
u32  rom_api_read(u32 offset, u32 size, void *dest);

#endif
