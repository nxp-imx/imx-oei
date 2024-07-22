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
 * @file MIMX9494_SRC_MEM.h
 * @version 1.0
 * @date 2023-11-01
 * @brief CMSIS Peripheral Access Layer for MIMX9494_SRC_MEM
 *
 * CMSIS Peripheral Access Layer for MIMX9494
 */

/* Prevention from multiple including the same memory map */
#if !defined(MIMX9494_SRC_MEM_H_)  /* Check if memory map has not been already included */
#define MIMX9494_SRC_MEM_H_

#include "MIMX943_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SRC_MEM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SRC_MEM_Peripheral_Access_Layer SRC_MEM Peripheral Access Layer
 * @{
 */

/** SRC_MEM - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4];
  __IO uint32_t MEM_CTRL;                          /**< MEM Low Power Control, offset: 0x4 */
  __IO uint32_t MEMLP_CTRL_0;                      /**< MEM Low Power Control_0, offset: 0x8 */
       uint8_t RESERVED_1[4];
  __IO uint32_t MEMLP_CTRL_1;                      /**< MEM Low Power Control_1, offset: 0x10 */
  __IO uint32_t MEMLP_CTRL_2;                      /**< MEM Low Power Control_2, offset: 0x14 */
  __I  uint32_t MEM_STAT;                          /**< MEM Status, offset: 0x18 */
} SRC_MEM_Type;

/* ----------------------------------------------------------------------------
   -- SRC_MEM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SRC_MEM_Register_Masks SRC_MEM Register Masks
 * @{
 */

/*! @name MEM_CTRL - MEM Low Power Control */
/*! @{ */

#define SRC_MEM_MEM_CTRL_MEM_LP_MODE_MASK        (0x2U)
#define SRC_MEM_MEM_CTRL_MEM_LP_MODE_SHIFT       (1U)
/*! MEM_LP_MODE - Memory Low Power Mode configuration. Locked by LOCK_CFG field.
 *  0b0..Power Down
 *  0b1..Retention Mode
 */
#define SRC_MEM_MEM_CTRL_MEM_LP_MODE(x)          (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEM_CTRL_MEM_LP_MODE_SHIFT)) & SRC_MEM_MEM_CTRL_MEM_LP_MODE_MASK)

#define SRC_MEM_MEM_CTRL_MEM_LF_CNT_CFG_MASK     (0xFF00U)
#define SRC_MEM_MEM_CTRL_MEM_LF_CNT_CFG_SHIFT    (8U)
/*! MEM_LF_CNT_CFG - MEM power up counter */
#define SRC_MEM_MEM_CTRL_MEM_LF_CNT_CFG(x)       (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEM_CTRL_MEM_LF_CNT_CFG_SHIFT)) & SRC_MEM_MEM_CTRL_MEM_LF_CNT_CFG_MASK)

#define SRC_MEM_MEM_CTRL_MEM_HF_CNT_CFG_MASK     (0xFF0000U)
#define SRC_MEM_MEM_CTRL_MEM_HF_CNT_CFG_SHIFT    (16U)
/*! MEM_HF_CNT_CFG - MEM power up counter */
#define SRC_MEM_MEM_CTRL_MEM_HF_CNT_CFG(x)       (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEM_CTRL_MEM_HF_CNT_CFG_SHIFT)) & SRC_MEM_MEM_CTRL_MEM_HF_CNT_CFG_MASK)

#define SRC_MEM_MEM_CTRL_LOCK_CFG_MASK           (0x1000000U)
#define SRC_MEM_MEM_CTRL_LOCK_CFG_SHIFT          (24U)
/*! LOCK_CFG - Configuration lock
 *  0b0..Not locked.
 *  0b1..Locked.
 */
#define SRC_MEM_MEM_CTRL_LOCK_CFG(x)             (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEM_CTRL_LOCK_CFG_SHIFT)) & SRC_MEM_MEM_CTRL_LOCK_CFG_MASK)
/*! @} */

/*! @name MEMLP_CTRL_0 - MEM Low Power Control_0 */
/*! @{ */

#define SRC_MEM_MEMLP_CTRL_0_MEMLP_ENT_CNT_MASK  (0xFFFFFFFFU)
#define SRC_MEM_MEMLP_CTRL_0_MEMLP_ENT_CNT_SHIFT (0U)
/*! MEMLP_ENT_CNT - Delay counter to start entering to memory low power mode. Locked by LOCK_CFG field */
#define SRC_MEM_MEMLP_CTRL_0_MEMLP_ENT_CNT(x)    (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEMLP_CTRL_0_MEMLP_ENT_CNT_SHIFT)) & SRC_MEM_MEMLP_CTRL_0_MEMLP_ENT_CNT_MASK)
/*! @} */

/*! @name MEMLP_CTRL_1 - MEM Low Power Control_1 */
/*! @{ */

#define SRC_MEM_MEMLP_CTRL_1_MEMLP_RET_PGEN_CNT_MASK (0xFFFFFFFFU)
#define SRC_MEM_MEMLP_CTRL_1_MEMLP_RET_PGEN_CNT_SHIFT (0U)
/*! MEMLP_RET_PGEN_CNT - Delay counter to interval for retn to pgen. Locked by LOCK_CFG field */
#define SRC_MEM_MEMLP_CTRL_1_MEMLP_RET_PGEN_CNT(x) (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEMLP_CTRL_1_MEMLP_RET_PGEN_CNT_SHIFT)) & SRC_MEM_MEMLP_CTRL_1_MEMLP_RET_PGEN_CNT_MASK)
/*! @} */

/*! @name MEMLP_CTRL_2 - MEM Low Power Control_2 */
/*! @{ */

#define SRC_MEM_MEMLP_CTRL_2_MEMLP_EXT_CNT_MASK  (0xFFFFFFFFU)
#define SRC_MEM_MEMLP_CTRL_2_MEMLP_EXT_CNT_SHIFT (0U)
/*! MEMLP_EXT_CNT - Delay counter to start exiting from memory low power mode. Locked by LOCK_CFG field */
#define SRC_MEM_MEMLP_CTRL_2_MEMLP_EXT_CNT(x)    (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEMLP_CTRL_2_MEMLP_EXT_CNT_SHIFT)) & SRC_MEM_MEMLP_CTRL_2_MEMLP_EXT_CNT_MASK)
/*! @} */

/*! @name MEM_STAT - MEM Status */
/*! @{ */

#define SRC_MEM_MEM_STAT_MEM_FSM_STAT_MASK       (0xFU)
#define SRC_MEM_MEM_STAT_MEM_FSM_STAT_SHIFT      (0U)
/*! MEM_FSM_STAT - MEM FSM status
 *  0b0000..MEM_IDLE_POR
 *  0b0001..MEM_IDLE_RUN
 *  0b0010..MEM_OFF_PRE
 *  0b0011..MEM_ENT_RET
 *  0b0100..MEM_ENT_PGEN
 *  0b0101..MEM_OFF_RSP
 *  0b0110..MEM_IDLE_SLEEP
 *  0b0111..MEM_ON_PRE
 *  0b1000..MEM_EXT_PGEN
 *  0b1001..MEM_EXT_RET
 *  0b1010..MEM_ON_RSP
 *  0b1011..Reserved
 *  0b1100..Reserved
 *  0b1101..Reserved
 *  0b1110..Reserved
 *  0b1111..Reserved
 */
#define SRC_MEM_MEM_STAT_MEM_FSM_STAT(x)         (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEM_STAT_MEM_FSM_STAT_SHIFT)) & SRC_MEM_MEM_STAT_MEM_FSM_STAT_MASK)

#define SRC_MEM_MEM_STAT_RET2N_STAT_MASK         (0x10U)
#define SRC_MEM_MEM_STAT_RET2N_STAT_SHIFT        (4U)
/*! RET2N_STAT - RET2N status
 *  0b0..Memory RET2N pin is low
 *  0b1..Memory RET2N pin is high
 */
#define SRC_MEM_MEM_STAT_RET2N_STAT(x)           (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEM_STAT_RET2N_STAT_SHIFT)) & SRC_MEM_MEM_STAT_RET2N_STAT_MASK)

#define SRC_MEM_MEM_STAT_RET1N_STAT_MASK         (0x20U)
#define SRC_MEM_MEM_STAT_RET1N_STAT_SHIFT        (5U)
/*! RET1N_STAT - RET1N status
 *  0b1..Memory RET1N pin is high
 *  0b0..Memory RET1N pin is low
 */
#define SRC_MEM_MEM_STAT_RET1N_STAT(x)           (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEM_STAT_RET1N_STAT_SHIFT)) & SRC_MEM_MEM_STAT_RET1N_STAT_MASK)

#define SRC_MEM_MEM_STAT_PGEN_STAT_MASK          (0x40U)
#define SRC_MEM_MEM_STAT_PGEN_STAT_SHIFT         (6U)
/*! PGEN_STAT - Power gate enable status
 *  0b0..Memory PGEN pin is low
 *  0b1..Memory PGEN pin is high
 */
#define SRC_MEM_MEM_STAT_PGEN_STAT(x)            (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEM_STAT_PGEN_STAT_SHIFT)) & SRC_MEM_MEM_STAT_PGEN_STAT_MASK)

#define SRC_MEM_MEM_STAT_MEM_STAT_MASK           (0x100U)
#define SRC_MEM_MEM_STAT_MEM_STAT_SHIFT          (8U)
/*! MEM_STAT - MEM status
 *  0b0..MEM exit low power
 *  0b1..MEM enter low power - retention1 mode or power down mode
 */
#define SRC_MEM_MEM_STAT_MEM_STAT(x)             (((uint32_t)(((uint32_t)(x)) << SRC_MEM_MEM_STAT_MEM_STAT_SHIFT)) & SRC_MEM_MEM_STAT_MEM_STAT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SRC_MEM_Register_Masks */


/* SRC_MEM - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral CCMSRCGPC__SRC__XSPR_AONMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_AONMIX_MEM_BASE     (0x54460900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_AONMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_AONMIX_MEM_BASE_NS  (0x44460900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_AONMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_AONMIX_MEM          ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_AONMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_AONMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_AONMIX_MEM_NS       ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_AONMIX_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M72MIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_M72MIX_MEM_BASE     (0x54461100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M72MIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_M72MIX_MEM_BASE_NS  (0x44461100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M72MIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_M72MIX_MEM          ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_M72MIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M72MIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_M72MIX_MEM_NS       ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_M72MIX_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_BASE (0x54461900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_BASE_NS (0x44461900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_NS ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_BASE (0x54461D00u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_BASE_NS (0x44461D00u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_NS ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_BASE (0x54462100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_BASE_NS (0x44462100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_NS ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_BASE (0x54462500u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_BASE_NS (0x44462500u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_NS ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0 base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_BASE (0x54462900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0 base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_BASE_NS (0x44462900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0 base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0 ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0 base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_NS ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1 base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_BASE (0x54462920u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1 base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_BASE_NS (0x44462920u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1 base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1 ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1 base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_NS ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DDRMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_BASE     (0x54462D00u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DDRMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_BASE_NS  (0x44462D00u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DDRMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_DDRMIX_MEM          ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DDRMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_NS       ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_BASE (0x54463100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_BASE_NS (0x44463100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM      ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_NS   ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M7MIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_M7MIX_MEM_BASE      (0x54463500u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M7MIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_M7MIX_MEM_BASE_NS   (0x44463500u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M7MIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_M7MIX_MEM           ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_M7MIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M7MIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_M7MIX_MEM_NS        ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_M7MIX_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_BASE    (0x54463900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_BASE_NS (0x44463900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM         ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_NS      ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NETCMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_BASE    (0x54464100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NETCMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_BASE_NS (0x44464100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NETCMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_NETCMIX_MEM         ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NETCMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_NS      ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0 base address */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_BASE    (0x54464500u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0 base address */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_BASE_NS (0x44464500u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0 base pointer */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0         ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0 base pointer */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_NS      ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1 base address */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_BASE    (0x54464520u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1 base address */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_BASE_NS (0x44464520u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1 base pointer */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1         ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1 base pointer */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_NS      ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NPUMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_BASE     (0x54464900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NPUMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_BASE_NS  (0x44464900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NPUMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_NPUMIX_MEM          ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NPUMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_NS       ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_BASE_NS)
  /** Peripheral CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_BASE  (0x54464D00u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_BASE_NS (0x44464D00u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM       ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_NS    ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_BASE_NS)
  /** Array initializer of SRC_MEM peripheral base addresses */
  #define SRC_MEM_BASE_ADDRS                       { CCMSRCGPC__SRC__XSPR_AONMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_M72MIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_BASE, CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_M7MIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_BASE, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_BASE, CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_BASE }
  /** Array initializer of SRC_MEM peripheral base pointers */
  #define SRC_MEM_BASE_PTRS                        { CCMSRCGPC__SRC__XSPR_AONMIX_MEM, CCMSRCGPC__SRC__XSPR_M72MIX_MEM, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1, CCMSRCGPC__SRC__XSPR_DDRMIX_MEM, CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM, CCMSRCGPC__SRC__XSPR_M7MIX_MEM, CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM, CCMSRCGPC__SRC__XSPR_NETCMIX_MEM, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1, CCMSRCGPC__SRC__XSPR_NPUMIX_MEM, CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM }
  /** Array initializer of SRC_MEM peripheral base addresses */
  #define SRC_MEM_BASE_ADDRS_NS                    { CCMSRCGPC__SRC__XSPR_AONMIX_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_M72MIX_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_BASE_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_BASE_NS, CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_M7MIX_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_BASE_NS, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_BASE_NS, CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_BASE_NS, CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_BASE_NS }
  /** Array initializer of SRC_MEM peripheral base pointers */
  #define SRC_MEM_BASE_PTRS_NS                     { CCMSRCGPC__SRC__XSPR_AONMIX_MEM_NS, CCMSRCGPC__SRC__XSPR_M72MIX_MEM_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_NS, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_NS, CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_NS, CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_NS, CCMSRCGPC__SRC__XSPR_M7MIX_MEM_NS, CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_NS, CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_NS, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_NS, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_NS, CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_NS, CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_NS }
#else
  /** Peripheral CCMSRCGPC__SRC__XSPR_AONMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_AONMIX_MEM_BASE     (0x44460900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_AONMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_AONMIX_MEM          ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_AONMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M72MIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_M72MIX_MEM_BASE     (0x44461100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M72MIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_M72MIX_MEM          ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_M72MIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_BASE (0x44461900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_BASE (0x44461D00u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_BASE (0x44462100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_BASE (0x44462500u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0 base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_BASE (0x44462900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0 base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0 ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1 base address */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_BASE (0x44462920u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1 base pointer */
  #define CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1 ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DDRMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_BASE     (0x44462D00u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DDRMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_DDRMIX_MEM          ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_BASE (0x44463100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM      ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M7MIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_M7MIX_MEM_BASE      (0x44463500u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_M7MIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_M7MIX_MEM           ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_M7MIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_BASE    (0x44463900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM         ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NETCMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_BASE    (0x44464100u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NETCMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_NETCMIX_MEM         ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0 base address */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_BASE    (0x44464500u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0 base pointer */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0         ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1 base address */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_BASE    (0x44464520u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1 base pointer */
  #define CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1         ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NPUMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_BASE     (0x44464900u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_NPUMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_NPUMIX_MEM          ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_BASE)
  /** Peripheral CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM base address */
  #define CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_BASE  (0x44464D00u)
  /** Peripheral CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM base pointer */
  #define CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM       ((SRC_MEM_Type *)CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_BASE)
  /** Array initializer of SRC_MEM peripheral base addresses */
  #define SRC_MEM_BASE_ADDRS                       { CCMSRCGPC__SRC__XSPR_AONMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_M72MIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0_BASE, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1_BASE, CCMSRCGPC__SRC__XSPR_DDRMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_M7MIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_NETCMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0_BASE, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1_BASE, CCMSRCGPC__SRC__XSPR_NPUMIX_MEM_BASE, CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM_BASE }
  /** Array initializer of SRC_MEM peripheral base pointers */
  #define SRC_MEM_BASE_PTRS                        { CCMSRCGPC__SRC__XSPR_AONMIX_MEM, CCMSRCGPC__SRC__XSPR_M72MIX_MEM, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE0_MEM, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE1_MEM, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE2_MEM, CCMSRCGPC__SRC__XSPR_CORTEXMIX_CORE3_MEM, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM0, CCMSRCGPC__SRC__XSPR_CORTEXMIX_PLATFORM_MEM1, CCMSRCGPC__SRC__XSPR_DDRMIX_MEM, CCMSRCGPC__SRC__XSPR_DISPLAYMIX_MEM, CCMSRCGPC__SRC__XSPR_M7MIX_MEM, CCMSRCGPC__SRC__XSPR_HSIOMIX_MEM, CCMSRCGPC__SRC__XSPR_NETCMIX_MEM, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM0, CCMSRCGPC__SRC__XSPR_NOCMIX_MEM1, CCMSRCGPC__SRC__XSPR_NPUMIX_MEM, CCMSRCGPC__SRC__XSPR_WAKEUPMIX_MEM }
#endif

/*!
 * @}
 */ /* end of group SRC_MEM_Peripheral_Access_Layer */

#endif  /* #if !defined(MIMX9494_SRC_MEM_H_) */
