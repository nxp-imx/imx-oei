cpu     := m33
SOC     := MIMX95
SOCFULL := $(SOC)
SOC_DEVICE_DIR := devices/$(SOC)

ifneq ($(REV),A0)
FLAGS += -DCONFIG_DUMMY_TRAIN_DATA_SUPPORT -DCONFIG_ELE
endif

BOARDS_DIR = $(ROOT_DIR)/boards
BOARD_DIR = $(BOARDS_DIR)/$(SOM)

INCLUDE +=  \
	-I$(BOARDS_DIR)  \
	-I$(BOARD_DIR)

ifeq ($(DEBUG),1)
OBJS += \
	$(OUT)/board.o  \
	$(OUT)/pin_mux.o
endif

VPATH +=  \
	$(BOARDS_DIR)  \
	$(BOARD_DIR)
