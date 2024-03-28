/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023-2024 NXP
 */

/**
 * OCRAM total, NS: 0x20480000 - 0x204D7FFF - according to RM
 * IRAM Free Space: 0x20498000 - 0x204D7FFF - according to CA55 ROM,
 *  => 0x204D7FFF - 0x20498000 + 1 = 0x40000 = 262144 bytes = 256 kBytes
 */
MEMORY {
	s_code (rx) : ORIGIN = 0x20498000, LENGTH = 0x00040000
}

OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)

SECTIONS
{
	.text : {
		. = ALIGN(8);
	        KEEP(*(.entry))
		*(.text*)
	} > s_code

	.rodata : {
		. = ALIGN(8);
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
	} > s_code

	.data : {
		. = ALIGN(8);
		*(.data*)
	} > s_code

	.end : {
		. = ALIGN(8);
		s_code_end = .;
	} > s_code
}
