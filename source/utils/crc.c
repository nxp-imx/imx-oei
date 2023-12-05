/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2024 NXP
 */
#include "crc.h"

/** Polynomial: 0xEDB88320 */
static u32 const p_table[] =
{
	0x00000000,0x1db71064,0x3b6e20c8,0x26d930ac,
	0X76dc4190,0X6b6b51f4,0X4db26158,0X5005713c,
	0xedb88320,0xf00f9344,0xd6d6a3e8,0xcb61b38c,
	0x9b64c2b0,0x86d3d2d4,0xa00ae278,0xbdbdf21c,
};

/**
 * Implement half-byte CRC algorithm
 */
u32 crc32(const void* addr, u32 len)
{
	u32 crc = ~0x00, idx, i, val;
	const u8 *chr = (const u8*)addr;

	for (i = 0; i < len; i++, chr++)
	{
		val = (u32)(*chr);

		idx = (crc ^ (val >> 0)) & 0x0F;
		crc = p_table[idx] ^ (crc >> 4);
		idx = (crc ^ (val >> 4)) & 0x0F;
		crc = p_table[idx] ^ (crc >> 4);
	}

	return ~crc;
}
