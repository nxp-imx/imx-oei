/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */
#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef DEBUG
int printf(const char *fmt, ...);
void putc(const char c);
#else
#define printf(...)	0
#define putc(...)
#endif
#endif
