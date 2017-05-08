ENTRY(_start)
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x00000000, LENGTH = 1024K
  DRAM (xrw)      : ORIGIN = 0x60000000, LENGTH = 512M
}
SECTIONS
{
 . = 0x0000;
  /* .startup . : { v_a9_init.o(.text) } */
  .text : 
  { 
    *(.text .text.*)
    *(.rodata .rodata*)
    _etext = .;
  } > FLASH

  .data : AT (_etext)
  {
    _data = .;

    /* c++ ctor */
    __start_global_ctor__ = .;
    *(.init_array)
    __end_global_ctor__ = .;

    *(.data .data.*)
    _edata = .;
  } > DRAM

  .bss(NOLOAD) :
  {
    _bss = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > DRAM
}
