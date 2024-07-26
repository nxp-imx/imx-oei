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

OEI_VERSION = imx_oei_2024q3
OEI_PREV_VER = None

MKIMAGE_BRANCH = master
MKIMAGE_BUILD = Linux_IMX_Trunk
MKIMAGE_N = latest

$(OUT)/build_info.h :
	@echo "Generating $@"
	$(AT)mkdir -p $(dir $@)
	$(AT)/bin/echo '#ifndef BUILD_INFO_H' > $@
	$(AT)/bin/echo '#define BUILD_INFO_H' >> $@
	$(AT)/bin/echo '' >> $@
	$(AT)/bin/echo '#define OEI_VERSION "$(OEI_VERSION)"' >> $@
	$(AT)/bin/echo '#define OEI_PREV_VER "$(OEI_PREV_VER)"' >> $@
	$(AT)/bin/echo '' >> $@
	$(AT)/bin/echo '#define OEI_DEVICES "$(SOC)($(REV))"' >> $@
	$(AT)/bin/echo '#define OEI_BOARD "$(SOM)"' >> $@
	$(AT)/bin/echo '' >> $@
	$(AT)/bin/echo -n '#define OEI_BRANCH ' >> $@
	$(AT)-git rev-parse --abbrev-ref HEAD >> $@
	$(AT)-perl -pi -e 'chomp if eof' $@
	$(AT)/bin/echo '' >> $@
	$(AT)/bin/echo -n '#define OEI_BUILD ' >> $@
	$(AT)-git rev-list --count --first-parent HEAD >> $@
	$(AT)-perl -pi -e 'chomp if eof' $@
	$(AT)/bin/echo 'UL' >> $@
	$(AT)/bin/echo -n '#define OEI_COMMIT 0x' >> $@
	$(AT)-git rev-parse --short=8 HEAD >> $@
	$(AT)-perl -pi -e 'chomp if eof' $@
	$(AT)/bin/echo 'UL' >> $@
	$(AT)date +'#define OEI_DATE "%b %d %C%y"' >> $@
	$(AT)date +'#define OEI_TIME "%T"' >> $@
	$(AT)/bin/echo '' >> $@
	$(AT)/bin/echo '#define OEI_MKIMAGE_BRANCH "$(MKIMAGE_BRANCH)"' >> $@
	$(AT)/bin/echo '#define OEI_MKIMAGE_BUILD "$(MKIMAGE_BUILD)"' >> $@
	$(AT)/bin/echo '#define OEI_MKIMAGE_N "$(MKIMAGE_N)"' >> $@
	$(AT)/bin/echo '' >> $@
	$(AT)/bin/echo '#endif' >> $@

rn_info.sed :
	$(AT)/bin/echo '' > $@
	$(AT)/bin/echo "sed -i 's/\#OEI_VERSION/$(OEI_VERSION)/g' rn.md" >> $@
	$(AT)/bin/echo "sed -i 's/\#OEI_PREV_VER/$(OEI_PREV_VER)/g' rn.md" >> $@
	$(AT)/bin/echo "sed -i 's/\#OEI_DEVICES/$(SOC)($(REV))/g' rn.md" >> $@
	$(AT)/bin/echo -n "sed -i 's/\#OEI_BRANCH/" >> $@
	$(AT)-git rev-parse --abbrev-ref HEAD >> $@
	$(AT)-perl -pi -e 'chomp if eof' $@
	$(AT)/bin/echo "/g' rn.md" >> $@
	$(AT)/bin/echo -n "sed -i 's/\#OEI_BUILD/" >> $@
	$(AT)-git rev-list --count --first-parent HEAD >> $@
	$(AT)-perl -pi -e 'chomp if eof' $@
	$(AT)/bin/echo "/g' rn.md" >> $@
	$(AT)/bin/echo -n "sed -i 's/\#OEI_COMMIT/" >> $@
	$(AT)-git rev-parse --short=8 HEAD >> $@
	$(AT)-perl -pi -e 'chomp if eof' $@
	$(AT)/bin/echo "/g' rn.md" >> $@
	$(AT)/bin/echo -n "sed -i 's/\#OEI_DATE/" >> $@
	$(AT)date +'%b %d %C%y' >> $@
	$(AT)-perl -pi -e 'chomp if eof' $@
	$(AT)/bin/echo "/g' rn.md" >> $@
	$(AT)/bin/echo "sed -i 's/\#MKIMAGE_BRANCH/$(MKIMAGE_BRANCH)/g' rn.md" >> $@
	$(AT)/bin/echo "sed -i 's/\#MKIMAGE_BUILD/$(MKIMAGE_BUILD)/g' rn.md" >> $@
	$(AT)/bin/echo '' >> $@

