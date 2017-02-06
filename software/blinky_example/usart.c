#include "usart.h"
#include "sys.h"
#include "gpio.h"

#include <string.h>

#define USART0_BASE 0x40024000
#define USART0_THR  0x4002401C
#define USART0_CSR  0x40024014
#define USART0_MR   0x40024004
#define USART0_CR   0x40024000
#define USART0_BRGR 0x40024020


void init_console(void)
{
    // Configure USART0 GPIO
    gpio_set_peripheral_function(USART0_TX, PERIPH_B);

    // Unlock PBAMASK register
    *((volatile int *)PM_UNLOCK) = 0xAA000028;

    // Set PBAMASK to enable USART0 clock
    *((volatile int *)PBAMASK) = (0x1 << 8);

    // Set Baud rate clock generator
    *((volatile int *)USART0_BRGR) = 13;

    // Set the char length to 8 and oversampling mode
    *((volatile int *)USART0_MR) = (0x1 << 6) | (0x1 << 7) | (0x1 << 19);

    // Enable transmission
    *((volatile int *)USART0_CR) = (0x1 << 6);
}


void putstr(char *str)
{
    int i = 0;
    for (i; i < 256; i++)
    {
        if (str[i] == '\0') break;
        put(str[i]);
    }
}


void put(char c)
{
    volatile int *thr = (volatile int *)USART0_THR;

    // Poll until transmit ready
    while (!is_set(*((volatile int *)USART0_CSR), 1)) {}

    // Put the character in the transmit register
    *thr = c;
}
