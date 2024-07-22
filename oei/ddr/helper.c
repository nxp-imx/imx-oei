// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright 2018, 2023-2024 NXP
 */
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include "ddr.h"
#include "ddr_retention.h"
#include "edma.h"
#include "oei.h"
#include "soc_edma.h"

extern char s_code_end[];

/**
 * Point the config ID to the position where the current register
 * (reg) is less or equal to the config register (cfg[id].reg)
 * The assumption is that the registers in "fsp_phy_msgh_cfg" are
 * in ascending order
 *
 * @fsp_msg: ddr fsp traing info
 * @reg: IMEM/DMEM offset address
 * @cfg_id: config index
 * @val: ddrphy config parameter
 */
static void Check_Cfg_Id(struct dram_fsp_msg *fsp_msg, uint32_t reg, uint32_t *cfg_id, uint16_t *val)
{
    struct ddrphy_cfg_param *cfg = fsp_msg->fsp_phy_msgh_cfg;
    uint32_t cfg_num = fsp_msg->fsp_phy_msgh_cfg_num;
    uint32_t id = (*cfg_id);

    while (id < cfg_num && ((cfg[id].reg & 0xff000) != DMEM_OFFSET_ADDR || reg > cfg[id].reg))
    {
        id++;
    }

    *val = (id == cfg_num || reg < cfg[id].reg ? 0 : cfg[id].val);
    *cfg_id = id;
}

/**
 * Get FW header offset as function of DDR FW type
 *
 * @fw_type: DDR FW type, either DDRFW_TRAINING or DDRFW_QUICKBOOT
 * @return:  FW header offset
 */
static struct ddr_fw_header *Ddr_Get_Fw_Hdr(enum ddrfw_type fw_type)
{
    struct ddr_fw_header *header = (struct ddr_fw_header *)((void *)&s_code_end);
    uint32_t header_size = sizeof(struct ddr_fw_header);
    uint32_t fw;

    switch (fw_type)
    {
    case DDRFW_QUICKBOOT:
        fw     = (uint32_t)(header) + header_size + header->imem_size + header->dmem_size;
        header = (struct ddr_fw_header *)(fw);
        break;
    case DDRFW_TRAINING:
    default:
        break;
    }

    return header;
}

/**
 * Wrapper function for waiting edma transfers
 *
 * @type: memory type IMEM/DMEM
 */
static void Wait_Edma_Transfer(enum mem_type type)
{
    uint8_t edma_ch = (type == DMEM) ? EDMA_CH1 : EDMA_CH0;

    edma_ops.wait_transfer(EDMA2_BASE_ADDR, edma_ch);
}

/**
 * Wrapper function for starting edma transfer
 *
 * @type: memory type IMEM/DMEM
 */
static void Start_Edma_Transfer(enum mem_type type)
{
    /* Use CH0 for IMEM and CH1 for DMEM loads. */
    uint8_t edma_ch = (type == DMEM) ? EDMA_CH1 : EDMA_CH0;

    edma_ops.start_transfer(EDMA2_BASE_ADDR, edma_ch);
    edma_ops.check_edma(EDMA2_BASE_ADDR, edma_ch);
}

/**
 * Configure EDMA channels for loading IMEM and DMEM.
 *
 * @fsp_msg: ddr fsp traing info
 * @type: memory type IMEM/DMEM
 */
static void Edma_Ddr_Load_Train_Firmware(struct dram_fsp_msg *fsp_msg, enum mem_type type, enum ddrfw_type fw_type)
{
    int ret;
    uint32_t fw_num, edma_ch;
    unsigned long fw, pr_to32;
    struct ddr_fw_header *header = Ddr_Get_Fw_Hdr(fw_type);
    uint32_t header_size = sizeof(struct ddr_fw_header);
    bool training = (fw_type == DDRFW_TRAINING);
    uint16_t val;
    uint32_t i, cfg_id;

    switch (type) {
    case IMEM:
        fw      = (unsigned long)header + header_size;
        fw_num  = header->imem_size;
        pr_to32 = IMEM_OFFSET_ADDR;
        edma_ch = EDMA_CH0;
        break;
    case DMEM:
        fw      = (unsigned long)header + header_size + header->imem_size;
        fw_num  = header->dmem_size;
        pr_to32 = DMEM_OFFSET_ADDR;
        edma_ch = EDMA_CH1;
        break;
    default:
        /* No error given function signature */
        return;
    }

    i = 0;
    if (training && type == DMEM && fsp_msg != NULL && fsp_msg->fsp_phy_msgh_cfg != NULL)
    {
        cfg_id = 0;
        for ( ; i < DDRPHY_QB_MSB_SIZE; i++, pr_to32++)
        {
            Check_Cfg_Id(fsp_msg, pr_to32, &cfg_id, &val);
            Write16(DDR_PHY_BASE + Ddrphy_AddrRemap(pr_to32), val);
            fw += sizeof(val);
        }
    }

    fw_num = fw_num - (i * sizeof(uint16_t));
    edma_ops.en_master_rep(EDMA2_BASE_ADDR, edma_ch);
    edma_ops.set_tbytes(EDMA2_BASE_ADDR, edma_ch, 2, 2);
    ret = edma_ops.configure(EDMA2_BASE_ADDR, edma_ch, fw, 2,
            DDR_PHY_BASE + Ddrphy_AddrRemap(pr_to32), 4, fw_num, 1);
    if (ret != 0)
    {
        edma_ops.clr_tcd(EDMA2_BASE_ADDR, edma_ch);
    }
}

/**
 * Load QuickBoot DMEM memory blocks.
 *
 * @msg_blks: message blocks
 * @qb_state: quick boot state data
 */
static void Edma_Ddr_Load_DMEM(uint16_t *msg_blk, ddrphy_qb_state *qb_state)
{
    int ret;
    struct ddr_fw_header *header = Ddr_Get_Fw_Hdr(DDRFW_QUICKBOOT);
    uint32_t header_size = sizeof(struct ddr_fw_header);
    unsigned long fw, pr_to32;
    uint32_t fw_num, msg_blk_size, csr_size;

    fw      = (unsigned long)(header) + header_size + header->imem_size;
    fw_num  = header->dmem_size;
    pr_to32 = DMEM_OFFSET_ADDR;
    msg_blk_size = (DDRPHY_QB_MSB_SIZE * sizeof(uint16_t));
    csr_size = (DDRPHY_QB_CSR_SIZE * sizeof(uint16_t));
    fw += msg_blk_size + csr_size;
    fw_num = fw_num - (msg_blk_size + csr_size);

    edma_ops.en_master_rep(EDMA2_BASE_ADDR, EDMA_CH1);
    edma_ops.set_tbytes(EDMA2_BASE_ADDR, EDMA_CH1 , 2, 2);

    /* load msg blocks */
    ret = edma_ops.configure(EDMA2_BASE_ADDR, EDMA_CH1, (unsigned int) msg_blk, 2,
        DDR_PHY_BASE + Ddrphy_AddrRemap(pr_to32), 4, msg_blk_size, 1);
    if (ret != 0)  { goto exit; }

    edma_ops.start_transfer(EDMA2_BASE_ADDR, EDMA_CH1);
    edma_ops.check_edma(EDMA2_BASE_ADDR, EDMA_CH1);

    edma_ops.wait_transfer(EDMA2_BASE_ADDR, EDMA_CH1);
    pr_to32 += DDRPHY_QB_MSB_SIZE;

    /* save CSRs to address starting */
    ret = edma_ops.configure(EDMA2_BASE_ADDR, EDMA_CH1, (unsigned int)&(qb_state->csr[0]),
        2, DDR_PHY_BASE + Ddrphy_AddrRemap(pr_to32), 4, csr_size, 1);

    if (ret != 0) { goto exit; }

    edma_ops.start_transfer(EDMA2_BASE_ADDR, EDMA_CH1);
    edma_ops.check_edma(EDMA2_BASE_ADDR, EDMA_CH1);
    edma_ops.wait_transfer(EDMA2_BASE_ADDR, EDMA_CH1);
    pr_to32 += DDRPHY_QB_CSR_SIZE;

    /* transfer the remaining DMEM memory blocks */
    ret = edma_ops.configure(EDMA2_BASE_ADDR, EDMA_CH1, fw, 2,
                     DDR_PHY_BASE + Ddrphy_AddrRemap(pr_to32), 4,
                 fw_num, 1);
    if (ret != 0) { goto exit; }

    Start_Edma_Transfer(DMEM);
    return;

exit:
    edma_ops.clr_tcd(EDMA2_BASE_ADDR, EDMA_CH1);
}

/*
 * Execute ACSM SRAM restore using edma
 * qb_state - quick boot data
 */
static void Edma_Acsm_Sram_Restore(ddrphy_qb_state *qb_state)
{
    int ret;

    edma_ops.set_tbytes(EDMA2_BASE_ADDR, EDMA_CH0 , 2, 2);
    ret = edma_ops.configure(EDMA2_BASE_ADDR, EDMA_CH0, (unsigned int)&(qb_state->acsm[0]) , 2,
              DDR_PHY_BASE + Ddrphy_AddrRemap(ACSM_SRAM_BASE_ADDR), 4, DDRPHY_QB_ACSM_SIZE, 1);
    if (ret != 0)
    {
        printf("Failed to set edma - error %d\n", ret);
        edma_ops.clr_tcd(EDMA2_BASE_ADDR, EDMA_CH0);
    }
    edma_ops.start_transfer(EDMA2_BASE_ADDR, EDMA_CH0);
    edma_ops.check_edma(EDMA2_BASE_ADDR, EDMA_CH0);
    edma_ops.wait_transfer(EDMA2_BASE_ADDR, EDMA_CH0);
}

extern char __RetentionStart[], __RetentionEnd[];

void Ddr_Cfg_Save(struct dram_timing_info *dtiming)
{
    struct ddr_info* ddr = (struct ddr_info*)((void *)__RetentionStart);
    unsigned int i, j;

    /* zero init the 64K buffer to avoid ECC errors */
    memset(ddr, 0, (uint32_t)(__RetentionEnd) - (uint32_t)(__RetentionStart));

    /* ddrc config next after the ddr_into struct */
    ddr->ddrc_cfg = (struct ddrc*)((unsigned int)ddr + sizeof(struct ddr_info));
    /* number of ddr registers */
    ddr->ddrc_cfg_num = dtiming->ddrc_cfg_num;

    /* save register address and value */
    for (i = 0; i < ddr->ddrc_cfg_num; i++)
    {
        ddr->ddrc_cfg[i].reg = dtiming->ddrc_cfg[i].reg;
        ddr->ddrc_cfg[i].val = dtiming->ddrc_cfg[i].val;
    }

    /* number of pstates */
    ddr->pstate_num = dtiming->fsp_cfg_num;
    /* pstate struct is after ddrc_cfg */
    ddr->pstate = (struct ddrc_pstate*)((unsigned int)ddr->ddrc_cfg + (ddr->ddrc_cfg_num * sizeof(struct ddrc)));

    for (j = 0; j < ddr->pstate_num; j++)
    {
        /* number of pstate specific ddrc registers */
        ddr->pstate[j].cfg_num = dtiming->fsp_cfg[j].ddrc_cfg_num;
        if (j > 0)
        {
            /* skip previous pstate structure */
            ddr->pstate[j].cfg = (struct ddrc*)((unsigned int)ddr->pstate[j-1].cfg + (ddr->pstate[j-1].cfg_num *sizeof(struct ddrc)));
        }
        else
        {
            /* first pstate cfg, skip no. of ddr_pstate structs */
            ddr->pstate[j].cfg = (struct ddrc*)((unsigned int)ddr->pstate + (sizeof(struct ddrc_pstate) * ddr->pstate_num));
        }

        /* save pstate specific register address and value */
        for (i = 0; i < ddr->pstate[j].cfg_num; i++)
        {
            ddr->pstate[j].cfg[i].reg = dtiming->fsp_cfg[j].ddrc_cfg[i].reg;
            ddr->pstate[j].cfg[i].val = dtiming->fsp_cfg[j].ddrc_cfg[i].val;
        }
    }

    /* save number of trained phy config registers */
    ddr->ddrphy_trained_csr_num = dtiming->ddrphy_trained_csr_num;
    /* skip last pstate struct */
    ddr->trained_csr = (struct ddrphy *)((unsigned int)ddr->pstate[ddr->pstate_num-1].cfg + (ddr->pstate[ddr->pstate_num-1].cfg_num * sizeof(struct ddrc)));

    /* save ddrphy trained csr registers only, value will be saved after phy training completes */
    for (i = 0; i < ddr->ddrphy_trained_csr_num; i++)
    {
        ddr->trained_csr[i].reg = dtiming->ddrphy_trained_csr[i].reg;
    }

    /* save pstate frequencies */
    for (i = 0; i < ddr->pstate_num; i++)
    {
        ddr->pstate_freq[i] = dtiming->fsp_table[i];
    }
}

void Ddr_Phy_Trained_Csr_Save(void)
{
    unsigned int i = 0;
    struct ddr_info* ddr = (struct ddr_info*)((void *)__RetentionStart);

    /* enable the ddrphy apb */
    Dwc_Ddrphy_Apb_Wr(0xd0000, 0x0);
    Dwc_Ddrphy_Apb_Wr(0xc0080, 0x3);

    /* save ddrphy trained csr value */
    for (i = 0; i < ddr->ddrphy_trained_csr_num; i++)
    {
                ddr->trained_csr[i].val = Dwc_Ddrphy_Apb_Rd(ddr->trained_csr[i].reg);
    }

    /* save ZQ calibration codes */
    ddr->ZQCalCodePU = Dwc_Ddrphy_Apb_Rd(0x20326);
    ddr->ZQCalCodePD = Dwc_Ddrphy_Apb_Rd(0x20327);

    /* disable the ddrphy apb */
    Dwc_Ddrphy_Apb_Wr(0xc0080, 0x2);
    Dwc_Ddrphy_Apb_Wr(0xd0000, 0x1);
}

struct ddr_phy_ops phy_ops = {
    .ddr_pre_load_firmware = Edma_Ddr_Load_Train_Firmware,
    .ddr_do_load_firmware = Start_Edma_Transfer,
    .ddr_post_load_firmware = Wait_Edma_Transfer,
    .ddr_load_DMEM = Edma_Ddr_Load_DMEM,
    .acsm_sram_restore = Edma_Acsm_Sram_Restore,
};
