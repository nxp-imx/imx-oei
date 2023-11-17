**OEI: Optional Execution Image that used by BootROM**

#### Usage:

Usage: make TARGET OPTIONS

Targets:
        all            : clean and rebuild
        help           : display help text
        clean          : remove all build files
        really-clean   : remove build directory


Options:
        board=mx95lp5/mx95lp4x
        oei=ddr/tcm
        DEBUG=1
        QBOOT=yes

- build oei ddr image for imx95lp5 board that from on cm33 ROM
make board=mx95lp5 oei=ddr DEBUG=1

