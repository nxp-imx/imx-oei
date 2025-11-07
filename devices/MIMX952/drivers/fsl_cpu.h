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
 * @addtogroup MX952_CPU_driver
 * @{
 *
 * @file
 * @brief
 *
 * Header for MX952 CPU driver.
 */
/*==========================================================================*/

#ifndef DRV_CPU_H
#define DRV_CPU_H

/* Includes */

#include "fsl_common.h"

/* Defines */

#ifndef DOXYGEN

#define CPU_NUM_IDX         7U

#define CPU_IDX_M33P        0U
#define CPU_IDX_M7P         1U
#define CPU_IDX_A55C0       2U
#define CPU_IDX_A55C1       3U
#define CPU_IDX_A55C2       4U
#define CPU_IDX_A55C3       5U
#define CPU_IDX_A55P        6U

#define CPU_IDX_A55C_LAST   CPU_IDX_A55C3

#define CPU_NUM_RUN_MODES       3U

#define CPU_RUN_MODE_START      0U
#define CPU_RUN_MODE_HOLD       1U
#define CPU_RUN_MODE_STOP       2U
#define CPU_RUN_MODE_SLEEP      3U

#define CPU_NUM_SLEEP_MODES     4U

#define CPU_SLEEP_MODE_RUN      0U
#define CPU_SLEEP_MODE_WAIT     1U
#define CPU_SLEEP_MODE_STOP     2U
#define CPU_SLEEP_MODE_SUSPEND  3U

#define CPU_NUM_PD_LPM              5U

#define CPU_PD_LPM_ON_NEVER         0U
#define CPU_PD_LPM_ON_RUN           1U
#define CPU_PD_LPM_ON_RUN_WAIT      2U
#define CPU_PD_LPM_ON_RUN_WAIT_STOP 3U
#define CPU_PD_LPM_ON_ALWAYS        4U

#define CPU_FSM_STATE_IDLE_RUN          0x00U
#define CPU_FSM_STATE_SLEEP_A55_HDSK    0x01U
#define CPU_FSM_STATE_SLEEP_SYSMAN      0x02U
#define CPU_FSM_STATE_SLEEP_SSAR        0x03U
#define CPU_FSM_STATE_SLEEP_RESET       0x08U
#define CPU_FSM_STATE_SLEEP_SYS         0x0BU
#define CPU_FSM_STATE_IDLE_SLEEP        0x0CU
#define CPU_FSM_STATE_WAKEUP_SYS        0x0DU
#define CPU_FSM_STATE_WAKEUP_POWER      0x0FU
#define CPU_FSM_STATE_WAKEUP_SSAR       0x16U
#define CPU_FSM_STATE_WAKEUP_SYSMAN     0x17U
#define CPU_FSM_STATE_WAKEUP_A55_HDSK   0x18U

#define CPU_PER_LPI_ON_NEVER            0U
#define CPU_PER_LPI_ON_RUN              1U
#define CPU_PER_LPI_ON_RUN_WAIT         2U
#define CPU_PER_LPI_ON_RUN_WAIT_STOP    3U
#define CPU_PER_LPI_ON_ALWAYS           4U

#define LPCG_CPU_LPM_EN                 1U

#define CPU_NUM_PER_LPI_IDX             19U

#define CPU_PER_LPI_IDX_GPIO1           0U
#define CPU_PER_LPI_IDX_GPIO2           1U
#define CPU_PER_LPI_IDX_GPIO3           2U
#define CPU_PER_LPI_IDX_GPIO4           3U
#define CPU_PER_LPI_IDX_GPIO5           4U
#define CPU_PER_LPI_IDX_CAN1            5U
#define CPU_PER_LPI_IDX_CAN2            6U
#define CPU_PER_LPI_IDX_CAN3            7U
#define CPU_PER_LPI_IDX_LPUART1         8U
#define CPU_PER_LPI_IDX_LPUART2         9U
#define CPU_PER_LPI_IDX_LPUART3         10U
#define CPU_PER_LPI_IDX_LPUART4         11U
#define CPU_PER_LPI_IDX_LPUART5         12U
#define CPU_PER_LPI_IDX_LPUART6         13U
#define CPU_PER_LPI_IDX_LPUART7         14U
#define CPU_PER_LPI_IDX_LPUART8         15U
#define CPU_PER_LPI_IDX_WDOG3           16U
#define CPU_PER_LPI_IDX_WDOG4           17U
#define CPU_PER_LPI_IDX_WDOG5           18U

#endif

/* Types */

/*!
 * CPU watchdog info structure
 *
 * Structure containing parameters for CPU watchdog.
 */
typedef struct
{
    IRQn_Type secIrq;       /*!< wdog secure IRQ number */
    IRQn_Type nonsecIrq;    /*!< wdog non-secure IRQ number */
    uint32_t rstLine;       /*!< wdog reset line */
} cpu_wdog_info_t;

/*!
 * CPU management info structure
 *
 * Structure containing parameters required for CPU management.
 */
typedef struct
{
    uint32_t srcMixIdx;                 /*!< CPU's SRC MIX identifier */
    __IO uint32_t *irqMaskReg;          /*!< CPU's IRQ mask register */
    __IO uint32_t *cpuWaitReg;          /*!< CPU WAIT register */
    uint32_t cpuWaitMask;               /*!< CPU WAIT register mask */
    IRQn_Type rstReqIrq;                /*!< CPU reset request IRQ number */
    IRQn_Type lockupIrq;                /*!< CPU lockup IRQ number */
    cpu_wdog_info_t const *wdogInfo;    /*!< CPU watchdog structure */
    __IO uint32_t *vectorRegHigh;       /*!< CPU vector high */
    __IO uint32_t *vectorRegLow;        /*!< CPU vector low */
    uint32_t vectorShift;               /*!< CPU vector shift */
    uint32_t cmcSysSleepCtrl;           /*!< CMC system sleep control */
    uint32_t cmcMisc;                   /*!< CMC misc control */
} cpu_mgmt_info_t;

/*!
 * LPI info structure
 *
 * Structure containing parameters required to hold LPI details.
 */
typedef struct
{
    uint32_t lpcgIdx;
} cpu_per_lpi_info_t;

/* Functions */

/*!
 * @name MX952 CPU driver functions
 * @{
 */

/*!
 * Set CPU WAIT signal
 *
 * @param[in]   cpuIdx          CPU identifier
 * @param[in]   enableCpuWait   Enable flag (1=enable, 0=disable)
 *
 * This function allows caller to set the WAIT signal for the given \a cpuIdx.
 *
 * @return Returns true if WAIT signal is set successfully for the given CPU,
 *         otherwise false.
 */
bool CPU_WaitSet(uint32_t cpuIdx, bool enableCpuWait);

/*!
 * Set CPU sleep mode
 *
 * @param[in]   cpuIdx      CPU identifier
 * @param[in]   sleepMode   CPU sleep mode
 *
 * This function allows caller to set sleep mode for the given CPU. When a CPU
 * executes WFI/WFE event, it enters to WAIT/STOP/SUSPEND state (or stay in
 * RUN mode) based on given \a sleepMode configuration.
 *
 * @return Returns true if CPU sleep mode is set successfully, otherwise false.
 */
bool CPU_SleepModeSet(uint32_t cpuIdx, uint32_t sleepMode);

/** @} */

/* Externs */

#endif /* DRV_CPU_H */

/** @} */

