#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcdDrawShapes.h"
#include "led.h"
#include "buzzer.h"

int state = 0;
static int fCol = 0;
static int fRow = 0;

int change = 0;

static char figures[] = {'T','A','S'};
int currFigure = 0;

int figureLength = 30;

static int blinkLimit = 125;

static int secCount = 0;
void changeFigureState(){
  clearScreen(COLOR_WHITE);
  if(currFigure > 2)
    currFigure = 0;
  char figure = figures[currFigure];
  switch(figure){
  case 'T':
    drawTriangle(COLOR_BLACK, figureLength, fCol, fRow);
    break;
  case 'A':
    drawAsterisc(COLOR_BLACK, figureLength, fCol, fRow);
    break;
  case 'S':
    drawSquare(COLOR_BLACK, figureLength, fCol, fRow);
    break;
  }
  currFigure++;
}

void fourCorners(){
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
  //changeFigureState();
  change++;
}
int movement= 1;
void squareGoRight(){
  if(fCol++ > screenWidth - figureLength)
    movement++;
  for(int i = 0; i < figureLength; i++){
    drawPixel(fCol - 1, fRow + i, COLOR_WHITE);
  }
}
void squareGoDown(){
  if(fRow++ > screenHeight - figureLength)
    movement++;
  for(int i = 0; i < figureLength; i++){
    drawPixel(fCol + i, fRow - 1, COLOR_WHITE);
  }
}
void squareGoLeft(){
  if(0 > fCol--)
    movement++;
  for(int i = 0; i < figureLength; i++){
    drawPixel(fCol + figureLength, fRow + i, COLOR_WHITE);
  }
}
void squareGoUp(){
  if(0 > fRow--)
    movement++;
  for(int i = 0; i < figureLength; i++){
    drawPixel(fCol + i, fRow + figureLength, COLOR_WHITE);
  }
}
void squareMove(){
  fillRectangle(fCol, fRow, figureLength, figureLength, COLOR_BLACK);
  if(movement > 4)
    movement = 1;
  switch(movement){
  case 1:
    squareGoRight();
    break;
  case 2:
    squareGoDown();
    break;
  case 3:
    squareGoLeft();
    break;
  case 4:
    squareGoUp();
    break;
  }
}  
void toggleLeds(){
  P1OUT ^= leds;
}
/*
 * Siren with buzzer
 * callBuzzer()
 * buzzerGoDown()
 * buzzerGoUp() 
 */
int siren = 2000;
int goDown = 1;
void buzzerGoDown(){
buzzer_set_period(siren);
  if(siren < 1000)
    goDown = 0;
  siren -= 100;
}
void buzzerGoUp(){
  buzzer_set_period(siren);
  if(siren > 2000)
    goDown = 1;
  siren += 100;
}
void callBuzzer(){
  if(goDown)
    buzzerGoDown();
  else
    buzzerGoUp();
}
/*
 * Using diferent state machines
 */
void currentStateMachine(){
  switch(state){
  case 1:
    blinkLimit = 125;
    toggleLeds();
    buzzer_set_period(0);
    clearScreen(COLOR_WHITE);
    break;
  case 2:
    blinkLimit = 125;
    P1OUT &= ~leds;
    callBuzzer();
    clearScreen(COLOR_WHITE);
    break;
  case 3:
    blinkLimit = 5;
    P1OUT &= ~leds;
    buzzer_set_period(0);
    squareMove();
    //fourCorners();
    break;
  case 4:
    blinkLimit = 125;
    P1OUT &= ~leds;
    buzzer_set_period(0);
    clearScreen(COLOR_WHITE);
    break;
  }
}

void __interrupt_vec(WDT_VECTOR) WDT(){/* 250 interrupts/sec */
  static char blink_count = 0;

  if (++blink_count == blinkLimit) {    
    currentStateMachine();
    blink_count = 0;
  }
}
