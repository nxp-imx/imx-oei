/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdarg.h>
#include <stdint.h>
#include "fsl_lpuart.h"
#include "board.h"

int putchar(int ch)
{
	const uint8_t cr = '\r';
	const board_uart_config_t *uartConfig = BOARD_GetDebugUart();

	if (uartConfig->base != NULL) {
		if (ch == '\n')
			LPUART_WriteBlocking(uartConfig->base, &cr, 1);

		LPUART_WriteBlocking(uartConfig->base, (const uint8_t *) &ch, 1);
	}

	return 0;
}
