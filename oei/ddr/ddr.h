/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2022-2024 NXP
 */

#ifndef __DDR_H
#define __DDR_H
#include <stdbool.h>
#include <stdint.h>

#include "fsl_device_registers.h"

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#define IP2APB_DDRPHY_IPS_BASE_ADDR(X) (DDR_PHY_BASE + (X * 0x2000000))
#define DDRPHY_MEM(X)                  (DDR_PHY_BASE + (X * 0x2000000) + 0x50000)

#define IMEM_LEN 0x10000 /* 65536 bytes */
#define DMEM_LEN 0x10000 /* 65536 bytes */

#define IMEM_OFFSET_ADDR 0x00050000
#define DMEM_OFFSET_ADDR 0x00058000

/* DDRC DDR_SDRAM_CFG[SDRAM_TYPE] */
enum sdram_type
{
    SDRAM_LPDDR5  = 1, /* 001b - LPDDR5 SDRAM */
    SDRAM_LPDDR4x = 4, /* 100b - LPDDR4x SDRAM */
};

struct ddr_fw_header
{
    uint32_t imem_size;
    uint32_t dmem_size;
};

/* PHY State */
enum pstate
{
    PS0,
    PS1,
    PS2,
    PS3,
};

enum msg_response
{
    TRAIN_SUCCESS = 0x7,
    TRAIN_STREAM_START = 0x8,
    TRAIN_FAIL = 0xff,
};

/* user data type */
enum fw_type
{
    FW_1D_IMAGE,
    FW_2D_IMAGE,
};

enum mem_type
{
    DMEM,
    IMEM,
};

struct ddrc_cfg_param
{
    unsigned int reg;
    unsigned int val;
};

struct __attribute__((__packed__)) ddrphy_cfg_param
{
    unsigned int   reg;
    unsigned short val;
};

struct dram_fsp_cfg
{
    struct ddrc_cfg_param *ddrc_cfg;
    unsigned int ddrc_cfg_num;
    struct ddrc_cfg_param *mr_cfg;
    unsigned int mr_cfg_num;
    unsigned int bypass;
};

struct dram_fsp_msg
{
    unsigned int drate;
    enum fw_type fw_type;
    /* pstate ddrphy config */
    struct ddrphy_cfg_param *fsp_phy_cfg;
    unsigned int fsp_phy_cfg_num;
    /* pstate message block(header) */
    struct ddrphy_cfg_param *fsp_phy_msgh_cfg;
    unsigned int fsp_phy_msgh_cfg_num;
    /* pstate PIE */
    struct ddrphy_cfg_param *fsp_phy_pie_cfg;
    unsigned int fsp_phy_pie_cfg_num;

    /* for simulation */
    struct ddrphy_cfg_param *fsp_phy_prog_csr_ps_cfg;
    unsigned int fsp_phy_prog_csr_ps_cfg_num;
};

struct dram_timing_info
{
    /* ddrc config */
    struct ddrc_cfg_param *ddrc_cfg;
    unsigned int ddrc_cfg_num;
    /* ddrc pstate config */
    struct dram_fsp_cfg *fsp_cfg;
    unsigned int fsp_cfg_num;
    /* ddrphy config */
    struct ddrphy_cfg_param *ddrphy_cfg;
    unsigned int ddrphy_cfg_num;
    /* ddr fsp train info */
    struct dram_fsp_msg *fsp_msg;
    unsigned int fsp_msg_num;
    /* ddr phy trained CSR */
    struct ddrphy_cfg_param *ddrphy_trained_csr;
    unsigned int ddrphy_trained_csr_num;
    /* ddr phy common PIE */
    struct ddrphy_cfg_param *ddrphy_pie;
    unsigned int ddrphy_pie_num;
    /* initialized drate table */
    unsigned int fsp_table[4];

    /* for emulation */
    unsigned int skip_fw;
    unsigned int prog_csr;
    struct ddrphy_cfg_param *ddrphy_prog_csr;
    unsigned int ddrphy_prog_csr_num;
};

extern struct dram_timing_info dram_timing;

enum sdram_type Ddrc_Get_Sdram_Type(void);
int Ddrc_Init(struct dram_timing_info *timing_info, uint32_t img_id);
int Ddr_Cfg_Phy(struct dram_timing_info *timing_info);

/* utils function for ddr phy training */
int Wait_Ddr_Phy_Training_Complete(void);
void Ddr_Phy_Init_Set_Dfi_Clk(unsigned int drate);
void Ddr_Phy_Init_Read_Msg_Block(void);
void Ddr_Phy_Cfg_Set(struct ddrphy_cfg_param *cfg, unsigned int num);
void Ddr_Cfg_Save(struct dram_timing_info *dtiming);
void Ddr_Phy_Trained_Csr_Save(void);

#define Ddrphy_AddrRemap(paddr_apb_from_ctlr)    (paddr_apb_from_ctlr << 2)

#define Dwc_Ddrphy_Apb_Wr(addr, data) \
    (*(uint32_t volatile *)(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + Ddrphy_AddrRemap(addr)) = (data))

#define Dwc_Ddrphy_Apb_Rd(addr) \
    *(uint32_t volatile *)(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + Ddrphy_AddrRemap(addr))

/* Quick Boot related */
#define DDRPHY_QB_CSR_ARRAY_SIZE    5168
#define DDRPHY_QB_ACSM_ARRAY_SIZE    4 * 1024
#define DDRPHY_QB_MSB_SIZE    0x200

/**
 * No PSTATE SRAM is saved by default, one Pstate defined.
 * PSTATE SRAM to be saved if 3 and more Pstates are defined.
 */
#if (defined(DDRPHY_PSTATES) && DDRPHY_PSTATES >= 3)
#define DDRPHY_QB_PSTATES    DDRPHY_PSTATES
#else
#define DDRPHY_QB_PSTATES    0
#endif
#define DDRPHY_QB_PST_ARRAY_SIZE    DDRPHY_QB_PSTATES * 4 * 1024

#define ACSM_SRAM_BASE_ADDR    0x41000
#define PSTATE_SRAM_BASE_ADDR    0xA0000

enum ddrfw_type
{
    DDRFW_TRAINING,
    DDRFW_QUICKBOOT,
};

typedef struct
{
#define MAC_LENGTH             8 /** 256 bits, 32-bit aligned */
    uint32_t mac[MAC_LENGTH];    /** For 95A0/1 keep CRC32 value in mac[0] */
    uint8_t TrainedVREFCA_A0;
    uint8_t TrainedVREFCA_A1;
    uint8_t TrainedVREFCA_B0;
    uint8_t TrainedVREFCA_B1;
    uint8_t TrainedVREFDQ_A0;
    uint8_t TrainedVREFDQ_A1;
    uint8_t TrainedVREFDQ_B0;
    uint8_t TrainedVREFDQ_B1;
    uint8_t TrainedVREFDQU_A0;
    uint8_t TrainedVREFDQU_A1;
    uint8_t TrainedVREFDQU_B0;
    uint8_t TrainedVREFDQU_B1;
    uint8_t TrainedDRAMDFE_A0;
    uint8_t TrainedDRAMDFE_A1;
    uint8_t TrainedDRAMDFE_B0;
    uint8_t TrainedDRAMDFE_B1;
    uint8_t TrainedDRAMDCA_A0;
    uint8_t TrainedDRAMDCA_A1;
    uint8_t TrainedDRAMDCA_B0;
    uint8_t TrainedDRAMDCA_B1;
    uint16_t QBPllUPllProg0;
    uint16_t QBPllUPllProg1;
    uint16_t QBPllUPllProg2;
    uint16_t QBPllUPllProg3;
    uint16_t QBPllCtrl1;
    uint16_t QBPllCtrl4;
    uint16_t QBPllCtrl5;
    uint16_t csr[DDRPHY_QB_CSR_ARRAY_SIZE];
    uint16_t acsm[DDRPHY_QB_ACSM_ARRAY_SIZE];
    uint16_t pst[DDRPHY_QB_PST_ARRAY_SIZE];
} ddrphy_qb_state;

/**
 * struct ddr_phy_ops  - ddr phy operations to load ddr phy firmware.
 *
 * @ddr_pre_load_firmware: Configure eDMA registers in case eDMA is used
 *                         or loads data with the execution core for no edma case.
 * @ddr_do_load_firmware: Used to start the transfer when eDMA is used or do nothing (dummy function)
 *                        when not using edma.
 * @ddr_post_load_firmware: Used to wait the eDMA transfer or do nothing (dummy function) when not
 *                          using edma.
 * @ddr_load_DMEM: Loads DMEM for Quick Boot mode selection.
 * @acsm_sram_restore: Restore SRAM data for Quick boot mode selection.
 */
struct ddr_phy_ops
{
    void (*ddr_pre_load_firmware)(struct dram_fsp_msg *fsp_msg, enum mem_type type, enum ddrfw_type fw);
    void (*ddr_do_load_firmware)(enum mem_type type);
    void (*ddr_post_load_firmware)(enum mem_type type);
    void (*ddr_load_DMEM)(uint16_t *msg_blk, ddrphy_qb_state *qb_state);
    void (*acsm_sram_restore)(ddrphy_qb_state *qb_state);
};

extern struct ddr_phy_ops phy_ops;

int Ddr_Cfg_Phy_Qb(struct dram_timing_info *timing_info, int fsp_id);
void Ddr_Phy_Qb_Save(void);

/**
 * Get training data location within the boot container.
 * Location will be stored at the address specified by "offset" parameter.
 *
 * @param offset  pointer to the address the location to be stored
 * @return      ROM_API_OKAY=0xF0 if call succeeded,
 *          any other value if call fails
 */
uint32_t Get_Training_Data_Offset(uint32_t *offset);

/**
 * Sign the training data
 *
 * @return    true if training data sign succeeded, false otherwise
 */
bool Ddr_Training_Data_Sign(void);

/**
 * Checks if loaded training data is valid and can be used
 * for quick boot flow.
 *
 * @return    true if training data is valid, false otherwise
 */
bool Ddr_Training_Data_Check(void);

/**
 * Training data sing/verify mechanism may lock in read-only
 * mode the memory used to load training data. This function
 * releases the memory in read-write mode.
 *
 * @return	true if training data is valid, false otherwise
 */
bool Ddr_Training_Data_Release(uint32_t img_id);

/**
 * Invalidate valid training data once quick boot flow completed
 */
void Ddr_Training_Data_Invalidate(void);

#endif
