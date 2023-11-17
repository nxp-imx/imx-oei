#include timings
include $(ROOT_DIR)/boards/$(SOM)/ddr/Makefile

OBJS += \
	$(OUT)/main.o \
	$(OUT)/ddr_init.o \
	$(OUT)/ddrphy_utils.o \
	$(OUT)/helper.o

QB = $(shell echo $(QBOOT) | tr A-Z a-z)
ifeq (${QB}, yes)
FLAGS += -DCONFIG_DDR_QBOOT
OBJS  += $(OUT)/ddrphy_qb.o
else
OBJS  += $(OUT)/ddrphy_train.o $(OUT)/ddrphy_qb_gen.o
endif

VPATH += source/ddr

IMG += oei-$(cpu)-ddr

include $(ROOT_DIR)/makefiles/gcc_cross.mak
