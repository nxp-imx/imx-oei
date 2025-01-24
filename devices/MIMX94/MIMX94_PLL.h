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
 * @file MIMX9494_PLL.h
 * @version 1.0
 * @date 2023-11-01
 * @brief CMSIS Peripheral Access Layer for MIMX9494_PLL
 *
 * CMSIS Peripheral Access Layer for MIMX9494
 */

/* Prevention from multiple including the same memory map */
#if !defined(MIMX9494_PLL_H_)  /* Check if memory map has not been already included */
#define MIMX9494_PLL_H_

#include "MIMX94_COMMON.h"

/* ----------------------------------------------------------------------------
   -- PLL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PLL_Peripheral_Access_Layer PLL Peripheral Access Layer
 * @{
 */

/** PLL - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0 */
    __IO uint32_t RW;                                /**< PLL Control, offset: 0x0 */
    __IO uint32_t SET;                               /**< PLL Control, offset: 0x4 */
    __IO uint32_t CLR;                               /**< PLL Control, offset: 0x8 */
    __IO uint32_t TOG;                               /**< PLL Control, offset: 0xC */
  } CTRL;
       uint8_t RESERVED_0[32];
  struct {                                         /* offset: 0x30 */
    __IO uint32_t RW;                                /**< Spread Spectrum, offset: 0x30, not available in all instances (available on 144 out of 192) */
    __IO uint32_t SET;                               /**< Spread Spectrum, offset: 0x34, not available in all instances (available on 144 out of 192) */
    __IO uint32_t CLR;                               /**< Spread Spectrum, offset: 0x38, not available in all instances (available on 144 out of 192) */
    __IO uint32_t TOG;                               /**< Spread Spectrum, offset: 0x3C, not available in all instances (available on 144 out of 192) */
  } SPREAD_SPECTRUM;
  struct {                                         /* offset: 0x40 */
    __IO uint32_t RW;                                /**< Numerator, offset: 0x40, not available in all instances (available on 144 out of 192) */
    __IO uint32_t SET;                               /**< Numerator, offset: 0x44, not available in all instances (available on 144 out of 192) */
    __IO uint32_t CLR;                               /**< Numerator, offset: 0x48, not available in all instances (available on 144 out of 192) */
    __IO uint32_t TOG;                               /**< Numerator, offset: 0x4C, not available in all instances (available on 144 out of 192) */
  } NUMERATOR;
  struct {                                         /* offset: 0x50 */
    __IO uint32_t RW;                                /**< Denominator, offset: 0x50, not available in all instances (available on 144 out of 192) */
    __IO uint32_t SET;                               /**< Denominator, offset: 0x54, not available in all instances (available on 144 out of 192) */
    __IO uint32_t CLR;                               /**< Denominator, offset: 0x58, not available in all instances (available on 144 out of 192) */
    __IO uint32_t TOG;                               /**< Denominator, offset: 0x5C, not available in all instances (available on 144 out of 192) */
  } DENOMINATOR;
  struct {                                         /* offset: 0x60 */
    __IO uint32_t RW;                                /**< PLL Dividers, offset: 0x60 */
    __IO uint32_t SET;                               /**< PLL Dividers, offset: 0x64 */
    __IO uint32_t CLR;                               /**< PLL Dividers, offset: 0x68 */
    __IO uint32_t TOG;                               /**< PLL Dividers, offset: 0x6C */
  } DIV;
  struct {                                         /* offset: 0x70, array step: 0x20 */
    struct {                                         /* offset: 0x70 */
      __IO uint32_t RW;                                /**< DFS Control, offset: 0x70, irregular array, not all indices are valid */
      __IO uint32_t SET;                               /**< DFS Control, offset: 0x74, irregular array, not all indices are valid */
      __IO uint32_t CLR;                               /**< DFS Control, offset: 0x78, irregular array, not all indices are valid */
      __IO uint32_t TOG;                               /**< DFS Control, offset: 0x7C, irregular array, not all indices are valid */
    } DFS_CTRL;
    struct {                                         /* offset: 0x80 */
      __IO uint32_t RW;                                /**< DFS Division_0..DFS Division_3, offset: 0x80, irregular array, not all indices are valid */
      __IO uint32_t SET;                               /**< DFS Division_0..DFS Division_3, offset: 0x84, irregular array, not all indices are valid */
      __IO uint32_t CLR;                               /**< DFS Division_0..DFS Division_3, offset: 0x88, irregular array, not all indices are valid */
      __IO uint32_t TOG;                               /**< DFS Division_0..DFS Division_3, offset: 0x8C, irregular array, not all indices are valid */
    } DFS_DIV;
  } NO_OF_DFS[4];
  __I  uint32_t PLL_STATUS;                        /**< PLL Status, offset: 0xF0 */
  __I  uint32_t DFS_STATUS;                        /**< DFS Status, offset: 0xF4, not available in all instances (available on 72 out of 192) */
} PLL_Type;

/* ----------------------------------------------------------------------------
   -- PLL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PLL_Register_Masks PLL Register Masks
 * @{
 */

/*! @name CTRL - PLL Control */
/*! @{ */

#define PLL_CTRL_POWERUP_MASK                    (0x1U)
#define PLL_CTRL_POWERUP_SHIFT                   (0U)
/*! POWERUP - Power Up
 *  0b0..Disable
 *  0b1..Enable
 */
#define PLL_CTRL_POWERUP(x)                      (((uint32_t)(((uint32_t)(x)) << PLL_CTRL_POWERUP_SHIFT)) & PLL_CTRL_POWERUP_MASK)

#define PLL_CTRL_CLKMUX_EN_MASK                  (0x2U)
#define PLL_CTRL_CLKMUX_EN_SHIFT                 (1U)
/*! CLKMUX_EN - CLKMUX Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define PLL_CTRL_CLKMUX_EN(x)                    (((uint32_t)(((uint32_t)(x)) << PLL_CTRL_CLKMUX_EN_SHIFT)) & PLL_CTRL_CLKMUX_EN_MASK)

#define PLL_CTRL_CLKMUX_BYPASS_MASK              (0x4U)
#define PLL_CTRL_CLKMUX_BYPASS_SHIFT             (2U)
/*! CLKMUX_BYPASS - CLKMUX_Bypass
 *  0b0..Normal mode
 *  0b1..PLL Bypass mode
 */
#define PLL_CTRL_CLKMUX_BYPASS(x)                (((uint32_t)(((uint32_t)(x)) << PLL_CTRL_CLKMUX_BYPASS_SHIFT)) & PLL_CTRL_CLKMUX_BYPASS_MASK)

#define PLL_CTRL_SPREADCTL_MASK                  (0x100U)
#define PLL_CTRL_SPREADCTL_SHIFT                 (8U)
/*! SPREADCTL - Modulation Type Select
 *  0b0..Centered around nominal frequency
 *  0b1..Spread below nominal frequency
 */
#define PLL_CTRL_SPREADCTL(x)                    (((uint32_t)(((uint32_t)(x)) << PLL_CTRL_SPREADCTL_SHIFT)) & PLL_CTRL_SPREADCTL_MASK)

#define PLL_CTRL_HW_CTRL_SEL_MASK                (0x10000U)
#define PLL_CTRL_HW_CTRL_SEL_SHIFT               (16U)
/*! HW_CTRL_SEL - Hardware Control Select
 *  0b0..Disable
 *  0b1..Enable
 */
#define PLL_CTRL_HW_CTRL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << PLL_CTRL_HW_CTRL_SEL_SHIFT)) & PLL_CTRL_HW_CTRL_SEL_MASK)

#define PLL_CTRL_LOCK_BYPASS_MASK                (0x80000000U)
#define PLL_CTRL_LOCK_BYPASS_SHIFT               (31U)
/*! LOCK_BYPASS - Lock Bypass
 *  0b0..Disable
 *  0b1..Enable
 */
#define PLL_CTRL_LOCK_BYPASS(x)                  (((uint32_t)(((uint32_t)(x)) << PLL_CTRL_LOCK_BYPASS_SHIFT)) & PLL_CTRL_LOCK_BYPASS_MASK)
/*! @} */

/*! @name SPREAD_SPECTRUM - Spread Spectrum */
/*! @{ */

#define PLL_SPREAD_SPECTRUM_STEP_MASK            (0x7FFFU)
#define PLL_SPREAD_SPECTRUM_STEP_SHIFT           (0U)
/*! STEP - Step */
#define PLL_SPREAD_SPECTRUM_STEP(x)              (((uint32_t)(((uint32_t)(x)) << PLL_SPREAD_SPECTRUM_STEP_SHIFT)) & PLL_SPREAD_SPECTRUM_STEP_MASK)

#define PLL_SPREAD_SPECTRUM_ENABLE_MASK          (0x8000U)
#define PLL_SPREAD_SPECTRUM_ENABLE_SHIFT         (15U)
/*! ENABLE - Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define PLL_SPREAD_SPECTRUM_ENABLE(x)            (((uint32_t)(((uint32_t)(x)) << PLL_SPREAD_SPECTRUM_ENABLE_SHIFT)) & PLL_SPREAD_SPECTRUM_ENABLE_MASK)

#define PLL_SPREAD_SPECTRUM_STOP_MASK            (0xFFFF0000U)
#define PLL_SPREAD_SPECTRUM_STOP_SHIFT           (16U)
/*! STOP - Stop */
#define PLL_SPREAD_SPECTRUM_STOP(x)              (((uint32_t)(((uint32_t)(x)) << PLL_SPREAD_SPECTRUM_STOP_SHIFT)) & PLL_SPREAD_SPECTRUM_STOP_MASK)
/*! @} */

/*! @name NUMERATOR - Numerator */
/*! @{ */

#define PLL_NUMERATOR_MFN_MASK                   (0xFFFFFFFCU)
#define PLL_NUMERATOR_MFN_SHIFT                  (2U)
/*! MFN - Numerator */
#define PLL_NUMERATOR_MFN(x)                     (((uint32_t)(((uint32_t)(x)) << PLL_NUMERATOR_MFN_SHIFT)) & PLL_NUMERATOR_MFN_MASK)
/*! @} */

/*! @name DENOMINATOR - Denominator */
/*! @{ */

#define PLL_DENOMINATOR_MFD_MASK                 (0x3FFFFFFFU)
#define PLL_DENOMINATOR_MFD_SHIFT                (0U)
/*! MFD - Denominator */
#define PLL_DENOMINATOR_MFD(x)                   (((uint32_t)(((uint32_t)(x)) << PLL_DENOMINATOR_MFD_SHIFT)) & PLL_DENOMINATOR_MFD_MASK)
/*! @} */

/*! @name DIV - PLL Dividers */
/*! @{ */

#define PLL_DIV_ODIV_MASK                        (0xFFU)
#define PLL_DIV_ODIV_SHIFT                       (0U)
/*! ODIV - Output Frequency Divider for Clock Output
 *  0b00000000..Divide by 2
 *  0b00000001..Divide by 3
 *  0b00000010..Divide by 2
 *  0b00000011..Divide by 3
 *  0b00000100..Divide by 4
 *  0b00000101..Divide by 5
 *  0b00000110..Divide by 6
 *  0b00001010..Divide by 10
 *  0b10000010..Divide by 130
 *  0b11111111..Divide by 255
 */
#define PLL_DIV_ODIV(x)                          (((uint32_t)(((uint32_t)(x)) << PLL_DIV_ODIV_SHIFT)) & PLL_DIV_ODIV_MASK)

#define PLL_DIV_RDIV_MASK                        (0xE000U)
#define PLL_DIV_RDIV_SHIFT                       (13U)
/*! RDIV - Input Clock Predivider
 *  0b000..Divide by 1
 *  0b001..Divide by 1
 *  0b010..Divide by 2
 *  0b011..Divide by 3
 *  0b100..Divide by 4
 *  0b101..Divide by 5
 *  0b110..Divide by 6
 *  0b111..Divide by 7
 */
#define PLL_DIV_RDIV(x)                          (((uint32_t)(((uint32_t)(x)) << PLL_DIV_RDIV_SHIFT)) & PLL_DIV_RDIV_MASK)

#define PLL_DIV_MFI_MASK                         (0x1FF0000U)
#define PLL_DIV_MFI_SHIFT                        (16U)
/*! MFI - Integer Portion of Loop Divider */
#define PLL_DIV_MFI(x)                           (((uint32_t)(((uint32_t)(x)) << PLL_DIV_MFI_SHIFT)) & PLL_DIV_MFI_MASK)
/*! @} */

/*! @name DFS - DFS Control */
/*! @{ */

#define PLL_NO_OF_DFS_HW_CTRL_SEL_MASK                 (0x10000U)
#define PLL_NO_OF_DFS_HW_CTRL_SEL_SHIFT                (16U)
/*! HW_CTRL_SEL - Hardware Control Select
 *  0b0..Disable. DFS is controlled by register.
 *  0b1..Enable. DFS is controlled by hardware inputs.
 */
#define PLL_NO_OF_DFS_HW_CTRL_SEL(x)                   (((uint32_t)(((uint32_t)(x)) << PLL_NO_OF_DFS_HW_CTRL_SEL_SHIFT)) & PLL_NO_OF_DFS_HW_CTRL_SEL_MASK)

#define PLL_NO_OF_DFS_BYPASS_EN_MASK                   (0x800000U)
#define PLL_NO_OF_DFS_BYPASS_EN_SHIFT                  (23U)
/*! BYPASS_EN - Bypass Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define PLL_NO_OF_DFS_BYPASS_EN(x)                     (((uint32_t)(((uint32_t)(x)) << PLL_NO_OF_DFS_BYPASS_EN_SHIFT)) & PLL_NO_OF_DFS_BYPASS_EN_MASK)

#define PLL_NO_OF_DFS_CLKOUT_DIVBY2_EN_MASK            (0x20000000U)
#define PLL_NO_OF_DFS_CLKOUT_DIVBY2_EN_SHIFT           (29U)
/*! CLKOUT_DIVBY2_EN - DFS Clock Output Divide by 2 Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define PLL_NO_OF_DFS_CLKOUT_DIVBY2_EN(x)              (((uint32_t)(((uint32_t)(x)) << PLL_NO_OF_DFS_CLKOUT_DIVBY2_EN_SHIFT)) & PLL_NO_OF_DFS_CLKOUT_DIVBY2_EN_MASK)

#define PLL_NO_OF_DFS_CLKOUT_EN_MASK                   (0x40000000U)
#define PLL_NO_OF_DFS_CLKOUT_EN_SHIFT                  (30U)
/*! CLKOUT_EN - DFS Clock Output Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define PLL_NO_OF_DFS_CLKOUT_EN(x)                     (((uint32_t)(((uint32_t)(x)) << PLL_NO_OF_DFS_CLKOUT_EN_SHIFT)) & PLL_NO_OF_DFS_CLKOUT_EN_MASK)

#define PLL_NO_OF_DFS_ENABLE_MASK                      (0x80000000U)
#define PLL_NO_OF_DFS_ENABLE_SHIFT                     (31U)
/*! ENABLE - DFS Block Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define PLL_NO_OF_DFS_ENABLE(x)                        (((uint32_t)(((uint32_t)(x)) << PLL_NO_OF_DFS_ENABLE_SHIFT)) & PLL_NO_OF_DFS_ENABLE_MASK)
/*! @} */

/*! @name DFS - DFS Division_0..DFS Division_3 */
/*! @{ */

#define PLL_NO_OF_DFS_MFN_MASK                         (0x7U)
#define PLL_NO_OF_DFS_MFN_SHIFT                        (0U)
/*! MFN - MFN */
#define PLL_NO_OF_DFS_MFN(x)                           (((uint32_t)(((uint32_t)(x)) << PLL_NO_OF_DFS_MFN_SHIFT)) & PLL_NO_OF_DFS_MFN_MASK)

#define PLL_NO_OF_DFS_MFI_MASK                         (0xFF00U)
#define PLL_NO_OF_DFS_MFI_SHIFT                        (8U)
/*! MFI - MFI */
#define PLL_NO_OF_DFS_MFI(x)                           (((uint32_t)(((uint32_t)(x)) << PLL_NO_OF_DFS_MFI_SHIFT)) & PLL_NO_OF_DFS_MFI_MASK)
/*! @} */

/*! @name PLL_STATUS - PLL Status */
/*! @{ */

#define PLL_PLL_STATUS_PLL_LOCK_MASK             (0x1U)
#define PLL_PLL_STATUS_PLL_LOCK_SHIFT            (0U)
/*! PLL_LOCK - PLL_LOCK */
#define PLL_PLL_STATUS_PLL_LOCK(x)               (((uint32_t)(((uint32_t)(x)) << PLL_PLL_STATUS_PLL_LOCK_SHIFT)) & PLL_PLL_STATUS_PLL_LOCK_MASK)

#define PLL_PLL_STATUS_PLL_LOL_MASK              (0x2U)
#define PLL_PLL_STATUS_PLL_LOL_SHIFT             (1U)
/*! PLL_LOL - PLL_LOL */
#define PLL_PLL_STATUS_PLL_LOL(x)                (((uint32_t)(((uint32_t)(x)) << PLL_PLL_STATUS_PLL_LOL_SHIFT)) & PLL_PLL_STATUS_PLL_LOL_MASK)

#define PLL_PLL_STATUS_ANA_MFN_MASK              (0xFFFFFFFCU)
#define PLL_PLL_STATUS_ANA_MFN_SHIFT             (2U)
/*! ANA_MFN - ANA_MFN */
#define PLL_PLL_STATUS_ANA_MFN(x)                (((uint32_t)(((uint32_t)(x)) << PLL_PLL_STATUS_ANA_MFN_SHIFT)) & PLL_PLL_STATUS_ANA_MFN_MASK)
/*! @} */

/*! @name DFS_STATUS - DFS Status */
/*! @{ */

#define PLL_DFS_STATUS_DFS_OK_MASK               (0xFU)  /* Merged from fields with different position or width, of widths (2, 3, 4), largest definition used */
#define PLL_DFS_STATUS_DFS_OK_SHIFT              (0U)
/*! DFS_OK - DFS OK
 *  0b0000..Not valid
 *  0b0001..Valid
 */
#define PLL_DFS_STATUS_DFS_OK(x)                 (((uint32_t)(((uint32_t)(x)) << PLL_DFS_STATUS_DFS_OK_SHIFT)) & PLL_DFS_STATUS_DFS_OK_MASK)  /* Merged from fields with different position or width, of widths (2, 3, 4), largest definition used */
/*! @} */


/*!
 * @}
 */ /* end of group PLL_Register_Masks */


/* PLL - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral SYS_PLL1 base address */
  #define SYS_PLL1_BASE                            (0x54481000u)
  /** Peripheral SYS_PLL1 base address */
  #define SYS_PLL1_BASE_NS                         (0x44481000u)
  /** Peripheral SYS_PLL1 base pointer */
  #define SYS_PLL1                                 ((PLL_Type *)SYS_PLL1_BASE)
  /** Peripheral SYS_PLL1 base pointer */
  #define SYS_PLL1_NS                              ((PLL_Type *)SYS_PLL1_BASE_NS)
  /** Peripheral AUDIO_PLL1 base address */
  #define AUDIO_PLL1_BASE                          (0x54481100u)
  /** Peripheral AUDIO_PLL1 base address */
  #define AUDIO_PLL1_BASE_NS                       (0x44481100u)
  /** Peripheral AUDIO_PLL1 base pointer */
  #define AUDIO_PLL1                               ((PLL_Type *)AUDIO_PLL1_BASE)
  /** Peripheral AUDIO_PLL1 base pointer */
  #define AUDIO_PLL1_NS                            ((PLL_Type *)AUDIO_PLL1_BASE_NS)
  /** Peripheral AUDIO_PLL2 base address */
  #define AUDIO_PLL2_BASE                          (0x54481200u)
  /** Peripheral AUDIO_PLL2 base address */
  #define AUDIO_PLL2_BASE_NS                       (0x44481200u)
  /** Peripheral AUDIO_PLL2 base pointer */
  #define AUDIO_PLL2                               ((PLL_Type *)AUDIO_PLL2_BASE)
  /** Peripheral AUDIO_PLL2 base pointer */
  #define AUDIO_PLL2_NS                            ((PLL_Type *)AUDIO_PLL2_BASE_NS)
  /** Peripheral ENCODER_PLL base address */
  #define ENCODER_PLL_BASE                         (0x54481300u)
  /** Peripheral ENCODER_PLL base address */
  #define ENCODER_PLL_BASE_NS                      (0x44481300u)
  /** Peripheral ENCODER_PLL base pointer */
  #define ENCODER_PLL                              ((PLL_Type *)ENCODER_PLL_BASE)
  /** Peripheral ENCODER_PLL base pointer */
  #define ENCODER_PLL_NS                           ((PLL_Type *)ENCODER_PLL_BASE_NS)
  /** Peripheral ARM_PLL base address */
  #define ARM_PLL_BASE                             (0x54481600u)
  /** Peripheral ARM_PLL base address */
  #define ARM_PLL_BASE_NS                          (0x44481600u)
  /** Peripheral ARM_PLL base pointer */
  #define ARM_PLL                                  ((PLL_Type *)ARM_PLL_BASE)
  /** Peripheral ARM_PLL base pointer */
  #define ARM_PLL_NS                               ((PLL_Type *)ARM_PLL_BASE_NS)
  /** Peripheral DRAM_PLL base address */
  #define DRAM_PLL_BASE                            (0x54481700u)
  /** Peripheral DRAM_PLL base address */
  #define DRAM_PLL_BASE_NS                         (0x44481700u)
  /** Peripheral DRAM_PLL base pointer */
  #define DRAM_PLL                                 ((PLL_Type *)DRAM_PLL_BASE)
  /** Peripheral DRAM_PLL base pointer */
  #define DRAM_PLL_NS                              ((PLL_Type *)DRAM_PLL_BASE_NS)
  /** Peripheral HSIO_PLL base address */
  #define HSIO_PLL_BASE                            (0x54481800u)
  /** Peripheral HSIO_PLL base address */
  #define HSIO_PLL_BASE_NS                         (0x44481800u)
  /** Peripheral HSIO_PLL base pointer */
  #define HSIO_PLL                                 ((PLL_Type *)HSIO_PLL_BASE)
  /** Peripheral HSIO_PLL base pointer */
  #define HSIO_PLL_NS                              ((PLL_Type *)HSIO_PLL_BASE_NS)
  /** Peripheral LDB_PLL base address */
  #define LDB_PLL_BASE                             (0x54481900u)
  /** Peripheral LDB_PLL base address */
  #define LDB_PLL_BASE_NS                          (0x44481900u)
  /** Peripheral LDB_PLL base pointer */
  #define LDB_PLL                                  ((PLL_Type *)LDB_PLL_BASE)
  /** Peripheral LDB_PLL base pointer */
  #define LDB_PLL_NS                               ((PLL_Type *)LDB_PLL_BASE_NS)
  /** Array initializer of PLL peripheral base addresses */
  #define PLL_BASE_ADDRS                           { SYS_PLL1_BASE, AUDIO_PLL1_BASE, AUDIO_PLL2_BASE, ENCODER_PLL_BASE, ARM_PLL_BASE, DRAM_PLL_BASE, HSIO_PLL_BASE, LDB_PLL_BASE }
  /** Array initializer of PLL peripheral base pointers */
  #define PLL_BASE_PTRS                            { SYS_PLL1, AUDIO_PLL1, AUDIO_PLL2, ENCODER_PLL, ARM_PLL, DRAM_PLL, HSIO_PLL, LDB_PLL }
  /** Array initializer of PLL peripheral base addresses */
  #define PLL_BASE_ADDRS_NS                        { SYS_PLL1_BASE_NS, AUDIO_PLL1_BASE_NS, AUDIO_PLL2_BASE_NS, ENCODER_PLL_BASE_NS, ARM_PLL_BASE_NS, DRAM_PLL_BASE_NS, HSIO_PLL_BASE_NS, LDB_PLL_BASE_NS }
  /** Array initializer of PLL peripheral base pointers */
  #define PLL_BASE_PTRS_NS                         { SYS_PLL1_NS, AUDIO_PLL1_NS, AUDIO_PLL2_NS, ENCODER_PLL_NS, ARM_PLL_NS, DRAM_PLL_NS, HSIO_PLL_NS, LDB_PLL_NS }
#else
  /** Peripheral SYS_PLL1 base address */
  #define SYS_PLL1_BASE                            (0x44481000u)
  /** Peripheral SYS_PLL1 base pointer */
  #define SYS_PLL1                                 ((PLL_Type *)SYS_PLL1_BASE)
  /** Peripheral AUDIO_PLL1 base address */
  #define AUDIO_PLL1_BASE                          (0x44481100u)
  /** Peripheral AUDIO_PLL1 base pointer */
  #define AUDIO_PLL1                               ((PLL_Type *)AUDIO_PLL1_BASE)
  /** Peripheral AUDIO_PLL2 base address */
  #define AUDIO_PLL2_BASE                          (0x44481200u)
  /** Peripheral AUDIO_PLL2 base pointer */
  #define AUDIO_PLL2                               ((PLL_Type *)AUDIO_PLL2_BASE)
  /** Peripheral ENCODER_PLL base address */
  #define ENCODER_PLL_BASE                         (0x44481300u)
  /** Peripheral ENCODER_PLL base pointer */
  #define ENCODER_PLL                              ((PLL_Type *)ENCODER_PLL_BASE)
  /** Peripheral ARM_PLL base address */
  #define ARM_PLL_BASE                             (0x44481600u)
  /** Peripheral ARM_PLL base pointer */
  #define ARM_PLL                                  ((PLL_Type *)ARM_PLL_BASE)
  /** Peripheral DRAM_PLL base address */
  #define DRAM_PLL_BASE                            (0x44481700u)
  /** Peripheral DRAM_PLL base pointer */
  #define DRAM_PLL                                 ((PLL_Type *)DRAM_PLL_BASE)
  /** Peripheral HSIO_PLL base address */
  #define HSIO_PLL_BASE                            (0x44481800u)
  /** Peripheral HSIO_PLL base pointer */
  #define HSIO_PLL                                 ((PLL_Type *)HSIO_PLL_BASE)
  /** Peripheral LDB_PLL base address */
  #define LDB_PLL_BASE                             (0x44481900u)
  /** Peripheral LDB_PLL base pointer */
  #define LDB_PLL                                  ((PLL_Type *)LDB_PLL_BASE)
  /** Array initializer of PLL peripheral base addresses */
  #define PLL_BASE_ADDRS                           { SYS_PLL1_BASE, AUDIO_PLL1_BASE, AUDIO_PLL2_BASE, ENCODER_PLL_BASE, ARM_PLL_BASE, DRAM_PLL_BASE, HSIO_PLL_BASE, LDB_PLL_BASE }
  /** Array initializer of PLL peripheral base pointers */
  #define PLL_BASE_PTRS                            { SYS_PLL1, AUDIO_PLL1, AUDIO_PLL2, ENCODER_PLL, ARM_PLL, DRAM_PLL, HSIO_PLL, LDB_PLL }
#endif

/*!
 * @}
 */ /* end of group PLL_Peripheral_Access_Layer */

#endif  /* #if !defined(MIMX9494_PLL_H_) */
