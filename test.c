//ref: http://blog.3mdeb.com/2014/08/07/debugging-coreboot-for-qemu-armv7-vexpress-a9-emulated-mainboard/

//#define VEXPRESS_A9

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

  volatile unsigned int * const ptr = (unsigned int *)0x70000000;
#if 0
void c_entry() 
{
  *ptr = 'b';
  #if 0
  char s[5];

  s[0]='a';
  while(1);
  #endif
}
#endif 
#if 1
void c_entry() 
{
#ifdef VEXPRESS_A9
  const char str[]="hello VEXPRESS_A9";
#else
  char str[]="hello ARM926EJ-S";
#endif
  print_uart0("Hello world!\r\n");
  print_uart0(str);

#if 0
  const char *s;
  //s=(const char *)0x4;
  s = str;
  while(*s != '\0') 
  { /* Loop until end of string */
    *UART0DR = (unsigned int)(*s); /* Transmit char */
    s++; /* Next char */
  }
  //*UART0DR = 'a';
  //*UART0DR = 'b';
#endif
}
#endif
