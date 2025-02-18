The Optional Executable Image (OEI) is an optional plugin loaded and executed by Cortex-M processor
ROM on many NXP i.MX processors. The Cortex-M is the boot core, runs the boot ROM which loads the OEI, and then
branches to the OEI. The OEI then configures some aspects of the hardware such as DDR config, init TCM ECC, etc.
There could be multiple OEI images in the boot container. After execution of OEI, the processor returns
to ROM execution.

Supported development environments include Ubuntu 2020.04, 2022.04, and 2024.04.

Download from GitHub
====================

To download the repo from [GitHub](https://github.com/nxp-imx/imx-oei), first install git:

    sudo apt update
    sudo apt -y install git

Then clone the repo:

git clone https://github.com/nxp-imx/imx-oei

Installing the Toolchain
========================

Compiling requires an ARM cross-compiler. Download and install the required arm-none-eabi toolchain from
the [Arm GNU Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
website. For example, from the x86_64 Linux hosted cross toolchains AArch32 bare-metal target
(arm-none-eabi) section, download the *.xz file to a directory for the tool chain and then:

    tar xvf *.xz

Set the CROSS_COMPILE environment variable. For example:

    export CROSS_COMPILE="ccache arm-none-eabi-"

When the toolchain is in a directory like arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi in this
*tools* directory.

Also ensure the Linux installation is up-to-date and then install:

    sudo apt -y install make gcc g++-multilib srecord

Compiling an OEI Image
=====================

For example to build DDR OEI, in the top directory of the code base (e.g. imx-oei):

    make board=mx95libra oei=ddr DEBUG=1

Copy the resulting binary image file, *build/mx95libra/ddr/oei-m33-ddr.bin*, to the iMX95 directory of the
[mkimage tool](https://github.com/nxp-imx/imx-mkimage).

Similarly, to build TCM init OEI, in the top directory of the code base (e.g. imx-oei):

    make board=mx95libra oei=tcm DEBUG=1

Then copy the resulting binary image file, *build/mx95libra/tcm/oei-m33-tcm.bin*, to the iMX95 directory of the
[mkimage tool](https://github.com/nxp-imx/imx-mkimage). Build a boot container using mkimage, program
it to the boot device, and boot the board. The OEI will display debug messages on the M33 debug
UART.
