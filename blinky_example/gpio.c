#include "gpio.h"
#include "bits.h"

#define GPIO_BASE 0x400E1000
#define GPIO_PORTSZ    0x200
#define GPIO_GPER_OFFS 0x000
#define GPIO_GPCR_OFFS 0x008
#define GPIO_ODER_OFFS 0x040
#define GPIO_OVR_OFFS  0x050
#define GPIO_PMR0_OFFS 0x010
#define GPIO_PMR1_OFFS 0x020
#define GPIO_PMR2_OFFS 0x030

void gpio_enable(int gpio)
{
    int port = gpio / 32;
    int pin = gpio % 32;

    int port_base = GPIO_BASE + port * GPIO_PORTSZ;
    int gper = port_base + GPIO_GPER_OFFS;
    int oder = port_base + GPIO_ODER_OFFS;

    volatile int *gper_reg = (volatile int *)gper;
    volatile int *oder_reg = (volatile int *)oder;

    *gper_reg = setb(*gper_reg, pin);
    *oder_reg = setb(*oder_reg, pin);
}

void gpio_set_value(int gpio, char value)
{
    int port = gpio / 32;
    int pin = gpio % 32;

    int port_base = GPIO_BASE + port * GPIO_PORTSZ;
    int ovr = port_base + GPIO_OVR_OFFS;

    volatile int *ovr_reg = (volatile int *)ovr;

    if (value)
    {
        *ovr_reg = setb(*ovr_reg, pin);
    }
    else
    {
        *ovr_reg = clrb(*ovr_reg, pin);
    }
}

void gpio_toggle(int gpio)
{
    int port = gpio / 32;
    int pin = gpio % 32;

    int port_base = GPIO_BASE + port * GPIO_PORTSZ;
    int ovr = port_base + GPIO_OVR_OFFS;

    volatile int *ovr_reg = (volatile int *)ovr;

    *ovr_reg = flpb(*ovr_reg, pin);
}

void gpio_set_peripheral_function(int gpio, int fn)
{
    int port = gpio / 32;
    int pin = gpio % 32;

    int port_base = GPIO_BASE + port * GPIO_PORTSZ;
    int gpcr = port_base + GPIO_GPCR_OFFS;

    volatile int *gpcr_reg = (volatile int *)gpcr;

    *gpcr_reg = setb(*gpcr_reg, pin);

    int pmr0 = port_base + GPIO_PMR0_OFFS;
    int pmr1 = port_base + GPIO_PMR1_OFFS;
    int pmr2 = port_base + GPIO_PMR2_OFFS;

    volatile int *pmr0_reg = (volatile int *)pmr0;
    volatile int *pmr1_reg = (volatile int *)pmr1;
    volatile int *pmr2_reg = (volatile int *)pmr2;

    if (is_set(*pmr0_reg, pin))
    {
        *pmr0_reg = setb(*pmr0_reg, pin);
    }
    else
    {
        *pmr0_reg = clrb(*pmr0_reg, pin);
    }

    if (is_set(*pmr1_reg, pin))
    {
        *pmr1_reg = setb(*pmr1_reg, pin);
    }
    else
    {
        *pmr1_reg = clrb(*pmr1_reg, pin);
    }

    if (is_set(*pmr2_reg, pin))
    {
        *pmr2_reg = setb(*pmr2_reg, pin);
    }
    else
    {
        *pmr2_reg = clrb(*pmr2_reg, pin);
    }
}
