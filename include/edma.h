// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2023-2024 NXP
 */
#include <asm/io.h>

#define EDMA_CH(ch) (ch)
#define EDMA_CH0 0
#define EDMA_CH1 1

/* errors in case edma src/dst address misalignment */
#define EDMA_SRC_ERR -1
#define EDMA_DST_ERR -2

#define DMA_MIDR_SET_MASK                        BIT(7)
#define DMA_CH_WO_TMC_MODE                       BIT(15)
#define DMA_CH_EN_MIDR_MASK                     (BIT(16) | BIT(14))

#define DMA_ATTR_DSIZE_MASK                     (0x7U)
#define DMA_ATTR_DSIZE_SHIFT                    (0U)
/*! DSIZE - Destination data transfer size
 *  0b000..8-bit
 *  0b001..16-bit
 *  0b010..32-bit
 *  0b011..64-bit
 *  0b100..16-byte
 *  0b101..32-byte
 *  0b110..64-byte
 *  0b111..128-byte
 */
#define DMA_ATTR_DSIZE(x)                       (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_DSIZE_SHIFT)) & DMA_ATTR_DSIZE_MASK)

#define DMA_ATTR_SSIZE_MASK                     (0x700U)
#define DMA_ATTR_SSIZE_SHIFT                    (8U)
/*! SSIZE - Source data transfer size
 *  0b000..8-bit
 *  0b001..16-bit
 *  0b010..32-bit
 *  0b011..64-bit
 *  0b100..16-byte
 *  0b101..32-byte
 *  0b110..64-byte
 *  0b111..128-byte
 */
#define DMA_ATTR_SSIZE(x)                       (((uint16_t)(((uint16_t)(x)) << DMA_ATTR_SSIZE_SHIFT)) & DMA_ATTR_SSIZE_MASK)

#define DMA_CH_ES_ERR_MASK                      (0x80000000U)
#define DMA_CH_CSR_DONE_MASK                    (0x40000000U)
#define DMA_CSR_START_MASK                      (0x1U)
#define DMA_CH_INT_INT_MASK                     (0x1U)
#define DMA_CH_CSR_ACTIVE_MASK                  (0x80000000U)
#define DMA_CH_CSR_DONE_MASK                    (0x40000000U)

/**
 * struct edma_driver  - edma driver operations entries.
 *
 * @init: initialise the clocks used by the edma
 * @deinit: deinitialise the edma.
 * @en_master_rep: enable master id replication
 * @set_tbytes: sets the source and destination transfer size (ATTR register)
 * @configure: configure the edma channel
 * @start_transfer: Starts the transfer after configuring and checking the edma channel
 * @check_edma: checks for errors after starting the transfer
 * @wait_transfer: Waits until the the major loop is finished - DONE bit set to 1 from CSR
 * @clr_tcd: clear the edma channel configuration
 * @write_only: Set the EDMA TMC to write-only, for which the source address is
 *              read once and all subsequent writes to the destination use that data.
 */
struct edma_driver {
	void (*init)(void);
	void (*deinit)(void);
	void (*en_master_rep)(uint32_t dma_base_addr, uint8_t ch);
	void (*set_tbytes)(uint32_t dma_base_addr, uint8_t ch,
			uint32_t src_size, uint32_t dst_size);
	int (*configure)(uint32_t dma_base_addr, uint8_t ch, uint32_t src_addr, uint32_t src_width,
			uint32_t dst_addr, uint32_t dst_width, uint32_t size, uint32_t mloop);
	void (*start_transfer)(uint32_t dma_base_addr, uint8_t ch);
	int (*check_edma)(uint32_t dma_base_addr, uint8_t ch);
	void (*wait_transfer)(uint32_t dma_base_addr, uint8_t ch);
	void (*clr_tcd)(uint32_t dma_base_addr, uint8_t ch);
	void (*write_only) (uint32_t dma_base_addr, uint8_t ch);
};

extern struct edma_driver edma_ops;
