#ifndef GPIO_H
#define GPIO_H

/* GPIO pin numbering. */
#define PB03 35
#define PA05  5 
#define PA07  7 
#define PA15 15
#define PA16 16
#define PC10 74

/* Functional names for common pins. */
#define USR_LED    PB03
#define USART0_RX  PA05
#define USART0_TX  PA07
#define RNG_EN     PA15
#define RNG_OUT    PA16

#define PERIPH_A   0b000
#define PERIPH_B   0b001
#define PERIPH_C   0b010
#define PERIPH_D   0b011
#define PERIPH_E   0b100
#define PERIPH_F   0b101
#define PERIPH_G   0b110
#define PERIPH_H   0b111

void gpio_enable(int gpio);

void gpio_set_value(int gpio, char value);

void gpio_toggle(int gpio);

void gpio_set_peripheral_function(int gpio, int fn);

#endif // GPIO_H
