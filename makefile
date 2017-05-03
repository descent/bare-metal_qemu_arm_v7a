#!/bin/sh
CC=arm-linux-gnueabihf-gcc
LD=arm-linux-gnueabihf-ld
AS=arm-linux-gnueabihf-as
OBJCOPY=arm-linux-gnueabihf-objcopy

test.bin: test.elf
	arm-linux-gnueabihf-objcopy -O binary test.elf test.bin

test.o: test.c
	arm-linux-gnueabihf-gcc -c -march=armv7-a -g test.c -o test.o
startup.o: startup.s
	arm-linux-gnueabihf-as -march=armv7-a -g startup.s -o startup.o
test.elf: startup.o test.o
	arm-linux-gnueabihf-ld -T test.ld test.o startup.o -o test.elf
qemu:
	qemu-system-arm -M vexpress-a9 -m 128M  -bios test.bin
clean:
	rm -rf *.o *.elf *.bin
