        .section .text
        .align  4
        .global _start
_start:
        ldr     pc, reset_p             // Reset.
        ldr     pc, undefined_p         // Undefined opcode.
        ldr     pc, swi_p               // Syscall.
        ldr     pc, prefetch_p          // Prefetch.
        ldr     pc, abort_p             // Abort.
        nop                             // Reserved. 
        ldr     pc, irq_p               // Interrupt.

// The addresses of the actual exception handlers.
reset_p:
        .word reset
undefined_p:
        .word undefined
swi_p:
        .word swi
prefetch_p:
        .word prefetch
abort_p:
        .word abort
irq_p:
        .word irq
reset:
  LDR sp, =0x70000000
  BL c_entry
  B .

undefined:
        b       undefined

prefetch:
        b       prefetch

abort:
        b       abort
irq:
  LDR sp, =0x70008000
  BL t
  b irq
swi:
        b       swi
