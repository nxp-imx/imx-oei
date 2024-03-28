/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2024 NXP
 */
#include "soc_rom.h"

static u32 rom_api_download_image(u8 *dest, u64 offset, u32 size)
{
	u32 off_l = ((offset >>  0) & 0xFFFFFFFF);
	u32 off_h = ((offset >> 32) & 0xFFFFFFFF);
	u32 xor = off_l ^ off_h ^ (u32)dest ^ size;

	return rapi.download_image(dest, offset, size, xor);
}

u32 rom_api_query_boot_info(u32 info_type, u32 *info)
{
	u32 xor = info_type ^ (u32)info;

	return rapi.query_boot_info(info_type, info, xor);
}

void rom_api_set_ready(void)
{
	rapi.set_ready();
}

u32 rom_api_read(u32 offset, u32 size, void *dest)
{
	u32 ret = 0, page_size;
	u32 off_in_page, aligned_size;

	ret |= rom_api_query_boot_info(QUERY_PAGE_SZ, &page_size);
	if (ret != ROM_API_OKAY)
		return 0;

	off_in_page = offset % page_size;
	aligned_size = ALIGN(size + off_in_page, page_size);

	if (aligned_size != size) {
		ret = rom_api_download_image((u8 *)dest, offset - off_in_page, aligned_size);
	} else {
		ret = rom_api_download_image((u8 *)dest, offset, size);
	}

	return (ret == ROM_API_OKAY ? size : 0);
}
