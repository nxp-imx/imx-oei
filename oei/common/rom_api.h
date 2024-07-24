/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2024 NXP
 */
#ifndef __ROM_API_H
#define __ROM_API_H

#include <stdbool.h>
#include <stdint.h>

enum boot_device
{
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

enum boot_dev_type
{
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

enum boot_stage_type
{
    BT_STAGE_PRIMARY = 0x6,
    BT_STAGE_SECONDARY = 0x9,
    BT_STAGE_RECOVERY = 0xa,
    BT_STAGE_USB = 0x5,
};

#define QUERY_ROM_VER       1
#define QUERY_BT_DEV        2
#define QUERY_PAGE_SZ       3
#define QUERY_IVT_OFF       4
#define QUERY_BT_STAGE      5
#define QUERY_IMG_OFF       6
#define ROM_API_OKAY        0xF0
#define ROM_API_ERR_INV_PAR 0x1

#define ALIGN_MASK(x, m)    (((x) + (m)) & ~(m))
#define ALIGN(x, a)         ALIGN_MASK((x), (__typeof__(x))(a) - 1)

#define IV_MAX_LEN        32
#define HASH_MAX_LEN        64
#define CONTAINER_HDR_ALIGNMENT    0x400

struct container_hdr
{
    uint8_t version;
    uint8_t length_lsb;
    uint8_t length_msb;
    uint8_t tag;
    uint32_t flags;
    uint16_t sw_version;
    uint8_t fuse_version;
    uint8_t num_images;
    uint16_t sig_blk_offset;
    uint16_t reserved;
} __attribute__ ((packed));

struct boot_img_t
{
    uint32_t offset;
    uint32_t size;
    uint64_t dst;
    uint64_t entry;
    uint32_t hab_flags;
    uint32_t meta;
    uint8_t hash[HASH_MAX_LEN];
    uint8_t iv[IV_MAX_LEN];
} __attribute__ ((packed));

typedef uint32_t (*download_image_fn)(uint8_t *dest, uint64_t offset, uint32_t size, uint32_t xor);
typedef uint32_t (*query_boot_info_fn)(uint32_t info_type, uint32_t *info, uint32_t xor);
typedef void (*set_ready_fn)(void);

struct rom_api
{
    uint16_t ver;
    uint16_t tag;
    uint32_t reserved1;
    download_image_fn  download_image;
    query_boot_info_fn query_boot_info;
    uint32_t rsvd2[5];
};

struct rom_api_wrapper
{
    const struct rom_api *rom;
    set_ready_fn set_ready;
};

uint32_t Rom_Api_Query_Boot_Info(uint32_t info_type, uint32_t *info);
void Rom_Api_Set_Ready(void);
uint32_t Rom_Api_Read(uint32_t offset, uint32_t size, void *dest);
bool Rom_Api_Boot_Dev_Is_Stream(void);

#endif
