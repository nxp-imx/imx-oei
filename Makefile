## ###################################################################
##
## Copyright 2024 NXP
##
## Redistribution and use in source and binary forms, with or without modification,
## are permitted provided that the following conditions are met:
##
## o Redistributions of source code must retain the above copyright notice, this list
##   of conditions and the following disclaimer.
##
## o Redistributions in binary form must reproduce the above copyright notice, this
##   list of conditions and the following disclaimer in the documentation and/or
##   other materials provided with the distribution.
##
## o Neither the name of the copyright holder nor the names of its
##   contributors may be used to endorse or promote products derived from this
##   software without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
## ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
## WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
## DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
## ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
## (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
## LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
## ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
## SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
##
## ###################################################################

# OEI root directory
ROOT_DIR ?= .

# Configure verbose logging
ifdef v
    V := $(v)
endif
ifeq ($(V),1)
    AT :=
else
    AT := @
endif
export AT

# Configure debug
ifdef d
    DEBUG := $(d)
endif
DEBUG ?= 0

ifeq ($(DEBUG),1)
    FLAGS += -DDEBUG
endif

# Configure board
ifdef board
    SOM := $(board)
endif
# Default to mx95lp5
SOM ?= mx95lp5

# Configure SOC revision
ifdef r
    R := $(r)
endif
# Default to A0
R ?= A0
LOWER_R := $(shell echo $(R) | tr A-Z a-z)
UPPER_R := $(shell echo $(R) | tr a-z A-Z)
REV = $(UPPER_R)
FLAGS += -DSREV_$(UPPER_R)

# Configure oei
ifdef oei
    OEI := $(oei)
endif
# Default to ddr
OEI ?= ddr

# Enable OEI specific self-test
ifdef t
    TEST := $(t)
endif
TEST ?= 0

# Configure output
BUILD = $(ROOT_DIR)/build
OUT = $(BUILD)/$(SOM)/$(OEI)
INCLUDE = -I$(OUT)

# Includes
include $(ROOT_DIR)/boards/$(SOM)/Makefile
include $(ROOT_DIR)/oei/common/Makefile

EMUL ?= 0
ifeq ($(EMUL),1)
    FLAGS += -DCONFIG_EMUL
endif

OBJS += $(HW_OBJS)

TARGETS = $(OUT)/$(TARGET)

img : $(TARGETS)

all :
	$(AT)+$(MAKE) clean
	$(AT)+$(MAKE) img

.SUFFIXES :

DEPS := $(OBJS:.o=.d)

-include $(DEPS)

$(OUT)/%.o : %.c $(OUT)/build_info.h
	@echo "Compiling $<"
	$(AT)mkdir -p $(dir $@)
	$(AT)${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

$(OUT)/%.o : %.S
	@echo "Assembling $<"
	$(AT)mkdir -p $(dir $@)
	$(AT)${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

$(OUT)/$(IMG) : $(OBJS)
	@echo "Linking $@ ...."
	$(AT)$(LD) -o $@ $(OBJS) $(LFLAGS) 

$(OUT)/$(IMG).elf : $(OBJS)
	@echo "Linking $@ ...."
	$(AT)$(LD) -o $@ $(OBJS) $(LFLAGS)
	$(AT)$(OBJCOPY) -O binary --gap-fill 0x0 $(OUT)/$(IMG).elf $(OUT)/$(IMG).bin --strip-debug
	$(AT)$(OBJDUMP) -D -S $(OUT)/$(IMG).elf > $(OUT)/$(IMG).dis
	$(AT)$(SIZE) $(OUT)/$(IMG).elf

clean:
	@echo "Cleaning ...."
	$(AT)rm -f $(OUT)/*

really-clean:
	@echo "Really cleaning ...."
	$(AT)rm -rf $(BUILD)
	$(AT)rm -f doc/build_info

help :
	@/bin/echo -e "Usage: make TARGET OPTIONS\n"
	@/bin/echo -e "Targets:"
	@/bin/echo -e "\tall            : clean and rebuild"
	@/bin/echo -e "\thelp           : display help text"
	@/bin/echo -e "\tclean          : remove all build files"
	@/bin/echo -e "\treally-clean   : remove build directory\n"
	@/bin/echo -e "\nOptions:"
	@/bin/echo -e "\tboard=mx95lp5/mx95lp4x/mx95lp4x-15  		: the board,            default: mx95lp5"
	@/bin/echo -e "\tboard=mx943lp5-19/mx943lp4-19/mx943lp4-15	: the board,            "
	@/bin/echo -e "\toei=ddr/tcm                         		: OEI type,             default: ddr"
	@/bin/echo -e "\tr=A0/B0                             		: SOC revision,         default: A0"
	@/bin/echo -e "\tDEBUG=1 or d=1                      		: enable debug output,  default: off"
	@/bin/echo -e "\tt=1                                 		: enable OEI self-test, default: off"
	@/bin/echo -e "\tv=1                                 		: verbose compile logs, default: off"
	@/bin/echo -e "\tLTO=1                               		: Enable Link Time opt, default: off"
	@/bin/echo -e "\tDDR_CONFIG=file name (w/o .c)       		: Override DDR cfg filename, default: off"


include ./oei/makefiles/build_info.mak
