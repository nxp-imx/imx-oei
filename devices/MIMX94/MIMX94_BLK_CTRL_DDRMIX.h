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
 * @file MIMX9494_BLK_CTRL_DDRMIX.h
 * @version 1.0
 * @date 2023-11-01
 * @brief CMSIS Peripheral Access Layer for MIMX9494_BLK_CTRL_DDRMIX
 *
 * CMSIS Peripheral Access Layer for MIMX9494
 */

/* Prevention from multiple including the same memory map */
#if !defined(MIMX9494_BLK_CTRL_DDRMIX_H_)  /* Check if memory map has not been already included */
#define MIMX9494_BLK_CTRL_DDRMIX_H_

#include "MIMX94_COMMON.h"

/* ----------------------------------------------------------------------------
   -- BLK_CTRL_DDRMIX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BLK_CTRL_DDRMIX_Peripheral_Access_Layer BLK_CTRL_DDRMIX Peripheral Access Layer
 * @{
 */

/** BLK_CTRL_DDRMIX - Register Layout Typedef */
typedef struct {
  __IO uint32_t HWFFC_CTRL;                        /**< DDRPHY DfiClk, DflCtlClk HWFFC Control, offset: 0x0 */
  __IO uint32_t CA55_SEL_CTRL;                     /**< CA55 Arm Pll Observe Select, offset: 0x4 */
  __IO uint32_t VREF_PSW_CTRL;                     /**< DRAM_VREF power switch, offset: 0x8 */
  __IO uint32_t DDRC_STOP_CTRL;                    /**< DDR Controller ipg_stop SW control, offset: 0xC */
  __IO uint32_t AUTO_CG_CTRL;                      /**< DDR Controller automatic clock gating control when no AXI transmit, offset: 0x10 */
  __IO uint32_t SSI_PWR_CTRL;                      /**< NOC2DDR SSI slave power control, offset: 0x14 */
  __IO uint32_t DDRC_EXCLUSIVE_EN;                 /**< DDRC AXI exclusive access monitor enable, offset: 0x18 */
  __IO uint32_t DDRC_URGENT_EN;                    /**< DDRC real_time read urgent and read urgent enable, offset: 0x1C */
  __IO uint32_t RT_MASTER_ID_0_1;                  /**< DDRC real_time master 6bit extend-ID range 0 and range 1, offset: 0x20 */
  __IO uint32_t RT_MASTER_ID_2_3;                  /**< DDRC real_time master 6bit extend-ID range 2 and range 3, offset: 0x24 */
  __IO uint32_t AXI_PARITY_ERR_CLR;                /**< DDRMIX AXI parity check clear register, offset: 0x28 */
  __IO uint32_t AXI_PARITY_ERR_INJECT;             /**< DDRMIX AXI parity error injection register, offset: 0x2C */
  __IO uint32_t RT_MASTER_ID_4_5;                  /**< DDRC real_time master 6bit extend-ID range 4 and range 5, offset: 0x30 */
  __IO uint32_t RT_MASTER_ID_6_7;                  /**< DDRC real_time master 6bit extend-ID range 6 and range 7, offset: 0x34 */
  __I  uint32_t FUSE_DISABLE_DDRMIX;               /**< Fuse to ddrmix_blk_ctrl, offset: 0x38 */
  __IO uint32_t DDRPHY_BYPCLK_SRC_SEL;             /**< DDRPHY BypClk ssource select, offset: 0x3C */
  __IO uint32_t LPCG_FORCE_ON_OFF;                 /**< FORCE_ON_OFF for LPCG instances, offset: 0x40 */
  __IO uint32_t LPCG_FORCE_ON_OFF_SEL;             /**< FORCE_ON_OFF_SEL for LPCG instances, offset: 0x44 */
  __IO uint32_t AUTO_IPG_STOP_ACK_EN;              /**< Enable for auto generated ddrc ipg_stop_ack, offset: 0x48 */
} BLK_CTRL_DDRMIX_Type;

/* ----------------------------------------------------------------------------
   -- BLK_CTRL_DDRMIX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BLK_CTRL_DDRMIX_Register_Masks BLK_CTRL_DDRMIX Register Masks
 * @{
 */

/*! @name HWFFC_CTRL - DDRPHY DfiClk, DflCtlClk HWFFC Control */
/*! @{ */

#define BLK_CTRL_DDRMIX_HWFFC_CTRL_HWFFC_EN_MASK (0x1U)
#define BLK_CTRL_DDRMIX_HWFFC_CTRL_HWFFC_EN_SHIFT (0U)
/*! HWFFC_EN - DDRPHY DfiClk, DfiCtlClk HWFFC Enable */
#define BLK_CTRL_DDRMIX_HWFFC_CTRL_HWFFC_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_HWFFC_CTRL_HWFFC_EN_SHIFT)) & BLK_CTRL_DDRMIX_HWFFC_CTRL_HWFFC_EN_MASK)

#define BLK_CTRL_DDRMIX_HWFFC_CTRL_HWFFC_SEL_MASK (0x2U)
#define BLK_CTRL_DDRMIX_HWFFC_CTRL_HWFFC_SEL_SHIFT (1U)
/*! HWFFC_SEL - DDRPHY DfiClk, DfiCtlClk HWFFC Select */
#define BLK_CTRL_DDRMIX_HWFFC_CTRL_HWFFC_SEL(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_HWFFC_CTRL_HWFFC_SEL_SHIFT)) & BLK_CTRL_DDRMIX_HWFFC_CTRL_HWFFC_SEL_MASK)
/*! @} */

/*! @name CA55_SEL_CTRL - CA55 Arm Pll Observe Select */
/*! @{ */

#define BLK_CTRL_DDRMIX_CA55_SEL_CTRL_CA55_SEL_MASK (0x1U)
#define BLK_CTRL_DDRMIX_CA55_SEL_CTRL_CA55_SEL_SHIFT (0U)
/*! CA55_SEL - CA55 Arm Pll select into DDRPHY */
#define BLK_CTRL_DDRMIX_CA55_SEL_CTRL_CA55_SEL(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_CA55_SEL_CTRL_CA55_SEL_SHIFT)) & BLK_CTRL_DDRMIX_CA55_SEL_CTRL_CA55_SEL_MASK)
/*! @} */

/*! @name VREF_PSW_CTRL - DRAM_VREF power switch */
/*! @{ */

#define BLK_CTRL_DDRMIX_VREF_PSW_CTRL_VREF_PSW_MASK (0x1U)
#define BLK_CTRL_DDRMIX_VREF_PSW_CTRL_VREF_PSW_SHIFT (0U)
/*! VREF_PSW - DDRPHY DRAM_VREF Power Switch */
#define BLK_CTRL_DDRMIX_VREF_PSW_CTRL_VREF_PSW(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_VREF_PSW_CTRL_VREF_PSW_SHIFT)) & BLK_CTRL_DDRMIX_VREF_PSW_CTRL_VREF_PSW_MASK)
/*! @} */

/*! @name DDRC_STOP_CTRL - DDR Controller ipg_stop SW control */
/*! @{ */

#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_MASK (0x1U)
#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_SHIFT (0U)
/*! DDRC_STOP - DDR Controller ipg_stop. */
#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_SHIFT)) & BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_MASK)

#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_ACK_MASK (0x2U)
#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_ACK_SHIFT (1U)
/*! DDRC_STOP_ACK - DDR Controller ipg_stop_ack. */
#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_ACK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_ACK_SHIFT)) & BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_ACK_MASK)

#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_DRAM_SELF_REFRESH_MASK (0x4U)
#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_DRAM_SELF_REFRESH_SHIFT (2U)
/*! DDRC_DRAM_SELF_REFRESH - DDR Controller ddrc_dram_self_refresh. */
#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_DRAM_SELF_REFRESH(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_DRAM_SELF_REFRESH_SHIFT)) & BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_DRAM_SELF_REFRESH_MASK)

#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_HOLD_EN_MASK (0x10U)
#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_HOLD_EN_SHIFT (4U)
/*! DDRC_STOP_HOLD_EN - DDR Controller ipg_stop holds for a period of time before clearing. */
#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_HOLD_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_HOLD_EN_SHIFT)) & BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_HOLD_EN_MASK)

#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_HOLD_PERIOD_MASK (0xFFFFFF00U)
#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_HOLD_PERIOD_SHIFT (8U)
/*! DDRC_STOP_HOLD_PERIOD - DDR Controller ipg_stop hold period before clearing. */
#define BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_HOLD_PERIOD(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_HOLD_PERIOD_SHIFT)) & BLK_CTRL_DDRMIX_DDRC_STOP_CTRL_DDRC_STOP_HOLD_PERIOD_MASK)
/*! @} */

/*! @name AUTO_CG_CTRL - DDR Controller automatic clock gating control when no AXI transmit */
/*! @{ */

#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_SSI_IDLE_STRAP_MASK (0xFFFFU)
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_SSI_IDLE_STRAP_SHIFT (0U)
/*! SSI_IDLE_STRAP - Number of cycles for SSI being idle before DDRC clock gating. */
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_SSI_IDLE_STRAP(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AUTO_CG_CTRL_SSI_IDLE_STRAP_SHIFT)) & BLK_CTRL_DDRMIX_AUTO_CG_CTRL_SSI_IDLE_STRAP_MASK)

#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_AUTO_CG_ENA_MASK (0x10000U)
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_AUTO_CG_ENA_SHIFT (16U)
/*! AUTO_CG_ENA - DDR Controller automatic clock gating enable bit. */
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_AUTO_CG_ENA(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AUTO_CG_CTRL_AUTO_CG_ENA_SHIFT)) & BLK_CTRL_DDRMIX_AUTO_CG_CTRL_AUTO_CG_ENA_MASK)

#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_HWFFC_ACG_FORCE_B_MASK (0x20000U)
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_HWFFC_ACG_FORCE_B_SHIFT (17U)
/*! HWFFC_ACG_FORCE_B - DDR Controller hwffc and auto CG send ipg_stop allow bit. Can only programmed once. */
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_HWFFC_ACG_FORCE_B(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AUTO_CG_CTRL_HWFFC_ACG_FORCE_B_SHIFT)) & BLK_CTRL_DDRMIX_AUTO_CG_CTRL_HWFFC_ACG_FORCE_B_MASK)

#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_CLK_MASK (0x1000000U)
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_CLK_SHIFT (24U)
/*! GATE_DDRC_CLK - DDR Auto Clock Gating is allowed for DDR Controller clock ipg_clk_ddrc. */
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_CLK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_CLK_SHIFT)) & BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_CLK_MASK)

#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_IPS_CLK_MASK (0x4000000U)
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_IPS_CLK_SHIFT (26U)
/*! GATE_DDRC_IPS_CLK - DDR Auto Clock Gating is allowed for DDR Controller IPS clock ips_clk_ddrc. */
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_IPS_CLK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_IPS_CLK_SHIFT)) & BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRC_IPS_CLK_MASK)

#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_DFICLK_MASK (0x10000000U)
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_DFICLK_SHIFT (28U)
/*! GATE_DDRPHY_DFICLK - DDR Auto Clock Gating is allowed for DDRPHY DfiClk clock. */
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_DFICLK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_DFICLK_SHIFT)) & BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_DFICLK_MASK)

#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_APBCLK_MASK (0x40000000U)
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_APBCLK_SHIFT (30U)
/*! GATE_DDRPHY_APBCLK - DDR Auto Clock Gating is allowed for DDRPHY APBCLK clock. */
#define BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_APBCLK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_APBCLK_SHIFT)) & BLK_CTRL_DDRMIX_AUTO_CG_CTRL_GATE_DDRPHY_APBCLK_MASK)
/*! @} */

/*! @name SSI_PWR_CTRL - NOC2DDR SSI slave power control */
/*! @{ */

#define BLK_CTRL_DDRMIX_SSI_PWR_CTRL_POWER_CONTROL_MASK (0x1U)
#define BLK_CTRL_DDRMIX_SSI_PWR_CTRL_POWER_CONTROL_SHIFT (0U)
/*! POWER_CONTROL - NOC2DDR SSI slave power_control signal */
#define BLK_CTRL_DDRMIX_SSI_PWR_CTRL_POWER_CONTROL(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_SSI_PWR_CTRL_POWER_CONTROL_SHIFT)) & BLK_CTRL_DDRMIX_SSI_PWR_CTRL_POWER_CONTROL_MASK)

#define BLK_CTRL_DDRMIX_SSI_PWR_CTRL_ISO_CONTROL_MASK (0x2U)
#define BLK_CTRL_DDRMIX_SSI_PWR_CTRL_ISO_CONTROL_SHIFT (1U)
/*! ISO_CONTROL - NOC2DDR SSI slave iso_control signal */
#define BLK_CTRL_DDRMIX_SSI_PWR_CTRL_ISO_CONTROL(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_SSI_PWR_CTRL_ISO_CONTROL_SHIFT)) & BLK_CTRL_DDRMIX_SSI_PWR_CTRL_ISO_CONTROL_MASK)
/*! @} */

/*! @name DDRC_EXCLUSIVE_EN - DDRC AXI exclusive access monitor enable */
/*! @{ */

#define BLK_CTRL_DDRMIX_DDRC_EXCLUSIVE_EN_EXCLUSIVE_EN_MASK (0x1U)
#define BLK_CTRL_DDRMIX_DDRC_EXCLUSIVE_EN_EXCLUSIVE_EN_SHIFT (0U)
/*! EXCLUSIVE_EN - DDRC AXI exclusive access monitor enable */
#define BLK_CTRL_DDRMIX_DDRC_EXCLUSIVE_EN_EXCLUSIVE_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_DDRC_EXCLUSIVE_EN_EXCLUSIVE_EN_SHIFT)) & BLK_CTRL_DDRMIX_DDRC_EXCLUSIVE_EN_EXCLUSIVE_EN_MASK)
/*! @} */

/*! @name DDRC_URGENT_EN - DDRC real_time read urgent and read urgent enable */
/*! @{ */

#define BLK_CTRL_DDRMIX_DDRC_URGENT_EN_READ_URGENT_EN_MASK (0x1U)
#define BLK_CTRL_DDRMIX_DDRC_URGENT_EN_READ_URGENT_EN_SHIFT (0U)
/*! READ_URGENT_EN - DDRC ddrc_read_urgent is enabled */
#define BLK_CTRL_DDRMIX_DDRC_URGENT_EN_READ_URGENT_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_DDRC_URGENT_EN_READ_URGENT_EN_SHIFT)) & BLK_CTRL_DDRMIX_DDRC_URGENT_EN_READ_URGENT_EN_MASK)

#define BLK_CTRL_DDRMIX_DDRC_URGENT_EN_AR_RT_URGENT_EN_MASK (0x2U)
#define BLK_CTRL_DDRMIX_DDRC_URGENT_EN_AR_RT_URGENT_EN_SHIFT (1U)
/*! AR_RT_URGENT_EN - DDRC ipa_ar_rt_urgent is enabled */
#define BLK_CTRL_DDRMIX_DDRC_URGENT_EN_AR_RT_URGENT_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_DDRC_URGENT_EN_AR_RT_URGENT_EN_SHIFT)) & BLK_CTRL_DDRMIX_DDRC_URGENT_EN_AR_RT_URGENT_EN_MASK)
/*! @} */

/*! @name RT_MASTER_ID_0_1 - DDRC real_time master 6bit extend-ID range 0 and range 1 */
/*! @{ */

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_ID_MASK (0x3FU)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_ID_SHIFT (0U)
/*! RANGE_0_ID - DDRC real_time master ID range 0 ID */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_ID(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_ID_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_ID_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_MASK_MASK (0x3F00U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_MASK_SHIFT (8U)
/*! RANGE_0_MASK - DDRC real_time master ID range 0 ID mask */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_MASK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_MASK_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_MASK_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_EN_MASK (0x8000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_EN_SHIFT (15U)
/*! RANGE_0_EN - DDRC real_time master ID range 0 enable */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_EN_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_0_EN_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_ID_MASK (0x3F0000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_ID_SHIFT (16U)
/*! RANGE_1_ID - DDRC real_time master ID range 1 ID */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_ID(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_ID_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_ID_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_MASK_MASK (0x3F000000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_MASK_SHIFT (24U)
/*! RANGE_1_MASK - DDRC real_time master ID range 1 ID mask */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_MASK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_MASK_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_MASK_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_EN_MASK (0x80000000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_EN_SHIFT (31U)
/*! RANGE_1_EN - DDRC real_time master ID range 1 enable */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_EN_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_0_1_RANGE_1_EN_MASK)
/*! @} */

/*! @name RT_MASTER_ID_2_3 - DDRC real_time master 6bit extend-ID range 2 and range 3 */
/*! @{ */

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_ID_MASK (0x3FU)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_ID_SHIFT (0U)
/*! RANGE_2_ID - DDRC real_time master ID range 2 ID */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_ID(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_ID_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_ID_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_MASK_MASK (0x3F00U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_MASK_SHIFT (8U)
/*! RANGE_2_MASK - DDRC real_time master ID range 2 ID mask */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_MASK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_MASK_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_MASK_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_EN_MASK (0x8000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_EN_SHIFT (15U)
/*! RANGE_2_EN - DDRC real_time master ID range 2 enable */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_EN_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_2_EN_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_ID_MASK (0x3F0000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_ID_SHIFT (16U)
/*! RANGE_3_ID - DDRC real_time master ID range 3 ID */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_ID(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_ID_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_ID_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_MASK_MASK (0x3F000000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_MASK_SHIFT (24U)
/*! RANGE_3_MASK - DDRC real_time master ID range 3 ID mask */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_MASK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_MASK_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_MASK_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_EN_MASK (0x80000000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_EN_SHIFT (31U)
/*! RANGE_3_EN - DDRC real_time master ID range 3 enable */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_EN_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_2_3_RANGE_3_EN_MASK)
/*! @} */

/*! @name AXI_PARITY_ERR_CLR - DDRMIX AXI parity check clear register */
/*! @{ */

#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_MST_ERR_CLR_MASK (0x1U)
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_MST_ERR_CLR_SHIFT (0U)
/*! MST_ERR_CLR - DDRMIX AXI parity master d_ip_axi_parity_master error clear */
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_MST_ERR_CLR(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_MST_ERR_CLR_SHIFT)) & BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_MST_ERR_CLR_MASK)

#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_SLV_ERR_CLR_MASK (0x100U)
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_SLV_ERR_CLR_SHIFT (8U)
/*! SLV_ERR_CLR - DDRMIX AXI parity slave d_ip_axi_parity_slave error clear */
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_SLV_ERR_CLR(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_SLV_ERR_CLR_SHIFT)) & BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_SLV_ERR_CLR_MASK)

#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_ERR_HOLD_MASK (0x70000U)
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_ERR_HOLD_SHIFT (16U)
/*! ERR_HOLD - DDRMIX AXI parity error hold time */
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_ERR_HOLD(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_ERR_HOLD_SHIFT)) & BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_ERR_HOLD_MASK)

#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_ERR_HOLD_EN_MASK (0x80000U)
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_ERR_HOLD_EN_SHIFT (19U)
/*! ERR_HOLD_EN - DDRMIX DDRC error hold enable */
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_ERR_HOLD_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_ERR_HOLD_EN_SHIFT)) & BLK_CTRL_DDRMIX_AXI_PARITY_ERR_CLR_ERR_HOLD_EN_MASK)
/*! @} */

/*! @name AXI_PARITY_ERR_INJECT - DDRMIX AXI parity error injection register */
/*! @{ */

#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_WDATA_ERR_INJ_MASK (0x1U)
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_WDATA_ERR_INJ_SHIFT (0U)
/*! WDATA_ERR_INJ - DDRMIX AXI parity error injection on wdatachk[0] */
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_WDATA_ERR_INJ(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_WDATA_ERR_INJ_SHIFT)) & BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_WDATA_ERR_INJ_MASK)

#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_RDATA_ERR_INJ_MASK (0x2U)
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_RDATA_ERR_INJ_SHIFT (1U)
/*! RDATA_ERR_INJ - DDRMIX AXI parity error injection on rdatachk[0] from axi parity slave */
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_RDATA_ERR_INJ(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_RDATA_ERR_INJ_SHIFT)) & BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_RDATA_ERR_INJ_MASK)

#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_RDATACHK_ERR_INJ_MASK (0x4U)
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_RDATACHK_ERR_INJ_SHIFT (2U)
/*! RDATACHK_ERR_INJ - DDRMIX AXI parity error injection on rdatachk[0] from ddrc */
#define BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_RDATACHK_ERR_INJ(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_RDATACHK_ERR_INJ_SHIFT)) & BLK_CTRL_DDRMIX_AXI_PARITY_ERR_INJECT_RDATACHK_ERR_INJ_MASK)
/*! @} */

/*! @name RT_MASTER_ID_4_5 - DDRC real_time master 6bit extend-ID range 4 and range 5 */
/*! @{ */

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_ID_MASK (0x3FU)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_ID_SHIFT (0U)
/*! RANGE_4_ID - DDRC real_time master ID range 4 ID */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_ID(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_ID_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_ID_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_MASK_MASK (0x3F00U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_MASK_SHIFT (8U)
/*! RANGE_4_MASK - DDRC real_time master ID range 4 ID mask */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_MASK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_MASK_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_MASK_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_EN_MASK (0x8000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_EN_SHIFT (15U)
/*! RANGE_4_EN - DDRC real_time master ID range 4 enable */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_EN_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_4_EN_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_ID_MASK (0x3F0000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_ID_SHIFT (16U)
/*! RANGE_5_ID - DDRC real_time master ID range 5 ID */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_ID(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_ID_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_ID_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_MASK_MASK (0x3F000000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_MASK_SHIFT (24U)
/*! RANGE_5_MASK - DDRC real_time master ID range 5 ID mask */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_MASK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_MASK_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_MASK_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_EN_MASK (0x80000000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_EN_SHIFT (31U)
/*! RANGE_5_EN - DDRC real_time master ID range 5 enable */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_EN_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_4_5_RANGE_5_EN_MASK)
/*! @} */

/*! @name RT_MASTER_ID_6_7 - DDRC real_time master 6bit extend-ID range 6 and range 7 */
/*! @{ */

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_ID_MASK (0x3FU)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_ID_SHIFT (0U)
/*! RANGE_6_ID - DDRC real_time master ID range 6 ID */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_ID(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_ID_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_ID_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_MASK_MASK (0x3F00U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_MASK_SHIFT (8U)
/*! RANGE_6_MASK - DDRC real_time master ID range 6 ID mask */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_MASK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_MASK_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_MASK_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_EN_MASK (0x8000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_EN_SHIFT (15U)
/*! RANGE_6_EN - DDRC real_time master ID range 6 enable */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_EN_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_6_EN_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_ID_MASK (0x3F0000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_ID_SHIFT (16U)
/*! RANGE_7_ID - DDRC real_time master ID range 7 ID */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_ID(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_ID_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_ID_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_MASK_MASK (0x3F000000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_MASK_SHIFT (24U)
/*! RANGE_7_MASK - DDRC real_time master ID range 7 ID mask */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_MASK(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_MASK_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_MASK_MASK)

#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_EN_MASK (0x80000000U)
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_EN_SHIFT (31U)
/*! RANGE_7_EN - DDRC real_time master ID range 7 enable */
#define BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_EN_SHIFT)) & BLK_CTRL_DDRMIX_RT_MASTER_ID_6_7_RANGE_7_EN_MASK)
/*! @} */

/*! @name FUSE_DISABLE_DDRMIX - Fuse to ddrmix_blk_ctrl */
/*! @{ */

#define BLK_CTRL_DDRMIX_FUSE_DISABLE_DDRMIX_FUSE_DISABLE_DDRMIX_MASK (0x3U)
#define BLK_CTRL_DDRMIX_FUSE_DISABLE_DDRMIX_FUSE_DISABLE_DDRMIX_SHIFT (0U)
/*! FUSE_DISABLE_DDRMIX - Read only reg for fuse mapped to ddrmix_blk_ctrl. */
#define BLK_CTRL_DDRMIX_FUSE_DISABLE_DDRMIX_FUSE_DISABLE_DDRMIX(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_FUSE_DISABLE_DDRMIX_FUSE_DISABLE_DDRMIX_SHIFT)) & BLK_CTRL_DDRMIX_FUSE_DISABLE_DDRMIX_FUSE_DISABLE_DDRMIX_MASK)
/*! @} */

/*! @name DDRPHY_BYPCLK_SRC_SEL - DDRPHY BypClk ssource select */
/*! @{ */

#define BLK_CTRL_DDRMIX_DDRPHY_BYPCLK_SRC_SEL_DRAM_PLL_SRC_EN_MASK (0x1U)
#define BLK_CTRL_DDRMIX_DDRPHY_BYPCLK_SRC_SEL_DRAM_PLL_SRC_EN_SHIFT (0U)
/*! DRAM_PLL_SRC_EN - 1: Use DRAM PLL clk for DDRPHY Bypass clk, 0: Use CCM clk for DDRPHY BYpass clk */
#define BLK_CTRL_DDRMIX_DDRPHY_BYPCLK_SRC_SEL_DRAM_PLL_SRC_EN(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_DDRPHY_BYPCLK_SRC_SEL_DRAM_PLL_SRC_EN_SHIFT)) & BLK_CTRL_DDRMIX_DDRPHY_BYPCLK_SRC_SEL_DRAM_PLL_SRC_EN_MASK)
/*! @} */

/*! @name LPCG_FORCE_ON_OFF - FORCE_ON_OFF for LPCG instances */
/*! @{ */

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_DDRC_LPCG_MASK (0x1U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_DDRC_LPCG_SHIFT (0U)
/*! ipc_dram_pll_root_clk_DDRC_LPCG - ipc_dram_pll_root_clk_DDRC_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_DDRC_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_DDRC_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_DDRC_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_LPCG_MASK (0x2U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_LPCG_SHIFT (1U)
/*! ipc_dram_pll_root_clk_LPCG - ipc_dram_pll_root_clk_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_SSI_LPCG_MASK (0x4U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_SSI_LPCG_SHIFT (2U)
/*! ipc_dram_pll_root_clk_SSI_LPCG - ipc_dram_pll_root_clk_SSI_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_SSI_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_SSI_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_dram_pll_root_clk_SSI_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_phy_dfi_clk_LPCG_MASK (0x8U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_phy_dfi_clk_LPCG_SHIFT (3U)
/*! ipc_phy_dfi_clk_LPCG - ipc_phy_dfi_clk_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_phy_dfi_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_phy_dfi_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_phy_dfi_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_clk_LPCG_MASK (0x10U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_clk_LPCG_SHIFT (4U)
/*! ipc_apb_root_clk_LPCG - ipc_apb_root_clk_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_async_ahb_clk_LPCG_MASK (0x20U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_async_ahb_clk_LPCG_SHIFT (5U)
/*! ipc_apb_root_async_ahb_clk_LPCG - ipc_apb_root_async_ahb_clk_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_async_ahb_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_async_ahb_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_async_ahb_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_crypt_clk_LPCG_MASK (0x40U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_crypt_clk_LPCG_SHIFT (6U)
/*! ipc_apb_root_crypt_clk_LPCG - ipc_apb_root_crypt_clk_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_crypt_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_crypt_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_crypt_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_pll_ref_clk_LPCG_MASK (0x80U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_pll_ref_clk_LPCG_SHIFT (7U)
/*! ipc_pll_ref_clk_LPCG - ipc_pll_ref_clk_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_pll_ref_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_pll_ref_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_pll_ref_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_ref_clk_LPCG_MASK (0x100U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_ref_clk_LPCG_SHIFT (8U)
/*! ipc_alt_ref_clk_LPCG - ipc_alt_ref_clk_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_ref_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_ref_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_ref_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_root_cmu_clk_LPCG_MASK (0x200U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_root_cmu_clk_LPCG_SHIFT (9U)
/*! ipc_alt_root_cmu_clk_LPCG - ipc_alt_root_cmu_clk_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_root_cmu_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_root_cmu_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_root_cmu_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_root_clk_LPCG_MASK (0x400U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_root_clk_LPCG_SHIFT (10U)
/*! ipc_alt_root_clk_LPCG - ipc_alt_root_clk_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_root_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_root_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_alt_root_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_clk_DDRC_LPCG_MASK (0x800U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_clk_DDRC_LPCG_SHIFT (11U)
/*! ipc_apb_root_clk_DDRC_LPCG - ipc_apb_root_clk_DDRC_LPCG.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_clk_DDRC_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_clk_DDRC_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_root_clk_DDRC_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_ref_clk_MASK (0x1000U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_ref_clk_SHIFT (12U)
/*! ipc_apb_ref_clk - ipc_apb_ref_clk.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_ref_clk(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_ref_clk_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_apb_ref_clk_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_pll_ai_clk_MASK (0x2000U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_pll_ai_clk_SHIFT (13U)
/*! ipc_pll_ai_clk - ipc_pll_ai_clk.force_on_off */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_pll_ai_clk(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_pll_ai_clk_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_ipc_pll_ai_clk_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_RESERVED_MASK (0xFFFFC000U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_RESERVED_SHIFT (14U)
/*! RESERVED - Reserved field */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_RESERVED(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_RESERVED_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_RESERVED_MASK)
/*! @} */

/*! @name LPCG_FORCE_ON_OFF_SEL - FORCE_ON_OFF_SEL for LPCG instances */
/*! @{ */

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_DDRC_LPCG_MASK (0x1U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_DDRC_LPCG_SHIFT (0U)
/*! ipc_dram_pll_root_clk_DDRC_LPCG - ipc_dram_pll_root_clk_DDRC_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_DDRC_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_DDRC_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_DDRC_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_LPCG_MASK (0x2U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_LPCG_SHIFT (1U)
/*! ipc_dram_pll_root_clk_LPCG - ipc_dram_pll_root_clk_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_SSI_LPCG_MASK (0x4U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_SSI_LPCG_SHIFT (2U)
/*! ipc_dram_pll_root_clk_SSI_LPCG - ipc_dram_pll_root_clk_SSI_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_SSI_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_SSI_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_dram_pll_root_clk_SSI_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_phy_dfi_clk_LPCG_MASK (0x8U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_phy_dfi_clk_LPCG_SHIFT (3U)
/*! ipc_phy_dfi_clk_LPCG - ipc_phy_dfi_clk_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_phy_dfi_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_phy_dfi_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_phy_dfi_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_clk_LPCG_MASK (0x10U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_clk_LPCG_SHIFT (4U)
/*! ipc_apb_root_clk_LPCG - ipc_apb_root_clk_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_async_ahb_clk_LPCG_MASK (0x20U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_async_ahb_clk_LPCG_SHIFT (5U)
/*! ipc_apb_root_async_ahb_clk_LPCG - ipc_apb_root_async_ahb_clk_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_async_ahb_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_async_ahb_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_async_ahb_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_crypt_clk_LPCG_MASK (0x40U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_crypt_clk_LPCG_SHIFT (6U)
/*! ipc_apb_root_crypt_clk_LPCG - ipc_apb_root_crypt_clk_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_crypt_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_crypt_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_crypt_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_pll_ref_clk_LPCG_MASK (0x80U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_pll_ref_clk_LPCG_SHIFT (7U)
/*! ipc_pll_ref_clk_LPCG - ipc_pll_ref_clk_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_pll_ref_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_pll_ref_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_pll_ref_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_ref_clk_LPCG_MASK (0x100U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_ref_clk_LPCG_SHIFT (8U)
/*! ipc_alt_ref_clk_LPCG - ipc_alt_ref_clk_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_ref_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_ref_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_ref_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_root_cmu_clk_LPCG_MASK (0x200U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_root_cmu_clk_LPCG_SHIFT (9U)
/*! ipc_alt_root_cmu_clk_LPCG - ipc_alt_root_cmu_clk_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_root_cmu_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_root_cmu_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_root_cmu_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_root_clk_LPCG_MASK (0x400U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_root_clk_LPCG_SHIFT (10U)
/*! ipc_alt_root_clk_LPCG - ipc_alt_root_clk_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_root_clk_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_root_clk_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_alt_root_clk_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_clk_DDRC_LPCG_MASK (0x800U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_clk_DDRC_LPCG_SHIFT (11U)
/*! ipc_apb_root_clk_DDRC_LPCG - ipc_apb_root_clk_DDRC_LPCG.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_clk_DDRC_LPCG(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_clk_DDRC_LPCG_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_root_clk_DDRC_LPCG_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_ref_clk_MASK (0x1000U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_ref_clk_SHIFT (12U)
/*! ipc_apb_ref_clk - ipc_apb_ref_clk.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_ref_clk(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_ref_clk_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_apb_ref_clk_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_pll_ai_clk_MASK (0x2000U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_pll_ai_clk_SHIFT (13U)
/*! ipc_pll_ai_clk - ipc_pll_ai_clk.force_on_off_sel */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_pll_ai_clk(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_pll_ai_clk_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_ipc_pll_ai_clk_MASK)

#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_RESERVED_MASK (0xFFFFC000U)
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_RESERVED_SHIFT (14U)
/*! RESERVED - Reserved field */
#define BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_RESERVED(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_RESERVED_SHIFT)) & BLK_CTRL_DDRMIX_LPCG_FORCE_ON_OFF_SEL_RESERVED_MASK)
/*! @} */

/*! @name AUTO_IPG_STOP_ACK_EN - Enable for auto generated ddrc ipg_stop_ack */
/*! @{ */

#define BLK_CTRL_DDRMIX_AUTO_IPG_STOP_ACK_EN_auto_ipg_stop_ack_en_MASK (0x1U)
#define BLK_CTRL_DDRMIX_AUTO_IPG_STOP_ACK_EN_auto_ipg_stop_ack_en_SHIFT (0U)
/*! auto_ipg_stop_ack_en - Enable for auto generated ddrc ipg_stop_ack */
#define BLK_CTRL_DDRMIX_AUTO_IPG_STOP_ACK_EN_auto_ipg_stop_ack_en(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AUTO_IPG_STOP_ACK_EN_auto_ipg_stop_ack_en_SHIFT)) & BLK_CTRL_DDRMIX_AUTO_IPG_STOP_ACK_EN_auto_ipg_stop_ack_en_MASK)

#define BLK_CTRL_DDRMIX_AUTO_IPG_STOP_ACK_EN_RESERVED_MASK (0xFFFFFFFEU)
#define BLK_CTRL_DDRMIX_AUTO_IPG_STOP_ACK_EN_RESERVED_SHIFT (1U)
/*! RESERVED - reserved space */
#define BLK_CTRL_DDRMIX_AUTO_IPG_STOP_ACK_EN_RESERVED(x) (((uint32_t)(((uint32_t)(x)) << BLK_CTRL_DDRMIX_AUTO_IPG_STOP_ACK_EN_RESERVED_SHIFT)) & BLK_CTRL_DDRMIX_AUTO_IPG_STOP_ACK_EN_RESERVED_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group BLK_CTRL_DDRMIX_Register_Masks */


/* BLK_CTRL_DDRMIX - Peripheral instance base addresses */
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
  /** Peripheral BLK_CTRL_DDRMIX base address */
  #define BLK_CTRL_DDRMIX_BASE               (0x5E010000u)
  /** Peripheral BLK_CTRL_DDRMIX base address */
  #define BLK_CTRL_DDRMIX_BASE_NS            (0x4E010000u)
  /** Peripheral BLK_CTRL_DDRMIX base pointer */
  #define BLK_CTRL_DDRMIX                    ((BLK_CTRL_DDRMIX_Type *)BLK_CTRL_DDRMIX_BASE)
  /** Peripheral BLK_CTRL_DDRMIX base pointer */
  #define BLK_CTRL_DDRMIX_NS                 ((BLK_CTRL_DDRMIX_Type *)BLK_CTRL_DDRMIX_BASE_NS)
  /** Array initializer of BLK_CTRL_DDRMIX peripheral base addresses */
  #define BLK_CTRL_DDRMIX_BASE_ADDRS           { BLK_CTRL_DDRMIX_BASE }
  /** Array initializer of BLK_CTRL_DDRMIX peripheral base pointers */
  #define BLK_CTRL_DDRMIX_BASE_PTRS            { BLK_CTRL_DDRMIX }
  /** Array initializer of BLK_CTRL_DDRMIX peripheral base addresses */
  #define BLK_CTRL_DDRMIX_BASE_ADDRS_NS        { BLK_CTRL_DDRMIX_BASE_NS }
  /** Array initializer of BLK_CTRL_DDRMIX peripheral base pointers */
  #define BLK_CTRL_DDRMIX_BASE_PTRS_NS         { BLK_CTRL_DDRMIX_NS }
#else
  /** Peripheral BLK_CTRL_DDRMIX base address */
  #define BLK_CTRL_DDRMIX_BASE               (0x4E010000u)
  /** Peripheral BLK_CTRL_DDRMIX base pointer */
  #define BLK_CTRL_DDRMIX                    ((BLK_CTRL_DDRMIX_Type *)BLK_CTRL_DDRMIX_BASE)
  /** Array initializer of BLK_CTRL_DDRMIX peripheral base addresses */
  #define BLK_CTRL_DDRMIX_BASE_ADDRS           { BLK_CTRL_DDRMIX_BASE }
  /** Array initializer of BLK_CTRL_DDRMIX peripheral base pointers */
  #define BLK_CTRL_DDRMIX_BASE_PTRS            { BLK_CTRL_DDRMIX }
#endif

/*!
 * @}
 */ /* end of group BLK_CTRL_DDRMIX_Peripheral_Access_Layer */

#endif  /* #if !defined(MIMX9494_BLK_CTRL_DDRMIX_H_) */
