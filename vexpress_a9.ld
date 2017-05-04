ENTRY(_Reset)
SECTIONS
{
 . = 0x0000;
 .startup . : { startup_vexpress_a9.o(.text) }
 .text : { *(.text) }
 .data : { *(.data) }
 .bss : { *(.bss COMMON) }
 . = ALIGN(8);
 . = . + 0x1000; /* 4kB of stack memory */
 stack_top = .;
}
