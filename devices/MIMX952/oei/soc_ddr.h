/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2025 NXP
 */
#ifndef __SOC_DDR_H
#define __SOC_DDR_H

#include "ddr.h"

#define NPU_SRAM_BASE          0x4aa00000
#define NPU_SRAM_SIZE          0x64000

/** QB Flow: hole size, 64k */
#define QB_STATE_STORAGE_SIZE  0x10000
/**
 * QB Flow: training data load location, end of NPU SRAM
 * = 0x4aa54000
 */
#define QB_STATE_LOAD_ADDR     (NPU_SRAM_BASE + NPU_SRAM_SIZE - QB_STATE_STORAGE_SIZE)
/** TR Flow: training data save location, end of NPU SRAM */
#define QB_STATE_SAVE_ADDR     QB_STATE_LOAD_ADDR
/** TR Flow: training data save location in NS DRAM */
#define QB_STATE_DDR_ADDR      0x8fe00000

#endif
