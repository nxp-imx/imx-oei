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
**     Reference manual:    iMX94RM rev1 draftK
**     Version:             rev. 1.0, 2023-11-01
**     Build:               b240315
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MIMX9494_cm33_core0
**
**     Copyright 2025 NXP
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
 * @file MIMX9494_SYS_CTR_READ.h
 * @version 1.0
 * @date 2023-11-01
 * @brief CMSIS Peripheral Access Layer for MIMX9494_SYS_CTR_READ
 *
 * CMSIS Peripheral Access Layer for MIMX9494
 */

/* Prevention from multiple including the same memory map */
#if !defined(MIMX9494_SYS_CTR_READ_H_)  /* Check if memory map has not been already included */
#define MIMX9494_SYS_CTR_READ_H_

#include "MIMX94_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SYS_CTR_READ Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYS_CTR_READ_Peripheral_Access_Layer SYS_CTR_READ Peripheral Access Layer
 * @{
 */

/** SYS_CTR_READ - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[8];
  __I  uint32_t CNTCV0;                            /**< Counter Count Value Low, offset: 0x8 */
  __I  uint32_t CNTCV1;                            /**< Counter Count Value High, offset: 0xC */
       uint8_t RESERVED_1[4032];
  __I  uint32_t CNTID0;                            /**< Counter ID, offset: 0xFD0 */
} SYS_CTR_READ_Type;

/* ----------------------------------------------------------------------------
   -- SYS_CTR_READ Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYS_CTR_READ_Register_Masks SYS_CTR_READ Register Masks
 * @{
 */

/*! @name CNTCV0 - Counter Count Value Low */
/*! @{ */

#define SYS_CTR_READ_CNTCV0_CNTCV0_MASK          (0xFFFFFFFFU)
#define SYS_CTR_READ_CNTCV0_CNTCV0_SHIFT         (0U)
/*! CNTCV0 - Counter Count Value Bits [31:0] */
#define SYS_CTR_READ_CNTCV0_CNTCV0(x)            (((uint32_t)(((uint32_t)(x)) << SYS_CTR_READ_CNTCV0_CNTCV0_SHIFT)) & SYS_CTR_READ_CNTCV0_CNTCV0_MASK)
/*! @} */

/*! @name CNTCV1 - Counter Count Value High */
/*! @{ */

#define SYS_CTR_READ_CNTCV1_CNTCV1_MASK          (0xFFFFFFU)
#define SYS_CTR_READ_CNTCV1_CNTCV1_SHIFT         (0U)
/*! CNTCV1 - Counter Count Value Bits [55:32] */
#define SYS_CTR_READ_CNTCV1_CNTCV1(x)            (((uint32_t)(((uint32_t)(x)) << SYS_CTR_READ_CNTCV1_CNTCV1_SHIFT)) & SYS_CTR_READ_CNTCV1_CNTCV1_MASK)
/*! @} */

/*! @name CNTID0 - Counter ID */
/*! @{ */

#define SYS_CTR_READ_CNTID0_CNTID_MASK           (0xFFFFFFFFU)
#define SYS_CTR_READ_CNTID0_CNTID_SHIFT          (0U)
/*! CNTID - Counter Identification */
#define SYS_CTR_READ_CNTID0_CNTID(x)             (((uint32_t)(((uint32_t)(x)) << SYS_CTR_READ_CNTID0_CNTID_SHIFT)) & SYS_CTR_READ_CNTID0_CNTID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SYS_CTR_READ_Register_Masks */


/* SYS_CTR_READ - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral AON__SYS_CTR1__SYS_CTR_READ base address */
  #define AON__SYS_CTR1__SYS_CTR_READ_BASE         (0x542B0000u)
  /** Peripheral AON__SYS_CTR1__SYS_CTR_READ base address */
  #define AON__SYS_CTR1__SYS_CTR_READ_BASE_NS      (0x442B0000u)
  /** Peripheral AON__SYS_CTR1__SYS_CTR_READ base pointer */
  #define AON__SYS_CTR1__SYS_CTR_READ              ((SYS_CTR_READ_Type *)AON__SYS_CTR1__SYS_CTR_READ_BASE)
  /** Peripheral AON__SYS_CTR1__SYS_CTR_READ base pointer */
  #define AON__SYS_CTR1__SYS_CTR_READ_NS           ((SYS_CTR_READ_Type *)AON__SYS_CTR1__SYS_CTR_READ_BASE_NS)
  /** Array initializer of SYS_CTR_READ peripheral base addresses */
  #define SYS_CTR_READ_BASE_ADDRS                  { AON__SYS_CTR1__SYS_CTR_READ_BASE }
  /** Array initializer of SYS_CTR_READ peripheral base pointers */
  #define SYS_CTR_READ_BASE_PTRS                   { AON__SYS_CTR1__SYS_CTR_READ }
  /** Array initializer of SYS_CTR_READ peripheral base addresses */
  #define SYS_CTR_READ_BASE_ADDRS_NS               { AON__SYS_CTR1__SYS_CTR_READ_BASE_NS }
  /** Array initializer of SYS_CTR_READ peripheral base pointers */
  #define SYS_CTR_READ_BASE_PTRS_NS                { AON__SYS_CTR1__SYS_CTR_READ_NS }
#else
  /** Peripheral AON__SYS_CTR1__SYS_CTR_READ base address */
  #define AON__SYS_CTR1__SYS_CTR_READ_BASE         (0x442B0000u)
  /** Peripheral AON__SYS_CTR1__SYS_CTR_READ base pointer */
  #define AON__SYS_CTR1__SYS_CTR_READ              ((SYS_CTR_READ_Type *)AON__SYS_CTR1__SYS_CTR_READ_BASE)
  /** Array initializer of SYS_CTR_READ peripheral base addresses */
  #define SYS_CTR_READ_BASE_ADDRS                  { AON__SYS_CTR1__SYS_CTR_READ_BASE }
  /** Array initializer of SYS_CTR_READ peripheral base pointers */
  #define SYS_CTR_READ_BASE_PTRS                   { AON__SYS_CTR1__SYS_CTR_READ }
#endif

/*!
 * @}
 */ /* end of group SYS_CTR_READ_Peripheral_Access_Layer */

#endif  /* #if !defined(MIMX9494_SYS_CTR_READ_H_) */
