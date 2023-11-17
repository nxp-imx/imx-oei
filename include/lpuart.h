/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */
#ifndef __LPUART_H
#define __LPUART_H

#ifdef DEBUG
int lpuart32_serial_init(void);
#else
#define lpuart32_serial_init(void)
#endif
#endif
