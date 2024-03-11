/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */

#ifndef ASM_TYPES
#define ASM_TYPES

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define NULL	0

typedef enum { false, true }	bool;

typedef signed char		int8;
typedef unsigned char		uint8;
typedef short int		int16;
typedef unsigned short int	uint16;
typedef int			int32;
typedef unsigned int		uint32;
typedef long long int		int64;
typedef unsigned long long int	uint64;

typedef uint8   u8;
typedef uint16  u16;
typedef uint32  u32;
typedef uint64  u64;
typedef uint8   uint8_t;
typedef uint16  uint16_t;
typedef uint32  uint32_t;
typedef uint64  uint64_t;
typedef uint64  ulong;

typedef volatile uint32_t __IOU32;
typedef volatile uint16_t __IOU16;
#endif
