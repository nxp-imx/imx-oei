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
 * @file MIMX9494_SYS_CTR_COMPARE.h
 * @version 1.0
 * @date 2023-11-01
 * @brief CMSIS Peripheral Access Layer for MIMX9494_SYS_CTR_COMPARE
 *
 * CMSIS Peripheral Access Layer for MIMX9494
 */

/* Prevention from multiple including the same memory map */
#if !defined(MIMX9494_SYS_CTR_COMPARE_H_)  /* Check if memory map has not been already included */
#define MIMX9494_SYS_CTR_COMPARE_H_

#include "MIMX943_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SYS_CTR_COMPARE Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYS_CTR_COMPARE_Peripheral_Access_Layer SYS_CTR_COMPARE Peripheral Access Layer
 * @{
 */

/** SYS_CTR_COMPARE - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[32];
  __IO uint32_t CMPCVL0;                           /**< Compare Count Value Low, offset: 0x20 */
  __IO uint32_t CMPCVH0;                           /**< Compare Count Value High, offset: 0x24 */
       uint8_t RESERVED_1[4];
  __IO uint32_t CMPCR0;                            /**< Compare Control, offset: 0x2C */
       uint8_t RESERVED_2[240];
  __IO uint32_t CMPCVL1;                           /**< Compare Count Value Low, offset: 0x120 */
  __IO uint32_t CMPCVH1;                           /**< Compare Count Value High, offset: 0x124 */
       uint8_t RESERVED_3[4];
  __IO uint32_t CMPCR1;                            /**< Compare Control, offset: 0x12C */
       uint8_t RESERVED_4[3744];
  __I  uint32_t CNTID0;                            /**< Counter ID, offset: 0xFD0 */
} SYS_CTR_COMPARE_Type;

/* ----------------------------------------------------------------------------
   -- SYS_CTR_COMPARE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYS_CTR_COMPARE_Register_Masks SYS_CTR_COMPARE Register Masks
 * @{
 */

/*! @name CMPCVL0 - Compare Count Value Low */
/*! @{ */

#define SYS_CTR_COMPARE_CMPCVL0_CMPCV0_MASK      (0xFFFFFFFFU)
#define SYS_CTR_COMPARE_CMPCVL0_CMPCV0_SHIFT     (0U)
/*! CMPCV0 - Compare Count Value Bits [31:0] */
#define SYS_CTR_COMPARE_CMPCVL0_CMPCV0(x)        (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CMPCVL0_CMPCV0_SHIFT)) & SYS_CTR_COMPARE_CMPCVL0_CMPCV0_MASK)
/*! @} */

/*! @name CMPCVH0 - Compare Count Value High */
/*! @{ */

#define SYS_CTR_COMPARE_CMPCVH0_CMPCV1_MASK      (0xFFFFFFU)
#define SYS_CTR_COMPARE_CMPCVH0_CMPCV1_SHIFT     (0U)
/*! CMPCV1 - Compare Count Value Bits [55:32] */
#define SYS_CTR_COMPARE_CMPCVH0_CMPCV1(x)        (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CMPCVH0_CMPCV1_SHIFT)) & SYS_CTR_COMPARE_CMPCVH0_CMPCV1_MASK)
/*! @} */

/*! @name CMPCR0 - Compare Control */
/*! @{ */

#define SYS_CTR_COMPARE_CMPCR0_EN_MASK           (0x1U)
#define SYS_CTR_COMPARE_CMPCR0_EN_SHIFT          (0U)
/*! EN - Compare Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define SYS_CTR_COMPARE_CMPCR0_EN(x)             (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CMPCR0_EN_SHIFT)) & SYS_CTR_COMPARE_CMPCR0_EN_MASK)

#define SYS_CTR_COMPARE_CMPCR0_IMASK_MASK        (0x2U)
#define SYS_CTR_COMPARE_CMPCR0_IMASK_SHIFT       (1U)
/*! IMASK - Interrupt Request Mask
 *  0b0..Not masked
 *  0b1..Masked
 */
#define SYS_CTR_COMPARE_CMPCR0_IMASK(x)          (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CMPCR0_IMASK_SHIFT)) & SYS_CTR_COMPARE_CMPCR0_IMASK_MASK)

#define SYS_CTR_COMPARE_CMPCR0_ISTAT_MASK        (0x4U)
#define SYS_CTR_COMPARE_CMPCR0_ISTAT_SHIFT       (2U)
/*! ISTAT - Compare Interrupt Status
 *  0b0..Either less than the compare value or compare is disabled
 *  0b1..Greater than or equal to the compare value and compare is enabled
 */
#define SYS_CTR_COMPARE_CMPCR0_ISTAT(x)          (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CMPCR0_ISTAT_SHIFT)) & SYS_CTR_COMPARE_CMPCR0_ISTAT_MASK)
/*! @} */

/*! @name CMPCVL1 - Compare Count Value Low */
/*! @{ */

#define SYS_CTR_COMPARE_CMPCVL1_CMPCV0_MASK      (0xFFFFFFFFU)
#define SYS_CTR_COMPARE_CMPCVL1_CMPCV0_SHIFT     (0U)
/*! CMPCV0 - Compare Count Value Bits [31:0] */
#define SYS_CTR_COMPARE_CMPCVL1_CMPCV0(x)        (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CMPCVL1_CMPCV0_SHIFT)) & SYS_CTR_COMPARE_CMPCVL1_CMPCV0_MASK)
/*! @} */

/*! @name CMPCVH1 - Compare Count Value High */
/*! @{ */

#define SYS_CTR_COMPARE_CMPCVH1_CMPCV1_MASK      (0xFFFFFFU)
#define SYS_CTR_COMPARE_CMPCVH1_CMPCV1_SHIFT     (0U)
/*! CMPCV1 - Compare Count Value Bits [55:32] */
#define SYS_CTR_COMPARE_CMPCVH1_CMPCV1(x)        (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CMPCVH1_CMPCV1_SHIFT)) & SYS_CTR_COMPARE_CMPCVH1_CMPCV1_MASK)
/*! @} */

/*! @name CMPCR1 - Compare Control */
/*! @{ */

#define SYS_CTR_COMPARE_CMPCR1_EN_MASK           (0x1U)
#define SYS_CTR_COMPARE_CMPCR1_EN_SHIFT          (0U)
/*! EN - Compare Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define SYS_CTR_COMPARE_CMPCR1_EN(x)             (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CMPCR1_EN_SHIFT)) & SYS_CTR_COMPARE_CMPCR1_EN_MASK)

#define SYS_CTR_COMPARE_CMPCR1_IMASK_MASK        (0x2U)
#define SYS_CTR_COMPARE_CMPCR1_IMASK_SHIFT       (1U)
/*! IMASK - Interrupt Request Mask
 *  0b0..Not masked
 *  0b1..Masked
 */
#define SYS_CTR_COMPARE_CMPCR1_IMASK(x)          (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CMPCR1_IMASK_SHIFT)) & SYS_CTR_COMPARE_CMPCR1_IMASK_MASK)

#define SYS_CTR_COMPARE_CMPCR1_ISTAT_MASK        (0x4U)
#define SYS_CTR_COMPARE_CMPCR1_ISTAT_SHIFT       (2U)
/*! ISTAT - Compare Interrupt Status
 *  0b0..Either less than the compare value or compare is disabled
 *  0b1..Greater than or equal to the compare value and compare is enabled
 */
#define SYS_CTR_COMPARE_CMPCR1_ISTAT(x)          (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CMPCR1_ISTAT_SHIFT)) & SYS_CTR_COMPARE_CMPCR1_ISTAT_MASK)
/*! @} */

/*! @name CNTID0 - Counter ID */
/*! @{ */

#define SYS_CTR_COMPARE_CNTID0_CNTID_MASK        (0xFFFFFFFFU)
#define SYS_CTR_COMPARE_CNTID0_CNTID_SHIFT       (0U)
/*! CNTID - Counter Identification */
#define SYS_CTR_COMPARE_CNTID0_CNTID(x)          (((uint32_t)(((uint32_t)(x)) << SYS_CTR_COMPARE_CNTID0_CNTID_SHIFT)) & SYS_CTR_COMPARE_CNTID0_CNTID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SYS_CTR_COMPARE_Register_Masks */


/* SYS_CTR_COMPARE - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral AON__SYS_CTR1__SYS_CTR_COMPARE base address */
  #define AON__SYS_CTR1__SYS_CTR_COMPARE_BASE      (0x542A0000u)
  /** Peripheral AON__SYS_CTR1__SYS_CTR_COMPARE base address */
  #define AON__SYS_CTR1__SYS_CTR_COMPARE_BASE_NS   (0x442A0000u)
  /** Peripheral AON__SYS_CTR1__SYS_CTR_COMPARE base pointer */
  #define AON__SYS_CTR1__SYS_CTR_COMPARE           ((SYS_CTR_COMPARE_Type *)AON__SYS_CTR1__SYS_CTR_COMPARE_BASE)
  /** Peripheral AON__SYS_CTR1__SYS_CTR_COMPARE base pointer */
  #define AON__SYS_CTR1__SYS_CTR_COMPARE_NS        ((SYS_CTR_COMPARE_Type *)AON__SYS_CTR1__SYS_CTR_COMPARE_BASE_NS)
  /** Array initializer of SYS_CTR_COMPARE peripheral base addresses */
  #define SYS_CTR_COMPARE_BASE_ADDRS               { AON__SYS_CTR1__SYS_CTR_COMPARE_BASE }
  /** Array initializer of SYS_CTR_COMPARE peripheral base pointers */
  #define SYS_CTR_COMPARE_BASE_PTRS                { AON__SYS_CTR1__SYS_CTR_COMPARE }
  /** Array initializer of SYS_CTR_COMPARE peripheral base addresses */
  #define SYS_CTR_COMPARE_BASE_ADDRS_NS            { AON__SYS_CTR1__SYS_CTR_COMPARE_BASE_NS }
  /** Array initializer of SYS_CTR_COMPARE peripheral base pointers */
  #define SYS_CTR_COMPARE_BASE_PTRS_NS             { AON__SYS_CTR1__SYS_CTR_COMPARE_NS }
#else
  /** Peripheral AON__SYS_CTR1__SYS_CTR_COMPARE base address */
  #define AON__SYS_CTR1__SYS_CTR_COMPARE_BASE      (0x442A0000u)
  /** Peripheral AON__SYS_CTR1__SYS_CTR_COMPARE base pointer */
  #define AON__SYS_CTR1__SYS_CTR_COMPARE           ((SYS_CTR_COMPARE_Type *)AON__SYS_CTR1__SYS_CTR_COMPARE_BASE)
  /** Array initializer of SYS_CTR_COMPARE peripheral base addresses */
  #define SYS_CTR_COMPARE_BASE_ADDRS               { AON__SYS_CTR1__SYS_CTR_COMPARE_BASE }
  /** Array initializer of SYS_CTR_COMPARE peripheral base pointers */
  #define SYS_CTR_COMPARE_BASE_PTRS                { AON__SYS_CTR1__SYS_CTR_COMPARE }
#endif

/*!
 * @}
 */ /* end of group SYS_CTR_COMPARE_Peripheral_Access_Layer */

#endif  /* #if !defined(MIMX9494_SYS_CTR_COMPARE_H_) */
