/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2024 NXP
 */
#include <stdint.h>
#include "soc_rom.h"

static uint32_t Rom_Api_Download_Image(uint8_t *dest, uint64_t offset, uint32_t size)
{
    uint32_t off_l = ((offset >>  0) & 0xFFFFFFFF);
    uint32_t off_h = ((offset >> 32) & 0xFFFFFFFF);
    uint32_t xor = off_l ^ off_h ^ (uint32_t)dest ^ size;

    return rapi.rom->download_image(dest, offset, size, xor);
}

uint32_t Rom_Api_Query_Boot_Info(uint32_t info_type, uint32_t *info)
{
    uint32_t xor = info_type ^ (uint32_t)info;

    return rapi.rom->query_boot_info(info_type, info, xor);
}

void Rom_Api_Set_Ready(void)
{
    rapi.set_ready();
}

uint32_t Rom_Api_Read(uint32_t offset, uint32_t size, void *dest)
{
    uint32_t ret = 0, page_size;
    uint32_t off_in_page, aligned_size;

    ret |= Rom_Api_Query_Boot_Info(QUERY_PAGE_SZ, &page_size);
    if (ret != ROM_API_OKAY)
        return 0;

    off_in_page = offset % page_size;
    aligned_size = ALIGN(size + off_in_page, page_size);

    if (aligned_size != size)
    {
        ret = Rom_Api_Download_Image((uint8_t *)dest, offset - off_in_page, aligned_size);
    }
    else
    {
        ret = Rom_Api_Download_Image((uint8_t *)dest, offset, size);
    }

    return (ret == ROM_API_OKAY ? size : 0);
}

bool Rom_Api_Boot_Dev_Is_Stream(void)
{
    uint32_t boot;
    enum boot_dev_type boot_type;

    Rom_Api_Set_Ready();
    Rom_Api_Query_Boot_Info(QUERY_BT_DEV, &boot);

    boot_type = boot >> 16;

    if (boot_type == BT_DEV_TYPE_MMC && (boot & 1))
        return true;

    if (boot_type >= BT_DEV_TYPE_USB && boot_type != BT_DEV_TYPE_INVALID)
        return true;

    return false;
}
