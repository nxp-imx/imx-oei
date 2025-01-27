/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_MIMX94_cm33))

#define MIMX94_cm33_SERIES

/* CMSIS-style register definitions */
#include "MIMX94_cm33.h"
/* CPU specific feature definitions */
#include "MIMX94_cm33_features.h"
/* CPU electrical spec definitions */
#include "MIMX94_elec_spec.h"


#else
#error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
