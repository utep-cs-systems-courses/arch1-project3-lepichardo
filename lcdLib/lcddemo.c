/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcdDrawShapes.h"

#define led BIT0

// Define switches
#define sw1 BIT0
#define sw2 BIT1
#define sw3 BIT2
#define sw4 BIT3
#define switches (sw1 | sw2 | sw3 | sw4)

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
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
  /*
  clearScreen(COLOR_RED);
  fillRectangle(30,30,50,50, COLOR_BLUE);
  */
  clearScreen(COLOR_WHITE);
  drawString11x16(20,20, "O0O", COLOR_BLACK, COLOR_RED);
  
  or_sr(0x18);
}

void switch_interrupt_handler(){
  char pval = P2IN;

  P2IES |= (pval & switches);	/* if switch up, sense down */
  P2IES &= (pval | ~switches);	/* if switch down, sense up */
  
  if (~pval & sw1){
    drawTriangle(COLOR_BLACK, 30);
  }
  
  if (~pval & sw2){
    drawAsterisc(COLOR_BLACK, 30);
  }

  if (~pval & sw3){
     drawSquare(COLOR_BLACK, 30);
  }

  if (~pval & sw4){
    clearScreen(COLOR_WHITE);
  }
}
void __interrupt_vec(PORT2_VECTOR) Port_2(){
   if (P2IFG & switches) { 
     P2IFG &= ~switches;
     switch_interrupt_handler(); 
   }
}

