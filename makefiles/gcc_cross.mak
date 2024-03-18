## ###################################################################
##
## Copyright 2023 NXP
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

# Configure targets
ifeq ($(BUILD_HEX),1)
	TARGET = $(IMG).hex
else
	TARGET = $(IMG).elf
endif

# Configure toolchain
OEI_CROSS_COMPILE ?= $(TOOLS)/arm-gnu-toolchain-*-none-eabi/bin/arm-none-eabi-
ARCHFLAGS = -mcpu=cortex-$(cpu) -mthumb -mfloat-abi=soft

cc = gcc
CC = $(OEI_CROSS_COMPILE)$(cc)
LD = $(OEI_CROSS_COMPILE)$(cc)
OBJCOPY = $(OEI_CROSS_COMPILE)objcopy
SIZE = $(OEI_CROSS_COMPILE)size
FLAGS += -DCPU_$(SOCFULL)_c$(cpu) -D$(SOC)

# Configure linker control file
LCF = $(SOC)_c$(cpu)

# Configure warnings
WARNS = -Wall -Wextra -Wno-missing-braces -Wno-missing-field-initializers \
    -Wfloat-equal -Wswitch-default -Wcast-align \
    -Wpointer-arith -Wredundant-decls -Wbad-function-cast -Wstrict-prototypes \
    -Wundef -Wcast-qual -Wshadow -Wold-style-definition -Wno-unused-parameter -Werror \
    -Wformat=0 -Wunreachable-code -Wstack-usage=1024 -Wno-array-bounds -Wno-type-limits

FLAGS += ${WARNS}

#### SUMMARY OF COMPILER FLAGS ####
#
# DEPENDENCY GENERATION
# -MMD = generate dependency files for non-system headers
#
# OPTIMIZATION 
# -O3 = optimzation level
# -ffunction-sections = place each function in its own section (allows removal during link phase using --gc-sections)
# -fdata-sections = place each data item in its own section (allows removal during link phase using --gc-sections)
#
# DEBUG
# -g = enable debug info generation
#
# C LANGUAGE
# -std=c99 = support ISO C99
# -ffreestanding = standard library may not exist
# -fno-builtin = do not recognize built-in functions
#
# CODE GENERATION
# -fshort-enums = allocate enum as smallest type that can hold declared range
#
# MACHINE-DEPENDENT
# -mno-unaligned-access = disable unaligned access
#
# OUTPUT
# -pipe = use pipes instead of temporary files
#
###################################
CFLAGS = $(ARCHFLAGS) $(FLAGS) -MMD -O3 -ffunction-sections -fdata-sections -g -std=c99 -ffreestanding -fno-builtin -fshort-enums -mno-unaligned-access -pipe

#### SUMMARY OF LINKER FLAGS ####
#
# -nostdlib = do not use standard system startup files or libraries when linking
# -gc-sections = linker garbage collection (allows function/data section removal during link phase)
# -Map = specifies map output file
# -T = specifies linker script
# 
#################################
LFLAGS += $(ARCHFLAGS) -Wl,--gc-sections -Wl,-Map=$(OUT)/$(IMG).map -nostdlib -nodefaultlibs -Wl,--no-warn-rwx-segments -T$(SOC_DEVICE_DIR)/gcc/$(LCF).ld
