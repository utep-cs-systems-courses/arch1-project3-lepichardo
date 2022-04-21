#ifndef switch_included
#define switch_included

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15
char switch_update_interrupt_sense();
void switch_interrupt_handler();
extern int switches;


#endif
