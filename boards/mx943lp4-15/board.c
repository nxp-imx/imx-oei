/*
 * Copyright 2023-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "oei.h"
#include "board.h"
#include "fsl_lpuart.h"
#include "fsl_ccm.h"
#include "fsl_clock.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Debug UART base pointer list */
static LPUART_Type *const s_uartBases[] = LPUART_BASE_PTRS;

/* Debug UART clock list */
static uint32_t const s_uartClks[] =
{
    0U,
    CLOCK_ROOT_LPUART1,
    CLOCK_ROOT_LPUART2,
    CLOCK_ROOT_LPUART3,
    CLOCK_ROOT_LPUART4,
    CLOCK_ROOT_LPUART5,
    CLOCK_ROOT_LPUART6,
    CLOCK_ROOT_LPUART7,
    CLOCK_ROOT_LPUART8
};

/* Debug UART configuration info */
static board_uart_config_t const s_uartConfig =
{
    .base = s_uartBases[BOARD_DEBUG_UART_INSTANCE],
    .clockId = s_uartClks[BOARD_DEBUG_UART_INSTANCE],
    .baud = BOARD_DEBUG_UART_BAUDRATE,
    .inst = BOARD_DEBUG_UART_INSTANCE
};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*--------------------------------------------------------------------------*/
/* Return the debug UART info                                               */
/*--------------------------------------------------------------------------*/
const board_uart_config_t *BOARD_GetDebugUart(void)
{
    return &s_uartConfig;
}

/*--------------------------------------------------------------------------*/
/* Initialize debug console                                                 */
/*--------------------------------------------------------------------------*/
void BOARD_InitDebugConsole(void)
{
    if (s_uartConfig.base != NULL)
    {
#if 0
        uint64_t rate = CCM_RootGetRate(s_uartConfig.clockId);
#else
        uint64_t rate = 24000000;
#endif

        /* Configure debug UART */
        lpuart_config_t lpuart_config;
        LPUART_GetDefaultConfig(&lpuart_config);
        lpuart_config.baudRate_Bps = s_uartConfig.baud;
        lpuart_config.rxFifoWatermark = ((uint8_t)
            FSL_FEATURE_LPUART_FIFO_SIZEn(s_uartConfig.base)) - 1U;
        lpuart_config.txFifoWatermark = ((uint8_t)
            FSL_FEATURE_LPUART_FIFO_SIZEn(s_uartConfig.base)) - 1U;
        lpuart_config.enableTx = true;
        lpuart_config.enableRx = true;
        (void) LPUART_Init(s_uartConfig.base, &lpuart_config,
            (uint32_t) rate & 0xFFFFFFFFU);
    }
}
