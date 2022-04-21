#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

void drawTriangle(u_int color, int length){

  clearScreen(COLOR_WHITE);
  int fCol = 50, fRow = 50;
  for (int a = 0; a < length; a++){
    drawPixel(fCol + a, fRow + a, color);
    drawPixel(fCol + length, fRow + a, color);
    drawPixel(fCol + a, fRow, color);
    
    if(a%2 == 1){
      for(int v = 0; v < a; v++){
	// Vertical lines within the triangle
	drawPixel(fCol + a, fRow + v, color);
	// Horizontal lines within the triangle
	drawPixel(fCol - v + length, fRow - a + length, color);
      }
    }
  }
}

void drawAsterisc(u_int color, int length){

  clearScreen(COLOR_WHITE);
  int fCol = 50, fRow = 50;
  for ( int a = 0; a < length; a++){
    drawPixel(fCol + a, fRow + a, color);
    drawPixel(fCol + (length / 2), fRow + a, color);
    drawPixel(fCol + a, fRow + (length / 2), color);
    drawPixel(fCol + a, fRow - a + length, color);
  }
}

void drawSquare(u_int color, int length){
  clearScreen(COLOR_WHITE);
  int fCol = 50, fRow = 50;
  for ( int a = 0; a < length; a++){
    drawPixel(fCol + a, fRow, color);
    drawPixel(fCol + a, fRow + length, color);
    drawPixel(fCol, fRow + a, color);
    drawPixel(fCol + length, fRow + a, color);    
  }
}
