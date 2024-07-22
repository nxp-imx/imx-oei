/*
 * Copyright 2023-2024 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FSL_CLOCK_H
#define FSL_CLOCK_H

/*!
 * @addtogroup CLOCK_driver
 * @{
 */

/*! @file */

/* Includes */

#include "fsl_common.h"

/* Defines */

#define CLOCK_OSC32K_HZ                     32768ULL
#define CLOCK_OSC24M_HZ                     24000000ULL
#define CLOCK_FRO_HZ                        300000000ULL
#define CLOCK_PLL_FREF_HZ                   CLOCK_OSC24M_HZ
#define CLOCK_M_HZ                          1000000ULL
#define CLOCK_K_HZ                          1000ULL

#define CLOCK_PLL_CALC_ACCURACY_HZ          1000U
#define CLOCK_PLL_MFD                       (CLOCK_PLL_FREF_HZ/CLOCK_PLL_CALC_ACCURACY_HZ)

#define CLOCK_NUM_PLL                       8U

#define CLOCK_PLL_SYS1                      0U
#define CLOCK_PLL_AUDIO1                    1U
#define CLOCK_PLL_AUDIO2                    2U
#define CLOCK_PLL_ENCODER                   3U
#define CLOCK_PLL_ARM                       4U
#define CLOCK_PLL_DRAM                      5U
#define CLOCK_PLL_HSIO                      6U
#define CLOCK_PLL_LDB                       7U

#define CLOCK_NUM_SRC                       46UL

#define CLOCK_SRC_EXT                       0U
#define CLOCK_SRC_OSC32K                    1U
#define CLOCK_SRC_OSC24M                    2U
#define CLOCK_SRC_FRO                       3U
#define CLOCK_SRC_SYSPLL1_VCO               4U
#define CLOCK_SRC_SYSPLL1_PFD0_UNGATED      5U
#define CLOCK_SRC_SYSPLL1_PFD0              6U
#define CLOCK_SRC_SYSPLL1_PFD0_DIV2         7U
#define CLOCK_SRC_SYSPLL1_PFD1_UNGATED      8U
#define CLOCK_SRC_SYSPLL1_PFD1              9U
#define CLOCK_SRC_SYSPLL1_PFD1_DIV2         10U
#define CLOCK_SRC_SYSPLL1_PFD2_UNGATED      11U
#define CLOCK_SRC_SYSPLL1_PFD2              12U
#define CLOCK_SRC_SYSPLL1_PFD2_DIV2         13U
#define CLOCK_SRC_AUDIOPLL1_VCO             14U
#define CLOCK_SRC_AUDIOPLL1                 15U
#define CLOCK_SRC_AUDIOPLL2_VCO             16U
#define CLOCK_SRC_AUDIOPLL2                 17U

#define CLOCK_SRC_RESERVED18                18U
#define CLOCK_SRC_RESERVED19                19U
#define CLOCK_SRC_RESERVED20                20U
#define CLOCK_SRC_RESERVED21                21U
#define CLOCK_SRC_RESERVED22                22U
#define CLOCK_SRC_RESERVED23                23U
#define CLOCK_SRC_ENCODER_VCO               24U
#define CLOCK_SRC_ENCODER_PFD0_UNGATED      25U
#define CLOCK_SRC_ENCODER_PFD0              26U
#define CLOCK_SRC_ENCODER_PFD1_UNGATED      27U
#define CLOCK_SRC_ENCODER_PFD1              28U

#define CLOCK_SRC_ARMPLL_VCO                29U
#define CLOCK_SRC_ARMPLL_PFD0_UNGATED       30U
#define CLOCK_SRC_ARMPLL_PFD0               31U
#define CLOCK_SRC_ARMPLL_PFD1_UNGATED       32U
#define CLOCK_SRC_ARMPLL_PFD1               33U
#define CLOCK_SRC_ARMPLL_PFD2_UNGATED       34U
#define CLOCK_SRC_ARMPLL_PFD2               35U
#define CLOCK_SRC_ARMPLL_PFD3_UNGATED       36U
#define CLOCK_SRC_ARMPLL_PFD3               37U

#define CLOCK_SRC_DRAMPLL_VCO               38U
#define CLOCK_SRC_DRAMPLL                   39U
#define CLOCK_SRC_HSIOPLL_VCO               40U
#define CLOCK_SRC_HSIOPLL                   41U
#define CLOCK_SRC_LDBPLL_VCO                42U
#define CLOCK_SRC_LDBPLL                    43U

/* TODO TDB */
#define CLOCK_SRC_EXT1                      44U
#define CLOCK_SRC_EXT2                      45U

#define CLOCK_NUM_ROOT                      128U
#define CLOCK_NUM_ROOT_MUX_SEL              4U

/* TODO CCM clock ROOT list */
#define CLOCK_ROOT_ADC                      0U
#define CLOCK_ROOT_BUS_AON                  1U
#define CLOCK_ROOT_CAN1                     2U
#define CLOCK_ROOT_GLITCHFILTER             3U
#define CLOCK_ROOT_GPT1                     4U
#define CLOCK_ROOT_I3C1_SLOW                5U
#define CLOCK_ROOT_LPI2C1                   6U
#define CLOCK_ROOT_LPI2C2                   7U
#define CLOCK_ROOT_LPSPI1                   8U
#define CLOCK_ROOT_LPSPI2                   9U
#define CLOCK_ROOT_LPTMR1                   10U
#define CLOCK_ROOT_LPUART1                  11U
#define CLOCK_ROOT_LPUART2                  12U
#define CLOCK_ROOT_M33                      13U
#define CLOCK_ROOT_M33_SYSTICK              14U
#define CLOCK_ROOT_PDM                      15U
#define CLOCK_ROOT_SAI1                     16U
#define CLOCK_ROOT_TPM2                     17U
#define CLOCK_ROOT_A55                      18U
#define CLOCK_ROOT_A55_MTR_BUS              19U
#define CLOCK_ROOT_A55_PERIPH               20U
#define CLOCK_ROOT_DRAM_ALT                 21U
#define CLOCK_ROOT_DRAM_APB                 22U
#define CLOCK_ROOT_DISP_APB                 23U
#define CLOCK_ROOT_DISP_AXI                 24U
#define CLOCK_ROOT_DISP_PIX                 25U
#define CLOCK_ROOT_HSIO_ACSCAN_480M         26U
#define CLOCK_ROOT_HSIO_ACSCAN_80M          27U
#define CLOCK_ROOT_HSIO                     28U
#define CLOCK_ROOT_HSIO_PCIE_AUX            29U
#define CLOCK_ROOT_HSIO_PCIE_TEST_160M      30U
#define CLOCK_ROOT_HSIO_PCIE_TEST_400M      31U
#define CLOCK_ROOT_HSIO_PCIE_TEST_500M      32U
#define CLOCK_ROOT_HSIO_PCIE_TEST_50M       33U
#define CLOCK_ROOT_HSIO_USB_TEST_60M        34U
#define CLOCK_ROOT_BUS_M7_0                 35U
#define CLOCK_ROOT_M7_0                     36U
#define CLOCK_ROOT_M7_0_SYSTICK             37U
#define CLOCK_ROOT_BUS_M7_1                 38U
#define CLOCK_ROOT_M7_1                     39U
#define CLOCK_ROOT_M7_1_SYSTICK             40U
#define CLOCK_ROOT_BUS_NETCMIX              41U
#define CLOCK_ROOT_ECAT                     42U
#define CLOCK_ROOT_ENET                     43U
#define CLOCK_ROOT_ENET_PHY_TEST_200M       44U
#define CLOCK_ROOT_ENET_PHY_TEST_500M       45U
#define CLOCK_ROOT_ENET_PHY_TEST_667M       46U
#define CLOCK_ROOT_ENET_REF                 47U
#define CLOCK_ROOT_ENET_TIMER1              48U
#define CLOCK_ROOT_ENET_TIMER2              49U
#define CLOCK_ROOT_ENET_TIMER3              50U
#define CLOCK_ROOT_FLEXIO3                  51U
#define CLOCK_ROOT_FLEXIO4                  52U
#define CLOCK_ROOT_M33_SYNC                 53U
#define CLOCK_ROOT_M33_SYNC_SYSTICK         54U
#define CLOCK_ROOT_MAC0                     55U
#define CLOCK_ROOT_MAC1                     56U
#define CLOCK_ROOT_MAC2                     57U
#define CLOCK_ROOT_MAC3                     58U
#define CLOCK_ROOT_MAC4                     59U
#define CLOCK_ROOT_MAC5                     60U
#define CLOCK_ROOT_NOC_APB                  61U
#define CLOCK_ROOT_NOC                      62U
#define CLOCK_ROOT_NPU_APB                  63U
#define CLOCK_ROOT_NPU                      64U
#define CLOCK_ROOT_CCM_CKO1                 65U
#define CLOCK_ROOT_CCM_CKO2                 66U
#define CLOCK_ROOT_CCM_CKO3                 67U
#define CLOCK_ROOT_CCM_CKO4                 68U
#define CLOCK_ROOT_BISS                     69U
#define CLOCK_ROOT_BUS_WAKEUP               70U
#define CLOCK_ROOT_CAN2                     71U
#define CLOCK_ROOT_CAN3                     72U
#define CLOCK_ROOT_CAN4                     73U
#define CLOCK_ROOT_CAN5                     74U
#define CLOCK_ROOT_ENDAT2_1                 75U
#define CLOCK_ROOT_ENDAT2_2                 76U
#define CLOCK_ROOT_ENDAT3_1_FAST            77U
#define CLOCK_ROOT_ENDAT3_1_SLOW            78U
#define CLOCK_ROOT_FLEXIO1                  79U
#define CLOCK_ROOT_FLEXIO2                  80U
#define CLOCK_ROOT_GPT2                     81U
#define CLOCK_ROOT_GPT3                     82U
#define CLOCK_ROOT_GPT4                     83U
#define CLOCK_ROOT_HIPERFACE1               84U
#define CLOCK_ROOT_HIPERFACE1_SYNC          85U
#define CLOCK_ROOT_HIPERFACE2               86U
#define CLOCK_ROOT_HIPERFACE2_SYNC          87U
#define CLOCK_ROOT_I3C2_SLOW                88U
#define CLOCK_ROOT_LPI2C3                   89U
#define CLOCK_ROOT_LPI2C4                   90U
#define CLOCK_ROOT_LPI2C5                   91U
#define CLOCK_ROOT_LPI2C6                   92U
#define CLOCK_ROOT_LPI2C7                   93U
#define CLOCK_ROOT_LPI2C8                   94U
#define CLOCK_ROOT_LPSPI3                   95U
#define CLOCK_ROOT_LPSPI4                   96U
#define CLOCK_ROOT_LPSPI5                   97U
#define CLOCK_ROOT_LPSPI6                   98U
#define CLOCK_ROOT_LPSPI7                   99U
#define CLOCK_ROOT_LPSPI8                   100U
#define CLOCK_ROOT_LPTMR2                   101U
#define CLOCK_ROOT_LPUART10                 102U
#define CLOCK_ROOT_LPUART11                 103U
#define CLOCK_ROOT_LPUART12                 104U
#define CLOCK_ROOT_LPUART3                  105U
#define CLOCK_ROOT_LPUART4                  106U
#define CLOCK_ROOT_LPUART5                  107U
#define CLOCK_ROOT_LPUART6                  108U
#define CLOCK_ROOT_LPUART7                  109U
#define CLOCK_ROOT_LPUART8                  110U
#define CLOCK_ROOT_LPUART9                  111U
#define CLOCK_ROOT_SAI2                     112U
#define CLOCK_ROOT_SAI3                     113U
#define CLOCK_ROOT_SAI4                     114U
#define CLOCK_ROOT_SWO_TRACE                115U
#define CLOCK_ROOT_TPM4                     116U
#define CLOCK_ROOT_TPM5                     117U
#define CLOCK_ROOT_TPM6                     118U
#define CLOCK_ROOT_USB_PHY_BURUNIN          119U
#define CLOCK_ROOT_USDHC1                   120U
#define CLOCK_ROOT_USDHC2                   121U
#define CLOCK_ROOT_USDHC3                   122U
#define CLOCK_ROOT_V2X_PK                   123U
#define CLOCK_ROOT_WAKEUP_AXI               124U
#define CLOCK_ROOT_XSPI_SLV_ROOT            125U
#define CLOCK_ROOT_XSPI1                    126U
#define CLOCK_ROOT_XSPI2                    127U

#define CLOCK_NUM_GPR                       3U
#define CLOCK_NUM_GPR_SEL                   8U
#define CLOCK_NUM_GPR_MUX_SEL               2U

#define CLOCK_GPR_SEL_EXT                   0U
#define CLOCK_GPR_SEL_A55C0                 1U
#define CLOCK_GPR_SEL_A55C1                 2U
#define CLOCK_GPR_SEL_A55C2                 3U
#define CLOCK_GPR_SEL_A55C3                 4U
#define CLOCK_GPR_SEL_A55P                  5U
#define CLOCK_GPR_SEL_DRAM                  6U
#define CLOCK_GPR_SEL_TEMPSENSE             7U

#define CLOCK_ROUND_RULE_CEILING            0U
#define CLOCK_ROUND_RULE_FLOOR              1U
#define CLOCK_ROUND_RULE_CLOSEST            2U

/* Types */
typedef struct
{
    bool isFrac;
    uint8_t numDFS;
} pll_attr_t;

typedef struct
{
    uint32_t selIdx;
    uint32_t selMask;
    uint32_t selShift;
    uint32_t selMux[CLOCK_NUM_GPR_MUX_SEL];
} ccm_gpr_sel_attr_t;

/* Functions */

bool CLOCK_SourceGetEnable(uint32_t sourceIdx);
bool CLOCK_SourceSetEnable(uint32_t sourceIdx, bool enable);
uint64_t CLOCK_SourceGetRate(uint32_t sourceIdx);
bool CLOCK_SourceSetRate(uint32_t sourceIdx, uint64_t rate, uint32_t roundRule);
bool CLOCK_SourceSetSsc(uint32_t sourceIdx, uint32_t spreadPercent,
    uint32_t modFreq, uint32_t enable);
bool CLOCK_SourceGetSsc(uint32_t sourceIdx, uint32_t *spreadPercent,
    uint32_t *modFreq, uint32_t *enable);

/* Externs */

extern uint64_t g_clockExt1Rate;
extern const pll_attr_t g_pllAttrs[];
extern const uint8_t g_clockRootMux[][CLOCK_NUM_ROOT_MUX_SEL];
extern const ccm_gpr_sel_attr_t g_clockGprSel[CLOCK_NUM_GPR_SEL];

#endif /* FSL_CLOCK_H */

/** @} */
