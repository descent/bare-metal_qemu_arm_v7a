@ 理論上來說，ARM的15個通用寄存器是通用的，但實際上並非如此，特別是在過程調用的過程中。
@ PCS(Procedure Call Standard for Arm architecture)就定義了過程調用中，寄存器的特殊用途。
@ 
@ Role in the procedure call standard
@ 
@ r15 PC The Program Counter.
@ 
@ r14 LR The Link Register.
@ 
@ r13 SP The Stack Pointer.
@ 
@ r12 IP The Intra-Procedure-call scratch register. （可簡單的認為暫存SP）
@ 
@ 實際上，還有一個r11是optional的，被稱為FP，即frame pointer。
@ 原文網址：https://read01.com/M0onoa.html
@ ref: http://infocenter.arm.com/help/topic/com.arm.doc.dui0448i/DUI0448I_v2p_ca9_trm.pdf
@ p 3-3, 0x6000_0000-0x7FFF_FFFF 512MB Local DDR2 lower, use the ddr2 address.
.global _Reset
_Reset:
 LDR sp, =0x70000000

         push    {fp} 
         add     fp, sp, #0
         sub     sp, sp, #12

@         mov     r3, #97 @ 0x61
@         ldr     r2, =0x70000000
@         strb    r3, [r2]
 BL c_entry
 B .
