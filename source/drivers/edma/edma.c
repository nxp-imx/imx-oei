// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2023-2024 NXP
 */
#include "edma.h"
#include "soc_edma.h"

/** Dummy function to cover init and deinit callbacks
 */
static void dma_dummy(void)
{

}

typedef enum
{
	/*! @brief DMA transfer configuration */
	DMA_TRANSFER_SIZE_1_BYTES = 0x0U, /* Src/Dest data transfer size is 1 byte every time */
	DMA_TRANSFER_SIZE_2_BYTES = 0x1U, /* Src/Dest data transfer size is 2 bytes every time */
	DMA_TRANSFER_SIZE_4_BYTES = 0x2U, /* Src/Dest data transfer size is 4 bytes every time */
	DMA_TRANSFER_SIZE_8_BYTES = 0x3U, /* Src/Dest data transfer size is 8 bytes every time */
	DMA_TRANSFER_SIZE_16_BYTES = 0x4U, /* Src/Dest data transfer size is 16 bytes every time */
	DMA_TRANSFER_SIZE_32_BYTES = 0x5U, /* Src/Dest data transfer size is 32 bytes every time */
	DMA_TRANSFER_SIZE_64_BYTES = 0x6U, /* Src/Dest data transfer size is 64 bytes every time */
	DMA_TRANSFER_SIZE_128_BYTES = 0x7U, /* Src/Dest data transfer size is 128 bytes every time */
} dma_transfer_size_e;

/**
 *  Map @width to ATTR register value
 *
 *  @width - transfer size in bytes
 *  Return: transfer size maped on ATTR register format
 */
static dma_transfer_size_e dma_width_mapping(uint32_t width)
{
	dma_transfer_size_e transfer_size = DMA_TRANSFER_SIZE_1_BYTES;

	switch (width) {
	/* width 8bit */
	case 1U:
		transfer_size = DMA_TRANSFER_SIZE_1_BYTES;
		break;
	/* width 16bit */
	case 2U:
		transfer_size = DMA_TRANSFER_SIZE_2_BYTES;
		break;
	/* width 32bit */
	case 4U:
		transfer_size = DMA_TRANSFER_SIZE_4_BYTES;
		break;
	/* width 64bit */
	case 8U:
		transfer_size = DMA_TRANSFER_SIZE_8_BYTES;
		break;
	/* width 128bit */
	case 16U:
		transfer_size = DMA_TRANSFER_SIZE_16_BYTES;
		break;
	/* width 256bit */
	case 32U:
		transfer_size = DMA_TRANSFER_SIZE_32_BYTES;
		break;
	/* width 512bit */
	case 64U:
		transfer_size = DMA_TRANSFER_SIZE_64_BYTES;
		break;
	/* width 1024bit */
	case 128U:
		transfer_size = DMA_TRANSFER_SIZE_128_BYTES;
		break;
	/* All the cases have been listed above, the default clause should not be reached. */
	default:
		break;
	}

	return transfer_size;
}

/**
 * Enable master replication and set secure/private attributes
 *
 * @dma_base_addr: edma address
 * @ch: edma channel used
 */
static void enable_dma_mst_rep(uint32_t dma_base_addr, uint8_t ch)
{
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);

	DMA->MP_CSR |= DMA_MIDR_SET_MASK;
	DMA->CH_PROT[ch] |= DMA_CH_EN_MIDR_MASK;
}

/**
 * Used to set the transfer size from source to destination per channel
 *
 * @dma_base_addr: edma address
 * @ch: edma channel used
 * @src_size: read size in  bytes from source
 * @dst_size: write size in bytes to destination
 * @size: size to transfer from src to dest (unit is byte)
 */
static void set_dma_transfer_bytes(uint32_t dma_base_addr, uint8_t ch,
				   uint32_t src_size, uint32_t dst_size)
{
	/* Change EDMA attribute */
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);
	dma_transfer_size_e src_transfer_size = dma_width_mapping(src_size);
	dma_transfer_size_e dst_transfer_size = dma_width_mapping(dst_size);
	DMA->TCD[ch].ATTR = DMA_ATTR_SSIZE(src_transfer_size) | DMA_ATTR_DSIZE(dst_transfer_size);
}

/**
 * Used to configure EDMA per channel before starting transfer
 *
 * @dma_base_addr: - edma address
 * @ch: edma channel
 * @src_addr: source address for read data
 * @src_width: source addr increase offset after each src read (unit is byte)
 * @dst_addr: destination address for write data
 * @dst_width: destination addr increase offset after each dst write (unit is byte)
 * @size: data size to transfer (unit is byte)
 * @mloop: major iterration count - citter & bitter reg
 * Return: Status of edma config 0/-1 success/fail
 */
static int set_dma(uint32_t dma_base_addr, uint8_t ch, uint32_t src_addr, uint32_t src_width,
		   uint32_t dst_addr, uint32_t dst_width, uint32_t size, uint32_t mloop)
{
	int ret = 0;
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);

	/* Check address alignment  */
	if ((src_addr % src_width) != 0)
	        return EDMA_SRC_ERR;

	if ((dst_addr % dst_width) != 0)
	        return EDMA_DST_ERR;

	/* Configure DMA */
	DMA->TCD[ch].SADDR = convert_to_dma_addr(src_addr & ~(CM33_28TH_BIT_MASK));
	DMA->TCD[ch].SOFF = src_width;
	DMA->TCD[ch].NBYTES_MLOFFNO = size;
	DMA->TCD[ch].SLAST_SDA = 0;
	DMA->TCD[ch].DADDR = convert_to_dma_addr(dst_addr & ~(CM33_28TH_BIT_MASK));
	DMA->TCD[ch].DOFF = dst_width;
	DMA->TCD[ch].CITER_ELINKNO = mloop;
	DMA->TCD[ch].DLAST_SGA = 0;
	DMA->TCD[ch].BITER_ELINKNO = mloop;
	/*
	 * Control status
	 * Disable request If this flag is set, the eDMA hardware automatically clears
	 * the corresponding ERQ bit when the current major iteration count reaches zero.
	 * 0b - No operation. The channel’s ERQ {H,L} bit is not affected.
	 * 1b - Clear the ERQ bit upon major loop completion, thus disabling hardware
	 * service requests. The channel’s ERQ {H,L} bit is cleared when the major loop is complete
	 */
	DMA->TCD[ch].CSR = 0x8;
	/* clear previous errors and done*/
	DMA->TCD[ch].CH_ES = DMA_CH_ES_ERR_MASK;
	DMA->TCD[ch].CH_CSR = DMA_CH_CSR_DONE_MASK;

	return ret;
}

/**
 * Start edma transfer
 *
 * @dma_base_addr: edma address
 * @ch: edma channel
 */
static void start_dma(uint32_t dma_base_addr, uint8_t ch)
{
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);

	/* start DMA transfer */
	DMA->TCD[ch].CSR |= DMA_CSR_START_MASK;
}

/**
 * Set Transfer Mode Control - TMC to Write-Only mode
 *
 * @dma_base_addr: edma address
 * @ch: edma channel
 */
static void dma_write_only(uint32_t dma_base_addr, uint8_t ch)
{
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);

	DMA->TCD[ch].CSR |= DMA_CH_WO_TMC_MODE;
}

/**
 * Clears TCT do default values
 *
 * @dma_base_addr: edma address
 * @ch: edma channel
 */
static void clr_dma(uint32_t dma_base_addr, uint8_t ch)
{
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);

	/* Configure DMA */
	DMA->TCD[ch].SADDR = 0;
	DMA->TCD[ch].SOFF = 0;
	DMA->TCD[ch].ATTR = 0;
	DMA->TCD[ch].NBYTES_MLOFFNO = 0;
	DMA->TCD[ch].SLAST_SDA = 0;
	DMA->TCD[ch].DADDR = 0;
	DMA->TCD[ch].DOFF = 0;
	DMA->TCD[ch].CITER_ELINKNO = 0;
	DMA->TCD[ch].DLAST_SGA = 0;
	DMA->TCD[ch].BITER_ELINKNO = 0;
	DMA->TCD[ch].CSR = 0;
	DMA->TCD[ch].CH_CSR = DMA_CH_CSR_DONE_MASK;
	DMA->TCD[ch].CH_ES = DMA_CH_ES_ERR_MASK;
	DMA->TCD[ch].CH_INT = DMA_CH_INT_INT_MASK;
}

/**
 * Wait until edma channel is active and return channel status
 * and check its status
 *
 * @dma_base_addr: edma address
 * @ch: edma channel
 * Return: Return channel status 0/-1 success/fail
 */
static int check_dma(uint32_t dma_base_addr, uint8_t ch)
{
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);

	return (DMA->TCD[ch].CH_ES & DMA_CH_ES_ERR_MASK) != 0U? -1: 0;
}

/**
 * Wait until major loop is completed on requested channel
 * and check its status
 *
 * @dma_base_addr: edma address
 * @ch: edma channel
 */
static void wait_major_loop(uint32_t dma_base_addr, uint8_t ch)
{
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);

	while ((DMA->TCD[ch].CH_CSR & DMA_CH_CSR_DONE_MASK) == 0U) {
	}
}

/**
 * Driver entrypoint
 */
struct edma_driver edma_ops = {
	.init = dma_dummy,
	.deinit = dma_dummy,
	.en_master_rep = enable_dma_mst_rep,
	.set_tbytes = set_dma_transfer_bytes,
	.configure = set_dma,
	.start_transfer = start_dma,
	.check_edma = check_dma,
	.wait_transfer = wait_major_loop,
	.clr_tcd = clr_dma,
	.write_only = dma_write_only,
};
