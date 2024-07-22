/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2024 NXP
 */

/* Entry Point */
ENTRY(oei_entry)

RETENTION_OFFSET = 0x2001A000;
RETENTION_SIZE   = 0x00010000;
STACK_SIZE       = DEFINED(__stack_size__) ? __stack_size__ : 0x400;

/**
 * M33 Code TCM (TCML) Free Space: 0x1FFC0000 - 0x1FFFFFFF - according to RM
 * M33 Sys  TCM (TCMU) Free Space: 0x30000000 - 0x3002DFFF - according to CM33 ROM
 */
MEMORY {
	/**
	 * s_code length includes the attached Synopsys FW,
	 * max size of m33-oei-ddrfw.bin is 0x50000 = 327680 bytes
	 */
	s_code (rx) : ORIGIN = 0x1FFC0000, LENGTH = 0x00050000
	/**
	 * s_data section is the mem since the end of s_code (0x1FFC0000 + 0x00050000)
	 * till the start of the TCM memory used by ROM (starts at 0x2002C000)
	 */
	s_data (rw) : ORIGIN = 0x20010000, LENGTH = 0x0001C000 /* end addr: 0x2002C000 */
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
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.data*)))
		. = ALIGN(4);
	} > s_code

	s_code_end = .;

	/* Uninitialized data section */
	.bss :
	{
		/* This is used by the startup in order to initialize the .bss section */
		. = ALIGN(4);
		__START_BSS = .;
		__bss_start__ = .;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
		__END_BSS = .;
	} > s_data

	.retention RETENTION_OFFSET :
	{
		. = ALIGN(4);
		__RetentionStart = .;
		. += RETENTION_SIZE;
		. = ALIGN(4);
		__RetentionEnd = .;
	} > s_data

	/* Initializes stack on the end of s_data */
	__StackTop   = ORIGIN(s_data) + LENGTH(s_data);
	__StackLimit = __StackTop - STACK_SIZE;

	.stack __StackLimit :
	{
		. = ALIGN(8);
		. += STACK_SIZE;
	} > s_data
}
