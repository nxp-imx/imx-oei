/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2024 NXP
 */
#ifndef __SOC_DDR_H
#define __SOC_DDR_H

#include "ddr.h"

#define QB_STATE_LOAD_ADDR	0x3001C000	/** QB Flow: training data load location, SysTCM, ends at 0x3002DFFF */
#define QB_STATE_LOAD_SIZE	0x10000		/** QB Flow: hole size, 64k */
#define QB_STATE_SAVE_ADDR	0x4aaf4000	/** TR Flow: training data save location */

#endif
