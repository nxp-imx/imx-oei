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
 * @file MIMX9494_cm33_core0.h
 * @version 1.0
 * @date 2023-11-01
 * @brief CMSIS Peripheral Access Layer for MIMX9494_cm33_core0
 *
 * CMSIS Peripheral Access Layer for MIMX9494_cm33_core0
 */

#ifndef _MIMX9494_CM33_CORE0_H_
#define _MIMX9494_CM33_CORE0_H_                  /**< Symbol preventing repeated inclusion */

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100U
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0000U


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 422                /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M33 SV Hard Fault Interrupt */
  MemoryManagement_IRQn        = -12,              /**< Cortex-M33 Memory Management Interrupt */
  BusFault_IRQn                = -11,              /**< Cortex-M33 Bus Fault Interrupt */
  UsageFault_IRQn              = -10,              /**< Cortex-M33 Usage Fault Interrupt */
  SecureFault_IRQn             = -9,               /**< Cortex-M33 Secure Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M33 SV Call Interrupt */
  DebugMonitor_IRQn            = -4,               /**< Cortex-M33 Debug Monitor Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M33 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M33 System Tick Interrupt */

  /* Device specific interrupts */
  Reserved16_IRQn              = 0,                /**< Reserved interrupt */
  Reserved17_IRQn              = 1,                /**< DAP interrupt */
  Reserved18_IRQn              = 2,                /**< CTI trigger outputs from CM7 platform */
  Reserved19_IRQn              = 3,                /**< CTI trigger outputs from CM33 platform */
  Reserved20_IRQn              = 4,                /**< CTI trigger outputs from CA55 platform */
  Reserved21_IRQn              = 5,                /**< Performance Unit Interrupts from CA55 platform */
  Reserved22_IRQn              = 6,                /**< ECC error from CA55 platform cache */
  Reserved23_IRQn              = 7,                /**< 1-bit or 2-bit ECC or Parity error from CA55 platform cache */
  Reserved24_IRQn              = 8,                /**< CTI trigger outputs from CM7_1 platform */
  Reserved25_IRQn              = 9,                /**< CTI trigger outputs from CM33_sync platform */
  CAN1_IRQn                    = 10,               /**< CAN1 interrupt */
  CAN1_ERROR_IRQn              = 11,               /**< CAN1 error interrupt */
  GPIO1_INT0_IRQn              = 12,               /**< General Purpose Input/Output 1 interrupt 0 */
  GPIO1_INT1_IRQn              = 13,               /**< General Purpose Input/Output 1 interrupt 1 */
  I3C1_IRQn                    = 14,               /**< Improved Inter-Integrated Circuit 1 interrupt */
  LPI2C1_IRQn                  = 15,               /**< Low Power Inter-Integrated Circuit module 1 */
  LPI2C2_IRQn                  = 16,               /**< Low Power Inter-Integrated Circuit module 2 */
  LPIT1_IRQn                   = 17,               /**< Low Power Periodic Interrupt Timer 1 */
  LPSPI1_IRQn                  = 18,               /**< Low Power Serial Peripheral Interface 1 */
  LPSPI2_IRQn                  = 19,               /**< Low Power Serial Peripheral Interface 2 */
  LPTMR1_IRQn                  = 20,               /**< Low Power Timer 1 */
  LPUART1_IRQn                 = 21,               /**< Low Power UART 1 */
  LPUART2_IRQn                 = 22,               /**< Low Power UART 2 */
  Reserved39_IRQn              = 23,               /**< AONMIX ELE MU0 SideA interrupt */
  Reserved40_IRQn              = 24,               /**< AONMIX ELE MU1 SideA interrupt */
  Reserved41_IRQn              = 25,               /**< AONMIX ELE MU2 SideA interrupt */
  Reserved42_IRQn              = 26,               /**< AONMIX ELE MU3 SideA interrupt */
  Reserved43_IRQn              = 27,               /**< AONMIX ELE MU4 SideA interrupt */
  Reserved44_IRQn              = 28,               /**< AONMIX ELE MU5 SideA interrupt */
  Reserved45_IRQn              = 29,               /**< AONMIX ELE MU6 SideA interrupt */
  Reserved46_IRQn              = 30,               /**< AONMIX ELE MU7 SideA interrupt */
  Reserved47_IRQn              = 31,               /**< AONMIX ELE MU8 SideA interrupt */
  V2X_FH_APCH0_IRQn            = 32,               /**< V2X-FH MU APCH0 (APP0) interrupt */
  V2X_FH_APHSM1_IRQn           = 33,               /**< V2X-FH MU APHSM1 (HSM1) interrupt */
  TPM1_IRQn                    = 34,               /**< Timer PWM module 1 */
  TPM2_IRQn                    = 35,               /**< Timer PWM module 2 */
  WDOG1_IRQn                   = 36,               /**< Watchdog 1 Interrupt */
  WDOG2_IRQn                   = 37,               /**< Watchdog 2 Interrupt */
  SAI1_IRQn                    = 38,               /**< Serial Audio Interface 1 */
  GPT1_IRQn                    = 39,               /**< AONMIX GPT1 */
  CAN2_IRQn                    = 40,               /**< WAKEUPMIX CAN2 interrupt */
  CAN2_ERROR_IRQn              = 41,               /**< WAKEUPMIX CAN2 error interrupt */
  CAN3_IRQn                    = 42,               /**< WAKEUPMIX CAN3 interrupt */
  CAN3_ERROR_IRQn              = 43,               /**< WAKEUPMIX CAN3 error interrupt */
  CAN4_IRQn                    = 44,               /**< WAKEUPMIX CAN4 interrupt */
  CAN4_ERROR_IRQn              = 45,               /**< WAKEUPMIX CAN4 error interrupt */
  CAN5_IRQn                    = 46,               /**< WAKEUPMIX CAN5 interrupt */
  CAN5_ERROR_IRQn              = 47,               /**< WAKEUPMIX CAN5 error interrupt */
  FLEXIO1_IRQn                 = 48,               /**< WAKEUPMIX Flexible IO 1 interrupt */
  FLEXIO2_IRQn                 = 49,               /**< WAKEUPMIX Flexible IO 2 interrupt */
  FLEXIO3_IRQn                 = 50,               /**< NETCMIX Flexible IO 3 interrupt */
  FLEXIO4_IRQn                 = 51,               /**< NETCMIX Flexible IO 4 interrupt */
  Reserved68_IRQn              = 52,               /**< Earlier assigned for WAKEUPMIX XSPI1 interrupt */
  Reserved69_IRQn              = 53,               /**< Earlier assigned for WAKEUPMIX XSPI2 interrupt */
  GPIO2_INT0_IRQn              = 54,               /**< WAKEUPMIX General Purpose Input/Output 2 interrupt 0 */
  GPIO2_INT1_IRQn              = 55,               /**< WAKEUPMIX General Purpose Input/Output 2 interrupt 1 */
  GPIO3_INT0_IRQn              = 56,               /**< WAKEUPMIX General Purpose Input/Output 3 interrupt 0 */
  GPIO3_INT1_IRQn              = 57,               /**< WAKEUPMIX General Purpose Input/Output 3 interrupt 1 */
  GPIO4_INT0_IRQn              = 58,               /**< WAKEUPMIX General Purpose Input/Output 4 interrupt 0 */
  GPIO4_INT1_IRQn              = 59,               /**< WAKEUPMIX General Purpose Input/Output 4 interrupt 1 */
  GPIO5_INT0_IRQn              = 60,               /**< WAKEUPMIX General Purpose Input/Output 5 interrupt 0 */
  GPIO5_INT1_IRQn              = 61,               /**< WAKEUPMIX General Purpose Input/Output 5 interrupt 1 */
  GPIO6_INT0_IRQn              = 62,               /**< WAKEUPMIX General Purpose Input/Output 6 interrupt 0 */
  GPIO6_INT1_IRQn              = 63,               /**< WAKEUPMIX General Purpose Input/Output 6 interrupt 1 */
  GPIO7_INT0_IRQn              = 64,               /**< WAKEUPMIX General Purpose Input/Output 7 interrupt 0 */
  GPIO7_INT1_IRQn              = 65,               /**< WAKEUPMIX General Purpose Input/Output 7 interrupt 1 */
  I3C2_IRQn                    = 66,               /**< WAKEUPMIX Improved Inter-Integrated Circuit 2 interrupt */
  LPI2C3_IRQn                  = 67,               /**< WAKEUPMIX Low Power Inter-Integrated Circuit module 3 */
  LPI2C4_IRQn                  = 68,               /**< WAKEUPMIX Low Power Inter-Integrated Circuit module 4 */
  LPIT2_IRQn                   = 69,               /**< WAKEUPMIX Low Power Periodic Interrupt Timer 2 */
  LPIT3_IRQn                   = 70,               /**< WAKEUPMIX Low Power Periodic Interrupt Timer 3 */
  LPSPI3_IRQn                  = 71,               /**< WAKEUPMIX Low Power Serial Peripheral Interface 3 */
  LPSPI4_IRQn                  = 72,               /**< WAKEUPMIX Low Power Serial Peripheral Interface 4 */
  LPTMR2_IRQn                  = 73,               /**< WAKEUPMIX Low Power Timer 2 */
  LPUART3_IRQn                 = 74,               /**< WAKEUPMIX Low Power UART 3 */
  LPUART4_IRQn                 = 75,               /**< WAKEUPMIX Low Power UART 4 */
  LPUART5_IRQn                 = 76,               /**< WAKEUPMIX Low Power UART 5 */
  LPUART6_IRQn                 = 77,               /**< WAKEUPMIX Low Power UART 6 */
  LPUART7_IRQn                 = 78,               /**< WAKEUPMIX Low Power UART 7 */
  LPUART8_IRQn                 = 79,               /**< WAKEUPMIX Low Power UART 8 */
  LPUART9_IRQn                 = 80,               /**< WAKEUPMIX Low Power UART 9 */
  LPUART10_IRQn                = 81,               /**< WAKEUPMIX Low Power UART 10 */
  LPUART11_IRQn                = 82,               /**< WAKEUPMIX Low Power UART 11 */
  LPUART12_IRQn                = 83,               /**< WAKEUPMIX Low Power UART 12 */
  BBNSM_IRQn                   = 84,               /**< BBNSM Non-Secure interrupt */
  SYSCTR1_IRQn                 = 85,               /**< AONMIX System Counter compare interrupt */
  TPM3_IRQn                    = 86,               /**< WAKEUPMIX Timer PWM module 3 */
  TPM4_IRQn                    = 87,               /**< WAKEUPMIX Timer PWM module 4 */
  TPM5_IRQn                    = 88,               /**< WAKEUPMIX Timer PWM module 5 */
  TPM6_IRQn                    = 89,               /**< WAKEUPMIX Timer PWM module 6 */
  WDOG3_IRQn                   = 90,               /**< WAKEUPMIX Watchdog 3 Interrupt */
  WDOG4_IRQn                   = 91,               /**< WAKEUPMIX Watchdog 4 Interrupt */
  WDOG5_IRQn                   = 92,               /**< WAKEUPMIX Watchdog 5 Interrupt */
  WDOG6_IRQn                   = 93,               /**< WAKEUPMIX Watchdog 6 Interrupt */
  WDOG7_IRQn                   = 94,               /**< NETCMIX Watchdog 7 Interrupt */
  WDOG8_IRQn                   = 95,               /**< NETCMIX Watchdog 8 Interrupt */
  USDHC1_IRQn                  = 96,               /**< MEGAMIX uSDHC1 Enhanced SDHC Interrupt Request */
  USDHC2_IRQn                  = 97,               /**< MEGAMIX uSDHC2 Enhanced SDHC Interrupt Request */
  EDMA2_ERROR_IRQn             = 98,               /**< WAKEUPMIX EDMA2 error interrupt */
  Reserved115_IRQn             = 99,               /**< JTAGSW DAP MDM-AP SRC reset source */
  Reserved116_IRQn             = 100,              /**< JTAGC SRC reset source (the JTAGC used for boundary scan, not JTAGC used for password authentication) */
  SAI2_IRQn                    = 101,              /**< WAKEUPMIX SAI2 interrupt */
  SAI3_IRQn                    = 102,              /**< WAKEUPMIX SAI3 interrupt */
  SAI4_IRQn                    = 103,              /**< WAKEUPMIX SAI4 interrupt */
  LPSPI5_IRQn                  = 104,              /**< WAKEUPMIX LPSPI5 interrupt */
  LPSPI6_IRQn                  = 105,              /**< WAKEUPMIX LPSPI6 interrupt */
  LPSPI7_IRQn                  = 106,              /**< WAKEUPMIX LPSPI7 interrupt */
  LPSPI8_IRQn                  = 107,              /**< WAKEUPMIX LPSPI8 interrupt */
  LPI2C5_IRQn                  = 108,              /**< WAKEUPMIX LPI2C5 interrupt */
  LPI2C6_IRQn                  = 109,              /**< WAKEUPMIX LPI2C6 interrupt */
  LPI2C7_IRQn                  = 110,              /**< WAKEUPMIX LPI2C7 interrupt */
  LPI2C8_IRQn                  = 111,              /**< WAKEUPMIX LPI2C8 interrupt */
  PDM_HWVAD_ERROR_IRQn         = 112,              /**< WAKEUPMIX PDM interrupt(hwvad err) */
  PDM_HWVAD_EVENT_IRQn         = 113,              /**< WAKEUPMIX PDM interrupt(hwvad event) */
  PDM_ERROR_IRQn               = 114,              /**< WAKEUPMIX PDM interrupt(mic err) */
  PDM_IRQn                     = 115,              /**< WAKEUPMIX PDM interrupt(mic event) */
  USDHC3_IRQn                  = 116,              /**< MEGAMIX uSDHC3 Enhanced SDHC Interrupt Request */
  Reserved133_IRQn             = 117,              /**< WAKEUPMIX ADC1 interrupt(er) */
  Reserved134_IRQn             = 118,              /**< WAKEUPMIX ADC1 interrupt(wd) */
  Reserved135_IRQn             = 119,              /**< WAKEUPMIX ADC1 interrupt(eoc) */
  Reserved136_IRQn             = 120,              /**< I3C1 wakeup irq after double sync */
  Reserved137_IRQn             = 121,              /**< I3C2 wakeup irq after double sync */
  MU5_A_IRQn                   = 122,              /**< AONMIX MU5 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU6_A_IRQn                   = 123,              /**< AONMIX MU6 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU7_A_IRQn                   = 124,              /**< AONMIX MU7 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU10_B_IRQn                  = 125,              /**< WAKEUPMIX MU10 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU11_B_IRQn                  = 126,              /**< WAKEUPMIX MU11 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU12_A_IRQn                  = 127,              /**< WAKEUPMIX MU12 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU13_A_IRQn                  = 128,              /**< WAKEUPMIX MU13 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU18_A_IRQn                  = 129,              /**< WAKEUPMIX MU18 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU18_B_IRQn                  = 130,              /**< WAKEUPMIX MU18 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU_E1_A_IRQn                 = 131,              /**< NETCMIX MU E1 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU_E2_A_IRQn                 = 132,              /**< NETCMIX MU E2 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU_E3_A_IRQn                 = 133,              /**< NETCMIX MU E3 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU_E4_A_IRQn                 = 134,              /**< NETCMIX MU E4 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  XSPI_SLV_IRQn                = 135,              /**< WAKEUPMIX XSPI Responder */
  FCCU_INT0_IRQn               = 136,              /**< AONMIX FCCU Interrupt Reaction 0 */
  FCCU_INT1_IRQn               = 137,              /**< AONMIX FCCU Interrupt Reaction 1 */
  FCCU_INT2_IRQn               = 138,              /**< AONMIX FCCU Interrupt Reaction 2 */
  FCCU_INT3_IRQn               = 139,              /**< AONMIX FCCU Interrupt Reaction 3(new interrupt for CM33_sync) */
  FCCU_INT4_IRQn               = 140,              /**< AONMIX FCCU Interrupt Reaction 4(new interrupt for CM7_1) */
  STCU_IRQn                    = 141,              /**< AONMIX STCU Selftest end Interrupt */
  Reserved158_IRQn             = 142,              /**< XBAR1 interrupt 0 and 1 */
  Reserved159_IRQn             = 143,              /**< XBAR1 interrupt 2 and 3 */
  GPT2_IRQn                    = 144,              /**< WAKEUPMIX GPT2 interrupt */
  GPT3_IRQn                    = 145,              /**< WAKEUPMIX GPT3 interrupt */
  GPT4_IRQn                    = 146,              /**< WAKEUPMIX GPT4 interrupt */
  Reserved163_IRQn             = 147,              /**< Endat2_1 interrupt/Hiperface1-DSL interrupt for safe events logged in EVENT_S register/Endat3 interrupt for background communication */
  Reserved164_IRQn             = 148,              /**< Hiperface1-DSL interrupt for events logged in EVENT_H or EVENT_L register/Endat3 interrupt */
  Reserved165_IRQn             = 149,              /**< Endat2_2  interrupt/Hiperface2-DSL interrupt for safe events logged in EVENT_S register/Biss interrupt for start of frame transmission */
  Reserved166_IRQn             = 150,              /**< Hiperface2-DSL interrupt for events logged in EVENT_H or EVENT_L register/Biss interrupt for end of frame transmission */
  Reserved167_IRQn             = 151,              /**< Flexpwm1(reload error, fault condition) */
  Reserved168_IRQn             = 152,              /**< Flexpwm1(capt0, comp0, reload0) */
  Reserved169_IRQn             = 153,              /**< Flexpwm1(capt1, comp1, reload1) */
  Reserved170_IRQn             = 154,              /**< Flexpwm1(capt2, comp2, reload2) */
  Reserved171_IRQn             = 155,              /**< Flexpwm1(capt3, comp3, reload3) */
  Reserved172_IRQn             = 156,              /**< Flexpwm2(reload error, fault condition) */
  Reserved173_IRQn             = 157,              /**< Flexpwm2(capt0, comp0, reload0) */
  Reserved174_IRQn             = 158,              /**< Flexpwm2(capt1, comp1, reload1) */
  Reserved175_IRQn             = 159,              /**< Flexpwm2(capt2, comp2, reload2) */
  Reserved176_IRQn             = 160,              /**< Flexpwm2(capt3, comp3, reload3) */
  Reserved177_IRQn             = 161,              /**< Flexpwm3(reload error, fault condition) */
  Reserved178_IRQn             = 162,              /**< Flexpwm3(capt0, comp0, reload0) */
  Reserved179_IRQn             = 163,              /**< Flexpwm3(capt1, comp1, reload1) */
  Reserved180_IRQn             = 164,              /**< Flexpwm3(capt2, comp2, reload2) */
  Reserved181_IRQn             = 165,              /**< Flexpwm3(capt3, comp3, reload3) */
  Reserved182_IRQn             = 166,              /**< Flexpwm4(reload error, fault condition) */
  Reserved183_IRQn             = 167,              /**< Flexpwm4(capt0, comp0, reload0) */
  Reserved184_IRQn             = 168,              /**< Flexpwm4(capt1, comp1, reload1) */
  Reserved185_IRQn             = 169,              /**< Flexpwm4(capt2, comp2, reload2) */
  Reserved186_IRQn             = 170,              /**< Flexpwm4(capt3, comp3, reload3) */
  ENC1_IRQn                    = 171,              /**< Quad dec1 interrupt */
  ENC2_IRQn                    = 172,              /**< Quad dec2 interrupt */
  ENC3_IRQn                    = 173,              /**< Quad dec3 interrupt */
  ENC4_IRQn                    = 174,              /**< Quad dec4 interrupt */
  EWM_IRQn                     = 175,              /**< Ewm out interrupt */
  Reserved192_IRQn             = 176,              /**< Ethercat interrupt(PDI_OPB) */
  Reserved193_IRQn             = 177,              /**< Ethercat interrupt(RESET_OUT) */
  Reserved194_IRQn             = 178,              /**< Ethercat interrupt(SYNC_OUT0) */
  Reserved195_IRQn             = 179,              /**< Ethercat interrupt(SYNC_OUT1) */
  USB1_IRQn                    = 180,              /**< USB-1(USB 3.0 Controller) interrupt */
  USB2_IRQn                    = 181,              /**< USB-2(USB 2.0 Controller) interrupt */
  SINC1_CH0_IRQn               = 182,              /**< SINC Filter1(sinc filter glue1) Channel 0 interrupt */
  SINC1_CH1_IRQn               = 183,              /**< SINC Filter1(sinc filter glue1) Channel 1 interrupt */
  SINC1_CH2_IRQn               = 184,              /**< SINC Filter1(sinc filter glue1) Channel 2 interrupt */
  SINC1_CH3_IRQn               = 185,              /**< SINC Filter1(sinc filter glue1) Channel 3 interrupt */
  SINC2_CH0_IRQn               = 186,              /**< SINC Filter2(sinc filter glue2) Channel 0 interrupt */
  SINC2_CH1_IRQn               = 187,              /**< SINC Filter2(sinc filter glue2) Channel 1 interrupt */
  SINC2_CH2_IRQn               = 188,              /**< SINC Filter2(sinc filter glue2) Channel 2 interrupt */
  SINC2_CH3_IRQn               = 189,              /**< SINC Filter2(sinc filter glue2) Channel 3 interrupt */
  SINC3_CH0_IRQn               = 190,              /**< SINC Filter3(sinc filter glue3 Channel 0 interrupt */
  SINC3_CH1_IRQn               = 191,              /**< SINC Filter3(sinc filter glue3) Channel 1 interrupt */
  SINC3_CH2_IRQn               = 192,              /**< SINC Filter3(sinc filter glue3) Channel 2 interrupt */
  SINC3_CH3_IRQn               = 193,              /**< SINC Filter3(sinc filter glue3) Channel 3 interrupt */
  SINC4_CH0_IRQn               = 194,              /**< SINC Filter4(sinc filter glue4 Channel 0 interrupt */
  SINC4_CH1_IRQn               = 195,              /**< SINC Filter4(sinc filter glue4) Channel 1 interrupt */
  SINC4_CH2_IRQn               = 196,              /**< SINC Filter4(sinc filter glue4) Channel 2 interrupt */
  SINC4_CH3_IRQn               = 197,              /**< SINC Filter4(sinc filter glue4) Channel 3 interrupt */
  QTIMER1_IRQn                 = 198,              /**< QTIMER1 interrupt */
  QTIMER2_IRQn                 = 199,              /**< QTIMER2 interrupt */
  QTIMER3_IRQn                 = 200,              /**< QTIMER3 interrupt */
  QTIMER4_IRQn                 = 201,              /**< QTIMER4 interrupt */
  QTIMER5_IRQn                 = 202,              /**< QTIMER5 interrupt */
  QTIMER6_IRQn                 = 203,              /**< QTIMER6 interrupt */
  QTIMER7_IRQn                 = 204,              /**< QTIMER7 interrupt */
  QTIMER8_IRQn                 = 205,              /**< QTIMER8 interrupt */
  EDMA4_ERROR_IRQn             = 206,              /**< EDMA4 error interrupt */
  Reserved223_IRQn             = 207,              /**< Anamix Gllitch Detector output (da_ip_voltage_glitch_detector_cln16ffc). It's a latch signal. It can be cleared. */
  Reserved224_IRQn             = 208,              /**< Anamix VDET output (da_ip_vdetect_c16ffc). Detects high threshold on Core supply. It's a latch signal. It can be cleared. */
  Reserved225_IRQn             = 209,              /**< Anamix VDET output (da_ip_vdetect_c16ffc). Detects Low threshold on Core supply. It's a latch signal. It can be cleared */
  Reserved226_IRQn             = 210,              /**< LPCG Timeout interrupt generated by CCGR (CCM) */
  Reserved227_IRQn             = 211,              /**< Reserved227 */
  Reserved228_IRQn             = 212,              /**< Reserved228 */
  Reserved229_IRQn             = 213,              /**< Reserved229 */
  Reserved230_IRQn             = 214,              /**< Reserved230 */
  Reserved231_IRQn             = 215,              /**< Reserved231 */
  Reserved232_IRQn             = 216,              /**< Reserved232 */
  Reserved233_IRQn             = 217,              /**< Reserved233 */
  Reserved234_IRQn             = 218,              /**< Reserved234 */
  Reserved235_IRQn             = 219,              /**< Reserved235 */
  Reserved236_IRQn             = 220,              /**< Reserved236 */
  Reserved237_IRQn             = 221,              /**< Reserved237 */
  Reserved238_IRQn             = 222,              /**< Reserved238 */
  Reserved239_IRQn             = 223,              /**< Reserved239 */
  EDMA2_CH0_31_IRQn            = 224,              /**< WAKEUPMIX EDMA2 channel 0~31 interrupt */
  EDMA2_CH32_63_IRQn           = 225,              /**< WAKEUPMIX EDMA2 channel 32~63 interrupt */
  EDMA4_CH0_31_IRQn            = 226,              /**< WAKEUPMIX EDMA4 channel 0~31 interrupt */
  EDMA4_CH32_63_IRQn           = 227,              /**< WAKEUPMIX EDMA4 channel 32~63 interrupt */
  EDMA3_CH0_31_IRQn            = 228,              /**< WAKEUPMIX ACP EDMA3 channel 0~31 interrupt */
  EDMA3_CH32_63_IRQn           = 229,              /**< WAKEUPMIX ACP EDMA3 channel 32~63 interrupt */
  EDMA1_CH0_IRQn               = 230,              /**< WAKEUPMIX EDMA1 channel 0 interrupt */
  EDMA1_CH1_IRQn               = 231,              /**< WAKEUPMIX EDMA1 channel 1 interrupt */
  EDMA1_CH2_IRQn               = 232,              /**< WAKEUPMIX EDMA1 channel 2 interrupt */
  EDMA1_CH3_IRQn               = 233,              /**< WAKEUPMIX EDMA1 channel 3 interrupt */
  EDMA1_CH4_IRQn               = 234,              /**< WAKEUPMIX EDMA1 channel 4 interrupt */
  EDMA1_CH5_IRQn               = 235,              /**< WAKEUPMIX EDMA1 channel 5 interrupt */
  EDMA1_CH6_IRQn               = 236,              /**< WAKEUPMIX EDMA1 channel 6 interrupt */
  EDMA1_CH7_IRQn               = 237,              /**< WAKEUPMIX EDMA1 channel 7 interrupt */
  EDMA1_CH8_IRQn               = 238,              /**< WAKEUPMIX EDMA1 channel 8 interrupt */
  EDMA1_CH9_IRQn               = 239,              /**< WAKEUPMIX EDMA1 channel 9 interrupt */
  EDMA1_CH10_IRQn              = 240,              /**< WAKEUPMIX EDMA1 channel 10 interrupt */
  EDMA1_CH11_IRQn              = 241,              /**< WAKEUPMIX EDMA1 channel 11 interrupt */
  EDMA1_CH12_IRQn              = 242,              /**< WAKEUPMIX EDMA1 channel 12 interrupt */
  EDMA1_CH13_IRQn              = 243,              /**< WAKEUPMIX EDMA1 channel 13 interrupt */
  EDMA1_CH14_IRQn              = 244,              /**< WAKEUPMIX EDMA1 channel 14 interrupt */
  EDMA1_CH15_IRQn              = 245,              /**< WAKEUPMIX EDMA1 channel 15 interrupt */
  EDMA1_CH16_IRQn              = 246,              /**< WAKEUPMIX EDMA1 channel 16 interrupt */
  EDMA1_CH17_IRQn              = 247,              /**< WAKEUPMIX EDMA1 channel 17 interrupt */
  EDMA1_CH18_IRQn              = 248,              /**< WAKEUPMIX EDMA1 channel 18 interrupt */
  EDMA1_CH19_IRQn              = 249,              /**< WAKEUPMIX EDMA1 channel 19 interrupt */
  EDMA1_CH20_IRQn              = 250,              /**< WAKEUPMIX EDMA1 channel 20 interrupt */
  EDMA1_CH21_IRQn              = 251,              /**< WAKEUPMIX EDMA1 channel 21 interrupt */
  EDMA1_CH22_IRQn              = 252,              /**< WAKEUPMIX EDMA1 channel 22 interrupt */
  EDMA1_CH23_IRQn              = 253,              /**< WAKEUPMIX EDMA1 channel 23 interrupt */
  EDMA1_CH24_IRQn              = 254,              /**< WAKEUPMIX EDMA1 channel 24 interrupt */
  EDMA1_CH25_IRQn              = 255,              /**< WAKEUPMIX EDMA1 channel 25 interrupt */
  EDMA1_CH26_IRQn              = 256,              /**< WAKEUPMIX EDMA1 channel 26 interrupt */
  EDMA1_CH27_IRQn              = 257,              /**< WAKEUPMIX EDMA1 channel 27 interrupt */
  EDMA1_CH28_IRQn              = 258,              /**< WAKEUPMIX EDMA1 channel 28 interrupt */
  EDMA1_CH29_IRQn              = 259,              /**< WAKEUPMIX EDMA1 channel 29 interrupt */
  EDMA1_CH30_IRQn              = 260,              /**< WAKEUPMIX EDMA1 channel 30 interrupt */
  EDMA1_CH31_IRQn              = 261,              /**< WAKEUPMIX EDMA1 channel 31 interrupt */
  MU1_A_IRQn                   = 262,              /**< AONMIX MU1 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU1_B_IRQn                   = 263,              /**< AONMIX MU1 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU2_A_IRQn                   = 264,              /**< AONMIX MU2 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU2_B_IRQn                   = 265,              /**< AONMIX MU2 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU3_A_IRQn                   = 266,              /**< AONMIX MU3 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU3_B_IRQn                   = 267,              /**< AONMIX MU3 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU4_A_IRQn                   = 268,              /**< AONMIX MU4 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU4_B_IRQn                   = 269,              /**< AONMIX MU4 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU5_B_IRQn                   = 270,              /**< AONMIX MU5 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU6_B_IRQn                   = 271,              /**< AONMIX MU6 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU7_B_IRQn                   = 272,              /**< AONMIX MU7 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU8_A_IRQn                   = 273,              /**< AONMIX MU8 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU8_B_IRQn                   = 274,              /**< AONMIX MU8 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU9_A_IRQn                   = 275,              /**< AONMIX MU9 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU9_B_IRQn                   = 276,              /**< AONMIX MU9 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU10_A_IRQn                  = 277,              /**< WAKEUPMIX MU10 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU11_A_IRQn                  = 278,              /**< WAKEUPMIX MU11 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU12_B_IRQn                  = 279,              /**< WAKEUPMIX MU12 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU13_B_IRQn                  = 280,              /**< WAKEUPMIX MU13 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU14_A_IRQn                  = 281,              /**< WAKEUPMIX MU14 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU14_B_IRQn                  = 282,              /**< WAKEUPMIX MU14 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU15_A_IRQn                  = 283,              /**< WAKEUPMIX MU15 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU15_B_IRQn                  = 284,              /**< WAKEUPMIX MU15 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU16_A_IRQn                  = 285,              /**< WAKEUPMIX MU16 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU16_B_IRQn                  = 286,              /**< WAKEUPMIX MU16 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU17_A_IRQn                  = 287,              /**< WAKEUPMIX MU17 Ored of all (tx,rx,gp,core,murip) interrupt to MUA */
  MU17_B_IRQn                  = 288,              /**< WAKEUPMIX MU17 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU_E1_B_IRQn                 = 289,              /**< NETCMIX MU E1 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU_E2_B_IRQn                 = 290,              /**< NETCMIX MU E2 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU_E3_B_IRQn                 = 291,              /**< NETCMIX MU E3 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MU_E4_B_IRQn                 = 292,              /**< NETCMIX MU E4 Ored of all (tx,rx,gp,core,murip) interrupt to MUB */
  MSGINTR1_IRQn                = 293,              /**< MSGINTR Instance 1 Interrupt */
  MSGINTR2_IRQn                = 294,              /**< MSGINTR Instance 2 Interrupt */
  MSGINTR3_IRQn                = 295,              /**< MSGINTR Instance 3 Interrupt */
  MSGINTR4_IRQn                = 296,              /**< MSGINTR Instance 4 Interrupt */
  MSGINTR5_IRQn                = 297,              /**< MSGINTR Instance 5 Interrupt */
  MSGINTR6_IRQn                = 298,              /**< MSGINTR Instance 6 Interrupt */
  MSGINTR7_IRQn                = 299,              /**< MSGINTR Instance 7 Interrupt */
  MSGINTR8_IRQn                = 300,              /**< MSGINTR Instance 8 Interrupt */
  V2X_FH_MU_APCH1_IRQn         = 301,              /**< V2X-FH MU APCH1 (APP1) interrupt */
  V2X_FH_MU_APHSM2_IRQn        = 302,              /**< V2X-FH MU APHSM2 (HSM2) interrupt */
  ELE_Group1_IRQn              = 303,              /**< ELE Group 1 reset source if no s500 reference clock is detected.  Output synchronized to 32khz clk. New signal name for i.MX94 is s4v1_fdet0_tclk_err_irq. (Cause Reset) */
  ELE_Group2_IRQn              = 304,              /**< ELE Group 2 reset source s500 reference clock is not detected or too slow.  Output synchronized to ref1_clk the S500 clock. New signal name for i.MX94 is s4v1_fdet2_tclk_err_irq.  (Reset Request in CM33 domain) */
  ELE_Group3_IRQn              = 305,              /**< ELE Group 2 reset source s500 reference clock is not detected or too slow.  Output synchronized to ref1_clk. New signal name for i.MX94 is s4v1_fdet3_tclk_err_irq */
  Reserved322_IRQn             = 306,              /**< ELE Group 2 reset source s500 reference clock is not detected or too slow.  Output synchronized to S500 clock domain. New signal name for i.MX94 is s4v1_fdet1_tclk_err_irq */
  Reserved323_IRQn             = 307,              /**< s500 glue logic IRQ */
  GPC_SM_REQ_IRQn              = 308,              /**< SRC/GPC Low Power Handshake Gasket interrupt request for system management */
  EDMA1_ERROR_IRQn             = 309,              /**< AONMIX EDMA1 error interrupt */
  Reserved326_IRQn             = 310,              /**< AONMIX TRDC transfer error interrupt */
  Reserved327_IRQn             = 311,              /**< WAKEUPMIX TRDC-MGR1 transfer error interrupt */
  Reserved328_IRQn             = 312,              /**< MEGAMIX TRDC transfer error interrupt */
  Reserved329_IRQn             = 313,              /**< NOCMIX TRDC transfer error interrupt */
  Reserved330_IRQn             = 314,              /**< DISPLAYMIX TRDC transfer error interrupt */
  Reserved331_IRQn             = 315,              /**< NETCMIX TRDC/NET_M33_Sync Platform transfer error interrupt */
  Reserved332_IRQn             = 316,              /**< HSIOMIX TRDC transfer error interrupt */
  Reserved333_IRQn             = 317,              /**< WAKEUPMIX TRDC-MGR2 transfer error interrupt */
  Reserved334_IRQn             = 318,              /**< AONMIX ERM Single bit corrected ECC error */
  Reserved335_IRQn             = 319,              /**< M7MIX0 ERM Single bit corrected ECC error */
  Reserved336_IRQn             = 320,              /**< M7MIX1 ERM Single bit corrected ECC error */
  Reserved337_IRQn             = 321,              /**< WAKEUPMIX ERM Single bit corrected ECC error */
  Reserved338_IRQn             = 322,              /**< NPUMIX ERM Single bit corrected ECC error */
  Reserved339_IRQn             = 323,              /**< NETCMIX ERM Single bit corrected ECC error */
  Reserved340_IRQn             = 324,              /**< OCRAM ECC multi bit error */
  Reserved341_IRQn             = 325,              /**< AONMIX MTR Master error interrupt */
  EDMA3_ERROR_IRQn             = 326,              /**< EDMA3 DMA error interrupt */
  Reserved343_IRQn             = 327,              /**< AONMIX M33 PS Tag/Data parity error */
  M33_TCM_ERROR_IRQn           = 328,              /**< AONMIX M33 TCM error interrupt */
  Reserved345_IRQn             = 329,              /**< M7MIX ECC multi bit error */
  Reserved346_IRQn             = 330,              /**< NETCMIX M33 PS Tag/Data parity error */
  M33_SYNC_TCM_ERROR_IRQn      = 331,              /**< NETCMIX M33 TCM error interrupt */
  ONE_POINT_FIVE_MB_OCRAM_ERROR_IRQn = 332,        /**< NETCMIX 1.5MB OCSRAM Error interrupt */
  Reserved349_IRQn             = 333,              /**< M7MIX1 ECC Multi-bit error */
  GIC700_FAULT_IRQn            = 334,              /**< GIC700 Fault(Uncorrectable ECC errors) */
  M33_MCM_IRQn                 = 335,              /**< CM33 MCM interrupt */
  M33_SYNC_MCM_IRQn            = 336,              /**< CM33_sync MCM interrupt */
  ONE_POINT_FIVE_MB_SRAM_MCM_IRQn = 337,           /**< NETCMIX 1.5MB SRAM MCM interrupt */
  M7MIX0_MCM_IRQn              = 338,              /**< M7MIX0 MCM interrupt */
  M7MIX1_MCM_IRQn              = 339,              /**< M7MIX1 MCM interrupt */
  OCRAM_ECC_SINGLE_BIT_ERROR_IRQn = 340,           /**< OCRAM ECC single bit error */
  GIC700_ERROR_IRQn            = 341,              /**< GIC700 Error(Correctable ECC errors) */
  SFA_IRQn                     = 342,              /**< ANAMIX SFA(Signal Frequency Analyzer) interrupt */
  TMPSNS_ANA_1_IRQn            = 343,              /**< ANAMIX TempSensor non-secure interrupt from Threshold 1 */
  TMPSNS_ANA_2_IRQn            = 344,              /**< ANAMIX TempSensor non-secure interrupt from Threshold 2 */
  Reserved361_IRQn             = 345,              /**< ANAMIX TempSensor non-secure data ready interrupt */
  TMPSNS_CORTEXA_1_IRQ         = 346,              /**< CORTEXAMIX TempSensor non-secure interrupt from Threshold 1 */
  TMPSNS_CORTEXA_2_IRQ         = 347,              /**< CORTEXAMIX TempSensor non-secure interrupt from Threshold 2 */
  Reserved364_IRQn             = 348,              /**< CORTEXAMIX TempSensor non-secure data ready interrupt */
  CM33_0_SYSRESETREQ_IRQn      = 349,              /**< AONMIX CM33 SYSREQRST SRC reset source */
  CM33_0_LOCKUP_IRQn           = 350,              /**< AONMIX CM33 LOCKUP SRC reset source */
  CM7_0_SYSRESETREQ_IRQn       = 351,              /**< CM7_0 SYSREQRST SRC reset source */
  CM7_0_LOCKUP_IRQn            = 352,              /**< CM7_0 LOCKUP SRC reset source */
  CM33_1_SYSRESETREQ_IRQn      = 353,              /**< NETCMIX CM33_sync SYSREQRST SRC reset source */
  CM33_1_LOCKUP_IRQn           = 354,              /**< NETCMIX CM33_sync LOCKUP SRC reset source */
  CM7_1_SYSRESETREQ_IRQn       = 355,              /**< CM7_1 SYSREQRST SRC reset source */
  CM7_1_LOCKUP_IRQn            = 356,              /**< CM7_1 LOCKUP SRC reset source */
  SOC_RESET_WO_NETC_IRQn       = 357,              /**< SoC reset without netc interrupt */
  Reserved374_IRQn             = 358,              /**< NETC iEPRC PCI INT (one per each of two RC-EC, first one) */
  Reserved375_IRQn             = 359,              /**< NETC iEPRC PCI INT (one per each of two RC-EC, second one) */
  PCIE1_INTA_IRQn              = 360,              /**< PCIe Controller 1 INTA */
  PCIE1_INTB_IRQn              = 361,              /**< PCIe Controller 1 INTB */
  PCIE1_INTC_IRQn              = 362,              /**< PCIe Controller 1 INTC */
  PCIE1_INTD_IRQn              = 363,              /**< PCIe Controller 1 INTD */
  Reserved380_IRQn             = 364,              /**< PCIe 1 miscellaneous interrupts/PCIe MSI reception interrupt for RC mode/PCIe Link reset request interrupt */
  Reserved381_IRQn             = 365,              /**< PCIe Controller 1 EDMA channel interrupt */
  PCIE2_INTA_IRQn              = 366,              /**< PCIe Controller 2 INTA */
  PCIE2_INTB_IRQn              = 367,              /**< PCIe Controller 2 INTB */
  PCIE2_INTC_IRQn              = 368,              /**< PCIe Controller 2 INTC */
  PCIE2_INTD_IRQn              = 369,              /**< PCIe Controller 2 INTD */
  Reserved386_IRQn             = 370,              /**< PCIe 2 miscellaneous interrupts/PCIe MSI reception interrupt for RC mode/PCIe Link reset request interrupt */
  Reserved387_IRQn             = 371,              /**< PCIe Controller 2 EDMA channel interrupt */
  Reserved388_IRQn             = 372,              /**< NPUMIX Wakeup interrupt from CLKREQ#, WAKEUP#, BEACON_DET */
  NPUMIX_FUNC_IRQn             = 373,              /**< NPUMIX Functional interrupt */
  Reserved390_IRQn             = 374,              /**< DRAM controller Performance Monitor Interrupt */
  Reserved391_IRQn             = 375,              /**< DRAM controller Critical Interrupt */
  Reserved392_IRQn             = 376,              /**< DRAM Phy Critical Interrupt 0~15 */
  Reserved393_IRQn             = 377,              /**< DISPLAYMIX DCIF: Interrupt output for CPU domain0 (Controlled by common registers group) */
  Reserved394_IRQn             = 378,              /**< DISPLAYMIX DCIF: Interrupt output for CPU domain1 (Controlled by background layer registers group) */
  Reserved395_IRQn             = 379,              /**< DISPLAYMIX DCIF: Interrupt output for CPU domain2 (Controlled by foreground layer registers group) */
  Reserved396_IRQn             = 380,              /**< Reserved */
  Reserved397_IRQn             = 381,              /**< Reserved */
  Reserved398_IRQn             = 382,              /**< DISPLAYMIX PXP interrupt 0 */
  Reserved399_IRQn             = 383,              /**< DISPLAYMIX PXP interrupt 1 */
  Reserved400_IRQn             = 384,              /**< V2X-FH MU APSHE (SHE) A_TX/A_RX interrupt */
  Reserved401_IRQn             = 385,              /**< V2X-FH MU SCU/APDEBUG (DEBUG) B_TX/B_RX interrupt */
  Reserved402_IRQn             = 386,              /**< USB-1 (USB 3.0) Wake-up Interrupt */
  Reserved403_IRQn             = 387,              /**< USB-2 (USB 2.0) Wake-up Interrupt */
  Reserved404_IRQn             = 388,              /**< GIC700 PMU Counter Overflow */
  Reserved405_IRQn             = 389,              /**< Reserved */
  Reserved406_IRQn             = 390,              /**< xspi1 all interrupts ORed output for EENV0 (MEENV)/xspi1 arbitration lock timeout interrupt for EENV0/xspi1 arbitration win interrupt for EENV0/xspi1 FlashA error interrupt for EENV0 */
  Reserved407_IRQn             = 391,              /**< xspi1 all interrupts ORed output for EENV1 (MEENV)/xspi1 arbitration lock timeout interrupt for EENV1/xspi1 arbitration lock timeout interrupt for EENV1/xspi1 arbitration win interrupt for EENV1/xspi1 FlashA error interrupt for EENV1 */
  Reserved408_IRQn             = 392,              /**< xspi1 all interrupts ORed output for EENV2 (MEENV)/xspi1 arbitration lock timeout interrupt for EENV2/        xspi1 arbitration win interrupt for EENV2/xspi1 FlashA error interrupt for EENV2 */
  Reserved409_IRQn             = 393,              /**< xspi1 all interrupts ORed output for EENV3 (MEENV)/xspi1 arbitration lock timeout interrupt for EENV3/xspi1 arbitration win interrupt for EENV3/xspi1 FlashA error interrupt for EENV3 */
  Reserved410_IRQn             = 394,              /**< xspi1 all interrupts ORed output for EENV4 (MEENV)/xspi1 arbitration lock timeout interrupt for EENV4/xspi1 arbitration win interrupt for EENV4/xspi1 FlashA error interrupt for EENV4 */
  Reserved411_IRQn             = 395,              /**< xspi2 all interrupts ORed output for EENV0 (MEENV)/xspi2 arbitration lock timeout interrupt for EENV0/xspi2 arbitration lock timeout interrupt for EENV0/xspi2 arbitration win interrupt for EENV0/xspi2 FlashA error interrupt for EENV0 */
  Reserved412_IRQn             = 396,              /**< xspi2 all interrupts ORed output for EENV1 (MEENV)/xspi2 arbitration lock timeout interrupt for EENV1/xspi2 arbitration lock timeout interrupt for EENV1/xspi2 arbitration win interrupt for EENV1/xspi2 FlashA error interrupt for EENV1 */
  Reserved413_IRQn             = 397,              /**< xspi2 all interrupts ORed output for EENV2 (MEENV)/xspi2 arbitration lock timeout interrupt for EENV2/xspi2 arbitration win interrupt for EENV2/xspi2 FlashA error interrupt for EENV2 */
  Reserved414_IRQn             = 398,              /**< xspi2 all interrupts ORed output for EENV3 (MEENV)/xspi2 arbitration lock timeout interrupt for EENV3/xspi2 arbitration win interrupt for EENV3/xspi2 FlashA error interrupt for EENV3 */
  Reserved415_IRQn             = 399,              /**< xspi2 all interrupts ORed output for EENV4 (MEENV)/xspi2 arbitration lock timeout interrupt for EENV4/xspi2 arbitration win interrupt for EENV4/xspi2 FlashA error interrupt for EENV4 */
  Reserved416_IRQn             = 400,              /**< Reserved */
  Reserved417_IRQn             = 401,              /**< Reserved */
  Reserved418_IRQn             = 402,              /**< Reserved */
  Reserved419_IRQn             = 403,              /**< Reserved */
  Reserved420_IRQn             = 404,              /**< Reserved */
  Reserved421_IRQn             = 405               /**< Reserved */
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Cortex M33 Core Configuration
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Cortex M33 Core Configuration
 * @{
 */

#define __MPU_PRESENT                  1         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS               4         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */
#define __FPU_PRESENT                  1         /**< Defines if an FPU is present or not */
#define __DSP_PRESENT                  1         /**< Defines if Armv8-M Mainline core supports DSP instructions */
#define __SAUREGION_PRESENT            1         /**< Defines if an SAU is present or not */

#include "core_cm33.h"                 /* Core Peripheral Access Layer */
#include "system_MIMX94_cm33.h"       /* Device specific configuration file */

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


/* ----------------------------------------------------------------------------
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
typedef enum _xbar_input_signal
{
    kXBAR1_InputLogicLow            = 0|0x100U,    /**< LOGIC_LOW output assigned to XBAR1_IN0 input. */
    kXBAR2_InputLogicLow            = 0|0x200U,    /**< LOGIC_LOW output assigned to XBAR2_IN0 input. */
    kXBAR3_InputLogicLow            = 0|0x300U,    /**< LOGIC_LOW output assigned to XBAR3_IN0 input. */
} xbar_input_signal_t;

typedef enum _xbar_output_signal
{
    kXBAR1_OutputRESERVED0          = 0|0x100U,    /**< XBAR1_OUT0 output is reserved. */
    kXBAR2_OutputRESERVED0          = 0|0x200U,    /**< XBAR2_OUT0 output is reserved. */
    kXBAR3_OutputRESERVED0          = 0|0x300U,    /**< XBAR3_OUT0 output is reserved. */
} xbar_output_signal_t;


/*!
 * @}
 */ /* end of group Mapping_Information */


/* ----------------------------------------------------------------------------
   -- Macros for use with bit field definitions (xxx_SHIFT, xxx_MASK).
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Bit_Field_Generic_Macros Macros for use with bit field definitions (xxx_SHIFT, xxx_MASK).
 * @{
 */

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang system_header
  #endif
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma system_include
#endif

/**
 * @brief Mask and left-shift a bit field value for use in a register bit range.
 * @param field Name of the register bit field.
 * @param value Value of the bit field.
 * @return Masked and shifted value.
 */
#define NXP_VAL2FLD(field, value)    (((value) << (field ## _SHIFT)) & (field ## _MASK))
/**
 * @brief Mask and right-shift a register value to extract a bit field value.
 * @param field Name of the register bit field.
 * @param value Value of the register.
 * @return Masked and shifted bit field value.
 */
#define NXP_FLD2VAL(field, value)    (((value) & (field ## _MASK)) >> (field ## _SHIFT))

/*!
 * @}
 */ /* end of group Bit_Field_Generic_Macros */


/* ----------------------------------------------------------------------------
   -- SDK Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDK_Compatibility_Symbols SDK Compatibility
 * @{
 */

/* No SDK compatibility issues. */

/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */


#endif  /* _MIMX9494_CM33_CORE0_H_ */

