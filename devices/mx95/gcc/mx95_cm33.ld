/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023-2024 NXP
 */

/**
 * M33 Code TCM (TCML) Free Space: 0x1FFC0000 - 0x1FFFFFFF - according to RM
 * M33 Sys  TCM (TCMU) Free Space: 0x30000000 - 0x3002DFFF - according to CM33 ROM
 */
MEMORY {
	s_code (rx) : ORIGIN = 0x1FFC0000, LENGTH = 0x00040000
}

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm) 

SECTIONS
{
	.text : {
		. = ALIGN(4);
	        KEEP(*(.entry))
		*(.text*)
	} > s_code

	.rodata : {
		. = ALIGN(4);
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
	} > s_code

	.data : {
		. = ALIGN(4);
		*(.data*)
	} > s_code

	.end : {
		. = ALIGN(4);
		s_code_end = .;
	} > s_code
}
