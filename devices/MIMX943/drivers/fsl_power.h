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

#ifndef DRV_PWR_H
#define DRV_PWR_H

/*!
 * @addtogroup PWR_driver
 * @{
 */

/*! @file */

/* Includes */

#include "fsl_common.h"

/* Defines */

#define PWR_NUM_MIX_SLICE               19UL

#define PWR_MIX_SLICE_IDX_ANA           0U
#define PWR_MIX_SLICE_IDX_AON           1U
#define PWR_MIX_SLICE_IDX_BBSM          2U
#define PWR_MIX_SLICE_IDX_M7_1          3U
#define PWR_MIX_SLICE_IDX_CCMSRCGPC     4U
#define PWR_MIX_SLICE_IDX_A55C0         5U
#define PWR_MIX_SLICE_IDX_A55C1         6U
#define PWR_MIX_SLICE_IDX_A55C2         7U
#define PWR_MIX_SLICE_IDX_A55C3         8U
#define PWR_MIX_SLICE_IDX_A55P          9U
#define PWR_MIX_SLICE_IDX_DDR           10U
#define PWR_MIX_SLICE_IDX_DISPLAY       11U
#define PWR_MIX_SLICE_IDX_M7_0          12U
#define PWR_MIX_SLICE_IDX_HSIO_TOP      13U
#define PWR_MIX_SLICE_IDX_HSIO_WAON     14U
#define PWR_MIX_SLICE_IDX_NETC          15U
#define PWR_MIX_SLICE_IDX_NOC           16U
#define PWR_MIX_SLICE_IDX_NPU           17U
#define PWR_MIX_SLICE_IDX_WAKEUP        18U

#define PWR_NUM_MEM_SLICE               17U

#define PWR_MEM_SLICE_IDX_AON           0U
#define PWR_MEM_SLICE_IDX_M7_1          1U
#define PWR_MEM_SLICE_IDX_A55C0         2U
#define PWR_MEM_SLICE_IDX_A55C1         3U
#define PWR_MEM_SLICE_IDX_A55C2         4U
#define PWR_MEM_SLICE_IDX_A55C3         5U
#define PWR_MEM_SLICE_IDX_A55P          6U
#define PWR_MEM_SLICE_IDX_A55L3         7U
#define PWR_MEM_SLICE_IDX_DDR           8U
#define PWR_MEM_SLICE_IDX_DISPLAY       9U
#define PWR_MEM_SLICE_IDX_M7_0          10U
#define PWR_MEM_SLICE_IDX_HSIO          11U
#define PWR_MEM_SLICE_IDX_NETC          12U
#define PWR_MEM_SLICE_IDX_NOC1          13U
#define PWR_MEM_SLICE_IDX_NOC2          14U
#define PWR_MEM_SLICE_IDX_NPU           15U
#define PWR_MEM_SLICE_IDX_WAKEUP        16U

#define PWR_MIX_SLICE_IDX_A55C_LAST     PWR_MIX_SLICE_IDX_A55C3

#define PWR_MIX_PSW_STAT_MASK           SRC_XSPR_FUNC_STAT_PSW_STAT_MASK
#define PWR_MIX_PSW_STAT_PUP            SRC_XSPR_FUNC_STAT_PSW_STAT(0U)
#define PWR_MIX_PSW_STAT_PDN            SRC_XSPR_FUNC_STAT_PSW_STAT(1U)

#define PWR_MIX_FUNC_STAT_MASK                  \
    (SRC_XSPR_FUNC_STAT_SYSMAN_STAT_MASK |      \
     SRC_XSPR_FUNC_STAT_MEM_STAT_MASK |         \
     SRC_XSPR_FUNC_STAT_A55_HDSK_STAT_MASK |    \
     SRC_XSPR_FUNC_STAT_SSAR_STAT_MASK |        \
     SRC_XSPR_FUNC_STAT_ISO_STAT_MASK |         \
     SRC_XSPR_FUNC_STAT_RST_STAT_MASK |         \
     SRC_XSPR_FUNC_STAT_PSW_STAT_MASK)

#define PWR_MIX_FUNC_STAT_PUP                   \
    (SRC_XSPR_FUNC_STAT_SYSMAN_STAT(0U) |       \
     SRC_XSPR_FUNC_STAT_MEM_STAT(0U) |          \
     SRC_XSPR_FUNC_STAT_A55_HDSK_STAT(0U) |     \
     SRC_XSPR_FUNC_STAT_SSAR_STAT(0U) |         \
     SRC_XSPR_FUNC_STAT_ISO_STAT(0U) |          \
     SRC_XSPR_FUNC_STAT_RST_STAT(1U) |          \
     SRC_XSPR_FUNC_STAT_PSW_STAT(0U))

#define PWR_MIX_FUNC_STAT_PDN                   \
    (SRC_XSPR_FUNC_STAT_SYSMAN_STAT(1U) |       \
     SRC_XSPR_FUNC_STAT_MEM_STAT(1U) |          \
     SRC_XSPR_FUNC_STAT_A55_HDSK_STAT(1U) |     \
     SRC_XSPR_FUNC_STAT_SSAR_STAT(1U) |         \
     SRC_XSPR_FUNC_STAT_ISO_STAT(1U) |          \
     SRC_XSPR_FUNC_STAT_RST_STAT(0U) |          \
     SRC_XSPR_FUNC_STAT_PSW_STAT(1U))

#define PWR_MIX_FLAG_SWITCHABLE         (1U << 0U)  /* MIX can be switched OFF */
#define PWR_MIX_FLAG_LPMSET             (1U << 1U)  /* MIX LPM can be set */

/* Macro to convert CPU ID to GPC domain ID
 * Note:  AUTHEN_CTRL.WHITE_LIST assignments use macro
 *        to define LPM voting logic mappings.  Offset
 *        mapping to GPC domain by TRDC ID assigned to M33
 *        to avoid collisions between WHITE_LIST access control
 *        and LPM voting logic.
 */
#define CM33_TRDC_ID                2U
#define CPU2GPC(cpuId)              ((cpuId) + CM33_TRDC_ID)

#define LPMSETTING_MASK(cpuId)          (0x7ULL << ((CPU2GPC(cpuId) << 2U)))
#define LPMSETTING_DOM(cpuId, lpmVal)   (((uint64_t) lpmVal) << ((CPU2GPC(cpuId) << 2U)))
#define LPMSETTING_VAL(cpuId, lpmReg)   ((((uint64_t) lpmReg) & LPMSETTING_MASK(cpuId)) >> ((CPU2GPC(cpuId) << 2U)))

#define PWR_GPC_REQ_MIX_ID_M7_0         0U
#define PWR_GPC_REQ_MIX_ID_S500         1U
#define PWR_GPC_REQ_MIX_ID_NPU          2U
#define PWR_GPC_REQ_MIX_ID_A55          3U
#define PWR_GPC_REQ_MIX_ID_M33          4U
#define PWR_GPC_REQ_MIX_ID_AON          5U
#define PWR_GPC_REQ_MIX_ID_DDR          6U
#define PWR_GPC_REQ_MIX_ID_WAKEUP       7U
#define PWR_GPC_REQ_MIX_ID_NOC          8U
#define PWR_GPC_REQ_MIX_ID_M7_1         9U
#define PWR_GPC_REQ_MIX_ID_HSIO         10U
#define PWR_GPC_REQ_MIX_ID_M33_S        11U
#define PWR_GPC_REQ_MIX_ID_NETC         12U
#define PWR_GPC_REQ_MIX_ID_DISPLAY      13U

#define PWR_GPC_REQ_STATE_CLK_GATE      1U
#define PWR_GPC_REQ_STATE_CLK_CHANGE    2U
#define PWR_GPC_REQ_STATE_RESET         3U
#define PWR_GPC_REQ_STATE_POWER         4U
#define PWR_GPC_REQ_STATE_RETENTION     5U

#define PWR_GPC_HS_RST_AON              1U
#define PWR_GPC_HS_RST_M33P             2U
#define PWR_GPC_HS_RST_ELE              3U
#define PWR_GPC_HS_RST_M7_1             5U
#define PWR_GPC_HS_RST_A55C0            7U
#define PWR_GPC_HS_RST_A55C1            8U
#define PWR_GPC_HS_RST_A55C2            9U
#define PWR_GPC_HS_RST_A55C3            10U
#define PWR_GPC_HS_RST_A55P             11U
#define PWR_GPC_HS_RST_DDR              12U
#define PWR_GPC_HS_RST_DDRPHY           13U
#define PWR_GPC_HS_RST_DISPLAY          14U
#define PWR_GPC_HS_RST_M7_0             15U
#define PWR_GPC_HS_RST_HSIO             16U
#define PWR_GPC_HS_RST_HSIOAON          17U
#define PWR_GPC_HS_RST_NETC             18U
#define PWR_GPC_HS_RST_M33S             19U
#define PWR_GPC_HS_RST_WDOG_7_8         20U
#define PWR_GPC_HS_RST_NOC              21U
#define PWR_GPC_HS_RST_WDOG_3_4         22U
#define PWR_GPC_HS_RST_NPU              23U
#define PWR_GPC_HS_RST_WAKEUP           24U
#define PWR_GPC_HS_RST_JTAG             25U
#define PWR_GPC_HS_RST_WDOG5            26U
#define PWR_GPC_HS_RST_WDOG6            27U

/* FIXME, the index should start from 30 */
#define PWR_GPC_HS_PWR_M7_1             31U
#define PWR_GPC_HS_PWR_A55C0            1U
#define PWR_GPC_HS_PWR_A55C1            2U
#define PWR_GPC_HS_PWR_A55C2            3U
#define PWR_GPC_HS_PWR_A55C3            4U
#define PWR_GPC_HS_PWR_A55P             5U
#define PWR_GPC_HS_PWR_DDR              6U
#define PWR_GPC_HS_PWR_DISPLAY          7U
#define PWR_GPC_HS_PWR_M7_0             8U
#define PWR_GPC_HS_PWR_HSIO             9U
#define PWR_GPC_HS_PWR_HSIOAON          10U
#define PWR_GPC_HS_PWR_NETC             11U
#define PWR_GPC_HS_PWR_NOC              12U
#define PWR_GPC_HS_PWR_NPU              13U
#define PWR_GPC_HS_PWR_WAKEUP           14U


/* Types */

typedef struct
{
    uint32_t flags;
    uint32_t memMask;
    uint32_t retainMask;
    uint32_t cpuMask;
    uint32_t ipIsoMask;
    uint32_t gpcReqMaskRst;
    uint32_t gpcReqMaskPwr;
    uint32_t authenCtrl;
    uint64_t lpmSetting;
} pwrmix_mgmt_info_t;

typedef struct 
{
    uint32_t srcMixIdx;
    uint32_t req;
    uint32_t stat;
} pwr_lp_hs_mode;

/* Functions */

bool PWR_Init(uint32_t srcMixIdx);
bool PWR_IsParentPowered(uint32_t srcMixIdx);
bool PWR_AnyChildPowered(uint32_t srcMixIdx);
uint32_t PWR_NumChildPowered(uint32_t srcMixIdx);
void PWR_SystemPowerDown(void);
void PWR_LpHandshakeMaskSet(uint32_t srcMixIdx, bool enableHandshake);
void PWR_EleLpHandshakeMaskSet(uint32_t srcMixIdx, bool enableHandshake);
void PWR_LpHandshakeModeGet(pwr_lp_hs_mode *lpHsMode);
void PWR_LpHandshakeAck(void);

/* Externs */
extern pwrmix_mgmt_info_t const g_pwrMixMgmtInfo[];

#endif /* DRV_PWR_H */

/** @} */
