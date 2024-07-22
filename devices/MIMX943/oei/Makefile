## SPDX-License-Identifier: BSD-3-Clause
##
## Copyright 2024 NXP
##

SERIES = MIMX9
SOC = MIMX943
SOCFULL = $(SOC)
CMSIS_DIR = $(ROOT_DIR)/CMSIS
DEVICE_DIR = $(ROOT_DIR)/devices
SERIES_DEVICE_DIR = $(DEVICE_DIR)/$(SERIES)
SOC_DEVICE_DIR = $(DEVICE_DIR)/$(SOC)
DRIVER_DIR = $(ROOT_DIR)/drivers
COMPONENTS_DIR = $(ROOT_DIR)/components
cpu = m33

INCLUDE += \
	-I$(CMSIS_DIR)/Core/Include  \
	-I$(DEVICE_DIR)  \
	-I$(SERIES_DEVICE_DIR)  \
	-I$(SERIES_DEVICE_DIR)/drivers  \
	-I$(SOC_DEVICE_DIR)  \
	-I$(SOC_DEVICE_DIR)/drivers  \
	-I$(SOC_DEVICE_DIR)/oei  \
	-I$(DRIVER_DIR)/common  \
	-I$(DRIVER_DIR)/edma  \
	-I$(DRIVER_DIR)/lpuart  \
	-I$(DRIVER_DIR)/sysctr  \
	-I$(COMPONENTS_DIR)/crc

VPATH += \
    $(DEVICE_DIR)  \
    $(SERIES_DEVICE_DIR)  \
    $(SERIES_DEVICE_DIR)/drivers  \
    $(SOC_DEVICE_DIR)  \
    $(SOC_DEVICE_DIR)/drivers  \
    $(SOC_DEVICE_DIR)/oei  \
    $(SOC_DEVICE_DIR)/$(cc)  \
    $(DRIVER_DIR)/edma  \
    $(DRIVER_DIR)/lpuart  \
    $(DRIVER_DIR)/sysctr  \
    $(COMPONENTS_DIR)/crc

SDK_OBJS = \
    $(OUT)/edma.o  \
    $(OUT)/fsl_ccm.o  \
    $(OUT)/fsl_clock.o  \
    $(OUT)/fsl_fract_pll.o  \
    $(OUT)/fsl_lpuart.o  \
    $(OUT)/fsl_power.o  \
    $(OUT)/fsl_src.o  \
    $(OUT)/fsl_sysctr.o

OBJS  +=  \
    $(OUT)/soc_clock.o  \
    $(OUT)/soc_edma.o  \
    $(OUT)/soc_printf.o  \
    $(OUT)/soc_time_cm33.o

ifeq ($(OEI),ddr)
INCLUDE += \
	-I$(DRIVER_DIR)/mu1 \
	-I$(DRIVER_DIR)/ele

VPATH += \
    $(DRIVER_DIR)/mu1 \
    $(DRIVER_DIR)/ele

OBJS  += \
    $(OUT)/soc_ddr.o \
    $(OUT)/fsl_mu.o \
    $(OUT)/fsl_ele.o \
    $(OUT)/crc.o
endif

OBJS += $(SDK_OBJS) $(OEI_OBJS)

VPATH += devices/$(SOC)/oei
