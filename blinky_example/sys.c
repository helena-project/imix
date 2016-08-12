#include "sys.h"
#include "usart.h"

void init_sys(void)
{
    init_clock();
    milliseconds = 0;
    sys_tick_enable();
    init_console();
}

void __attribute__ ((isr)) general_purpose_handler(void)
{
    while (1) {}
}

void __attribute__ ((isr)) sys_tick_handler(void)
{
    milliseconds++;
}

#define SYST_CSR        0xE000E010
#define SYST_RVR        0xE000E014
#define SYST_CVR        0xE000E018
#define NVIC_ISER_BASE  0xE000E100

void sys_tick_enable(void)
{
    // Program reload value
    *((volatile int *)SYST_RVR) = 999;

    // Clear current value
    *((volatile int *)SYST_CVR) = 0;

    // Program control and status register
    *((volatile int *)SYST_CSR) = 0x7;

    // Enable SysTick interrupt (SysTick is IRQ 15)
    *((volatile int *)NVIC_ISER_BASE) = 0x1 << 15;
}

void wait(unsigned int ms)
{
    unsigned int now = milliseconds;
    while (ms > milliseconds - now)
    {
    }
}

void init_clock(void)
{
    // RC1M clock Section 12.7.5
    // Unlock section 12: 0xAA000058
    // Set bit 0 of RC1MCR 0x058
    // Unlock section 10: 0xAA000000
    // Set MCCTRL to 6
    // Poll SR 0x0D4 for CKRDY (bit 5)

    *((volatile int *)BSCIF_UNLOCK) = 0xAA000058;

    *((volatile int *)RC1MCR) |= 0x1;

    *((volatile int *)PM_UNLOCK) = 0xAA000000; 

    *((volatile int *)PM_MCCTRL) = 6;

    while (!is_set(*((volatile int *)PM_SR), 5)) {}
}
