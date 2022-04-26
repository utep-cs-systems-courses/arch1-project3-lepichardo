/** 
 * \file lcddemo.c  
 */
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcdDrawShapes.h"
#include "animations.h"

#define led BIT0

// Define switches
#define sw1 BIT0
#define sw2 BIT1
#define sw3 BIT2
#define sw4 BIT3
#define switches (sw1 | sw2 | sw3 | sw4)

/** Initializes everything, clears the screen */
int main()
{
  configureClocks();

  P1DIR |= led;
  P1OUT &= ~led;
  
  // Activate switches
  P2REN |= switches;
  P2IE |= switches;
  P2OUT |= switches;
  P2DIR &= ~switches;

  lcd_init();
  u_char width = screenWidth, height = screenHeight;
  
  clearScreen(COLOR_WHITE);
  //drawString11x16(20,20, "O0O", COLOR_BLACK, COLOR_RED);
  
  or_sr(0x18);
}

void switch_interrupt_handler(){
  char pval = P2IN;

  P2IES |= (pval & switches);	/* if switch up, sense down */
  P2IES &= (pval | ~switches);	/* if switch down, sense up */
  
  if (~pval & sw1){
    state = 1;
    enableWDTInterrupts();
  }  
  if (~pval & sw2){
    state = 2;
    enableWDTInterrupts();
  }
  if (~pval & sw3){
    state = 3;
    enableWDTInterrupts();
  }
  if (~pval & sw4){
    state = 4;
    enableWDTInterrupts();
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
   if (P2IFG & switches) { 
     P2IFG &= ~switches;
     switch_interrupt_handler(); 
   }
}
