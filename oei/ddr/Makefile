#include timings
include $(ROOT_DIR)/boards/$(SOM)/ddr/Makefile

OBJS += \
	$(OUT)/main.o \
	$(OUT)/ddr_init.o \
	$(OUT)/ddrphy_utils.o \
	$(OUT)/helper.o

OBJS  += \
	$(OUT)/ddrphy_qb.o \
	$(OUT)/ddrphy_train.o \
	$(OUT)/ddrphy_qb_gen.o \
	$(OUT)/romapi.o

VPATH += oei/ddr

IMG += oei-$(cpu)-ddr

include $(ROOT_DIR)/oei/makefiles/gcc_cross.mak
