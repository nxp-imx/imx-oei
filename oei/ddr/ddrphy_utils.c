// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright 2018, 2023-2024 NXP
 */

#include <stdio.h>
#include <stdbool.h>

#include "oei.h"
#include "clock.h"
#include "ddr.h"

static inline void Poll_Pmu_Message_Ready(void)
{
    unsigned int reg;

    do
    {
        reg = Dwc_Ddrphy_Apb_Rd(0xd0004);
    } while (reg & 0x1);
}

static inline void Ack_Pmu_Message_Receive(void)
{
    unsigned int reg;

    Dwc_Ddrphy_Apb_Wr(0xd0031, 0x0);

    do
    {
        reg = Dwc_Ddrphy_Apb_Rd(0xd0004);
    } while (!(reg & 0x1));

    Dwc_Ddrphy_Apb_Wr(0xd0031, 0x1);
}

static inline unsigned int Get_Mail(void)
{
    unsigned int reg;

    Poll_Pmu_Message_Ready();

    reg = Dwc_Ddrphy_Apb_Rd(0xd0032);

    Ack_Pmu_Message_Receive();

    return reg;
}

static inline unsigned int Get_Stream_Message(void)
{
    unsigned int reg, reg2;

    Poll_Pmu_Message_Ready();

    reg = Dwc_Ddrphy_Apb_Rd(0xd0032);

    reg2 = Dwc_Ddrphy_Apb_Rd(0xd0034);

    reg2 = (reg2 << 16) | reg;

    Ack_Pmu_Message_Receive();

    return reg2;
}

static inline void Decode_Streaming_Message(void)
{
    unsigned int string_index;
    uint32_t i = 0;

    string_index = Get_Stream_Message();
    while (i < (string_index & 0xffff))
    {
        Get_Stream_Message();
        i++;
    }
}

int Wait_Ddr_Phy_Training_Complete(void)
{
    unsigned int mail;

    while (true)
    {
        mail = Get_Mail();
        switch (mail)
        {
        case 0x08:
            Decode_Streaming_Message();
            break;
        case 0x07:
            /** Training PASS */
            return 0;
        case 0xff:
            /** Training FAILED */
            return -1;
        default:
            break;
        }
    }
}

void Ddr_Phy_Init_Set_Dfi_Clk(unsigned int drate)
{
    switch (drate)
    {
    case 6400:
        Dram_PLL_Init(MHZ(800));
        Dram_Disable_Bypass();
        break;
    case 4800:
        Dram_PLL_Init(MHZ(600));
        Dram_Disable_Bypass();
        break;
    case 4266: /* Assume 4266 */
        Dram_PLL_Init(533250000);
        Dram_Disable_Bypass();
        break;
    case 4000:
        Dram_PLL_Init(MHZ(500));
        Dram_Disable_Bypass();
        break;
    case 3733: /* Assume 3733 */
        Dram_PLL_Init(466625000);
        Dram_Disable_Bypass();
        break;
    case 3200:
        Dram_PLL_Init(400000000);
        Dram_Disable_Bypass();
        break;
    case 1866: /* Assume 1866 */
        Dram_PLL_Init(233250000);
        Dram_Disable_Bypass();
        break;
    case 1600:
        Dram_PLL_Init(200000000);
        Dram_Disable_Bypass();
        break;
    default:
        printf("Clk rate not found\n");
        return;
    }
}

void Ddr_Phy_Cfg_Set(struct ddrphy_cfg_param *cfg, unsigned int num)
{
    unsigned int i;

    for (i = 0; i < num; i++, cfg++)
    {
        Dwc_Ddrphy_Apb_Wr(cfg->reg, cfg->val);
    }
}

__attribute__ ((weak)) void Ddr_Phy_Init_Read_Msg_Block(void)
{
}
