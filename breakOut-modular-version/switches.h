#ifndef switches_included
#define switches_included

#define SW1 BIT0
#define SW4 BIT3

#define SWITCHES (SW1 | SW4)

extern int switches;

char switch_update_interrupt_sense();
void switch_init();
void switch_interrupt_handler();

#endif // included
