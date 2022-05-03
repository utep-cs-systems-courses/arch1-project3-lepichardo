#ifndef led_included
#define led_included

#define redLed BIT0
#define greenLed BIT6
#define leds (greenLed | redLed)

void led_init();

#endif
