#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcdDrawShapes.h"

#define redLed BIT0
#define greenLed BIT6
#define leds (greenLed | redLed)


void led_init(){
  P1DIR |= leds;
  P1OUT &= ~leds;
}
