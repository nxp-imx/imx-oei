// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2018, 2023 NXP
 */

#include "ddr.h"
#include "asm/arch/clock.h"

static inline void poll_pmu_message_ready(void)
{
	unsigned int reg;

	do {
		reg = dwc_ddrphy_apb_rd(0xd0004);
	} while (reg & 0x1);
}

static inline void ack_pmu_message_receive(void)
{
	unsigned int reg;

	dwc_ddrphy_apb_wr(0xd0031, 0x0);

	do {
		reg = dwc_ddrphy_apb_rd(0xd0004);
	} while (!(reg & 0x1));

	dwc_ddrphy_apb_wr(0xd0031, 0x1);
}

static inline unsigned int get_mail(void)
{
	unsigned int reg;

	poll_pmu_message_ready();

	reg = dwc_ddrphy_apb_rd(0xd0032);

	ack_pmu_message_receive();

	return reg;
}

static inline unsigned int get_stream_message(void)
{
	unsigned int reg, reg2;

	poll_pmu_message_ready();

	reg = dwc_ddrphy_apb_rd(0xd0032);

	reg2 = dwc_ddrphy_apb_rd(0xd0034);

	reg2 = (reg2 << 16) | reg;

	ack_pmu_message_receive();

	return reg2;
}

static inline void decode_streaming_message(void)
{
	unsigned int string_index;
	u32 i = 0;

	string_index = get_stream_message();
	while (i < (string_index & 0xffff)) {
		get_stream_message();
		i++;
	}
}

int wait_ddrphy_training_complete(void)
{
	unsigned int mail;

	while (1) {
		mail = get_mail();
		switch (mail) {
		case 0x08:
			decode_streaming_message();
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

void ddrphy_init_set_dfi_clk(unsigned int drate)
{
	switch (drate) {
	case 6400:
		dram_pll_init(MHZ(800));
		dram_disable_bypass();
		break;
	case 4800:
		dram_pll_init(MHZ(600));
		dram_disable_bypass();
		break;
	case 4266: /* Assume 4266.(6) */
		dram_pll_init(533333333);
		dram_disable_bypass();
		break;
	case 3733: /* Assume 3733.(3) */
		dram_pll_init(466666666);
		dram_disable_bypass();
		break;
	case 3200:
		dram_pll_init(MHZ(400));
		dram_disable_bypass();
		break;
	case 2133: /* Assume 2133.(3) */
		dram_pll_init(266666666);
		dram_disable_bypass();
		break;
	case 2400:
		dram_pll_init(MHZ(300));
		dram_disable_bypass();
		break;
	case 1866:
		dram_pll_init(MHZ(233));
		dram_disable_bypass();
		break;
	case 1600:
		dram_pll_init(MHZ(200));
		dram_disable_bypass();
		break;
	case 1200:
		dram_pll_init(MHZ(150));
		dram_disable_bypass();
		break;
	case 1066:
		dram_pll_init(MHZ(133));
		dram_disable_bypass();
		break;
	case 933:
		dram_pll_init(MHZ(116));
		dram_disable_bypass();
		break;
	case 800:
		dram_pll_init(MHZ(100));
		dram_disable_bypass();
		break;
	case 667:
		dram_pll_init(MHZ(83));
		dram_disable_bypass();
		break;
	case 625:
		dram_enable_bypass(MHZ(625));
		break;
	case 400:
		dram_enable_bypass(MHZ(400));
		break;
	case 333:
		dram_enable_bypass(MHZ(333));
		break;
	case 200:
		dram_enable_bypass(MHZ(200));
		break;
	case 100:
		dram_enable_bypass(MHZ(100));
		break;
	default:
		return;
	}
}

void ddrphy_cfg_set(struct ddrphy_cfg_param *cfg, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++, cfg++)
		dwc_ddrphy_apb_wr(cfg->reg, cfg->val);
}

__attribute__ ((weak)) void ddrphy_init_read_msg_block(void)
{
}
