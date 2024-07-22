/*
** ###################################################################
**     Processors:          MIMX9494AVKXD_cm33_core0
**                          MIMX9494AVKXJ_cm33_core0
**                          MIMX9494AVKXM_cm33_core0
**                          MIMX9494AVMXD_cm33_core0
**                          MIMX9494AVMXJ_cm33_core0
**                          MIMX9494AVMXM_cm33_core0
**                          MIMX9494CVKXD_cm33_core0
**                          MIMX9494CVKXJ_cm33_core0
**                          MIMX9494CVKXM_cm33_core0
**                          MIMX9494CVMXD_cm33_core0
**                          MIMX9494CVMXJ_cm33_core0
**                          MIMX9494CVMXM_cm33_core0
**                          MIMX9494DVKXD_cm33_core0
**                          MIMX9494DVKXJ_cm33_core0
**                          MIMX9494DVKXM_cm33_core0
**                          MIMX9494DVMXD_cm33_core0
**                          MIMX9494DVMXJ_cm33_core0
**                          MIMX9494DVMXM_cm33_core0
**                          MIMX9494XVKXD_cm33_core0
**                          MIMX9494XVKXJ_cm33_core0
**                          MIMX9494XVKXM_cm33_core0
**                          MIMX9494XVMXD_cm33_core0
**                          MIMX9494XVMXJ_cm33_core0
**                          MIMX9494XVMXM_cm33_core0
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**
**     Reference manual:    iMX943RM rev1 draftK
**     Version:             rev. 1.0, 2023-11-01
**     Build:               b240315
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MIMX9494_cm33_core0
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2023-11-01)
**         Initial version.
**         core name and core alias name
**         +---------------------------------------------------------------------+
**         | core name  |                  core alias name                       |
**         +---------------------------------------------------------------------+
**         | cm33_core0 | m33, cm33                                              |
**         +---------------------------------------------------------------------+
**         | cm33_core1 | m33_2, cm33_2, cm33_sync, netcmix_cm33                 |
**         +---------------------------------------------------------------------+
**         | cm7_core0  | m7, cm7                                                |
**         +---------------------------------------------------------------------+
**         | cm7_core1  | m7_2, cm7_2                                            |
**         +---------------------------------------------------------------------+
**         | ca55_core0 | a55, ca55, a55_0, ca55_0                               |
**         +---------------------------------------------------------------------+
**         | ca55_core1 | a55, ca55, a55_1, ca55_1                               |
**         +---------------------------------------------------------------------+
**         | ca55_core2 | a55, ca55, a55_2, ca55_2                               |
**         +---------------------------------------------------------------------+
**         | ca55_core3 | a55, ca55, a55_3, ca55_3                               |
**         +---------------------------------------------------------------------+
**
** ###################################################################
*/

/*!
 * @file MIMX9494_MU.h
 * @version 1.0
 * @date 2023-11-01
 * @brief CMSIS Peripheral Access Layer for MIMX9494_MU
 *
 * CMSIS Peripheral Access Layer for MIMX9494
 */

/* Prevention from multiple including the same memory map */
#if !defined(MIMX9494_MU_H_)  /* Check if memory map has not been already included */
#define MIMX9494_MU_H_

#include "MIMX943_COMMON.h"
/*!
 * @brief Core boot mode.
 */
typedef enum _mu_core_boot_mode
{
    kMU_CoreBootFromAddr0 = 0x00U, /*!< Boot from 0x00.      */
    kMU_CoreBootFromFlash = 0x01U, /*!< Boot from Flash base. */
    kMU_CoreBootFromItcm  = 0x02U, /*!< Boot from ITCM base. */
} mu_core_boot_mode_t;


/* ----------------------------------------------------------------------------
   -- MU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MU_Peripheral_Access_Layer MU Peripheral Access Layer
 * @{
 */

/** MU - Register Layout Typedef */
typedef struct {
  __I  uint32_t VER;                               /**< Version ID, offset: 0x0 */
  __I  uint32_t PAR;                               /**< Parameter, offset: 0x4 */
  __IO uint32_t CR;                                /**< Control, offset: 0x8 */
  __IO uint32_t SR;                                /**< Status, offset: 0xC */
  __IO uint32_t CCR0;                              /**< Core Control 0, offset: 0x10 */
  __IO uint32_t CIER0;                             /**< Core Interrupt Enable 0, offset: 0x14 */
  __IO uint32_t CSSR0;                             /**< Core Sticky Status 0, offset: 0x18 */
  __I  uint32_t CSR0;                              /**< Core Status 0, offset: 0x1C, not available in all instances (available on 1032 out of 1056) */
       uint8_t RESERVED_0[224];
  __IO uint32_t FCR;                               /**< Flag Control, offset: 0x100 */
  __I  uint32_t FSR;                               /**< Flag Status, offset: 0x104 */
       uint8_t RESERVED_1[8];
  __IO uint32_t GIER;                              /**< General-Purpose Interrupt Enable, offset: 0x110 */
  __IO uint32_t GCR;                               /**< General-Purpose Control, offset: 0x114 */
  __IO uint32_t GSR;                               /**< General-purpose Status, offset: 0x118 */
       uint8_t RESERVED_2[4];
  __IO uint32_t TCR;                               /**< Transmit Control, offset: 0x120 */
  __I  uint32_t TSR;                               /**< Transmit Status, offset: 0x124 */
  __IO uint32_t RCR;                               /**< Receive Control, offset: 0x128 */
  __I  uint32_t RSR;                               /**< Receive Status, offset: 0x12C */
       uint8_t RESERVED_3[208];
  __O  uint32_t TR[4];                             /**< Transmit, array offset: 0x200, array step: 0x4 */
       uint8_t RESERVED_4[112];
  __I  uint32_t RR[4];                             /**< Receive, array offset: 0x280, array step: 0x4 */
} MU_Type;

/* ----------------------------------------------------------------------------
   -- MU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MU_Register_Masks MU Register Masks
 * @{
 */

/*! @name VER - Version ID */
/*! @{ */

#define MU_VER_FEATURE_MASK                      (0xFFFFU)
#define MU_VER_FEATURE_SHIFT                     (0U)
/*! FEATURE - Feature Set Number */
#define MU_VER_FEATURE(x)                        (((uint32_t)(((uint32_t)(x)) << MU_VER_FEATURE_SHIFT)) & MU_VER_FEATURE_MASK)

#define MU_VER_MINOR_MASK                        (0xFF0000U)
#define MU_VER_MINOR_SHIFT                       (16U)
/*! MINOR - Minor Version Number */
#define MU_VER_MINOR(x)                          (((uint32_t)(((uint32_t)(x)) << MU_VER_MINOR_SHIFT)) & MU_VER_MINOR_MASK)

#define MU_VER_MAJOR_MASK                        (0xFF000000U)
#define MU_VER_MAJOR_SHIFT                       (24U)
/*! MAJOR - Major Version Number */
#define MU_VER_MAJOR(x)                          (((uint32_t)(((uint32_t)(x)) << MU_VER_MAJOR_SHIFT)) & MU_VER_MAJOR_MASK)
/*! @} */

/*! @name PAR - Parameter */
/*! @{ */

#define MU_PAR_TR_NUM_MASK                       (0xFFU)
#define MU_PAR_TR_NUM_SHIFT                      (0U)
/*! TR_NUM - Transmit Register Number */
#define MU_PAR_TR_NUM(x)                         (((uint32_t)(((uint32_t)(x)) << MU_PAR_TR_NUM_SHIFT)) & MU_PAR_TR_NUM_MASK)

#define MU_PAR_RR_NUM_MASK                       (0xFF00U)
#define MU_PAR_RR_NUM_SHIFT                      (8U)
/*! RR_NUM - Receive Register Number */
#define MU_PAR_RR_NUM(x)                         (((uint32_t)(((uint32_t)(x)) << MU_PAR_RR_NUM_SHIFT)) & MU_PAR_RR_NUM_MASK)

#define MU_PAR_GIR_NUM_MASK                      (0xFF0000U)
#define MU_PAR_GIR_NUM_SHIFT                     (16U)
/*! GIR_NUM - General-Purpose Interrupt Request Number */
#define MU_PAR_GIR_NUM(x)                        (((uint32_t)(((uint32_t)(x)) << MU_PAR_GIR_NUM_SHIFT)) & MU_PAR_GIR_NUM_MASK)

#define MU_PAR_FLAG_WIDTH_MASK                   (0xFF000000U)
#define MU_PAR_FLAG_WIDTH_SHIFT                  (24U)
/*! FLAG_WIDTH - Flag Width */
#define MU_PAR_FLAG_WIDTH(x)                     (((uint32_t)(((uint32_t)(x)) << MU_PAR_FLAG_WIDTH_SHIFT)) & MU_PAR_FLAG_WIDTH_MASK)
/*! @} */

/*! @name CR - Control */
/*! @{ */

#define MU_CR_MUR_MASK                           (0x1U)
#define MU_CR_MUR_SHIFT                          (0U)
/*! MUR - MU Reset
 *  0b0..Idle
 *  0b1..Reset
 */
#define MU_CR_MUR(x)                             (((uint32_t)(((uint32_t)(x)) << MU_CR_MUR_SHIFT)) & MU_CR_MUR_MASK)

#define MU_CR_MURIE_MASK                         (0x2U)
#define MU_CR_MURIE_SHIFT                        (1U)
/*! MURIE - MUB Reset Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_CR_MURIE(x)                           (((uint32_t)(((uint32_t)(x)) << MU_CR_MURIE_SHIFT)) & MU_CR_MURIE_MASK)
/*! @} */

/*! @name SR - Status */
/*! @{ */

#define MU_SR_MURS_MASK                          (0x1U)
#define MU_SR_MURS_SHIFT                         (0U)
/*! MURS - MUA and MUB Reset State
 *  0b0..Out of reset
 *  0b1..In reset
 */
#define MU_SR_MURS(x)                            (((uint32_t)(((uint32_t)(x)) << MU_SR_MURS_SHIFT)) & MU_SR_MURS_MASK)

#define MU_SR_MURIP_MASK                         (0x2U)
#define MU_SR_MURIP_SHIFT                        (1U)
/*! MURIP - MU Reset Interrupt Pending Flag
 *  0b0..Reset not issued
 *  0b1..Reset issued
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define MU_SR_MURIP(x)                           (((uint32_t)(((uint32_t)(x)) << MU_SR_MURIP_SHIFT)) & MU_SR_MURIP_MASK)

#define MU_SR_EP_MASK                            (0x4U)
#define MU_SR_EP_SHIFT                           (2U)
/*! EP - MUB Side Event Pending
 *  0b0..Not pending
 *  0b1..Pending
 */
#define MU_SR_EP(x)                              (((uint32_t)(((uint32_t)(x)) << MU_SR_EP_SHIFT)) & MU_SR_EP_MASK)

#define MU_SR_FUP_MASK                           (0x8U)
#define MU_SR_FUP_SHIFT                          (3U)
/*! FUP - MUB Flag Update Pending
 *  0b0..No pending update flags (initiated by MUA)
 *  0b1..Pending update flags (initiated by MUA)
 */
#define MU_SR_FUP(x)                             (((uint32_t)(((uint32_t)(x)) << MU_SR_FUP_SHIFT)) & MU_SR_FUP_MASK)

#define MU_SR_GIRP_MASK                          (0x10U)
#define MU_SR_GIRP_SHIFT                         (4U)
/*! GIRP - MUB General-Purpose Interrupt Pending
 *  0b0..No request sent
 *  0b1..Request sent
 */
#define MU_SR_GIRP(x)                            (((uint32_t)(((uint32_t)(x)) << MU_SR_GIRP_SHIFT)) & MU_SR_GIRP_MASK)

#define MU_SR_TEP_MASK                           (0x20U)
#define MU_SR_TEP_SHIFT                          (5U)
/*! TEP - MUB Transmit Empty Pending
 *  0b0..Not pending; MUA is reading no Receive (RRn) register
 *  0b1..Pending; MUA is reading a Receive (RRn) register
 */
#define MU_SR_TEP(x)                             (((uint32_t)(((uint32_t)(x)) << MU_SR_TEP_SHIFT)) & MU_SR_TEP_MASK)

#define MU_SR_RFP_MASK                           (0x40U)
#define MU_SR_RFP_SHIFT                          (6U)
/*! RFP - MUB Receive Full Pending
 *  0b0..Not pending; MUA is not writing to a Transmit register
 *  0b1..Pending; MUA is writing to a Transmit register
 */
#define MU_SR_RFP(x)                             (((uint32_t)(((uint32_t)(x)) << MU_SR_RFP_SHIFT)) & MU_SR_RFP_MASK)

#define MU_SR_CEP_MASK                           (0x80U)
#define MU_SR_CEP_SHIFT                          (7U)
/*! CEP - Processor B Event Pending
 *  0b0..No event pending
 *  0b1..Event pending
 */
#define MU_SR_CEP(x)                             (((uint32_t)(((uint32_t)(x)) << MU_SR_CEP_SHIFT)) & MU_SR_CEP_MASK)
/*! @} */

/*! @name CCR0 - Core Control 0 */
/*! @{ */

#define MU_CCR0_NMI_MASK                         (0x1U)
#define MU_CCR0_NMI_SHIFT                        (0U)
/*! NMI - MUB Nonmaskable Interrupt Request
 *  0b0..Nonmaskable interrupt not issued
 *  0b1..Nonmaskable interrupt issued
 */
#define MU_CCR0_NMI(x)                           (((uint32_t)(((uint32_t)(x)) << MU_CCR0_NMI_SHIFT)) & MU_CCR0_NMI_MASK)

#define MU_CCR0_HR_MASK                          (0x2U)
#define MU_CCR0_HR_SHIFT                         (1U)
/*! HR - Processor A Hardware Reset
 *  0b0..Deassert hardware reset to processor A.
 *  0b1..Assert hardware reset to processor A.
 */
#define MU_CCR0_HR(x)                            (((uint32_t)(((uint32_t)(x)) << MU_CCR0_HR_SHIFT)) & MU_CCR0_HR_MASK)

#define MU_CCR0_HRM_MASK                         (0x4U)
#define MU_CCR0_HRM_SHIFT                        (2U)
/*! HRM - Processor B Hardware Reset Mask
 *  0b0..Enable
 *  0b1..Disable
 */
#define MU_CCR0_HRM(x)                           (((uint32_t)(((uint32_t)(x)) << MU_CCR0_HRM_SHIFT)) & MU_CCR0_HRM_MASK)

#define MU_CCR0_CLKE_MASK                        (0x8U)
#define MU_CCR0_CLKE_SHIFT                       (3U)
/*! CLKE - Processor B clock enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MU_CCR0_CLKE(x)                          (((uint32_t)(((uint32_t)(x)) << MU_CCR0_CLKE_SHIFT)) & MU_CCR0_CLKE_MASK)

#define MU_CCR0_RSTH_MASK                        (0x10U)
#define MU_CCR0_RSTH_SHIFT                       (4U)
/*! RSTH - Processor A Reset Hold
 *  0b0..Release from reset
 *  0b1..Hold in reset
 */
#define MU_CCR0_RSTH(x)                          (((uint32_t)(((uint32_t)(x)) << MU_CCR0_RSTH_SHIFT)) & MU_CCR0_RSTH_MASK)

#define MU_CCR0_BOOT_MASK                        (0x60U)
#define MU_CCR0_BOOT_SHIFT                       (5U)
/*! BOOT - Target Processor A Boot Configuration
 *  0b00..Processor Boot option 0
 *  0b01..Processor Boot option 1
 *  0b10..Processor Boot option 2
 *  0b11..Processor Boot option 3
 */
#define MU_CCR0_BOOT(x)                          (((uint32_t)(((uint32_t)(x)) << MU_CCR0_BOOT_SHIFT)) & MU_CCR0_BOOT_MASK)
/*! @} */

/*! @name CIER0 - Core Interrupt Enable 0 */
/*! @{ */

#define MU_CIER0_HRIE_MASK                       (0x2U)
#define MU_CIER0_HRIE_SHIFT                      (1U)
/*! HRIE - Processor B Hardware Reset Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_CIER0_HRIE(x)                         (((uint32_t)(((uint32_t)(x)) << MU_CIER0_HRIE_SHIFT)) & MU_CIER0_HRIE_MASK)

#define MU_CIER0_RUNIE_MASK                      (0x4U)
#define MU_CIER0_RUNIE_SHIFT                     (2U)
/*! RUNIE - Processor B Run Mode Entry Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_CIER0_RUNIE(x)                        (((uint32_t)(((uint32_t)(x)) << MU_CIER0_RUNIE_SHIFT)) & MU_CIER0_RUNIE_MASK)

#define MU_CIER0_RAIE_MASK                       (0x8U)
#define MU_CIER0_RAIE_SHIFT                      (3U)
/*! RAIE - Processor B Reset Assertion Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_CIER0_RAIE(x)                         (((uint32_t)(((uint32_t)(x)) << MU_CIER0_RAIE_SHIFT)) & MU_CIER0_RAIE_MASK)

#define MU_CIER0_HALTIE_MASK                     (0x10U)
#define MU_CIER0_HALTIE_SHIFT                    (4U)
/*! HALTIE - Processor B Halt Mode Entry Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_CIER0_HALTIE(x)                       (((uint32_t)(((uint32_t)(x)) << MU_CIER0_HALTIE_SHIFT)) & MU_CIER0_HALTIE_MASK)

#define MU_CIER0_WAITIE_MASK                     (0x20U)
#define MU_CIER0_WAITIE_SHIFT                    (5U)
/*! WAITIE - Processor B Wait Mode Entry Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_CIER0_WAITIE(x)                       (((uint32_t)(((uint32_t)(x)) << MU_CIER0_WAITIE_SHIFT)) & MU_CIER0_WAITIE_MASK)

#define MU_CIER0_STOPIE_MASK                     (0x40U)
#define MU_CIER0_STOPIE_SHIFT                    (6U)
/*! STOPIE - Processor B Stop Mode Entry Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_CIER0_STOPIE(x)                       (((uint32_t)(((uint32_t)(x)) << MU_CIER0_STOPIE_SHIFT)) & MU_CIER0_STOPIE_MASK)

#define MU_CIER0_PDIE_MASK                       (0x80U)
#define MU_CIER0_PDIE_SHIFT                      (7U)
/*! PDIE - Processor B Power-Down Mode Entry Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_CIER0_PDIE(x)                         (((uint32_t)(((uint32_t)(x)) << MU_CIER0_PDIE_SHIFT)) & MU_CIER0_PDIE_MASK)
/*! @} */

/*! @name CSSR0 - Core Sticky Status 0 */
/*! @{ */

#define MU_CSSR0_NMIC_MASK                       (0x1U)
#define MU_CSSR0_NMIC_SHIFT                      (0U)
/*! NMIC - Processor B Nonmaskable Interrupt Clear
 *  0b0..Default
 *  0b1..Clear MUA_CCR0[NMI]
 */
#define MU_CSSR0_NMIC(x)                         (((uint32_t)(((uint32_t)(x)) << MU_CSSR0_NMIC_SHIFT)) & MU_CSSR0_NMIC_MASK)

#define MU_CSSR0_HRIP_MASK                       (0x2U)
#define MU_CSSR0_HRIP_SHIFT                      (1U)
/*! HRIP - Processor B Hardware Reset Interrupt Pending Flag
 *  0b0..No hardware reset initiated
 *  0b1..Hardware reset initiated
 */
#define MU_CSSR0_HRIP(x)                         (((uint32_t)(((uint32_t)(x)) << MU_CSSR0_HRIP_SHIFT)) & MU_CSSR0_HRIP_MASK)

#define MU_CSSR0_RUN_MASK                        (0x4U)
#define MU_CSSR0_RUN_SHIFT                       (2U)
/*! RUN - Processor B Run Mode Entry Interrupt Pending Flag
 *  0b0..Processor A did not enter Run mode.
 *  0b1..Processor A entered Run mode.
 */
#define MU_CSSR0_RUN(x)                          (((uint32_t)(((uint32_t)(x)) << MU_CSSR0_RUN_SHIFT)) & MU_CSSR0_RUN_MASK)

#define MU_CSSR0_RAIP_MASK                       (0x8U)
#define MU_CSSR0_RAIP_SHIFT                      (3U)
/*! RAIP - Processor B Reset Asserted Interrupt Pending Flag
 *  0b0..Processor A did not enter reset.
 *  0b1..Processor A entered reset.
 */
#define MU_CSSR0_RAIP(x)                         (((uint32_t)(((uint32_t)(x)) << MU_CSSR0_RAIP_SHIFT)) & MU_CSSR0_RAIP_MASK)

#define MU_CSSR0_HALT_MASK                       (0x10U)
#define MU_CSSR0_HALT_SHIFT                      (4U)
/*! HALT - Processor B Halt Mode Entry Interrupt Pending Flag
 *  0b0..Processor A did not enter Halt Mode.
 *  0b1..Processor A entered Halt Mode.
 */
#define MU_CSSR0_HALT(x)                         (((uint32_t)(((uint32_t)(x)) << MU_CSSR0_HALT_SHIFT)) & MU_CSSR0_HALT_MASK)

#define MU_CSSR0_WAIT_MASK                       (0x20U)
#define MU_CSSR0_WAIT_SHIFT                      (5U)
/*! WAIT - Processor B Wait Mode Entry Interrupt Pending
 *  0b0..Processor A did not enter Wait Mode.
 *  0b1..Processor A entered Wait Mode.
 */
#define MU_CSSR0_WAIT(x)                         (((uint32_t)(((uint32_t)(x)) << MU_CSSR0_WAIT_SHIFT)) & MU_CSSR0_WAIT_MASK)

#define MU_CSSR0_STOP_MASK                       (0x40U)
#define MU_CSSR0_STOP_SHIFT                      (6U)
/*! STOP - Processor B Stop Mode Entry Interrupt Pending Flag
 *  0b0..Processor A did not enter Stop mode.
 *  0b1..Processor A entered Stop mode.
 */
#define MU_CSSR0_STOP(x)                         (((uint32_t)(((uint32_t)(x)) << MU_CSSR0_STOP_SHIFT)) & MU_CSSR0_STOP_MASK)

#define MU_CSSR0_PD_MASK                         (0x80U)
#define MU_CSSR0_PD_SHIFT                        (7U)
/*! PD - Processor B Power-Down mode Entry Interrupt Pending Flag
 *  0b0..Processor A did not enter Power-Down mode.
 *  0b1..Processor A entered Power-Down mode.
 */
#define MU_CSSR0_PD(x)                           (((uint32_t)(((uint32_t)(x)) << MU_CSSR0_PD_SHIFT)) & MU_CSSR0_PD_MASK)
/*! @} */

/*! @name CSR0 - Core Status 0 */
/*! @{ */

#define MU_CSR0_HRIP_MASK                        (0x2U)
#define MU_CSR0_HRIP_SHIFT                       (1U)
/*! HRIP - Processor B Hardware Reset Interrupt Pending
 *  0b0..No hardware reset initiated
 *  0b1..Hardware reset initiated
 */
#define MU_CSR0_HRIP(x)                          (((uint32_t)(((uint32_t)(x)) << MU_CSR0_HRIP_SHIFT)) & MU_CSR0_HRIP_MASK)

#define MU_CSR0_RUN_MASK                         (0x4U)
#define MU_CSR0_RUN_SHIFT                        (2U)
/*! RUN - Processor B Run Mode Entry
 *  0b0..Not in Run Mode
 *  0b1..In Run Mode
 */
#define MU_CSR0_RUN(x)                           (((uint32_t)(((uint32_t)(x)) << MU_CSR0_RUN_SHIFT)) & MU_CSR0_RUN_MASK)

#define MU_CSR0_RAIP_MASK                        (0x8U)
#define MU_CSR0_RAIP_SHIFT                       (3U)
/*! RAIP - Processor B Reset Asserted Interrupt Pending
 *  0b0..Not in reset
 *  0b1..In reset
 */
#define MU_CSR0_RAIP(x)                          (((uint32_t)(((uint32_t)(x)) << MU_CSR0_RAIP_SHIFT)) & MU_CSR0_RAIP_MASK)

#define MU_CSR0_HALT_MASK                        (0x10U)
#define MU_CSR0_HALT_SHIFT                       (4U)
/*! HALT - Processor B Halt Mode Entry
 *  0b0..Not in Halt mode
 *  0b1..In Halt mode
 */
#define MU_CSR0_HALT(x)                          (((uint32_t)(((uint32_t)(x)) << MU_CSR0_HALT_SHIFT)) & MU_CSR0_HALT_MASK)

#define MU_CSR0_WAIT_MASK                        (0x20U)
#define MU_CSR0_WAIT_SHIFT                       (5U)
/*! WAIT - Processor B Wait Mode Entry
 *  0b0..Not in Wait mode
 *  0b1..In Wait mode
 */
#define MU_CSR0_WAIT(x)                          (((uint32_t)(((uint32_t)(x)) << MU_CSR0_WAIT_SHIFT)) & MU_CSR0_WAIT_MASK)

#define MU_CSR0_STOP_MASK                        (0x40U)
#define MU_CSR0_STOP_SHIFT                       (6U)
/*! STOP - Processor B Stop Mode Entry
 *  0b0..Not in Stop mode
 *  0b1..In Stop mode
 */
#define MU_CSR0_STOP(x)                          (((uint32_t)(((uint32_t)(x)) << MU_CSR0_STOP_SHIFT)) & MU_CSR0_STOP_MASK)

#define MU_CSR0_PD_MASK                          (0x80U)
#define MU_CSR0_PD_SHIFT                         (7U)
/*! PD - Processor B Power-Down Mode Entry
 *  0b0..Not in Power-Down mode
 *  0b1..In Power-Down mode
 */
#define MU_CSR0_PD(x)                            (((uint32_t)(((uint32_t)(x)) << MU_CSR0_PD_SHIFT)) & MU_CSR0_PD_MASK)
/*! @} */

/*! @name FCR - Flag Control */
/*! @{ */

#define MU_FCR_F0_MASK                           (0x1U)
#define MU_FCR_F0_SHIFT                          (0U)
/*! F0 - MUB to MUA Flag
 *  0b0..Clear MUA_FSR[Fn]
 *  0b1..Set MUA_FSR[Fn]
 */
#define MU_FCR_F0(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F0_SHIFT)) & MU_FCR_F0_MASK)

#define MU_FCR_F1_MASK                           (0x2U)
#define MU_FCR_F1_SHIFT                          (1U)
/*! F1 - MUB to MUA Flag
 *  0b0..Clear MUA_FSR[Fn]
 *  0b1..Set MUA_FSR[Fn]
 */
#define MU_FCR_F1(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F1_SHIFT)) & MU_FCR_F1_MASK)

#define MU_FCR_F2_MASK                           (0x4U)
#define MU_FCR_F2_SHIFT                          (2U)
/*! F2 - MUB to MUA Flag
 *  0b0..Clear MUA_FSR[Fn]
 *  0b1..Set MUA_FSR[Fn]
 */
#define MU_FCR_F2(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F2_SHIFT)) & MU_FCR_F2_MASK)
/*! @} */

/*! @name FSR - Flag Status */
/*! @{ */

#define MU_FSR_F0_MASK                           (0x1U)
#define MU_FSR_F0_SHIFT                          (0U)
/*! F0 - MUB to MUA-Side Flag
 *  0b0..MUA_FCR[Fn] = 0
 *  0b1..MUA_FCR[Fn] = 1
 */
#define MU_FSR_F0(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F0_SHIFT)) & MU_FSR_F0_MASK)

#define MU_FSR_F1_MASK                           (0x2U)
#define MU_FSR_F1_SHIFT                          (1U)
/*! F1 - MUB to MUA-Side Flag
 *  0b0..MUA_FCR[Fn] = 0
 *  0b1..MUA_FCR[Fn] = 1
 */
#define MU_FSR_F1(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F1_SHIFT)) & MU_FSR_F1_MASK)

#define MU_FSR_F2_MASK                           (0x4U)
#define MU_FSR_F2_SHIFT                          (2U)
/*! F2 - MUB to MUA-Side Flag
 *  0b0..MUA_FCR[Fn] = 0
 *  0b1..MUA_FCR[Fn] = 1
 */
#define MU_FSR_F2(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F2_SHIFT)) & MU_FSR_F2_MASK)
/*! @} */

/*! @name GIER - General-Purpose Interrupt Enable */
/*! @{ */

#define MU_GIER_GIE0_MASK                        (0x1U)
#define MU_GIER_GIE0_SHIFT                       (0U)
/*! GIE0 - MUB General-purpose Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_GIER_GIE0(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE0_SHIFT)) & MU_GIER_GIE0_MASK)

#define MU_GIER_GIE1_MASK                        (0x2U)
#define MU_GIER_GIE1_SHIFT                       (1U)
/*! GIE1 - MUB General-purpose Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_GIER_GIE1(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE1_SHIFT)) & MU_GIER_GIE1_MASK)

#define MU_GIER_GIE2_MASK                        (0x4U)
#define MU_GIER_GIE2_SHIFT                       (2U)
/*! GIE2 - MUB General-purpose Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_GIER_GIE2(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE2_SHIFT)) & MU_GIER_GIE2_MASK)

#define MU_GIER_GIE3_MASK                        (0x8U)
#define MU_GIER_GIE3_SHIFT                       (3U)
/*! GIE3 - MUB General-purpose Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_GIER_GIE3(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE3_SHIFT)) & MU_GIER_GIE3_MASK)
/*! @} */

/*! @name GCR - General-Purpose Control */
/*! @{ */

#define MU_GCR_GIR0_MASK                         (0x1U)
#define MU_GCR_GIR0_SHIFT                        (0U)
/*! GIR0 - MUB General-Purpose Interrupt Request
 *  0b0..Not requested
 *  0b1..Requested
 */
#define MU_GCR_GIR0(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR0_SHIFT)) & MU_GCR_GIR0_MASK)

#define MU_GCR_GIR1_MASK                         (0x2U)
#define MU_GCR_GIR1_SHIFT                        (1U)
/*! GIR1 - MUB General-Purpose Interrupt Request
 *  0b0..Not requested
 *  0b1..Requested
 */
#define MU_GCR_GIR1(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR1_SHIFT)) & MU_GCR_GIR1_MASK)

#define MU_GCR_GIR2_MASK                         (0x4U)
#define MU_GCR_GIR2_SHIFT                        (2U)
/*! GIR2 - MUB General-Purpose Interrupt Request
 *  0b0..Not requested
 *  0b1..Requested
 */
#define MU_GCR_GIR2(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR2_SHIFT)) & MU_GCR_GIR2_MASK)

#define MU_GCR_GIR3_MASK                         (0x8U)
#define MU_GCR_GIR3_SHIFT                        (3U)
/*! GIR3 - MUB General-Purpose Interrupt Request
 *  0b0..Not requested
 *  0b1..Requested
 */
#define MU_GCR_GIR3(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR3_SHIFT)) & MU_GCR_GIR3_MASK)
/*! @} */

/*! @name GSR - General-purpose Status */
/*! @{ */

#define MU_GSR_GIP0_MASK                         (0x1U)
#define MU_GSR_GIP0_SHIFT                        (0U)
/*! GIP0 - MUB General-Purpose Interrupt Request Pending
 *  0b0..Not pending
 *  0b1..Pending
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define MU_GSR_GIP0(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP0_SHIFT)) & MU_GSR_GIP0_MASK)

#define MU_GSR_GIP1_MASK                         (0x2U)
#define MU_GSR_GIP1_SHIFT                        (1U)
/*! GIP1 - MUB General-Purpose Interrupt Request Pending
 *  0b0..Not pending
 *  0b1..Pending
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define MU_GSR_GIP1(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP1_SHIFT)) & MU_GSR_GIP1_MASK)

#define MU_GSR_GIP2_MASK                         (0x4U)
#define MU_GSR_GIP2_SHIFT                        (2U)
/*! GIP2 - MUB General-Purpose Interrupt Request Pending
 *  0b0..Not pending
 *  0b1..Pending
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define MU_GSR_GIP2(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP2_SHIFT)) & MU_GSR_GIP2_MASK)

#define MU_GSR_GIP3_MASK                         (0x8U)
#define MU_GSR_GIP3_SHIFT                        (3U)
/*! GIP3 - MUB General-Purpose Interrupt Request Pending
 *  0b0..Not pending
 *  0b1..Pending
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define MU_GSR_GIP3(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP3_SHIFT)) & MU_GSR_GIP3_MASK)
/*! @} */

/*! @name TCR - Transmit Control */
/*! @{ */

#define MU_TCR_TIE0_MASK                         (0x1U)
#define MU_TCR_TIE0_SHIFT                        (0U)
/*! TIE0 - MUB Transmit Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_TCR_TIE0(x)                           (((uint32_t)(((uint32_t)(x)) << MU_TCR_TIE0_SHIFT)) & MU_TCR_TIE0_MASK)

#define MU_TCR_TIE1_MASK                         (0x2U)
#define MU_TCR_TIE1_SHIFT                        (1U)
/*! TIE1 - MUB Transmit Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_TCR_TIE1(x)                           (((uint32_t)(((uint32_t)(x)) << MU_TCR_TIE1_SHIFT)) & MU_TCR_TIE1_MASK)

#define MU_TCR_TIE2_MASK                         (0x4U)
#define MU_TCR_TIE2_SHIFT                        (2U)
/*! TIE2 - MUB Transmit Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_TCR_TIE2(x)                           (((uint32_t)(((uint32_t)(x)) << MU_TCR_TIE2_SHIFT)) & MU_TCR_TIE2_MASK)

#define MU_TCR_TIE3_MASK                         (0x8U)
#define MU_TCR_TIE3_SHIFT                        (3U)
/*! TIE3 - MUB Transmit Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_TCR_TIE3(x)                           (((uint32_t)(((uint32_t)(x)) << MU_TCR_TIE3_SHIFT)) & MU_TCR_TIE3_MASK)
/*! @} */

/*! @name TSR - Transmit Status */
/*! @{ */

#define MU_TSR_TE0_MASK                          (0x1U)
#define MU_TSR_TE0_SHIFT                         (0U)
/*! TE0 - MUB Transmit Empty
 *  0b0..Not empty
 *  0b1..Empty
 */
#define MU_TSR_TE0(x)                            (((uint32_t)(((uint32_t)(x)) << MU_TSR_TE0_SHIFT)) & MU_TSR_TE0_MASK)

#define MU_TSR_TE1_MASK                          (0x2U)
#define MU_TSR_TE1_SHIFT                         (1U)
/*! TE1 - MUB Transmit Empty
 *  0b0..Not empty
 *  0b1..Empty
 */
#define MU_TSR_TE1(x)                            (((uint32_t)(((uint32_t)(x)) << MU_TSR_TE1_SHIFT)) & MU_TSR_TE1_MASK)

#define MU_TSR_TE2_MASK                          (0x4U)
#define MU_TSR_TE2_SHIFT                         (2U)
/*! TE2 - MUB Transmit Empty
 *  0b0..Not empty
 *  0b1..Empty
 */
#define MU_TSR_TE2(x)                            (((uint32_t)(((uint32_t)(x)) << MU_TSR_TE2_SHIFT)) & MU_TSR_TE2_MASK)

#define MU_TSR_TE3_MASK                          (0x8U)
#define MU_TSR_TE3_SHIFT                         (3U)
/*! TE3 - MUB Transmit Empty
 *  0b0..Not empty
 *  0b1..Empty
 */
#define MU_TSR_TE3(x)                            (((uint32_t)(((uint32_t)(x)) << MU_TSR_TE3_SHIFT)) & MU_TSR_TE3_MASK)
/*! @} */

/*! @name RCR - Receive Control */
/*! @{ */

#define MU_RCR_RIE0_MASK                         (0x1U)
#define MU_RCR_RIE0_SHIFT                        (0U)
/*! RIE0 - MUB Receive Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_RCR_RIE0(x)                           (((uint32_t)(((uint32_t)(x)) << MU_RCR_RIE0_SHIFT)) & MU_RCR_RIE0_MASK)

#define MU_RCR_RIE1_MASK                         (0x2U)
#define MU_RCR_RIE1_SHIFT                        (1U)
/*! RIE1 - MUB Receive Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_RCR_RIE1(x)                           (((uint32_t)(((uint32_t)(x)) << MU_RCR_RIE1_SHIFT)) & MU_RCR_RIE1_MASK)

#define MU_RCR_RIE2_MASK                         (0x4U)
#define MU_RCR_RIE2_SHIFT                        (2U)
/*! RIE2 - MUB Receive Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_RCR_RIE2(x)                           (((uint32_t)(((uint32_t)(x)) << MU_RCR_RIE2_SHIFT)) & MU_RCR_RIE2_MASK)

#define MU_RCR_RIE3_MASK                         (0x8U)
#define MU_RCR_RIE3_SHIFT                        (3U)
/*! RIE3 - MUB Receive Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define MU_RCR_RIE3(x)                           (((uint32_t)(((uint32_t)(x)) << MU_RCR_RIE3_SHIFT)) & MU_RCR_RIE3_MASK)
/*! @} */

/*! @name RSR - Receive Status */
/*! @{ */

#define MU_RSR_RF0_MASK                          (0x1U)
#define MU_RSR_RF0_SHIFT                         (0U)
/*! RF0 - MUB Receive Register Full
 *  0b0..Not full
 *  0b1..Full
 */
#define MU_RSR_RF0(x)                            (((uint32_t)(((uint32_t)(x)) << MU_RSR_RF0_SHIFT)) & MU_RSR_RF0_MASK)

#define MU_RSR_RF1_MASK                          (0x2U)
#define MU_RSR_RF1_SHIFT                         (1U)
/*! RF1 - MUB Receive Register Full
 *  0b0..Not full
 *  0b1..Full
 */
#define MU_RSR_RF1(x)                            (((uint32_t)(((uint32_t)(x)) << MU_RSR_RF1_SHIFT)) & MU_RSR_RF1_MASK)

#define MU_RSR_RF2_MASK                          (0x4U)
#define MU_RSR_RF2_SHIFT                         (2U)
/*! RF2 - MUB Receive Register Full
 *  0b0..Not full
 *  0b1..Full
 */
#define MU_RSR_RF2(x)                            (((uint32_t)(((uint32_t)(x)) << MU_RSR_RF2_SHIFT)) & MU_RSR_RF2_MASK)

#define MU_RSR_RF3_MASK                          (0x8U)
#define MU_RSR_RF3_SHIFT                         (3U)
/*! RF3 - MUB Receive Register Full
 *  0b0..Not full
 *  0b1..Full
 */
#define MU_RSR_RF3(x)                            (((uint32_t)(((uint32_t)(x)) << MU_RSR_RF3_SHIFT)) & MU_RSR_RF3_MASK)
/*! @} */

/*! @name TR - Transmit */
/*! @{ */

#define MU_TR_TR_DATA_MASK                       (0xFFFFFFFFU)
#define MU_TR_TR_DATA_SHIFT                      (0U)
/*! TR_DATA - MUB Transmit Data */
#define MU_TR_TR_DATA(x)                         (((uint32_t)(((uint32_t)(x)) << MU_TR_TR_DATA_SHIFT)) & MU_TR_TR_DATA_MASK)
/*! @} */

/* The count of MU_TR */
#define MU_TR_COUNT                              (4U)

/*! @name RR - Receive */
/*! @{ */

#define MU_RR_RR_DATA_MASK                       (0xFFFFFFFFU)
#define MU_RR_RR_DATA_SHIFT                      (0U)
/*! RR_DATA - MUB Receive Data */
#define MU_RR_RR_DATA(x)                         (((uint32_t)(((uint32_t)(x)) << MU_RR_RR_DATA_SHIFT)) & MU_RR_RR_DATA_MASK)
/*! @} */

/* The count of MU_RR */
#define MU_RR_COUNT                              (4U)


/*!
 * @}
 */ /* end of group MU_Register_Masks */


/* MU - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral MU1_MUA base address */
  #define MU1_MUA_BASE                             (0x54220000u)
  /** Peripheral MU1_MUA base address */
  #define MU1_MUA_BASE_NS                          (0x44220000u)
  /** Peripheral MU1_MUA base pointer */
  #define MU1_MUA                                  ((MU_Type *)MU1_MUA_BASE)
  /** Peripheral MU1_MUA base pointer */
  #define MU1_MUA_NS                               ((MU_Type *)MU1_MUA_BASE_NS)
  /** Peripheral MU1_MUB base address */
  #define MU1_MUB_BASE                             (0x54230000u)
  /** Peripheral MU1_MUB base address */
  #define MU1_MUB_BASE_NS                          (0x44230000u)
  /** Peripheral MU1_MUB base pointer */
  #define MU1_MUB                                  ((MU_Type *)MU1_MUB_BASE)
  /** Peripheral MU1_MUB base pointer */
  #define MU1_MUB_NS                               ((MU_Type *)MU1_MUB_BASE_NS)
  /** Peripheral MU2_MUA base address */
  #define MU2_MUA_BASE                             (0x545B0000u)
  /** Peripheral MU2_MUA base address */
  #define MU2_MUA_BASE_NS                          (0x445B0000u)
  /** Peripheral MU2_MUA base pointer */
  #define MU2_MUA                                  ((MU_Type *)MU2_MUA_BASE)
  /** Peripheral MU2_MUA base pointer */
  #define MU2_MUA_NS                               ((MU_Type *)MU2_MUA_BASE_NS)
  /** Peripheral MU2_MUB base address */
  #define MU2_MUB_BASE                             (0x545C0000u)
  /** Peripheral MU2_MUB base address */
  #define MU2_MUB_BASE_NS                          (0x445C0000u)
  /** Peripheral MU2_MUB base pointer */
  #define MU2_MUB                                  ((MU_Type *)MU2_MUB_BASE)
  /** Peripheral MU2_MUB base pointer */
  #define MU2_MUB_NS                               ((MU_Type *)MU2_MUB_BASE_NS)
  /** Peripheral MU3_MUA base address */
  #define MU3_MUA_BASE                             (0x545D0000u)
  /** Peripheral MU3_MUA base address */
  #define MU3_MUA_BASE_NS                          (0x445D0000u)
  /** Peripheral MU3_MUA base pointer */
  #define MU3_MUA                                  ((MU_Type *)MU3_MUA_BASE)
  /** Peripheral MU3_MUA base pointer */
  #define MU3_MUA_NS                               ((MU_Type *)MU3_MUA_BASE_NS)
  /** Peripheral MU3_MUB base address */
  #define MU3_MUB_BASE                             (0x545E0000u)
  /** Peripheral MU3_MUB base address */
  #define MU3_MUB_BASE_NS                          (0x445E0000u)
  /** Peripheral MU3_MUB base pointer */
  #define MU3_MUB                                  ((MU_Type *)MU3_MUB_BASE)
  /** Peripheral MU3_MUB base pointer */
  #define MU3_MUB_NS                               ((MU_Type *)MU3_MUB_BASE_NS)
  /** Peripheral MU4_MUA base address */
  #define MU4_MUA_BASE                             (0x545F0000u)
  /** Peripheral MU4_MUA base address */
  #define MU4_MUA_BASE_NS                          (0x445F0000u)
  /** Peripheral MU4_MUA base pointer */
  #define MU4_MUA                                  ((MU_Type *)MU4_MUA_BASE)
  /** Peripheral MU4_MUA base pointer */
  #define MU4_MUA_NS                               ((MU_Type *)MU4_MUA_BASE_NS)
  /** Peripheral MU4_MUB base address */
  #define MU4_MUB_BASE                             (0x54600000u)
  /** Peripheral MU4_MUB base address */
  #define MU4_MUB_BASE_NS                          (0x44600000u)
  /** Peripheral MU4_MUB base pointer */
  #define MU4_MUB                                  ((MU_Type *)MU4_MUB_BASE)
  /** Peripheral MU4_MUB base pointer */
  #define MU4_MUB_NS                               ((MU_Type *)MU4_MUB_BASE_NS)
  /** Peripheral MU5_MUA base address */
  #define MU5_MUA_BASE                             (0x54610000u)
  /** Peripheral MU5_MUA base address */
  #define MU5_MUA_BASE_NS                          (0x44610000u)
  /** Peripheral MU5_MUA base pointer */
  #define MU5_MUA                                  ((MU_Type *)MU5_MUA_BASE)
  /** Peripheral MU5_MUA base pointer */
  #define MU5_MUA_NS                               ((MU_Type *)MU5_MUA_BASE_NS)
  /** Peripheral MU5_MUB base address */
  #define MU5_MUB_BASE                             (0x54620000u)
  /** Peripheral MU5_MUB base address */
  #define MU5_MUB_BASE_NS                          (0x44620000u)
  /** Peripheral MU5_MUB base pointer */
  #define MU5_MUB                                  ((MU_Type *)MU5_MUB_BASE)
  /** Peripheral MU5_MUB base pointer */
  #define MU5_MUB_NS                               ((MU_Type *)MU5_MUB_BASE_NS)
  /** Peripheral MU6_MUA base address */
  #define MU6_MUA_BASE                             (0x54630000u)
  /** Peripheral MU6_MUA base address */
  #define MU6_MUA_BASE_NS                          (0x44630000u)
  /** Peripheral MU6_MUA base pointer */
  #define MU6_MUA                                  ((MU_Type *)MU6_MUA_BASE)
  /** Peripheral MU6_MUA base pointer */
  #define MU6_MUA_NS                               ((MU_Type *)MU6_MUA_BASE_NS)
  /** Peripheral MU6_MUB base address */
  #define MU6_MUB_BASE                             (0x54640000u)
  /** Peripheral MU6_MUB base address */
  #define MU6_MUB_BASE_NS                          (0x44640000u)
  /** Peripheral MU6_MUB base pointer */
  #define MU6_MUB                                  ((MU_Type *)MU6_MUB_BASE)
  /** Peripheral MU6_MUB base pointer */
  #define MU6_MUB_NS                               ((MU_Type *)MU6_MUB_BASE_NS)
  /** Peripheral MU7_MUA base address */
  #define MU7_MUA_BASE                             (0x54700000u)
  /** Peripheral MU7_MUA base address */
  #define MU7_MUA_BASE_NS                          (0x44700000u)
  /** Peripheral MU7_MUA base pointer */
  #define MU7_MUA                                  ((MU_Type *)MU7_MUA_BASE)
  /** Peripheral MU7_MUA base pointer */
  #define MU7_MUA_NS                               ((MU_Type *)MU7_MUA_BASE_NS)
  /** Peripheral MU7_MUB base address */
  #define MU7_MUB_BASE                             (0x54710000u)
  /** Peripheral MU7_MUB base address */
  #define MU7_MUB_BASE_NS                          (0x44710000u)
  /** Peripheral MU7_MUB base pointer */
  #define MU7_MUB                                  ((MU_Type *)MU7_MUB_BASE)
  /** Peripheral MU7_MUB base pointer */
  #define MU7_MUB_NS                               ((MU_Type *)MU7_MUB_BASE_NS)
  /** Peripheral MU8_MUA base address */
  #define MU8_MUA_BASE                             (0x54720000u)
  /** Peripheral MU8_MUA base address */
  #define MU8_MUA_BASE_NS                          (0x44720000u)
  /** Peripheral MU8_MUA base pointer */
  #define MU8_MUA                                  ((MU_Type *)MU8_MUA_BASE)
  /** Peripheral MU8_MUA base pointer */
  #define MU8_MUA_NS                               ((MU_Type *)MU8_MUA_BASE_NS)
  /** Peripheral MU8_MUB base address */
  #define MU8_MUB_BASE                             (0x54730000u)
  /** Peripheral MU8_MUB base address */
  #define MU8_MUB_BASE_NS                          (0x44730000u)
  /** Peripheral MU8_MUB base pointer */
  #define MU8_MUB                                  ((MU_Type *)MU8_MUB_BASE)
  /** Peripheral MU8_MUB base pointer */
  #define MU8_MUB_NS                               ((MU_Type *)MU8_MUB_BASE_NS)
  /** Peripheral MU9_MUA base address */
  #define MU9_MUA_BASE                             (0x54740000u)
  /** Peripheral MU9_MUA base address */
  #define MU9_MUA_BASE_NS                          (0x44740000u)
  /** Peripheral MU9_MUA base pointer */
  #define MU9_MUA                                  ((MU_Type *)MU9_MUA_BASE)
  /** Peripheral MU9_MUA base pointer */
  #define MU9_MUA_NS                               ((MU_Type *)MU9_MUA_BASE_NS)
  /** Peripheral MU9_MUB base address */
  #define MU9_MUB_BASE                             (0x54750000u)
  /** Peripheral MU9_MUB base address */
  #define MU9_MUB_BASE_NS                          (0x44750000u)
  /** Peripheral MU9_MUB base pointer */
  #define MU9_MUB                                  ((MU_Type *)MU9_MUB_BASE)
  /** Peripheral MU9_MUB base pointer */
  #define MU9_MUB_NS                               ((MU_Type *)MU9_MUB_BASE_NS)
  /** Peripheral NETC__MUA1__MUA base address */
  #define NETC__MUA1__MUA_BASE                     (0x5D120000u)
  /** Peripheral NETC__MUA1__MUA base address */
  #define NETC__MUA1__MUA_BASE_NS                  (0x4D120000u)
  /** Peripheral NETC__MUA1__MUA base pointer */
  #define NETC__MUA1__MUA                          ((MU_Type *)NETC__MUA1__MUA_BASE)
  /** Peripheral NETC__MUA1__MUA base pointer */
  #define NETC__MUA1__MUA_NS                       ((MU_Type *)NETC__MUA1__MUA_BASE_NS)
  /** Peripheral NETC__MUA1__MUB base address */
  #define NETC__MUA1__MUB_BASE                     (0x5D130000u)
  /** Peripheral NETC__MUA1__MUB base address */
  #define NETC__MUA1__MUB_BASE_NS                  (0x4D130000u)
  /** Peripheral NETC__MUA1__MUB base pointer */
  #define NETC__MUA1__MUB                          ((MU_Type *)NETC__MUA1__MUB_BASE)
  /** Peripheral NETC__MUA1__MUB base pointer */
  #define NETC__MUA1__MUB_NS                       ((MU_Type *)NETC__MUA1__MUB_BASE_NS)
  /** Peripheral NETC__MUA2__MUA base address */
  #define NETC__MUA2__MUA_BASE                     (0x5D140000u)
  /** Peripheral NETC__MUA2__MUA base address */
  #define NETC__MUA2__MUA_BASE_NS                  (0x4D140000u)
  /** Peripheral NETC__MUA2__MUA base pointer */
  #define NETC__MUA2__MUA                          ((MU_Type *)NETC__MUA2__MUA_BASE)
  /** Peripheral NETC__MUA2__MUA base pointer */
  #define NETC__MUA2__MUA_NS                       ((MU_Type *)NETC__MUA2__MUA_BASE_NS)
  /** Peripheral NETC__MUA2__MUB base address */
  #define NETC__MUA2__MUB_BASE                     (0x5D150000u)
  /** Peripheral NETC__MUA2__MUB base address */
  #define NETC__MUA2__MUB_BASE_NS                  (0x4D150000u)
  /** Peripheral NETC__MUA2__MUB base pointer */
  #define NETC__MUA2__MUB                          ((MU_Type *)NETC__MUA2__MUB_BASE)
  /** Peripheral NETC__MUA2__MUB base pointer */
  #define NETC__MUA2__MUB_NS                       ((MU_Type *)NETC__MUA2__MUB_BASE_NS)
  /** Peripheral NETC__MUA3__MUA base address */
  #define NETC__MUA3__MUA_BASE                     (0x5D160000u)
  /** Peripheral NETC__MUA3__MUA base address */
  #define NETC__MUA3__MUA_BASE_NS                  (0x4D160000u)
  /** Peripheral NETC__MUA3__MUA base pointer */
  #define NETC__MUA3__MUA                          ((MU_Type *)NETC__MUA3__MUA_BASE)
  /** Peripheral NETC__MUA3__MUA base pointer */
  #define NETC__MUA3__MUA_NS                       ((MU_Type *)NETC__MUA3__MUA_BASE_NS)
  /** Peripheral NETC__MUA3__MUB base address */
  #define NETC__MUA3__MUB_BASE                     (0x5D170000u)
  /** Peripheral NETC__MUA3__MUB base address */
  #define NETC__MUA3__MUB_BASE_NS                  (0x4D170000u)
  /** Peripheral NETC__MUA3__MUB base pointer */
  #define NETC__MUA3__MUB                          ((MU_Type *)NETC__MUA3__MUB_BASE)
  /** Peripheral NETC__MUA3__MUB base pointer */
  #define NETC__MUA3__MUB_NS                       ((MU_Type *)NETC__MUA3__MUB_BASE_NS)
  /** Peripheral NETC__MUA4__MUA base address */
  #define NETC__MUA4__MUA_BASE                     (0x5D180000u)
  /** Peripheral NETC__MUA4__MUA base address */
  #define NETC__MUA4__MUA_BASE_NS                  (0x4D180000u)
  /** Peripheral NETC__MUA4__MUA base pointer */
  #define NETC__MUA4__MUA                          ((MU_Type *)NETC__MUA4__MUA_BASE)
  /** Peripheral NETC__MUA4__MUA base pointer */
  #define NETC__MUA4__MUA_NS                       ((MU_Type *)NETC__MUA4__MUA_BASE_NS)
  /** Peripheral NETC__MUA4__MUB base address */
  #define NETC__MUA4__MUB_BASE                     (0x5D190000u)
  /** Peripheral NETC__MUA4__MUB base address */
  #define NETC__MUA4__MUB_BASE_NS                  (0x4D190000u)
  /** Peripheral NETC__MUA4__MUB base pointer */
  #define NETC__MUA4__MUB                          ((MU_Type *)NETC__MUA4__MUB_BASE)
  /** Peripheral NETC__MUA4__MUB base pointer */
  #define NETC__MUA4__MUB_NS                       ((MU_Type *)NETC__MUA4__MUB_BASE_NS)
  /** Peripheral WAKEUP__MUI_A10__MUA base address */
  #define WAKEUP__MUI_A10__MUA_BASE                (0x52430000u)
  /** Peripheral WAKEUP__MUI_A10__MUA base address */
  #define WAKEUP__MUI_A10__MUA_BASE_NS             (0x42430000u)
  /** Peripheral WAKEUP__MUI_A10__MUA base pointer */
  #define WAKEUP__MUI_A10__MUA                     ((MU_Type *)WAKEUP__MUI_A10__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A10__MUA base pointer */
  #define WAKEUP__MUI_A10__MUA_NS                  ((MU_Type *)WAKEUP__MUI_A10__MUA_BASE_NS)
  /** Peripheral WAKEUP__MUI_A10__MUB base address */
  #define WAKEUP__MUI_A10__MUB_BASE                (0x52440000u)
  /** Peripheral WAKEUP__MUI_A10__MUB base address */
  #define WAKEUP__MUI_A10__MUB_BASE_NS             (0x42440000u)
  /** Peripheral WAKEUP__MUI_A10__MUB base pointer */
  #define WAKEUP__MUI_A10__MUB                     ((MU_Type *)WAKEUP__MUI_A10__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A10__MUB base pointer */
  #define WAKEUP__MUI_A10__MUB_NS                  ((MU_Type *)WAKEUP__MUI_A10__MUB_BASE_NS)
  /** Peripheral WAKEUP__MUI_A11__MUA base address */
  #define WAKEUP__MUI_A11__MUA_BASE                (0x52730000u)
  /** Peripheral WAKEUP__MUI_A11__MUA base address */
  #define WAKEUP__MUI_A11__MUA_BASE_NS             (0x42730000u)
  /** Peripheral WAKEUP__MUI_A11__MUA base pointer */
  #define WAKEUP__MUI_A11__MUA                     ((MU_Type *)WAKEUP__MUI_A11__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A11__MUA base pointer */
  #define WAKEUP__MUI_A11__MUA_NS                  ((MU_Type *)WAKEUP__MUI_A11__MUA_BASE_NS)
  /** Peripheral WAKEUP__MUI_A11__MUB base address */
  #define WAKEUP__MUI_A11__MUB_BASE                (0x52740000u)
  /** Peripheral WAKEUP__MUI_A11__MUB base address */
  #define WAKEUP__MUI_A11__MUB_BASE_NS             (0x42740000u)
  /** Peripheral WAKEUP__MUI_A11__MUB base pointer */
  #define WAKEUP__MUI_A11__MUB                     ((MU_Type *)WAKEUP__MUI_A11__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A11__MUB base pointer */
  #define WAKEUP__MUI_A11__MUB_NS                  ((MU_Type *)WAKEUP__MUI_A11__MUB_BASE_NS)
  /** Peripheral WAKEUP__MUI_A12__MUA base address */
  #define WAKEUP__MUI_A12__MUA_BASE                (0x52AB0000u)
  /** Peripheral WAKEUP__MUI_A12__MUA base address */
  #define WAKEUP__MUI_A12__MUA_BASE_NS             (0x42AB0000u)
  /** Peripheral WAKEUP__MUI_A12__MUA base pointer */
  #define WAKEUP__MUI_A12__MUA                     ((MU_Type *)WAKEUP__MUI_A12__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A12__MUA base pointer */
  #define WAKEUP__MUI_A12__MUA_NS                  ((MU_Type *)WAKEUP__MUI_A12__MUA_BASE_NS)
  /** Peripheral WAKEUP__MUI_A12__MUB base address */
  #define WAKEUP__MUI_A12__MUB_BASE                (0x52AC0000u)
  /** Peripheral WAKEUP__MUI_A12__MUB base address */
  #define WAKEUP__MUI_A12__MUB_BASE_NS             (0x42AC0000u)
  /** Peripheral WAKEUP__MUI_A12__MUB base pointer */
  #define WAKEUP__MUI_A12__MUB                     ((MU_Type *)WAKEUP__MUI_A12__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A12__MUB base pointer */
  #define WAKEUP__MUI_A12__MUB_NS                  ((MU_Type *)WAKEUP__MUI_A12__MUB_BASE_NS)
  /** Peripheral WAKEUP__MUI_A13__MUA base address */
  #define WAKEUP__MUI_A13__MUA_BASE                (0x52AD0000u)
  /** Peripheral WAKEUP__MUI_A13__MUA base address */
  #define WAKEUP__MUI_A13__MUA_BASE_NS             (0x42AD0000u)
  /** Peripheral WAKEUP__MUI_A13__MUA base pointer */
  #define WAKEUP__MUI_A13__MUA                     ((MU_Type *)WAKEUP__MUI_A13__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A13__MUA base pointer */
  #define WAKEUP__MUI_A13__MUA_NS                  ((MU_Type *)WAKEUP__MUI_A13__MUA_BASE_NS)
  /** Peripheral WAKEUP__MUI_A13__MUB base address */
  #define WAKEUP__MUI_A13__MUB_BASE                (0x52AE0000u)
  /** Peripheral WAKEUP__MUI_A13__MUB base address */
  #define WAKEUP__MUI_A13__MUB_BASE_NS             (0x42AE0000u)
  /** Peripheral WAKEUP__MUI_A13__MUB base pointer */
  #define WAKEUP__MUI_A13__MUB                     ((MU_Type *)WAKEUP__MUI_A13__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A13__MUB base pointer */
  #define WAKEUP__MUI_A13__MUB_NS                  ((MU_Type *)WAKEUP__MUI_A13__MUB_BASE_NS)
  /** Peripheral WAKEUP__MUI_A14__MUA base address */
  #define WAKEUP__MUI_A14__MUA_BASE                (0x52AF0000u)
  /** Peripheral WAKEUP__MUI_A14__MUA base address */
  #define WAKEUP__MUI_A14__MUA_BASE_NS             (0x42AF0000u)
  /** Peripheral WAKEUP__MUI_A14__MUA base pointer */
  #define WAKEUP__MUI_A14__MUA                     ((MU_Type *)WAKEUP__MUI_A14__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A14__MUA base pointer */
  #define WAKEUP__MUI_A14__MUA_NS                  ((MU_Type *)WAKEUP__MUI_A14__MUA_BASE_NS)
  /** Peripheral WAKEUP__MUI_A14__MUB base address */
  #define WAKEUP__MUI_A14__MUB_BASE                (0x52B00000u)
  /** Peripheral WAKEUP__MUI_A14__MUB base address */
  #define WAKEUP__MUI_A14__MUB_BASE_NS             (0x42B00000u)
  /** Peripheral WAKEUP__MUI_A14__MUB base pointer */
  #define WAKEUP__MUI_A14__MUB                     ((MU_Type *)WAKEUP__MUI_A14__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A14__MUB base pointer */
  #define WAKEUP__MUI_A14__MUB_NS                  ((MU_Type *)WAKEUP__MUI_A14__MUB_BASE_NS)
  /** Peripheral WAKEUP__MUI_A15__MUA base address */
  #define WAKEUP__MUI_A15__MUA_BASE                (0x52B10000u)
  /** Peripheral WAKEUP__MUI_A15__MUA base address */
  #define WAKEUP__MUI_A15__MUA_BASE_NS             (0x42B10000u)
  /** Peripheral WAKEUP__MUI_A15__MUA base pointer */
  #define WAKEUP__MUI_A15__MUA                     ((MU_Type *)WAKEUP__MUI_A15__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A15__MUA base pointer */
  #define WAKEUP__MUI_A15__MUA_NS                  ((MU_Type *)WAKEUP__MUI_A15__MUA_BASE_NS)
  /** Peripheral WAKEUP__MUI_A15__MUB base address */
  #define WAKEUP__MUI_A15__MUB_BASE                (0x52B20000u)
  /** Peripheral WAKEUP__MUI_A15__MUB base address */
  #define WAKEUP__MUI_A15__MUB_BASE_NS             (0x42B20000u)
  /** Peripheral WAKEUP__MUI_A15__MUB base pointer */
  #define WAKEUP__MUI_A15__MUB                     ((MU_Type *)WAKEUP__MUI_A15__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A15__MUB base pointer */
  #define WAKEUP__MUI_A15__MUB_NS                  ((MU_Type *)WAKEUP__MUI_A15__MUB_BASE_NS)
  /** Peripheral WAKEUP__MUI_A16__MUA base address */
  #define WAKEUP__MUI_A16__MUA_BASE                (0x52B30000u)
  /** Peripheral WAKEUP__MUI_A16__MUA base address */
  #define WAKEUP__MUI_A16__MUA_BASE_NS             (0x42B30000u)
  /** Peripheral WAKEUP__MUI_A16__MUA base pointer */
  #define WAKEUP__MUI_A16__MUA                     ((MU_Type *)WAKEUP__MUI_A16__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A16__MUA base pointer */
  #define WAKEUP__MUI_A16__MUA_NS                  ((MU_Type *)WAKEUP__MUI_A16__MUA_BASE_NS)
  /** Peripheral WAKEUP__MUI_A16__MUB base address */
  #define WAKEUP__MUI_A16__MUB_BASE                (0x52B40000u)
  /** Peripheral WAKEUP__MUI_A16__MUB base address */
  #define WAKEUP__MUI_A16__MUB_BASE_NS             (0x42B40000u)
  /** Peripheral WAKEUP__MUI_A16__MUB base pointer */
  #define WAKEUP__MUI_A16__MUB                     ((MU_Type *)WAKEUP__MUI_A16__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A16__MUB base pointer */
  #define WAKEUP__MUI_A16__MUB_NS                  ((MU_Type *)WAKEUP__MUI_A16__MUB_BASE_NS)
  /** Peripheral WAKEUP__MUI_A17__MUA base address */
  #define WAKEUP__MUI_A17__MUA_BASE                (0x52B50000u)
  /** Peripheral WAKEUP__MUI_A17__MUA base address */
  #define WAKEUP__MUI_A17__MUA_BASE_NS             (0x42B50000u)
  /** Peripheral WAKEUP__MUI_A17__MUA base pointer */
  #define WAKEUP__MUI_A17__MUA                     ((MU_Type *)WAKEUP__MUI_A17__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A17__MUA base pointer */
  #define WAKEUP__MUI_A17__MUA_NS                  ((MU_Type *)WAKEUP__MUI_A17__MUA_BASE_NS)
  /** Peripheral WAKEUP__MUI_A17__MUB base address */
  #define WAKEUP__MUI_A17__MUB_BASE                (0x52B60000u)
  /** Peripheral WAKEUP__MUI_A17__MUB base address */
  #define WAKEUP__MUI_A17__MUB_BASE_NS             (0x42B60000u)
  /** Peripheral WAKEUP__MUI_A17__MUB base pointer */
  #define WAKEUP__MUI_A17__MUB                     ((MU_Type *)WAKEUP__MUI_A17__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A17__MUB base pointer */
  #define WAKEUP__MUI_A17__MUB_NS                  ((MU_Type *)WAKEUP__MUI_A17__MUB_BASE_NS)
  /** Peripheral WAKEUP__MUI_A18__MUA base address */
  #define WAKEUP__MUI_A18__MUA_BASE                (0x52B70000u)
  /** Peripheral WAKEUP__MUI_A18__MUA base address */
  #define WAKEUP__MUI_A18__MUA_BASE_NS             (0x42B70000u)
  /** Peripheral WAKEUP__MUI_A18__MUA base pointer */
  #define WAKEUP__MUI_A18__MUA                     ((MU_Type *)WAKEUP__MUI_A18__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A18__MUA base pointer */
  #define WAKEUP__MUI_A18__MUA_NS                  ((MU_Type *)WAKEUP__MUI_A18__MUA_BASE_NS)
  /** Peripheral WAKEUP__MUI_A18__MUB base address */
  #define WAKEUP__MUI_A18__MUB_BASE                (0x52B80000u)
  /** Peripheral WAKEUP__MUI_A18__MUB base address */
  #define WAKEUP__MUI_A18__MUB_BASE_NS             (0x42B80000u)
  /** Peripheral WAKEUP__MUI_A18__MUB base pointer */
  #define WAKEUP__MUI_A18__MUB                     ((MU_Type *)WAKEUP__MUI_A18__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A18__MUB base pointer */
  #define WAKEUP__MUI_A18__MUB_NS                  ((MU_Type *)WAKEUP__MUI_A18__MUB_BASE_NS)
  /** Array initializer of MU peripheral base addresses */
  #define MU_BASE_ADDRS                            { MU1_MUA_BASE, MU1_MUB_BASE, MU2_MUA_BASE, MU2_MUB_BASE, MU3_MUA_BASE, MU3_MUB_BASE, MU4_MUA_BASE, MU4_MUB_BASE, MU5_MUA_BASE, MU5_MUB_BASE, MU6_MUA_BASE, MU6_MUB_BASE, MU7_MUA_BASE, MU7_MUB_BASE, MU8_MUA_BASE, MU8_MUB_BASE, MU9_MUA_BASE, MU9_MUB_BASE, NETC__MUA1__MUA_BASE, NETC__MUA1__MUB_BASE, NETC__MUA2__MUA_BASE, NETC__MUA2__MUB_BASE, NETC__MUA3__MUA_BASE, NETC__MUA3__MUB_BASE, NETC__MUA4__MUA_BASE, NETC__MUA4__MUB_BASE, WAKEUP__MUI_A10__MUA_BASE, WAKEUP__MUI_A10__MUB_BASE, WAKEUP__MUI_A11__MUA_BASE, WAKEUP__MUI_A11__MUB_BASE, WAKEUP__MUI_A12__MUA_BASE, WAKEUP__MUI_A12__MUB_BASE, WAKEUP__MUI_A13__MUA_BASE, WAKEUP__MUI_A13__MUB_BASE, WAKEUP__MUI_A14__MUA_BASE, WAKEUP__MUI_A14__MUB_BASE, WAKEUP__MUI_A15__MUA_BASE, WAKEUP__MUI_A15__MUB_BASE, WAKEUP__MUI_A16__MUA_BASE, WAKEUP__MUI_A16__MUB_BASE, WAKEUP__MUI_A17__MUA_BASE, WAKEUP__MUI_A17__MUB_BASE, WAKEUP__MUI_A18__MUA_BASE, WAKEUP__MUI_A18__MUB_BASE }
  /** Array initializer of MU peripheral base pointers */
  #define MU_BASE_PTRS                             { MU1_MUA, MU1_MUB, MU2_MUA, MU2_MUB, MU3_MUA, MU3_MUB, MU4_MUA, MU4_MUB, MU5_MUA, MU5_MUB, MU6_MUA, MU6_MUB, MU7_MUA, MU7_MUB, MU8_MUA, MU8_MUB, MU9_MUA, MU9_MUB, NETC__MUA1__MUA, NETC__MUA1__MUB, NETC__MUA2__MUA, NETC__MUA2__MUB, NETC__MUA3__MUA, NETC__MUA3__MUB, NETC__MUA4__MUA, NETC__MUA4__MUB, WAKEUP__MUI_A10__MUA, WAKEUP__MUI_A10__MUB, WAKEUP__MUI_A11__MUA, WAKEUP__MUI_A11__MUB, WAKEUP__MUI_A12__MUA, WAKEUP__MUI_A12__MUB, WAKEUP__MUI_A13__MUA, WAKEUP__MUI_A13__MUB, WAKEUP__MUI_A14__MUA, WAKEUP__MUI_A14__MUB, WAKEUP__MUI_A15__MUA, WAKEUP__MUI_A15__MUB, WAKEUP__MUI_A16__MUA, WAKEUP__MUI_A16__MUB, WAKEUP__MUI_A17__MUA, WAKEUP__MUI_A17__MUB, WAKEUP__MUI_A18__MUA, WAKEUP__MUI_A18__MUB }
  /** Array initializer of MU peripheral base addresses */
  #define MU_BASE_ADDRS_NS                         { MU1_MUA_BASE_NS, MU1_MUB_BASE_NS, MU2_MUA_BASE_NS, MU2_MUB_BASE_NS, MU3_MUA_BASE_NS, MU3_MUB_BASE_NS, MU4_MUA_BASE_NS, MU4_MUB_BASE_NS, MU5_MUA_BASE_NS, MU5_MUB_BASE_NS, MU6_MUA_BASE_NS, MU6_MUB_BASE_NS, MU7_MUA_BASE_NS, MU7_MUB_BASE_NS, MU8_MUA_BASE_NS, MU8_MUB_BASE_NS, MU9_MUA_BASE_NS, MU9_MUB_BASE_NS, NETC__MUA1__MUA_BASE_NS, NETC__MUA1__MUB_BASE_NS, NETC__MUA2__MUA_BASE_NS, NETC__MUA2__MUB_BASE_NS, NETC__MUA3__MUA_BASE_NS, NETC__MUA3__MUB_BASE_NS, NETC__MUA4__MUA_BASE_NS, NETC__MUA4__MUB_BASE_NS, WAKEUP__MUI_A10__MUA_BASE_NS, WAKEUP__MUI_A10__MUB_BASE_NS, WAKEUP__MUI_A11__MUA_BASE_NS, WAKEUP__MUI_A11__MUB_BASE_NS, WAKEUP__MUI_A12__MUA_BASE_NS, WAKEUP__MUI_A12__MUB_BASE_NS, WAKEUP__MUI_A13__MUA_BASE_NS, WAKEUP__MUI_A13__MUB_BASE_NS, WAKEUP__MUI_A14__MUA_BASE_NS, WAKEUP__MUI_A14__MUB_BASE_NS, WAKEUP__MUI_A15__MUA_BASE_NS, WAKEUP__MUI_A15__MUB_BASE_NS, WAKEUP__MUI_A16__MUA_BASE_NS, WAKEUP__MUI_A16__MUB_BASE_NS, WAKEUP__MUI_A17__MUA_BASE_NS, WAKEUP__MUI_A17__MUB_BASE_NS, WAKEUP__MUI_A18__MUA_BASE_NS, WAKEUP__MUI_A18__MUB_BASE_NS }
  /** Array initializer of MU peripheral base pointers */
  #define MU_BASE_PTRS_NS                          { MU1_MUA_NS, MU1_MUB_NS, MU2_MUA_NS, MU2_MUB_NS, MU3_MUA_NS, MU3_MUB_NS, MU4_MUA_NS, MU4_MUB_NS, MU5_MUA_NS, MU5_MUB_NS, MU6_MUA_NS, MU6_MUB_NS, MU7_MUA_NS, MU7_MUB_NS, MU8_MUA_NS, MU8_MUB_NS, MU9_MUA_NS, MU9_MUB_NS, NETC__MUA1__MUA_NS, NETC__MUA1__MUB_NS, NETC__MUA2__MUA_NS, NETC__MUA2__MUB_NS, NETC__MUA3__MUA_NS, NETC__MUA3__MUB_NS, NETC__MUA4__MUA_NS, NETC__MUA4__MUB_NS, WAKEUP__MUI_A10__MUA_NS, WAKEUP__MUI_A10__MUB_NS, WAKEUP__MUI_A11__MUA_NS, WAKEUP__MUI_A11__MUB_NS, WAKEUP__MUI_A12__MUA_NS, WAKEUP__MUI_A12__MUB_NS, WAKEUP__MUI_A13__MUA_NS, WAKEUP__MUI_A13__MUB_NS, WAKEUP__MUI_A14__MUA_NS, WAKEUP__MUI_A14__MUB_NS, WAKEUP__MUI_A15__MUA_NS, WAKEUP__MUI_A15__MUB_NS, WAKEUP__MUI_A16__MUA_NS, WAKEUP__MUI_A16__MUB_NS, WAKEUP__MUI_A17__MUA_NS, WAKEUP__MUI_A17__MUB_NS, WAKEUP__MUI_A18__MUA_NS, WAKEUP__MUI_A18__MUB_NS }
#else
  /** Peripheral MU1_MUA base address */
  #define MU1_MUA_BASE                             (0x44220000u)
  /** Peripheral MU1_MUA base pointer */
  #define MU1_MUA                                  ((MU_Type *)MU1_MUA_BASE)
  /** Peripheral MU1_MUB base address */
  #define MU1_MUB_BASE                             (0x44230000u)
  /** Peripheral MU1_MUB base pointer */
  #define MU1_MUB                                  ((MU_Type *)MU1_MUB_BASE)
  /** Peripheral MU2_MUA base address */
  #define MU2_MUA_BASE                             (0x445B0000u)
  /** Peripheral MU2_MUA base pointer */
  #define MU2_MUA                                  ((MU_Type *)MU2_MUA_BASE)
  /** Peripheral MU2_MUB base address */
  #define MU2_MUB_BASE                             (0x445C0000u)
  /** Peripheral MU2_MUB base pointer */
  #define MU2_MUB                                  ((MU_Type *)MU2_MUB_BASE)
  /** Peripheral MU3_MUA base address */
  #define MU3_MUA_BASE                             (0x445D0000u)
  /** Peripheral MU3_MUA base pointer */
  #define MU3_MUA                                  ((MU_Type *)MU3_MUA_BASE)
  /** Peripheral MU3_MUB base address */
  #define MU3_MUB_BASE                             (0x445E0000u)
  /** Peripheral MU3_MUB base pointer */
  #define MU3_MUB                                  ((MU_Type *)MU3_MUB_BASE)
  /** Peripheral MU4_MUA base address */
  #define MU4_MUA_BASE                             (0x445F0000u)
  /** Peripheral MU4_MUA base pointer */
  #define MU4_MUA                                  ((MU_Type *)MU4_MUA_BASE)
  /** Peripheral MU4_MUB base address */
  #define MU4_MUB_BASE                             (0x44600000u)
  /** Peripheral MU4_MUB base pointer */
  #define MU4_MUB                                  ((MU_Type *)MU4_MUB_BASE)
  /** Peripheral MU5_MUA base address */
  #define MU5_MUA_BASE                             (0x44610000u)
  /** Peripheral MU5_MUA base pointer */
  #define MU5_MUA                                  ((MU_Type *)MU5_MUA_BASE)
  /** Peripheral MU5_MUB base address */
  #define MU5_MUB_BASE                             (0x44620000u)
  /** Peripheral MU5_MUB base pointer */
  #define MU5_MUB                                  ((MU_Type *)MU5_MUB_BASE)
  /** Peripheral MU6_MUA base address */
  #define MU6_MUA_BASE                             (0x44630000u)
  /** Peripheral MU6_MUA base pointer */
  #define MU6_MUA                                  ((MU_Type *)MU6_MUA_BASE)
  /** Peripheral MU6_MUB base address */
  #define MU6_MUB_BASE                             (0x44640000u)
  /** Peripheral MU6_MUB base pointer */
  #define MU6_MUB                                  ((MU_Type *)MU6_MUB_BASE)
  /** Peripheral MU7_MUA base address */
  #define MU7_MUA_BASE                             (0x44700000u)
  /** Peripheral MU7_MUA base pointer */
  #define MU7_MUA                                  ((MU_Type *)MU7_MUA_BASE)
  /** Peripheral MU7_MUB base address */
  #define MU7_MUB_BASE                             (0x44710000u)
  /** Peripheral MU7_MUB base pointer */
  #define MU7_MUB                                  ((MU_Type *)MU7_MUB_BASE)
  /** Peripheral MU8_MUA base address */
  #define MU8_MUA_BASE                             (0x44720000u)
  /** Peripheral MU8_MUA base pointer */
  #define MU8_MUA                                  ((MU_Type *)MU8_MUA_BASE)
  /** Peripheral MU8_MUB base address */
  #define MU8_MUB_BASE                             (0x44730000u)
  /** Peripheral MU8_MUB base pointer */
  #define MU8_MUB                                  ((MU_Type *)MU8_MUB_BASE)
  /** Peripheral MU9_MUA base address */
  #define MU9_MUA_BASE                             (0x44740000u)
  /** Peripheral MU9_MUA base pointer */
  #define MU9_MUA                                  ((MU_Type *)MU9_MUA_BASE)
  /** Peripheral MU9_MUB base address */
  #define MU9_MUB_BASE                             (0x44750000u)
  /** Peripheral MU9_MUB base pointer */
  #define MU9_MUB                                  ((MU_Type *)MU9_MUB_BASE)
  /** Peripheral NETC__MUA1__MUA base address */
  #define NETC__MUA1__MUA_BASE                     (0x4D120000u)
  /** Peripheral NETC__MUA1__MUA base pointer */
  #define NETC__MUA1__MUA                          ((MU_Type *)NETC__MUA1__MUA_BASE)
  /** Peripheral NETC__MUA1__MUB base address */
  #define NETC__MUA1__MUB_BASE                     (0x4D130000u)
  /** Peripheral NETC__MUA1__MUB base pointer */
  #define NETC__MUA1__MUB                          ((MU_Type *)NETC__MUA1__MUB_BASE)
  /** Peripheral NETC__MUA2__MUA base address */
  #define NETC__MUA2__MUA_BASE                     (0x4D140000u)
  /** Peripheral NETC__MUA2__MUA base pointer */
  #define NETC__MUA2__MUA                          ((MU_Type *)NETC__MUA2__MUA_BASE)
  /** Peripheral NETC__MUA2__MUB base address */
  #define NETC__MUA2__MUB_BASE                     (0x4D150000u)
  /** Peripheral NETC__MUA2__MUB base pointer */
  #define NETC__MUA2__MUB                          ((MU_Type *)NETC__MUA2__MUB_BASE)
  /** Peripheral NETC__MUA3__MUA base address */
  #define NETC__MUA3__MUA_BASE                     (0x4D160000u)
  /** Peripheral NETC__MUA3__MUA base pointer */
  #define NETC__MUA3__MUA                          ((MU_Type *)NETC__MUA3__MUA_BASE)
  /** Peripheral NETC__MUA3__MUB base address */
  #define NETC__MUA3__MUB_BASE                     (0x4D170000u)
  /** Peripheral NETC__MUA3__MUB base pointer */
  #define NETC__MUA3__MUB                          ((MU_Type *)NETC__MUA3__MUB_BASE)
  /** Peripheral NETC__MUA4__MUA base address */
  #define NETC__MUA4__MUA_BASE                     (0x4D180000u)
  /** Peripheral NETC__MUA4__MUA base pointer */
  #define NETC__MUA4__MUA                          ((MU_Type *)NETC__MUA4__MUA_BASE)
  /** Peripheral NETC__MUA4__MUB base address */
  #define NETC__MUA4__MUB_BASE                     (0x4D190000u)
  /** Peripheral NETC__MUA4__MUB base pointer */
  #define NETC__MUA4__MUB                          ((MU_Type *)NETC__MUA4__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A10__MUA base address */
  #define WAKEUP__MUI_A10__MUA_BASE                (0x42430000u)
  /** Peripheral WAKEUP__MUI_A10__MUA base pointer */
  #define WAKEUP__MUI_A10__MUA                     ((MU_Type *)WAKEUP__MUI_A10__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A10__MUB base address */
  #define WAKEUP__MUI_A10__MUB_BASE                (0x42440000u)
  /** Peripheral WAKEUP__MUI_A10__MUB base pointer */
  #define WAKEUP__MUI_A10__MUB                     ((MU_Type *)WAKEUP__MUI_A10__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A11__MUA base address */
  #define WAKEUP__MUI_A11__MUA_BASE                (0x42730000u)
  /** Peripheral WAKEUP__MUI_A11__MUA base pointer */
  #define WAKEUP__MUI_A11__MUA                     ((MU_Type *)WAKEUP__MUI_A11__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A11__MUB base address */
  #define WAKEUP__MUI_A11__MUB_BASE                (0x42740000u)
  /** Peripheral WAKEUP__MUI_A11__MUB base pointer */
  #define WAKEUP__MUI_A11__MUB                     ((MU_Type *)WAKEUP__MUI_A11__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A12__MUA base address */
  #define WAKEUP__MUI_A12__MUA_BASE                (0x42AB0000u)
  /** Peripheral WAKEUP__MUI_A12__MUA base pointer */
  #define WAKEUP__MUI_A12__MUA                     ((MU_Type *)WAKEUP__MUI_A12__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A12__MUB base address */
  #define WAKEUP__MUI_A12__MUB_BASE                (0x42AC0000u)
  /** Peripheral WAKEUP__MUI_A12__MUB base pointer */
  #define WAKEUP__MUI_A12__MUB                     ((MU_Type *)WAKEUP__MUI_A12__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A13__MUA base address */
  #define WAKEUP__MUI_A13__MUA_BASE                (0x42AD0000u)
  /** Peripheral WAKEUP__MUI_A13__MUA base pointer */
  #define WAKEUP__MUI_A13__MUA                     ((MU_Type *)WAKEUP__MUI_A13__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A13__MUB base address */
  #define WAKEUP__MUI_A13__MUB_BASE                (0x42AE0000u)
  /** Peripheral WAKEUP__MUI_A13__MUB base pointer */
  #define WAKEUP__MUI_A13__MUB                     ((MU_Type *)WAKEUP__MUI_A13__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A14__MUA base address */
  #define WAKEUP__MUI_A14__MUA_BASE                (0x42AF0000u)
  /** Peripheral WAKEUP__MUI_A14__MUA base pointer */
  #define WAKEUP__MUI_A14__MUA                     ((MU_Type *)WAKEUP__MUI_A14__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A14__MUB base address */
  #define WAKEUP__MUI_A14__MUB_BASE                (0x42B00000u)
  /** Peripheral WAKEUP__MUI_A14__MUB base pointer */
  #define WAKEUP__MUI_A14__MUB                     ((MU_Type *)WAKEUP__MUI_A14__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A15__MUA base address */
  #define WAKEUP__MUI_A15__MUA_BASE                (0x42B10000u)
  /** Peripheral WAKEUP__MUI_A15__MUA base pointer */
  #define WAKEUP__MUI_A15__MUA                     ((MU_Type *)WAKEUP__MUI_A15__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A15__MUB base address */
  #define WAKEUP__MUI_A15__MUB_BASE                (0x42B20000u)
  /** Peripheral WAKEUP__MUI_A15__MUB base pointer */
  #define WAKEUP__MUI_A15__MUB                     ((MU_Type *)WAKEUP__MUI_A15__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A16__MUA base address */
  #define WAKEUP__MUI_A16__MUA_BASE                (0x42B30000u)
  /** Peripheral WAKEUP__MUI_A16__MUA base pointer */
  #define WAKEUP__MUI_A16__MUA                     ((MU_Type *)WAKEUP__MUI_A16__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A16__MUB base address */
  #define WAKEUP__MUI_A16__MUB_BASE                (0x42B40000u)
  /** Peripheral WAKEUP__MUI_A16__MUB base pointer */
  #define WAKEUP__MUI_A16__MUB                     ((MU_Type *)WAKEUP__MUI_A16__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A17__MUA base address */
  #define WAKEUP__MUI_A17__MUA_BASE                (0x42B50000u)
  /** Peripheral WAKEUP__MUI_A17__MUA base pointer */
  #define WAKEUP__MUI_A17__MUA                     ((MU_Type *)WAKEUP__MUI_A17__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A17__MUB base address */
  #define WAKEUP__MUI_A17__MUB_BASE                (0x42B60000u)
  /** Peripheral WAKEUP__MUI_A17__MUB base pointer */
  #define WAKEUP__MUI_A17__MUB                     ((MU_Type *)WAKEUP__MUI_A17__MUB_BASE)
  /** Peripheral WAKEUP__MUI_A18__MUA base address */
  #define WAKEUP__MUI_A18__MUA_BASE                (0x42B70000u)
  /** Peripheral WAKEUP__MUI_A18__MUA base pointer */
  #define WAKEUP__MUI_A18__MUA                     ((MU_Type *)WAKEUP__MUI_A18__MUA_BASE)
  /** Peripheral WAKEUP__MUI_A18__MUB base address */
  #define WAKEUP__MUI_A18__MUB_BASE                (0x42B80000u)
  /** Peripheral WAKEUP__MUI_A18__MUB base pointer */
  #define WAKEUP__MUI_A18__MUB                     ((MU_Type *)WAKEUP__MUI_A18__MUB_BASE)
  /** Array initializer of MU peripheral base addresses */
  #define MU_BASE_ADDRS                            { MU1_MUA_BASE, MU1_MUB_BASE, MU2_MUA_BASE, MU2_MUB_BASE, MU3_MUA_BASE, MU3_MUB_BASE, MU4_MUA_BASE, MU4_MUB_BASE, MU5_MUA_BASE, MU5_MUB_BASE, MU6_MUA_BASE, MU6_MUB_BASE, MU7_MUA_BASE, MU7_MUB_BASE, MU8_MUA_BASE, MU8_MUB_BASE, MU9_MUA_BASE, MU9_MUB_BASE, NETC__MUA1__MUA_BASE, NETC__MUA1__MUB_BASE, NETC__MUA2__MUA_BASE, NETC__MUA2__MUB_BASE, NETC__MUA3__MUA_BASE, NETC__MUA3__MUB_BASE, NETC__MUA4__MUA_BASE, NETC__MUA4__MUB_BASE, WAKEUP__MUI_A10__MUA_BASE, WAKEUP__MUI_A10__MUB_BASE, WAKEUP__MUI_A11__MUA_BASE, WAKEUP__MUI_A11__MUB_BASE, WAKEUP__MUI_A12__MUA_BASE, WAKEUP__MUI_A12__MUB_BASE, WAKEUP__MUI_A13__MUA_BASE, WAKEUP__MUI_A13__MUB_BASE, WAKEUP__MUI_A14__MUA_BASE, WAKEUP__MUI_A14__MUB_BASE, WAKEUP__MUI_A15__MUA_BASE, WAKEUP__MUI_A15__MUB_BASE, WAKEUP__MUI_A16__MUA_BASE, WAKEUP__MUI_A16__MUB_BASE, WAKEUP__MUI_A17__MUA_BASE, WAKEUP__MUI_A17__MUB_BASE, WAKEUP__MUI_A18__MUA_BASE, WAKEUP__MUI_A18__MUB_BASE }
  /** Array initializer of MU peripheral base pointers */
  #define MU_BASE_PTRS                             { MU1_MUA, MU1_MUB, MU2_MUA, MU2_MUB, MU3_MUA, MU3_MUB, MU4_MUA, MU4_MUB, MU5_MUA, MU5_MUB, MU6_MUA, MU6_MUB, MU7_MUA, MU7_MUB, MU8_MUA, MU8_MUB, MU9_MUA, MU9_MUB, NETC__MUA1__MUA, NETC__MUA1__MUB, NETC__MUA2__MUA, NETC__MUA2__MUB, NETC__MUA3__MUA, NETC__MUA3__MUB, NETC__MUA4__MUA, NETC__MUA4__MUB, WAKEUP__MUI_A10__MUA, WAKEUP__MUI_A10__MUB, WAKEUP__MUI_A11__MUA, WAKEUP__MUI_A11__MUB, WAKEUP__MUI_A12__MUA, WAKEUP__MUI_A12__MUB, WAKEUP__MUI_A13__MUA, WAKEUP__MUI_A13__MUB, WAKEUP__MUI_A14__MUA, WAKEUP__MUI_A14__MUB, WAKEUP__MUI_A15__MUA, WAKEUP__MUI_A15__MUB, WAKEUP__MUI_A16__MUA, WAKEUP__MUI_A16__MUB, WAKEUP__MUI_A17__MUA, WAKEUP__MUI_A17__MUB, WAKEUP__MUI_A18__MUA, WAKEUP__MUI_A18__MUB }
#endif
/** Interrupt vectors for the MU peripheral type */
#define MU_IRQS                                  { MU1_A_IRQn, MU1_B_IRQn, MU2_A_IRQn, MU2_B_IRQn, MU3_A_IRQn, MU3_B_IRQn, MU4_A_IRQn, MU4_B_IRQn, MU5_A_IRQn, MU5_B_IRQn, MU6_A_IRQn, MU6_B_IRQn, MU7_A_IRQn, MU7_B_IRQn, MU8_A_IRQn, MU8_B_IRQn, MU9_A_IRQn, MU9_B_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn }

/** Peripheral MU_ELE0 base address */
#define MU_ELE0_BASE (0x47520000u)
/** Peripheral MU_ELE0 base pointer */
#define MU_ELE0      ((MU_Type *)MU_ELE0_BASE)

/*!
 * @}
 */ /* end of group MU_Peripheral_Access_Layer */

#endif  /* #if !defined(MIMX9494_MU_H_) */
