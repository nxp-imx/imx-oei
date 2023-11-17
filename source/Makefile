ifeq ($(oei), ddr)
include $(ROOT_DIR)/source/ddr/Makefile
else ifeq ($(oei), tcm)
include $(ROOT_DIR)/source/tcm/Makefile
endif

OBJS += \
	$(OUT)/time-cm33.o \
	$(OUT)/clock_imx95.o \
	$(OUT)/clock_root.o \
	$(OUT)/clock_common.o

ifeq ($(DEBUG), 1)
OBJS += \
	$(OUT)/pinmux.o \
	$(OUT)/tiny-printf.o \
	$(OUT)/lpuart.o
endif

INCLUDE += -Iinclude

VPATH += \
	source/utils \
	source/clocks
