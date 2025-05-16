// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright 2024 NXP
 */
#if defined(CONFIG_ELE)
#include "fsl_ele.h"
#else
#include "crc.h"
#endif
#include "soc_ddr.h"
#include "soc_rom.h"

static uint32_t get_dev_offset(uint32_t *offset)
{
    struct container_hdr *phdr = (struct container_hdr *)QB_STATE_LOAD_ADDR;
    struct boot_img_t *img_entry;
    uint32_t ctn_off, img_end, readsize;
    uint8_t i, num_images;
    int ret;

    ret = Rom_Api_Query_Boot_Info(QUERY_IMG_OFF, &ctn_off);
    if (ret != ROM_API_OKAY) { return ret; }

    /** third container offset */
    ctn_off += 2U * CONTAINER_HDR_ALIGNMENT;
    readsize = Rom_Api_Read(ctn_off, CONTAINER_HDR_ALIGNMENT, phdr);
    if (readsize != CONTAINER_HDR_ALIGNMENT)
    {
        return ROM_API_ERR_INV_PAR;
    }

    if (phdr->tag != 0x87U || phdr->version != 0x00U)
    {
        return ROM_API_ERR_INV_PAR;
    }

    num_images = phdr->num_images;
    img_entry = (struct boot_img_t *)(++phdr);

    for (i = 0U; i < num_images; i++)
    {
        img_end = img_entry->offset + img_entry->size;
        if (i + 1U < num_images)
        {
            img_entry++;
            if (img_end + QB_STATE_STORAGE_SIZE == img_entry->offset)
            {
                /** hole detected */
                (*offset) = ctn_off + img_end;
                return ROM_API_OKAY;
            }
        }
    }

    return ROM_API_ERR_INV_PAR;
}

uint32_t Get_Training_Data_Offset(uint32_t *offset)
{
    uint32_t boot;
    enum boot_dev_type boot_type;
    uint32_t ret = ROM_API_OKAY;

    Rom_Api_Set_Ready();
    ret |= Rom_Api_Query_Boot_Info(QUERY_BT_DEV, &boot);
    if (ret != ROM_API_OKAY) { return ret; }

    boot_type = boot >> 16U;
    switch (boot_type)
    {
        case BT_DEV_TYPE_MMC:
            if (boot & 1U)
            {
                (*offset) = 0U;
                break;
            }
            [[fallthrough]];
        case BT_DEV_TYPE_SD:
        case BT_DEV_TYPE_FLEXSPINOR:
            ret = get_dev_offset(offset);
            break;
        case BT_DEV_TYPE_NAND:
        case BT_DEV_TYPE_SPI_NOR:
        case BT_DEV_TYPE_FLEXSPINAND:
        case BT_DEV_TYPE_USB:
        default:
            (*offset) = 0U;
            break;
    }

    return ret;
}

void Ddr_Post_Init(void)
{
    /**
     * RT_PULSE_EN = 1 requires AR_RT_URGENT_EN be set in DDRC_URGENT_EN
     * so real time masters will be able to send urgent signal to ar_rt_urgent.
     */
    BLK_CTRL_DDRMIX->DDRC_URGENT_EN |=
        BLK_CTRL_DDRMIX_DDRC_URGENT_EN_AR_RT_URGENT_EN(1);
}

#if defined(CONFIG_ELE)
bool Ddr_Training_Data_Sign(void)
{
    ddrphy_qb_state *qb_state;
    uint32_t size;
    int ret;

    qb_state = (ddrphy_qb_state *)(QB_STATE_SAVE_ADDR);
    size = sizeof(ddrphy_qb_state) - MAC_LENGTH * sizeof(uint32_t);

    ret = ELE_SignData(&qb_state->TrainedVREFCA_A0, size, &qb_state->mac, 0U);

    return (ret == ELE_SUCCESS_IND);
}

bool Ddr_Training_Data_Check(void)
{
    ddrphy_qb_state *qb_state;
    uint32_t i, sum, size;
    int ret;

    qb_state = (ddrphy_qb_state *)(QB_STATE_LOAD_ADDR);
    size = sizeof(ddrphy_qb_state) - MAC_LENGTH * sizeof(uint32_t);

    /**
     * Check if signature is empty
     */
    for (sum = 0, i = 0; i < MAC_LENGTH; i++)
    {
        sum |= qb_state->mac[i];
    }

    /**
     * For empty signature there is no need to send ELE request to check it
     */
    if (sum == 0)
    {
        return false;
    }

    ret = ELE_VerifyData(&qb_state->TrainedVREFCA_A0, size, &qb_state->mac, 0U);

    return (ret == ELE_SUCCESS_IND);
}

bool Ddr_Training_Data_Release(uint32_t img_id)
{
    int ret;

    ret = ELE_ReleaseImageRam(img_id, 0U);

    return (ret == ELE_SUCCESS_IND);
}

void Ddr_Training_Data_Invalidate(void)
{
    ddrphy_qb_state *qb_state;

    qb_state = (ddrphy_qb_state *)(QB_STATE_SAVE_ADDR);
    qb_state->mac[0U] = 0U;
}
#else
bool Ddr_Training_Data_Sign(void)
{
       ddrphy_qb_state *qb_state;
       uint32_t size;

       qb_state = (ddrphy_qb_state *)(QB_STATE_SAVE_ADDR);
       size = sizeof(ddrphy_qb_state) - MAC_LENGTH * sizeof(uint32_t);
       qb_state->mac[0] = CRC_Crc32(&qb_state->TrainedVREFCA_A0, size);

       return true;
}

bool Ddr_Training_Data_Check(void)
{
    ddrphy_qb_state *qb_state;
    uint32_t size, crc;

    qb_state = (ddrphy_qb_state *)(QB_STATE_LOAD_ADDR);

    size = sizeof(ddrphy_qb_state) - MAC_LENGTH * sizeof(uint32_t);
    crc = CRC_Crc32(&qb_state->TrainedVREFCA_A0, size);

    return (crc == qb_state->mac[0]);
}

bool Ddr_Training_Data_Release(uint32_t img_id)
{
    return true;
}

void Ddr_Training_Data_Invalidate(void)
{
    ddrphy_qb_state *qb_state;

    qb_state = (ddrphy_qb_state *)(QB_STATE_SAVE_ADDR);
    qb_state->mac[0] = 0U;
}
#endif
