#!/bin/sh

CC=arm-linux-gnueabihf-gcc
LD=arm-linux-gnueabihf-ld
AS=arm-linux-gnueabihf-as
OBJCOPY=arm-linux-gnueabihf-objcopy


ifdef ARM926EJ_S
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJCOPY=arm-none-eabi-objcopy
CFLAGS+=-DARM926EJ_S -mcpu=arm926ej-s
QEMU_ARGS= -M versatilepb -m 128M  -kernel test.bin

else # a9

CFLAGS+=-DVEXPRESS_A9 -march=armv7-a
QEMU_ARGS= -M vexpress-a9 -m 128M -bios test.bin
endif


test.bin: test.elf
	$(OBJCOPY) -O binary test.elf test.bin

test.o: test.c
	$(CC) $(CFLAGS) -c -g test.c -o test.o
startup.o: startup.s
	$(AS) -g startup.s -o startup.o
test.elf: startup.o test.o
	$(LD) -g -T test.ld test.o startup.o -o test.elf
qemu:
	qemu-system-arm $(QEMU_ARGS)
debug.ld: test.ld
	sed -e 's/0x10000/0x0/' test.ld > $@

test.gdb.elf: startup.o test.o debug.ld
	$(LD) -g -T debug.ld test.o startup.o -o $@
clean:
	rm -rf *.o *.elf *.bin

