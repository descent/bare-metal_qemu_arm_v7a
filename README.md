build ARM926EJ-S version
make ARM926EJ_S=1 test.bin
qemu-system-arm -M versatilepb -m 128M  -kernel test.bin
ctrl+alt+3 see the hello message


build VEXPRESS_A9 version
make
qemu-system-arm -M vexpress-a9 -m 512M  -bios test.a9.bin
ctrl+alt+4 see the hello message

or you can use -nographic
ex:
qemu-system-arm -M versatilepb -m 128M  -kernel test.bin -nographic
qemu-system-arm -M vexpress-a9 -m 512M  -bios test.a9.bin -nographic

vexpress-a9 ddr2 memory from: 
ref: http://infocenter.arm.com/help/topic/com.arm.doc.dui0448i/DUI0448I_v2p_ca9_trm.pdf
p 3-3, 0x6000_0000-0x7FFF_FFFF 512MB Local DDR2 lower, use the ddr2 address.

