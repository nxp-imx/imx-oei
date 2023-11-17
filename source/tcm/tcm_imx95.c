// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2023 NXP
 */
#include <asm/arch/ccm_regs.h>
#include <asm/arch/clock.h>
#include <asm/types.h>

typedef struct
{
	unsigned int start_addr;
	unsigned int end_addr;
} mem_tbl;

/* WAKEUP.EDMA5 - Register Layout Typedef */
typedef struct {
    uint32_t MP_CSR;                            /**< Management Page Control Register, offset: 0x0 */
    uint32_t MP_ES;                             /**< Management Page Error Status Register, offset: 0x4 */
    uint32_t MP_INT_LOW;                        /**< Management Page Interrupt Request Status Register - Low, offset: 0x8 */
    uint32_t MP_INT_HIGH;                       /**< Management Page Interrupt Request Status Register- High, offset: 0xC */
    uint32_t MP_HRS_LOW;                        /**< Management Page Hardware Request Status Register - Low, offset: 0x10 */
    uint32_t MP_HRS_HIGH;                       /**< Management Page Hardware Request Status Register - High, offset: 0x14 */
    uint8_t RESERVED_0[232];
    uint32_t CH_GRPRI[64];                      /**< Channel Arbitration Group Register, array offset: 0x100, array step: 0x4 */
    uint8_t RESERVED_1[65024];
    struct {                                    /* offset: 0x10000,  */
        uint32_t CH_CSR;                        /**< Channel Control and Status Register, array offset: 0x10000,  */
        uint32_t CH_ES;                         /**< Channel Error Status Register, array offset: 0x10004,  */
        uint32_t CH_INT;                        /**< Channel Interrupt Status Register, array offset: 0x10008,  */
        uint32_t CH_SBR;                        /**< Channel System Bus Register, array offset: 0x1000C,  */
        uint32_t CH_PRI;                        /**< Channel Priority Register, array offset: 0x10010,  */
        uint32_t CH_MUX;                        /**< Channel Multiplexor Configuration, array offset: 0x10014,  */
        uint32_t CH_MATTR;                      /**< Memory Attributes Register, array offset: 0x10018,  */
        uint8_t RESERVED_0[4];                  /* array offset: 0x1001C */
        uint32_t SADDR;                         /**< TCD Source Address Register, array offset: 0x10020,  */
        uint32_t SADDR_HIGH;                    /**< TCD Source Address Register, array offset: 0x10024,  */
        uint16_t SOFF;                          /**< TCD Signed Source Address Offset Register, array offset: 0x10028,  */
        uint16_t ATTR;                          /**< TCD Transfer Attributes Register, array offset: 0x1002A,  */
        union {                                 /* offset: 0x1002C,  */
            uint32_t NBYTES_MLOFFNO;            /**< TCD Transfer Size without Minor Loop Offsets Register, array offset: 0x1002C,  */
            uint32_t NBYTES_MLOFFYES;           /**< TCD Transfer Size with Minor Loop Offsets Register, array offset: 0x1002C,  */
        };
        uint32_t SLAST_SDA;                     /**< TCD Last Source Address Adjustment / Store DADDR Address Register, array offset: 0x10030,  */
        uint32_t SLAST_SDA_HIGH;                /**< TCD Last Source Address Adjustment / Store DADDR Address Register, array offset: 0x10034,  */
        uint32_t DADDR;                         /**< TCD Destination Address Register, array offset: 0x10038,  */
        uint32_t DADDR_HIGH;                    /**< TCD Destination Address Register, array offset: 0x1003C,  */
        uint32_t DLAST_SGA;                     /**< TCD Last Destination Address Adjustment / Scatter Gather Address Register, array offset: 0x10040,  */
        uint32_t DLAST_SGA_HIGH;                /**< TCD Last Destination Address Adjustment / Scatter Gather Address Register, array offset: 0x10044,  */
        uint16_t DOFF;                          /**< TCD Signed Destination Address Offset Register, array offset: 0x10048,  */
        union {                                 /* offset: 0x1004A,  */
            uint16_t CITER_ELINKNO;             /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) Register, array offset: 0x1004A,  */
            uint16_t CITER_ELINKYES;            /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) Register, array offset: 0x1004A,  */
        };
        uint16_t CSR;                           /**< TCD Control and Status Register, array offset: 0x1004C,  */
        union {                                 /* offset: 0x1004E,  */
            uint16_t BITER_ELINKNO;             /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) Register, array offset: 0x1004E,  */
            uint16_t BITER_ELINKYES;            /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) Register, array offset: 0x1004E,  */
        };
        uint8_t RESERVED_1[0x8000 - 0x4E - 2];
    } TCD[64];
} DMA_Type;

/* WAKEUP.EDMA5_MP3 base address: 4221_0000h */
#define EDMA2_BASE_ADDR (0x42000000)

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

/*
 * TCM of Cortex-M7 when M7_CFG[TCM_SIZE] = 0b000
 * TCM_SIZE: M7 TCM SIZE
 *           000b - Regular TCM, 256 KB ITCM, and 256 KB DTCM
 *           001b - Double ITCM, 512 KB ITCM
 *           010b - Double DTCM, 512 KB DTCM
 *           011b - Reserved
 *           100b - HALF ITCM, 128 KB ITCM, and 384 KB DTCM
 *           101b - HALF DTCM, 384 KB ITCM, and 128 KB DTCM
 *           110b - Reserved
 *           111b - Reserved
 */
#define CM7_ITCM_START_ADDR (0x203C0000)
#define CM7_ITCM_END_ADDR (0x203FFFFF)
#define CM7_DTCM_START_ADDR (0x20400000)
#define CM7_DTCM_END_ADDR (0x2043FFFF)

/* From cortex-m33 view */
#define CM33_28TH_BIT_MASK (0x10000000)
#define CM33_ITCM_START_ADDR (0x0FF80000)
#define CM33_ITCM_END_ADDR   (0x0FFFFFFF)
#define CM33_DTCM_START_ADDR (0x20000000)
#define CM33_DTCM_END_ADDR (0x2007FFFF)

/* From dma view */
#define CM33_ITCM_START_ADDR_FROM_DMA_VIEW  (0x20180000)
#define CM33_ITCM_END_ADDR_FROM_DMA_VIEW    (0x201FFFFF)
#define CM33_DTCM_START_ADDR_FROM_DMA_VIEW  (0x20200000)
#define CM33_DTCM_END_ADDR_FROM_DMA_VIEW    (0x2027FFFF)


#define OCRAM_START_ADDR 0x20480000
#define OCRAM_SOURCE_DATA_SIZE (128 * 1024) /* edma copy ocram's data(data is 0) to tcm */

#define SRC_M7MIX_SLICE_SW_CTRL (0x44464820UL)

static void debug(const char *fmt_s, ...)
{

}

static void enable_dma_clock(void)
{
    /* edma2 clock root is bus wakeup and wakeup axi */
    ccm_clk_root_cfg(BUS_WAKEUP_CLK_ROOT, SYS_PLL_PFD1_DIV2, 3); /* 400 MHz / 3 = 133.33 MHz(SYS_PLL_PFD1_DIV2 is 400 MHz?) */
    ccm_clk_root_cfg(WAKEUP_AXI_CLK_ROOT, SYS_PLL_PFD1, 4); /* 800 MHz / 4 = 200 MHz(SYS_PLL_PFD1 is 800 MHz?) */
}

static void disable_dma_clock(void)
{

}


static unsigned int convert_to_dma_addr(unsigned int cpu_view_addr)
{
	unsigned int dst_addr = cpu_view_addr;

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
/*! @brief DMA transfer configuration */
typedef enum
{
    DMA_TRANSFER_SIZE_1_BYTES = 0x0U, /*!< Source/Destination data transfer size is 1 byte every time */
    DMA_TRANSFER_SIZE_2_BYTES = 0x1U, /*!< Source/Destination data transfer size is 2 bytes every time */
    DMA_TRANSFER_SIZE_4_BYTES = 0x2U, /*!< Source/Destination data transfer size is 4 bytes every time */
    DMA_TRANSFER_SIZE_8_BYTES = 0x3U, /*!< Source/Destination data transfer size is 8 bytes every time */
    DMA_TRANSFER_SIZE_16_BYTES = 0x4U, /*!< Source/Destination data transfer size is 16 bytes every time */
    DMA_TRANSFER_SIZE_32_BYTES = 0x5U, /*!< Source/Destination data transfer size is 32 bytes every time */
    DMA_TRANSFER_SIZE_64_BYTES = 0x6U, /*!< Source/Destination data transfer size is 64 bytes every time */
    DMA_TRANSFER_SIZE_128_BYTES = 0x7U, /*!< Source/Destination data transfer size is 128 bytes every time */
} dma_transfer_size_e;

static dma_transfer_size_e dma_width_mapping(unsigned int width)
{
    dma_transfer_size_e transfer_size = DMA_TRANSFER_SIZE_1_BYTES;

    /* map width to register value */
    switch (width)
    {
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
        default:
            /* All the cases have been listed above, the default clause should not be reached. */
            break;
    }

    return transfer_size;
}

/*
 * size: unit is byte
 * src_width: eDMA transfer source address's data width(unit is byte)
 * dst_width: eDMA transfer destination address's data width(unit is byte)
 */
static int set_dma(unsigned int dma_base_addr, unsigned int src_addr, unsigned int src_width, unsigned int dst_addr, unsigned int dst_width, unsigned int size)
{
	int ret = -1;
	debug("%s: %d\n", __func__, __LINE__);

	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);
	dma_transfer_size_e src_transfer_size = dma_width_mapping(src_width);
	dma_transfer_size_e dst_transfer_size = dma_width_mapping(dst_width);
	
	/* Check address alignment  */
	if ((src_addr % src_width) != 0)
	        return ret;
	if ((dst_addr % dst_width) != 0)
	        return ret;
	
	/* Configure DMA */
	DMA->TCD[0].SADDR = convert_to_dma_addr(src_addr & ~(CM33_28TH_BIT_MASK));
	debug("SADDR: 0x%x val: 0x%x\n", &(DMA->TCD[0].SADDR), DMA->TCD[0].SADDR);
	DMA->TCD[0].SOFF = src_width;
	debug("SOFF: 0x%x val: 0x%x\n", &(DMA->TCD[0].SOFF), DMA->TCD[0].SOFF);
	DMA->TCD[0].ATTR = DMA_ATTR_SSIZE(src_transfer_size) | DMA_ATTR_DSIZE(dst_transfer_size);
	//DMA->TCD[0].ATTR = 0x0203;
	debug("ATTR: 0x%x val: 0x%x\n", &(DMA->TCD[0].ATTR), DMA->TCD[0].ATTR);
	DMA->TCD[0].NBYTES_MLOFFNO = size;
	debug("NBYTES_MLOFFNO: 0x%x val: 0x%x\n", &(DMA->TCD[0].NBYTES_MLOFFNO), DMA->TCD[0].NBYTES_MLOFFNO);
	DMA->TCD[0].SLAST_SDA = 0;
	debug("SLAST_SDA: 0x%x val: 0x%x\n", &(DMA->TCD[0].SLAST_SDA), DMA->TCD[0].SLAST_SDA);
	DMA->TCD[0].DADDR = convert_to_dma_addr(dst_addr & ~(CM33_28TH_BIT_MASK));
	debug("DADDR: 0x%x val: 0x%x\n", &(DMA->TCD[0].DADDR), DMA->TCD[0].DADDR);
	DMA->TCD[0].DOFF = dst_width;
	debug("DOFF: 0x%x val: 0x%x\n", &(DMA->TCD[0].DOFF), DMA->TCD[0].DOFF);
	DMA->TCD[0].CITER_ELINKNO = 2;
	debug("CITER_ELINKNO: 0x%x val: 0x%x\n", &(DMA->TCD[0].CITER_ELINKNO), DMA->TCD[0].CITER_ELINKNO);
	DMA->TCD[0].DLAST_SGA = 0;
	debug("DLAST_SGA: 0x%x val: 0x%x\n", &(DMA->TCD[0].DLAST_SGA), DMA->TCD[0].DLAST_SGA);
	DMA->TCD[0].BITER_ELINKNO = 2;
	debug("BITER_ELINKNO: 0x%x val: 0x%x\n", &(DMA->TCD[0].BITER_ELINKNO), DMA->TCD[0].BITER_ELINKNO);
	/*
	 *
	 * Control status
	 *
	 * Disable requestIf this flag is set, the eDMA hardware automatically clears the corresponding ERQ bit when the current major iteration count reaches zero.
	 * 0b - No operation. The channel’s ERQ {H,L} bit is not affected.
	 * 1b - Clear the ERQ bit upon major loop completion, thus disabling hardware service requests. The channel’s ERQ {H,L} bit is cleared when the major loop is complete
	 */
	DMA->TCD[0].CSR = 0x8;
	debug("CSR: 0x%x val: 0x%x\n", &(DMA->TCD[0].CSR), DMA->TCD[0].CSR);
	
	/* clear previous errors and done*/
	DMA->TCD[0].CH_ES = DMA_CH_ES_ERR_MASK;
	DMA->TCD[0].CH_CSR = DMA_CH_CSR_DONE_MASK;
	
	/*
	 * The following instructions are needed to guarantee the dma channel is
	 * active on the first test of the while() loop
	 */
	//__asm("DSB;");
	//__asm("ISB;");
	ret = 0;
	
	return ret;
}

static void start_dma(uint32_t dma_base_addr)
{
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);
	
	/* start DMA transfer */
	DMA->TCD[0].CSR = DMA_CSR_START_MASK;
	debug("CSR: 0x%x val: 0x%x\n", &(DMA->TCD[0].CSR), DMA->TCD[0].CSR);
}

static void clr_dma(uint32_t dma_base_addr)
{
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);
	
	debug("%s: %d\n", __func__, __LINE__);
	
	/* Configure DMA */
	DMA->TCD[0].SADDR = 0;
	DMA->TCD[0].SOFF = 0;
	DMA->TCD[0].ATTR = 0;
	DMA->TCD[0].NBYTES_MLOFFNO = 0;
	DMA->TCD[0].SLAST_SDA = 0;
	DMA->TCD[0].DADDR = 0;
	DMA->TCD[0].DOFF = 0;
	DMA->TCD[0].CITER_ELINKNO = 0;
	DMA->TCD[0].DLAST_SGA = 0;
	DMA->TCD[0].BITER_ELINKNO = 0;
	DMA->TCD[0].CSR = 0;
	DMA->TCD[0].CH_CSR = DMA_CH_CSR_DONE_MASK;
	DMA->TCD[0].CH_ES = DMA_CH_ES_ERR_MASK;
	DMA->TCD[0].CH_INT = DMA_CH_INT_INT_MASK;
}

static int check_dma(uint32_t dma_base_addr)
{
	DMA_Type *DMA = (DMA_Type *)(dma_base_addr);
	
	int status = 0;
	
	debug("%s: %d\n", __func__, __LINE__);
	
	/* Poll the dma channel until it completes */
	while ((DMA->TCD[0].CH_CSR & DMA_CH_CSR_ACTIVE_MASK) != 0U) {
	}
	
	debug("DMA->TCD[0].CH_ES val: 0x%x\n", DMA->TCD[0].CH_ES);
	debug("DMA_CH_ES_ERR_MASK is: 0x%x\n", DMA_CH_ES_ERR_MASK);
	
	if ((DMA->TCD[0].CH_ES & DMA_CH_ES_ERR_MASK) != 0U) {
	    status = -1;
	    debug("%s: %d failed to check DMA status\n", __func__, __LINE__);
	} else {
	    status = 0;
	}
	
	return status;
}

void power_up_m7mix(void)
{
	/* Do we need power up m7 mix? actually cm33 bootrom/ca55 bootrom will power up m7 mix when contaimer image include m7 firmware */
	if (*(volatile unsigned int *)SRC_M7MIX_SLICE_SW_CTRL != 0)
		*(volatile unsigned int *)SRC_M7MIX_SLICE_SW_CTRL = 0U; 
}

static int tcm_init_by_dma(void)
{
	int ret = -1;
/*	unsigned int itcm_size = CM7_ITCM_END_ADDR -  CM7_ITCM_START_ADDR + 1;
	unsigned int dtcm_size = CM7_DTCM_END_ADDR -  CM7_DTCM_START_ADDR + 1; */
	u32 i = 0;
	u32 j = 0;
	mem_tbl tcm_tbl[] = {
					{CM7_ITCM_START_ADDR, CM7_ITCM_END_ADDR},
					{CM7_DTCM_START_ADDR, CM7_DTCM_END_ADDR}
				};
	unsigned int transfer_size = 0;

	enable_dma_clock();
	power_up_m7mix();
	for (i = 0; i < sizeof(tcm_tbl) / sizeof(mem_tbl); i++)
	{
		for (j = tcm_tbl[i].start_addr; ;)
		{
			if (j + OCRAM_SOURCE_DATA_SIZE <=  tcm_tbl[i].end_addr)
			{
				transfer_size = OCRAM_SOURCE_DATA_SIZE;
			}
			else
			{
				transfer_size = tcm_tbl[i].end_addr - j + 1;
			}

			ret = set_dma(EDMA2_BASE_ADDR, OCRAM_START_ADDR, 8, j, 8, transfer_size);
			if (ret != 0)
			{
				debug("failed to set dma\n", i);
				goto exit;
			}
			
			start_dma(EDMA2_BASE_ADDR);
			ret = check_dma(EDMA2_BASE_ADDR);
			if (ret != 0)
			{
				debug("failed to init tcm_tbl[%d]\n", i);
				goto exit;
			}
			clr_dma(EDMA2_BASE_ADDR);
			j += transfer_size;
			if ( j == tcm_tbl[i].end_addr + 1)
			{
				break;
			}
		}
	}
exit:
	clr_dma(EDMA2_BASE_ADDR);
	disable_dma_clock();
	
	return ret;
}

int tcm_init(void)
{
	return tcm_init_by_dma();
}
