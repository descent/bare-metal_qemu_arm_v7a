/* Definitions for the ARM SP804 Dual-Timer.
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0271d/Babehiha.html
 */
#if 0
//#define VEXPRESS_A9
#if defined (VERSATILEPB)
#define BASE 0x0101E2000
#elif defined (VEXPRESS_A9)
#define BASE 0x10011000
#else // Newer cores.
#define BASE 0x1C110000
#endif
#endif

#define BASE 0x10011000

#define IRQ 2
#define CLOCK 1000000

#define T(offset) ((volatile unsigned int *)((BASE + (offset))))

#define Timer1Load    T(0x000)  // Timer 1 load register.
#define Timer1Value   T(0x004)  // Current value register.
#define Timer1Control T(0x008)  // Timer 1 control register.
  #define TimerEn   0x0080      // 0 = disabled, 1 = enabled.
  #define TimerMode 0x0040      // 0 = free running, 1 = periodic.
  #define IntEnable 0x0020      // 0 = disabled, 1 = enabled.
  #define TimerPre  0x000C      // Prescale 00 = clk/1   01 = clk/16
                                //          01 = clk/256 11 = undefined
  #define TimerSize 0x0002      // 0 = 16-bit, 1 = 32-bit.
  #define OneShot   0x0001      // 0 = wrapping, 1 = one-shot.

#define Timer1IntClr  T(0x00C)  // Interrupt clear register.
#define Timer1RIS     T(0x010)  // Raw interrupt status register.
#define Timer1MIS     T(0x014)  // Masked interrupt status register.
  #define TimerInt  0x0001      // Timer interrupt bit.

#define Timer1BGLoad  T(0x018)  // Background load register.

#define Timer2Load    T(0x020)  // Timer 2 load register.
#define Timer2Value   T(0x024)  // Current value register.
#define Timer2Control T(0x028)  // Timer 2 control register.
#define Timer2IntClr  T(0x02C)  // Interrupt clear register.
#define Timer2RIS     T(0x030)  // Raw interrupt status register.
#define Timer2MIS     T(0x034)  // Masked interrupt status register.
#define Timer2BGLoad  T(0x038)  // Background load register.

void init(void);
