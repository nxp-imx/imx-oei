// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2023-2024 NXP
 */
#include "soc_edma.h"

/**
 * Converts CPU address view to DMA view.
 *
 * @cpu_view_addr - address to be converted.
 * Return: address from DMA view.
 */
uint32_t convert_to_dma_addr(uint32_t cpu_view_addr)
{
	uint32_t dst_addr = cpu_view_addr;

	if ((cpu_view_addr >= CM33_ITCM_START_ADDR) && (cpu_view_addr <= CM33_ITCM_END_ADDR))
	{
		dst_addr = (int)cpu_view_addr - (int)CM33_ITCM_START_ADDR + CM33_ITCM_START_ADDR_FROM_DMA_VIEW;
	}

	if ((cpu_view_addr >= CM33_DTCM_START_ADDR) && (cpu_view_addr <= CM33_DTCM_END_ADDR))
	{
		dst_addr = (int)cpu_view_addr - (int)CM33_DTCM_START_ADDR + CM33_DTCM_START_ADDR_FROM_DMA_VIEW;
	}

	return dst_addr;
}
