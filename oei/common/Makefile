include $(ROOT_DIR)/devices/$(SOC)/oei/Makefile
include $(ROOT_DIR)/oei/$(OEI)/Makefile

OBJS += \
	$(OUT)/oei_entry.o

OBJS += \
	$(OUT)/printf.o

INCLUDE += -I$(ROOT_DIR)/oei/common -I$(ROOT_DIR)/oei/$(OEI)
INCLUDE += -I$(SOC_DEVICE_DIR) -I$(SOC_DEVICE_DIR)/oei

VPATH += \
	oei/common \
	oei/utils
