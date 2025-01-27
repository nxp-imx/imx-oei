/*
 * Copyright 2025 NXP
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

/*==========================================================================*/
/*!
 * @addtogroup MX94_PWR_driver
 * @{
 *
 * @file
 * @brief
 *
 * Header for MX94 Power Driver.
 */
/*==========================================================================*/

#ifndef DRV_PWR_H
#define DRV_PWR_H

/* Includes */

#include "fsl_common.h"

/* Defines */

#ifndef DOXYGEN

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
#define PWR_MIX_FLAG_QCH_TIMEOUT        (1U << 2U)  /* MIX supports Q-Channel timeout */

/* Macro to convert CPU ID to GPC domain ID
 * Note:  AUTHEN_CTRL.WHITE_LIST assignments use macro
 *        to define LPM voting logic mappings.  Offset
 *        mapping to GPC domain by TRDC ID assigned to M33
 *        to avoid collisions between WHITE_LIST access control
 *        and LPM voting logic.
 */
#define CM33_TRDC_ID                2U
#define CPU2GPC(cpuId)              ((cpuId) + CM33_TRDC_ID)

#define WHITELIST_MASK(cpuId)           (1UL << (CPU2GPC(cpuId)))
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

#define PWR_GPC_HS_PWR_M7_1             31U     /* gpcReqIdxPwr = 0 */
#define PWR_GPC_HS_PWR_A55C0            1U      /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_A55C1            2U      /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_A55C2            3U      /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_A55C3            4U      /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_A55P             5U      /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_DDR              6U      /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_DISPLAY          7U      /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_M7_0             8U      /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_HSIO             9U      /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_HSIOAON          10U     /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_NETC             11U     /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_NOC              12U     /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_NPU              13U     /* gpcReqIdxPwr = 1 */
#define PWR_GPC_HS_PWR_WAKEUP           14U     /* gpcReqIdxPwr = 1 */

#endif

/* Types */

/*!
 * Power MIX management structure
 */
typedef struct
{
    uint32_t flags;             /*!< MIX capabilities */
    uint32_t memMask;           /*!< Bitmask of MEM slice instances */
    uint32_t retainMask;        /*!< Bitmask of MEM slices always retained */
    uint32_t cpuMask;           /*!< CPU mask */
    uint32_t ipIsoMask;         /*!< ISO mask */
    uint32_t gpcReqMaskRst;     /*!< GPC reset request mask */
    uint32_t gpcReqMaskPwr;     /*!< GPC power request mask */
    uint32_t gpcReqIdxPwr;      /*!< GPC power request register index */
    uint32_t authenCtrl;        /*!< MIX authentication control */
    uint64_t lpmSetting;        /*!< MIX LPM setting */
    uint32_t lpcgIdxStart;      /*!< MIX LPCG starting index */
    uint32_t lpcgIdxEnd;        /*!< MIX LPCG ending index */
} pwrmix_mgmt_info_t;

/*!
 * Structure containing SM LP handshake details
 */
typedef struct 
{
    uint32_t srcMixIdx;     /*!< SRX MIX identifier for the active LP request */
    uint32_t req;           /*!< Active LP request */
    uint32_t stat;          /*!< Active LP request status */
} pwr_lp_hs_mode;

/* Functions */

/*!
 * @name MX95 Power driver functions
 * @{
 */

/*!
 * Initialize MIX slice power configuration
 *
 * @param[in]   srcMixIdx       SRC MIX identifier
 *
 * This function initializes given MIX slice's power configuration.
 *
 * @return Returns true if MIX slice's power initialization is successful,
 *         otherwise false.
 */
bool PWR_Init(uint32_t srcMixIdx);

/*!
 * Check if parent of MIX slice is powered
 *
 * @param[in]   srcMixIdx       SRC MIX identifier
 *
 * @return Returns true if parent of MIX slice is powered-on, otherwise false.
 */
bool PWR_IsParentPowered(uint32_t srcMixIdx);

/*!
 * Check if any child of MIX slice is powered
 *
 * @param[in]   srcMixIdx       SRC MIX identifier
 *
 * @return Returns true if any child of the given MIX slice is powered-on,
 *         otherwise false.
 */
bool PWR_AnyChildPowered(uint32_t srcMixIdx);

/*!
 * Find number of children domains powered
 *
 * @param[in]   srcMixIdx       SRC MIX identifier
 *
 * @return Returns number of powered-on child domains for the given MIX slice.
 */
uint32_t PWR_NumChildPowered(uint32_t srcMixIdx);

/*!
 * Request system power down
 *
 * This function allows caller to request system power down.
 */
void PWR_SystemPowerDown(void);

/*!
 * Configure SM LP handshake mask
 *
 * @param[in]   srcMixIdx           SRC MIX identifier
 * @param[in]   enableHandshake     Handshake enable flag (1=enable, 0=disable)
 *
 * This function enable/disable SM LP handshake.
 */
void PWR_LpHandshakeMaskSet(uint32_t srcMixIdx, bool enableHandshake);

/*!
 * Configure ELE LP handshake mask
 *
 * @param[in]   srcMixIdx           SRC MIX identifier
 * @param[in]   enableHandshake     Handshake enable flag (1=enable, 0=disable)
 *
 * This function enable/disable ELE LP handshake.
 */
void PWR_EleLpHandshakeMaskSet(uint32_t srcMixIdx, bool enableHandshake);

/*!
 * Get SM LP handshake mode details
 *
 * @param[out]   lpHsMode    Structure containing SM LP handshake details
 *
 * This function gets SM LP handshake mode details like SRC MIX for active lp
 * request, LP request and status.
 */
void PWR_LpHandshakeModeGet(pwr_lp_hs_mode *lpHsMode);

/*!
 * Acknowledge LP handshake
 */
void PWR_LpHandshakeAck(void);

/** @} */

/* Externs */

/*! Power MIX management info */
extern pwrmix_mgmt_info_t const g_pwrMixMgmtInfo[];

#endif /* DRV_PWR_H */

/** @} */

