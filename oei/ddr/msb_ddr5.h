/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2024 NXP
 */
#ifndef __MSB_DDR5_H
#define __MSB_DDR5_H

#include <stdint.h>

typedef struct _MSB_DDR5_t {
   uint8_t  Reserved_00[0x10];  /** 0x00 */
   uint16_t SequenceCtrl;       /** 0x10 */
   uint8_t  Reserved_01[0x7];   /** 0x12 */
   uint8_t  Quickboot;          /** 0x19 */
   uint8_t  Reserved_02[0x19];  /** 0x1a */
   uint8_t  TrainedVREFCA_A0;   /** 0x33 */
   uint8_t  TrainedVREFCA_A1;   /** 0x34 */
   uint8_t  TrainedVREFDQ_A0;   /** 0x35 */
   uint8_t  TrainedVREFDQ_A1;   /** 0x36 */
   uint8_t  Reserved_03[0x17];  /** 0x37 */
   uint8_t  TrainedVREFCA_B0;   /** 0x4e */
   uint8_t  TrainedVREFCA_B1;   /** 0x4f */
   uint8_t  TrainedVREFDQ_B0;   /** 0x50 */
   uint8_t  TrainedVREFDQ_B1;   /** 0x51 */
   uint8_t  Reserved_04[0x1c];  /** 0x52 */
   uint8_t  MR12_A0;            /** 0x6e */
   uint8_t  MR12_A1;            /** 0x6f */
   uint8_t  MR12_B0;            /** 0x70 */
   uint8_t  MR12_B1;            /** 0x71 */
   uint8_t  Reserved_05[0x4];   /** 0x72 */
   uint8_t  MR14_A0;            /** 0x76 */
   uint8_t  MR14_A1;            /** 0x77 */
   uint8_t  MR14_B0;            /** 0x78 */
   uint8_t  MR14_B1;            /** 0x79 */
   uint8_t  MR15_A0;            /** 0x7a */
   uint8_t  MR15_A1;            /** 0x7b */
   uint8_t  MR15_B0;            /** 0x7c */
   uint8_t  MR15_B1;            /** 0x7d */
   uint8_t  Reserved_06[0x1c];  /** 0x7e */
   uint8_t  MR24_A0;            /** 0x9a */
   uint8_t  MR24_A1;            /** 0x9b */
   uint8_t  MR24_B0;            /** 0x9c */
   uint8_t  MR24_B1;            /** 0x9d */
   uint8_t  Reserved_07[0x10];  /** 0x9e */
   uint8_t  MR30_A0;            /** 0xae */
   uint8_t  MR30_A1;            /** 0xaf */
   uint8_t  MR30_B0;            /** 0xb0 */
   uint8_t  MR30_B1;            /** 0xb1 */
   uint8_t  Reserved_08[0x1e];  /** 0xb2 */
   uint8_t  TrainedVREFDQU_A0;  /** 0xd0 */
   uint8_t  TrainedDRAMDFE_A0;  /** 0xd1 */
   uint8_t  TrainedDRAMDCA_A0;  /** 0xd2 */
   uint8_t  Reserved_09[2];     /** 0xd3 */
   uint8_t  TrainedVREFDQU_A1;  /** 0xd5 */
   uint8_t  TrainedDRAMDFE_A1;  /** 0xd6 */
   uint8_t  TrainedDRAMDCA_A1;  /** 0xd7 */
   uint8_t  Reserved_10[2];     /** 0xd8 */
   uint8_t  TrainedVREFDQU_B0;  /** 0xda */
   uint8_t  TrainedDRAMDFE_B0;  /** 0xdb */
   uint8_t  TrainedDRAMDCA_B0;  /** 0xdc */
   uint8_t  Reserved_11[2];     /** 0xdd */
   uint8_t  TrainedVREFDQU_B1;  /** 0xdf */
   uint8_t  TrainedDRAMDFE_B1;  /** 0xe0 */
   uint8_t  TrainedDRAMDCA_B1;  /** 0xe1 */
   uint8_t  Reserved_12[0x4e];  /** 0xe2 */
   uint16_t QBPllUPllProg0;     /** 0x130 */
   uint16_t QBPllUPllProg1;     /** 0x132 */
   uint16_t QBPllUPllProg2;     /** 0x134 */
   uint16_t QBPllUPllProg3;     /** 0x136 */
   uint16_t QBPllCtrl1;         /** 0x138 */
   uint16_t QBPllCtrl4;         /** 0x13a */
   uint16_t QBPllCtrl5;         /** 0x13c */
   uint8_t  Reserved_13[0x2c2]; /** 0x13e..0x3ff */
} __attribute__ ((packed)) MSB_DDR5_t;

#endif
