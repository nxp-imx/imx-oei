// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2023-2024 NXP
 */

#include <asm/types.h>

/* WAKEUP.EDMA5_MP3 base address: 4221_0000h */
#define EDMA2_BASE_ADDR (0x42000000)

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
#define SRC_M7MIX_SLICE_FUNC_STAT (0x444648b4UL)
/* WAKEUP.EDMA5 - Register Layout Typedef */

typedef struct {
	__IOU32 MP_CSR;                          /** Management Page Control Register, offset: 0x0 */
	__IOU32 MP_ES;                           /** Management Page Error Status Register, offset: 0x4 */
	__IOU32 MP_INT_LOW;                      /** Management Page Interrupt Request Status Register - Low, offset: 0x8 */
	__IOU32 MP_INT_HIGH;                     /** Management Page Interrupt Request Status Register- High, offset: 0xC */
	__IOU32 MP_HRS_LOW;                      /** Management Page Hardware Request Status Register - Low, offset: 0x10 */
	__IOU32 MP_HRS_HIGH;                     /** Management Page Hardware Request Status Register - High, offset: 0x14 */
	uint8_t reserved_0[8];
	__IOU32 MP_STOPCH;                       /** Management Page Stop Channel Register - High, offset: 0x20 */
	uint8_t reserved_1[12];
	__IOU32 MP_SSR_LOW;                      /** Management Page Stop Status Register - High, offset: 0x30 */
	__IOU32 MP_SSR_HIGH;                     /** Management Page Stop Status Register - High, offset: 0x34 */
	uint8_t reserved_2[200];
	__IOU32 CH_GRPRI[64];                    /** Channel Arbitration Group Register, offset: 0x100, array step: 0x4 */
	__IOU32 CH_MUX[64];                      /** Channel Multiplexor Configuration, offset: 0x200, array step: 0x4 */
	uint8_t reserved_3[256];
	__IOU32 CH_PROT[64];                     /** Channel Protection Register, offset: 0x400, array step: 0x4 */
	uint8_t reserved_4[64256];
	struct {                                 /* offset: 0x10000,  */
		__IOU32 CH_CSR;                  /** Channel Control and Status Register, offset: 0x10000,  */
		__IOU32 CH_ES;                   /** Channel Error Status Register, offset: 0x10004,  */
		__IOU32 CH_INT;                  /** Channel Interrupt Status Register, offset: 0x10008,  */
		__IOU32 CH_SBR;                  /** Channel System Bus Register, offset: 0x1000C,  */
		__IOU32 CH_PRI;                  /** Channel Priority Register, offset: 0x10010,  */
		__IOU32 CH_MUX;                  /** Channel Multiplexor Configuration, offset: 0x10014,  */
		__IOU32 CH_MATTR;                /** Memory Attributes Register, offset: 0x10018,  */
		uint8_t RESERVED_0[4];           /* offset: 0x1001C */
		__IOU32 SADDR;                   /** TCD Source Address Register, offset: 0x10020,  */
		__IOU32 SADDR_HIGH;              /** TCD Source Address Register, offset: 0x10024,  */
		__IOU16 SOFF;                    /** TCD Signed Source Address Offset Register, offset: 0x10028,  */
		__IOU16 ATTR;                    /** TCD Transfer Attributes Register, offset: 0x1002A,  */
		union {                          /* offset: 0x1002C,  */
			__IOU32 NBYTES_MLOFFNO;  /** TCD Transfer Size without Minor Loop Offsets Register, offset: 0x1002C,  */
			__IOU32 NBYTES_MLOFFYES; /** TCD Transfer Size with Minor Loop Offsets Register, offset: 0x1002C,  */
		};
		__IOU32 SLAST_SDA;               /** TCD Last Source Address Adjustment / Store DADDR Address Register, offset: 0x10030,  */
		__IOU32 SLAST_SDA_HIGH;          /** TCD Last Source Address Adjustment / Store DADDR Address Register, offset: 0x10034,  */
		__IOU32 DADDR;                   /** TCD Destination Address Register, offset: 0x10038,  */
		__IOU32 DADDR_HIGH;              /** TCD Destination Address Register, offset: 0x1003C,  */
		__IOU32 DLAST_SGA;               /** TCD Last Destination Address Adjustment / Scatter Gather Address Register, offset: 0x10040,  */
		__IOU32 DLAST_SGA_HIGH;          /** TCD Last Destination Address Adjustment / Scatter Gather Address Register, offset: 0x10044,  */
		__IOU16 DOFF;                    /** TCD Signed Destination Address Offset Register, offset: 0x10048,  */
		union {                          /* offset: 0x1004A,  */
			__IOU16 CITER_ELINKNO;   /** TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) Register, offset: 0x1004A,  */
			__IOU16 CITER_ELINKYES;  /** TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) Register, offset: 0x1004A,  */
		};
		__IOU16 CSR;                     /** TCD Control and Status Register, rray offset: 0x1004C,  */
		union {                          /**  offset: 0x1004E,  **/
			__IOU16 BITER_ELINKNO;   /** TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) Register, offset: 0x1004E,*/
			__IOU16 BITER_ELINKYES;  /** TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) Register, offset: 0x1004E,*/
		};
		uint8_t RESERVED_1[0x8000 - 0x4E - 2];
	} TCD[64];
} DMA_Type;

uint32_t convert_to_dma_addr(uint32_t cpu_view_addr);
