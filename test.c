//ref: http://blog.3mdeb.com/2014/08/07/debugging-coreboot-for-qemu-armv7-vexpress-a9-emulated-mainboard/

#define VEXPRESS_A9

#ifdef ARM926EJ_S
// qemu-system-arm -M versatilepb -m 128M -nographic -kernel test.bin
volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;
#endif

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
 
void c_entry() 
{
  //print_uart0("Hello world!\n");
  *UART0DR = 'a';
  *UART0DR = 'b';
}
