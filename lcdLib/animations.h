#ifndef animations_included
#define animations_include

int state;
static int fCol;
static int fRow;
int machine;

void changeFigureState();
void fourCorners();
void squareMove();
void squareGoRight();
void squareGoDown();
void squareGoLeft();
void squareGoUp();

void toggleLeds();

void callBuzzer();
void buzzerGoDown();
void buzzerGoUp();

void currentStateMachine();

#endif
