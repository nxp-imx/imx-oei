/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2024 NXP
 */
#ifndef __SOC_DDR_H
#define __SOC_DDR_H

#include "ddr.h"

#define QB_STATE_LOAD_ADDR	0x204c8000	/** QB Flow: training data load location, end of OCRAM */
#define QB_STATE_STORAGE_SIZE	0x10000		/** QB Flow: hole size, 64k */
#define QB_STATE_SAVE_ADDR	0x4aa34000 	/** TR Flow: training data save location */

#endif
