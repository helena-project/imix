#include "sys.h"
#include "gpio.h"

void main(void);

typedef void(* const isr_vector)(void);

isr_vector __attribute((section(".vectors"))) vector_table[] = 
{
    (isr_vector)&__stack_end, // Initial SP
    (isr_vector)&main,        // Initial PC
    &general_purpose_handler, // NMI
    &general_purpose_handler, // Hard fault
    &general_purpose_handler, // Mem manage
    &general_purpose_handler, // Bus fault
    &general_purpose_handler, // Usage fault
    0, 0, 0, 0,
    &general_purpose_handler, // SVC handler
    &general_purpose_handler, // Debug monitor
    0,
    &general_purpose_handler, // Pend SVC 
    &sys_tick_handler,        // SysTick
};

void main(void)
{
    init_sys();

    gpio_enable(PC10);

    while (1)
    {
        putstr("Toggling");
        gpio_toggle(PC10);
        wait(500); // ms
    }
}
