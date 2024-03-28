/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2024 NXP
 */
#ifndef __SOC_ROM_H
#define __SOC_ROM_H

#include "rom_api.h"

static const struct rom_api rapi = {
	.download_image  = (download_image_fn)  0x10011cb5,
	.query_boot_info = (query_boot_info_fn) 0x10011fd1,
	.set_ready       = (set_ready_fn)       0x10012097,
};

#endif
