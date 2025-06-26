/*
 * Copyright 2023-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "board.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
#if (BOARD_DEBUG_UART_INSTANCE == 1U)
    /* Configure LPUART 1 */
    IOMUXC_SetPinMux(IOMUXC_PAD_UART1_RXD__LPUART1_RX, 0U);
    IOMUXC_SetPinConfig(IOMUXC_PAD_UART1_RXD__LPUART1_RX, IOMUXC_PAD_PD(1U));

    IOMUXC_SetPinMux(IOMUXC_PAD_UART1_TXD__LPUART1_TX, 0);
    IOMUXC_SetPinConfig(IOMUXC_PAD_UART1_TXD__LPUART1_TX, IOMUXC_PAD_DSE(0xFU));
#elif (BOARD_DEBUG_UART_INSTANCE == 2U)
    /* Configure LPUART 2 */
    IOMUXC_SetPinMux(IOMUXC_PAD_UART2_RXD__LPUART2_RX, 0);
    IOMUXC_SetPinConfig(IOMUXC_PAD_UART2_RXD__LPUART2_RX, IOMUXC_PAD_PD(1U));

    IOMUXC_SetPinMux(IOMUXC_PAD_UART2_TXD__LPUART2_TX, 0);
    IOMUXC_SetPinConfig(IOMUXC_PAD_UART2_TXD__LPUART2_TX, IOMUXC_PAD_DSE(0xFU));
#endif
}
