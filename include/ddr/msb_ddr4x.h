/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */
#ifndef __MSB_DDR4X_H
#define __MSB_DDR4X_H

typedef struct _MSB_DDR4X_t {
   uint8_t  Reserved_00[0x10];  /** 0x00 */
   uint16_t SequenceCtrl;       /** 0x10 */
   uint8_t  Reserved_01[0x7];   /** 0x12 */
   uint8_t  Quickboot;          /** 0x19 */
   uint8_t  Reserved_02[0x1d];  /** 0x1a */
   uint8_t  MR12_A0;            /** 0x37 */
   uint8_t  Reserved_03[0x01];  /** 0x38 */
   uint8_t  MR14_A0;            /** 0x39 */
   uint8_t  Reserved_04[0x09];  /** 0x3a */
   uint8_t  MR12_A1;            /** 0x43 */
   uint8_t  Reserved_05[0x01];  /** 0x44 */
   uint8_t  MR14_A1;            /** 0x45 */
   uint8_t  Reserved_06[0x05];  /** 0x46 */
   uint8_t  TrainedVREFCA_A0;   /** 0x4b */
   uint8_t  TrainedVREFCA_A1;   /** 0x4c */
   uint8_t  TrainedVREFDQ_A0;   /** 0x4d */
   uint8_t  TrainedVREFDQ_A1;   /** 0x4e */
   uint8_t  Reserved_07[0x1b];  /** 0x4f */
   uint8_t  MR12_B0;            /** 0x6a */
   uint8_t  Reserved_08[0x01];  /** 0x6b */
   uint8_t  MR14_B0;            /** 0x6c */
   uint8_t  Reserved_09[0x09];  /** 0x6d */
   uint8_t  MR12_B1;            /** 0x76 */
   uint8_t  Reserved_10[0x01];  /** 0x77 */
   uint8_t  MR14_B1;            /** 0x78 */
   uint8_t  Reserved_11[0x05];  /** 0x79 */
   uint8_t  TrainedVREFCA_B0;   /** 0x7e */
   uint8_t  TrainedVREFCA_B1;   /** 0x7f */
   uint8_t  TrainedVREFDQ_B0;   /** 0x80 */
   uint8_t  TrainedVREFDQ_B1;   /** 0x81 */
   uint8_t  Reserved_12[0xae];  /** 0x82 */
   uint16_t QBPllUPllProg0;     /** 0x130 */
   uint16_t QBPllUPllProg1;     /** 0x132 */
   uint16_t QBPllUPllProg2;     /** 0x134 */
   uint16_t QBPllUPllProg3;     /** 0x136 */
   uint16_t QBPllCtrl1;         /** 0x138 */
   uint16_t QBPllCtrl4;         /** 0x13a */
   uint16_t QBPllCtrl5;         /** 0x13c */
   uint8_t  Reserved_13[0x2c2]; /** 0x13e..0x3ff */
} __attribute__ ((packed)) MSB_DDR4X_t;

#endif
