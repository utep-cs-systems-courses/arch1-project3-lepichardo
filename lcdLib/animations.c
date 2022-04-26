#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcdDrawShapes.h"

int state = 0;
static int fCol = 0;
static int fRow = 0;

int change = 0;

static char figures[] = {'T','A','S'};
int currFigure = 0;

void changeFigure(){
  if(currFigure > 2)
    currFigure = 0;
  char figure = figures[currFigure];
  switch(figure){
  case 'T':
    drawTriangle(COLOR_BLACK, 30, fCol, fRow);
    break;
  case 'A':
    drawAsterisc(COLOR_BLACK, 30, fCol, fRow);
    break;
  case 'S':
    drawSquare(COLOR_BLACK, 30, fCol, fRow);
    break;
  }
  currFigure++;
}

void fourCornersState(){
  if(change > 3)
    change = 0;
  if (change == 0){
    fCol = 5;
    fRow = 5;
  }
  else if(change == 1){
    fCol = 95;
    fRow = 5;
  }
  else if(change == 2){
    fCol = 95;
    fRow = 125;
  }
  else if(change == 3){
    fCol = 5;
    fRow = 125; 
  }
  changeFigure();
  change++;
}


void __interrupt_vec(WDT_VECTOR) WDT(){/* 250 interrupts/sec */

  static char blink_count = 0;
  if (++blink_count == 125) {
    if(state == 1){
      fourCornersState();
    }
    else if(state == 2){
      fCol = 50;
      fRow = 50;
      changeFigure();
    }
    else if(state == 3){
      drawSquare(COLOR_BLACK, 30, fCol, fRow);
    }
    else{
      clearScreen(COLOR_WHITE);
    }
    blink_count = 0;
  }
}
