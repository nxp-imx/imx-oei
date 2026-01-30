/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2025-2026 NXP
 */

/* Entry Point */
ENTRY(oei_entry)

CM33_TCMU_OFFSET = 0x1FFC0000;
BSS_STACK_OFFSET = 0x20019000;
RETENTION_OFFSET = 0x2001A000;
RETENTION_SIZE   = 0x00010000;
STACK_SIZE       = 0x00000400;
__StackTop       = RETENTION_OFFSET;
__StackLimit     = __StackTop - STACK_SIZE;

/**
 * M33 Code TCM (TCML) Free Space: 0x1FFC0000 - 0x1FFFFFFF - according to RM
 * M33 Sys  TCM (TCMU) Free Space: 0x20000000 - 0x2002DFFF - according to CM33 ROM
 */
MEMORY {
	/**
	 * s_code includes OEI binary having attached two sets of Synopsys FW - training
	 * and quick boot. The memory allocated for resulting m33-oei-ddrfw.bin is
	 * [0x1FFC0000..0x20018FFF], total: 0x59000 (364544) bytes
	 */
	s_code (rx) : ORIGIN = CM33_TCMU_OFFSET, LENGTH = (BSS_STACK_OFFSET - CM33_TCMU_OFFSET)
	/**
	 * s_data keeps BSS and stack, [0x20019000..0x20019FFF]
	 */
	s_data (rw) : ORIGIN = BSS_STACK_OFFSET, LENGTH = (RETENTION_OFFSET - BSS_STACK_OFFSET)
	/**
	 * s_retn keeps DDR retention data, [0x2001A000..0x20029FFF]
	 */
	s_retn (rw) : ORIGIN = RETENTION_OFFSET, LENGTH = RETENTION_SIZE
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

	ASSERT(__START_BSS >= BSS_STACK_OFFSET, "s_data overflowed by BSS")

	/* Initializes stack on the end of s_data */
	.stack __StackLimit :
	{
		. = ALIGN(8);
		. += STACK_SIZE;
	} > s_data

	.retention RETENTION_OFFSET :
	{
		. = ALIGN(4);
		__RetentionStart = .;
		. += RETENTION_SIZE;
		. = ALIGN(4);
		__RetentionEnd = .;
	} > s_retn
}
