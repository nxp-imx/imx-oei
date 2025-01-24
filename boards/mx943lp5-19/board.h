/*
 * Copyright 2023-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BOARD_H
#define BOARD_H

#include "fsl_common.h"
#include "pin_mux.h"
#include "config_board.h"

/*!
 * @addtogroup BRD_OEI_MX95EVK
 * @{
 *
 * @file
 * @brief
 *
 * Header file containing the board API.
 */

/*******************************************************************************
 * Types
 ******************************************************************************/

/*!
 * Debug UART configuration info
 */
typedef struct
{
    LPUART_Type *const base;  /*!< LPUART base pointer */
    uint32_t clockId;         /*!< Clock ID */
    uint32_t baud;            /*!< Baud rate */
    uint8_t inst;             /*!< Instance number */
} board_uart_config_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

/*! Init hardware */
void BOARD_InitHardware(void);

/*! Init clocks */
void BOARD_InitClocks(void);

/*!
 * Get a device clock debug UART info.
 *
 * This function returns the UART info for the UART used for SM
 * debug.
 *
 * @return Returns the debug UART config info.
 */
const board_uart_config_t *BOARD_GetDebugUart(void);

/*! Init the debug UART */
void BOARD_InitDebugConsole(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** @} */

#endif /* BOARD_H */
