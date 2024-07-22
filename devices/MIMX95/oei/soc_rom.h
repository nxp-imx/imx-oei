/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2024 NXP
 */
#ifndef __SOC_ROM_H
#define __SOC_ROM_H

#include "rom_api.h"

#if (!defined(SREV_A0))
static inline void dummy_set_ready(void)
{
}

#define ROM_START 0x10000000
static const struct rom_api_wrapper rapi =
{
    .rom             = (struct rom_api *)(ROM_START + 0x500),
    .set_ready       = (set_ready_fn) dummy_set_ready,
};
#else
static const struct rom_api rom =
{
    .download_image  = (download_image_fn)  0x10011cb5,
    .query_boot_info = (query_boot_info_fn) 0x10011fd1,
};

static const struct rom_api_wrapper rapi =
{
    .rom             = &rom,
    .set_ready       = (set_ready_fn)       0x10012097,
};
#endif
#endif
