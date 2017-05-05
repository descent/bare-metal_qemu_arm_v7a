//ref: http://blog.3mdeb.com/2014/08/07/debugging-coreboot-for-qemu-armv7-vexpress-a9-emulated-mainboard/

#include "arm_sp804.h"

#ifdef VEXPRESS_A9
// qemu-system-arm -M vexpress-a9 -m 128M  -bios test.bin
volatile unsigned int * const UART0DR = (unsigned int *)0x10009000;
#endif
 
void print_uart0(const char *s) 
{
  while(*s != '\0') { /* Loop until end of string */
    *UART0DR = (unsigned int)(*s); /* Transmit char */
    s++; /* Next char */
  }
}

void t()
{
  *UART0DR = 'a';
}

void c_entry() 
{
  const char str[]="hello VEXPRESS_A9";
  print_uart0("Hello world!\r\n");
  print_uart0(str);
  init();
}
