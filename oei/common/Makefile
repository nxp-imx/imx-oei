include $(ROOT_DIR)/devices/$(SOC)/oei/Makefile
include $(ROOT_DIR)/oei/$(OEI)/Makefile

OBJS += \
	$(OUT)/oei_entry.o

ifeq ($(DEBUG), 1)
OBJS += \
	$(OUT)/printf.o
endif

INCLUDE += -I$(ROOT_DIR)/oei/common -I$(ROOT_DIR)/oei/$(OEI)
INCLUDE += -I$(SOC_DEVICE_DIR) -I$(SOC_DEVICE_DIR)/oei

VPATH += \
	oei/common \
	oei/utils
