/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */
#ifndef __PINMUX_H
#define __PINMUX_H

#ifdef DEBUG
void pinmux_config(void);
#else
void pinmux_config(void)
{
}
#endif
#endif
