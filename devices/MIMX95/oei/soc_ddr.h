/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2024-2025 NXP
 */
#ifndef __SOC_DDR_H
#define __SOC_DDR_H

#include "ddr.h"

#define QB_STATE_LOAD_ADDR     0x4aaf0000	        /** QB Flow: training data load location, end of NPU SRAM */
#define QB_STATE_STORAGE_SIZE  0x10000		        /** QB Flow: hole size, 64k */
#define QB_STATE_SAVE_ADDR     QB_STATE_LOAD_ADDR	/** TR Flow: training data save location, end of NPU SRAM */

#endif
