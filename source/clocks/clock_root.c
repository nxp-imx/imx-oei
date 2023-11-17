// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2022 NXP
 */
#include <asm/arch/soc_memory_map.h>
#include <asm/arch/clock.h>
#include <asm/arch/ccm_regs.h>
#include <asm/arch/imx-regs.h>
#include <errno.h>
#include <time.h>
#include <iopoll.h>

#if defined(CONFIG_IMX95)
#if defined(CA55)
#define CCM_BASE	CCM_NS_RBASE
#elif defined(CM33)
#define CCM_BASE	CCM_RBASE
#else
#error "Please specify either -DCA55 or -DCM33 !"
#endif

static struct ccm_reg *ccm_reg = (struct ccm_reg *)CCM_BASE;

static enum ccm_clk_src clk_root_mux[][4] = {
	{ OSC_24M_CLK, SYS_PLL_PFD0_DIV2, SYS_PLL_PFD1_DIV2, FRO_CLK },		/* Low-speed clocks */
	{ OSC_24M_CLK, SYS_PLL_PFD0, SYS_PLL_PFD1_DIV2, FRO_CLK },		/* Non-IO clocks */
	{ OSC_24M_CLK, SYS_PLL_PFD0, SYS_PLL_PFD1, SYS_PLL_PFD2},		/* Clocks for IP with max frequency in the range 400-1000MHz */
	{ OSC_24M_CLK, AUDIO_PLL_CLK, AUDIO_PLL2_CLK, EXT_CLK },		/* Audio interface-related clocks */
	{ OSC_24M_CLK, AUDIO_PLL_CLK, VIDEO_PLL_CLK, VIDEO_PLL_CLK },		/* Video interface-related clocks */
	{ OSC_24M_CLK, SYS_PLL_PFD0, OSC_32K_CLK, AUDIO_PLL_CLK },		/* CKO1 clocks */
	{ OSC_24M_CLK, SYS_PLL_PFD0, OSC_32K_CLK, VIDEO_PLL_CLK },		/* CKO2/4 clocks */
	{ OSC_24M_CLK, SYS_PLL_PFD0, OSC_32K_CLK, AUDIO_PLL2_CLK },		/* CKO3 clocks */
	{ OSC_24M_CLK, SYS_PLL_PFD0, AUDIO_PLL_CLK, EXT_CLK },			/* TPM clocks */
	{ OSC_24M_CLK, AUDIO_PLL_CLK, VIDEO_PLL_CLK, SYS_PLL_PFD2 },		/* hsio_acscan_480m */
}; /*  In i.MX95, the CCM inputs video_pll2_clk and video_pll3_clk are connected to the ANAMIX output video_pll1_clk. */

static struct clk_root_map clk_root_array[] = {
	{ ADC_CLK_ROOT,			0 },
	{ TMU_CLK_ROOT,			0 },
	{ BUS_AON_CLK_ROOT,		0 },
	{ CAN1_CLK_ROOT,		0 },
	{ I3C1_CLK_ROOT,		0 },
	{ I3C1_SLOW_CLK_ROOT,		0 },
	{ LPI2C1_CLK_ROOT,		0 },
	{ LPI2C2_CLK_ROOT,		0 },
	{ LPSPI1_CLK_ROOT,		0 },
	{ LPSPI2_CLK_ROOT,		0 },
	{ LPTMR1_CLK_ROOT,		0 },
	{ LPUART1_CLK_ROOT,		0 },
	{ LPUART2_CLK_ROOT,		0 },
	{ M33_CLK_ROOT,			1 },
	{ M33_SYSTICK_CLK_ROOT,		0 },
	{ MQS1_CLK_ROOT,		3 },
	{ PDM_CLK_ROOT,			3 },
	{ SAI1_CLK_ROOT,		3 },
	{ ELE_CLK_ROOT,		        1 },
	{ TPM2_CLK_ROOT,		8 },
	{ CAM_APB_CLK_ROOT,		0 },
	{ CAM_AXI_CLK_ROOT,		2 },
	{ CAM_CM0_CLK_ROOT,		2 },
	{ CAM_ISI_CLK_ROOT,		2 },
	{ MIPI_PHY_CFG_CLK_ROOT,	4 },
	{ MIPI_PHY_PLL_BYPASS_CLK_ROOT, 4 },
	{ MIPI_PHY_PLL_REF_CLK_ROOT,	4 },
	{ MIPI_TEST_BYTE_CLK_ROOT,	4 },
	{ ARM_A55_CLK_ROOT,		2 },
	{ ARM_A55_MTR_BUS_CLK_ROOT,	0 },
	{ ARM_A55_PERIPH_CLK_ROOT,	2 },
	{ DRAM_ALT_CLK_ROOT,		2 },
	{ DRAM_APB_CLK_ROOT,		0 },
	{ DISP_APB_CLK_ROOT,		0 },
	{ DISP_AXI_CLK_ROOT,		2 },
	{ DISP_OCRAM_CLK_ROOT,		2 },
	{ DISP1_PIX_CLK_ROOT,		4 },
	{ GPU_APB_CLK_ROOT,		0 },
	{ GPU_CLK_ROOT,			2 },
	{ HSIO_ACSCAN_480M_CLK_ROOT,	9 },
	{ HSIO_ACSCAN_80M_CLK_ROOT,	0 },
	{ HSIO_CLK_ROOT,		2 },
	{ HSIO_PCIE_AUX_CLK_ROOT,	0 },
	{ HSIO_PCIE_TEST_160M_CLK_ROOT, 2 },
	{ HSIO_PCIE_TEST_400M_CLK_ROOT, 2 },
	{ HSIO_PCIE_TEST_500M_CLK_ROOT, 2 },
	{ HSIO_USB_TEST_50M_CLK_ROOT,	0 },
	{ HSIO_USB_TEST_60M_CLK_ROOT,	0 },
	{ BUS_M7_CLK_ROOT,		0 },
	{ M7_CLK_ROOT,			2 },
	{ M7_SYSTICK_CLK_ROOT,		0 },
	{ BUS_NETCMIX_CLK_ROOT,		0 },
	{ ENET_CLK_ROOT,		2 },
	{ ENET_PHY_TEST_200M_CLK_ROOT,	1 },
	{ ENET_PHY_TEST_500M_CLK_ROOT,	2 },
	{ ENET_PHY_TEST_667M_CLK_ROOT,	2 },
	{ ENET_REF_CLK_ROOT,		1 },
	{ ENET_TIMER1_CLK_ROOT,		0 },
	{ MQS2_CLK_ROOT,		3 },
	{ SAI2_CLK_ROOT,		3 },
	{ NOC_APB_CLK_ROOT,		0 },
	{ NOC_CLK_ROOT,			2 },
	{ NPU_APB_CLK_ROOT,		0 },
	{ NPU_CLK_ROOT,			2 },
	{ CCM_CKO1_CLK_ROOT,		5 },
	{ CCM_CKO2_CLK_ROOT,		6 },
	{ CCM_CKO3_CLK_ROOT,		7 },
	{ CCM_CKO4_CLK_ROOT,		6 },
	{ VPU_APB_CLK_ROOT,		0 },
	{ VPU_CLK_ROOT,			2 },
	{ VPU_JPEG_CLK_ROOT,		2 },
	{ AUDIO_XCVR_CLK_ROOT,		1 },
	{ BUS_WAKEUP_CLK_ROOT,		0 },
	{ CAN2_CLK_ROOT,		0 },
	{ CAN3_CLK_ROOT,		0 },
	{ CAN4_CLK_ROOT,		0 },
	{ CAN5_CLK_ROOT,		0 },
	{ FLEXIO1_CLK_ROOT,		0 },
	{ FLEXIO2_CLK_ROOT,		0 },
	{ FLEXSPI1_CLK_ROOT,		2 },
	{ I3C2_SLOW_CLK_ROOT,		0 },
	{ LPI2C3_CLK_ROOT,		0 },
	{ LPI2C4_CLK_ROOT, 		0 },
	{ LPI2C5_CLK_ROOT, 		0 },
	{ LPI2C6_CLK_ROOT, 		0 },
	{ LPI2C7_CLK_ROOT, 		0 },
	{ LPI2C8_CLK_ROOT, 		0 },
	{ LPSPI3_CLK_ROOT, 		0 },
	{ LPSPI4_CLK_ROOT, 		0 },
	{ LPSPI5_CLK_ROOT, 		0 },
	{ LPSPI6_CLK_ROOT, 		0 },
	{ LPSPI7_CLK_ROOT, 		0 },
	{ LPSPI8_CLK_ROOT, 		0 },
	{ LPTMR2_CLK_ROOT,		0 },
	{ LPUART3_CLK_ROOT,		0 },
	{ LPUART4_CLK_ROOT, 		0 },
	{ LPUART5_CLK_ROOT, 		0 },
	{ LPUART6_CLK_ROOT, 		0 },
	{ LPUART7_CLK_ROOT, 		0 },
	{ LPUART8_CLK_ROOT, 		0 },
	{ SAI3_CLK_ROOT,		3 },
	{ SAI4_CLK_ROOT, 		3 },
	{ SAI5_CLK_ROOT, 		3 },
	{ SPDIF_CLK_ROOT,		3 },
	{ SWO_TRACE_CLK_ROOT,		0 },
	{ TPM4_CLK_ROOT,		8 },
	{ TPM5_CLK_ROOT, 		8 },
	{ TPM6_CLK_ROOT, 		8 },
	{ USB_PHY_BURUNIN_CLK_ROOT,	0 },
	{ USDHC1_CLK_ROOT,		2 },
	{ USDHC2_CLK_ROOT,		2 },
	{ USDHC3_CLK_ROOT,		2 },
	{ V2X_PK_CLK_ROOT,		2 },
	{ WAKEUP_AXI_CLK_ROOT,		2 },
	{ XSPI_SLV_ROOT_CLK_ROOT,	2 },
};
#endif

int ccm_clk_root_cfg(u32 clk_root_id, enum ccm_clk_src src, u32 div)
{
	int ret;
	u32 i, mux, status;

	if (clk_root_id >= CLK_ROOT_NUM || div > 256 || div == 0)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(clk_root_array); i++) {
		if (clk_root_array[i].clk_root_id == clk_root_id )
			break;
	}

	if(i == ARRAY_SIZE(clk_root_array))
		return -EINVAL;

	mux = clk_root_array[i].mux_type;

	for (i = 0; i < 4; i++) {
		if (src == clk_root_mux[mux][i])
			break;
	}

	if (i == 4)
		return -EINVAL;

	writel((i << 8) | (div - 1), &ccm_reg->clk_roots[clk_root_id].control);

	ret = readl_poll_timeout(&ccm_reg->clk_roots[clk_root_id].status0, status,
				 !(status & CLK_ROOT_STATUS_CHANGING), 200000);
	return ret;
};

int ccm_shared_gpr_set(u32 gpr, u32 val)
{
	if (gpr >= SHARED_GPR_NUM)
		return -EINVAL;

	writel(val, &ccm_reg->clk_shared_gpr[gpr].gpr);

	return 0;
}
