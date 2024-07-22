/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2024 NXP
 */

#ifndef DDR_RETENTION_H
#define DDR_RETENTION_H

struct ddrc
{
    uint32_t reg;
    uint32_t val;
};

struct ddrphy
{
    uint32_t reg;
    uint16_t val;
};

struct ddrc_pstate
{
    struct ddrc *cfg;
    uint32_t cfg_num;
};

struct ddr_info
{
    /* ddrc config */
    struct ddrc *ddrc_cfg;
    uint32_t ddrc_cfg_num;
    /* ddrc pstate config */
    struct ddrc_pstate *pstate;
    uint32_t pstate_num;
    /* ddr phy trained CSR */
    struct ddrphy *trained_csr;
    uint32_t ddrphy_trained_csr_num;
    /* pstate freq table */
    uint32_t pstate_freq[4];
    uint32_t ZQCalCodePU;
    uint32_t ZQCalCodePD;
};

#endif
