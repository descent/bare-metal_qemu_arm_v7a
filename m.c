//ref: http://blog.3mdeb.com/2014/08/07/debugging-coreboot-for-qemu-armv7-vexpress-a9-emulated-mainboard/

#include "mytype.h"
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

extern u32 _etext;
extern u32 _sidata;
extern u32 _data;
extern u32 _edata;
extern u32 _bss;
extern u32 _ebss;

#if 1
void init_c_env(void)
{
  u32 *pulSrc, *pulDest;

  pulSrc = &_etext;

  for (pulDest = &_data; pulDest < &_edata;)
    *pulDest++ = *pulSrc++;

  for (pulDest = &_bss; pulDest < &_ebss;)
    *pulDest++ = 0;
}
#endif


// sign version
char* s32_itoa_s(int n, char* str, int radix)
{
  char digit[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char* p=str;
  char* head=str;
  //int radix = 10;

//  if(!p || radix < 2 || radix > 36)
//    return p;
  if (n==0)
  {
    *p++='0';
    *p=0;
    return str;
  }
  if (radix == 10 && n < 0)
  {
    *p++='-';
    n= -n;
  }
  while(n)
  {
    *p++=digit[n%radix];
    //s32_put_char(*(p-1), (u8*)(0xb8000+80*2));
    n/=radix;
  }
  *p=0;
  #if 1
  for (--p; head < p ; ++head, --p)
  {
    char temp=*head;
    if (*(p-1) != '-')
    {
      *head=*p;
      *p=temp;
    }
  }
  #endif
  return str;
}

void c_entry() 
{
  init_c_env();

  char str[]="hello VEXPRESS_A9";
  char num[10];

  s32_itoa_s(246, num, 10);
  print_uart0(num);
  print_uart0("\r\n");

  print_uart0("Hello world!\r\n");
  print_uart0(str);
  //init();
}

#if 0
int main(int argc, char *argv[])
{
  
  return 0;
}
#endif
