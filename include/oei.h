/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023 NXP
 */
#ifndef __OEI_H
#define __OEI_H
/*
 * Success and system ROM code will not request EdgeLock secure enclave to update OEI
 * memory TRDC configuration, which permission is executable and no write permission.
 */
#define OEI_SUCCESS		0xFAu
/*
 * Success with free memory request, system ROM will send release memory request to
 * EdgeLock secure enclave, which should release the write permission but lock the
 * execution permission.
 */
#define OEI_SUCCESS_FREE_MEM	0x55u
/*
 * ROM code will break the boot flow, move to next boot stage and reset the system
 */
#define OEI_FAIL		0x33u

#endif
