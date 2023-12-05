/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2024 NXP
 */
#ifndef CRC
#define CRC

#include "asm/types.h"

/**
 * Calculate CRC based on half-byte CRC algorithm
 */
u32 crc32(const void *addr, u32 length);

#endif
