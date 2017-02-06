#ifndef SYS_H
#define SYS_H

#define PM_BASE   0x400E0000
#define PM_UNLOCK 0x400E0058
#define PBAMASK   0x400E0028
#define PM_SR     0x400E00D4
#define PM_MCCTRL 0x400E0000


#define BSCIF_UNLOCK 0x400F0418
#define RC1MCR       0x400F0458

void init_clock(void);

extern int __stack_end;
extern void main(void);

unsigned int milliseconds;

void init_sys(void);

void __attribute__ ((isr)) general_purpose_handler(void);

void __attribute__ ((isr)) sys_tick_handler(void);

void sys_tick_enable(void);

void wait(unsigned int ms);

#endif // SYS_H
