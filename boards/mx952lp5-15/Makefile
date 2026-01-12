## SPDX-License-Identifier: BSD-3-Clause
##
## Copyright 2025 NXP
##

cpu     = m33
SOC     = MIMX952
SOCFULL = $(SOC)
SOC_DEVICE_DIR = devices/$(SOC)

FLAGS += -DCONFIG_DUMMY_TRAIN_DATA_SUPPORT -DCONFIG_ELE

BOARDS_DIR = $(ROOT_DIR)/boards
BOARD_DIR = $(BOARDS_DIR)/$(SOM)

INCLUDE +=  \
	-I$(BOARDS_DIR)  \
	-I$(BOARD_DIR)

OBJS += \
	$(OUT)/board.o

ifeq ($(DEBUG),1)
OBJS += \
	$(OUT)/pin_mux.o
endif

VPATH +=  \
	$(BOARDS_DIR)  \
	$(BOARD_DIR)
