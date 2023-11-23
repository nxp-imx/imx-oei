ifeq ($(PSTATES),3)
OBJS  += $(OUT)/XIMX95LPD5EVK19_train_timing.o
FLAGS += -DDDRPHY_PSTATES=$(PSTATES)
else
OBJS  += $(OUT)/XIMX95LPD5EVK19_6400mbps_train_timing.o
FLAGS += -DDDRPHY_PSTATES=1
endif

FLAGS += -DDDR5

VPATH += boards/mx95lp5/ddr
