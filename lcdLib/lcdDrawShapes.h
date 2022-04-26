#ifndef lcdDrawShapes_included
#define lcdDrawShapes_included

/** Draw Triangle
 *
 * \param color Color of triangle
 * \param length Length of triangle
 */
void drawTriangle(u_int color, int length, int fCol, int fRow);

/** Draw an Asterisc
 *
 * \param color Color of Asteric
 * \param length Length of asterisc
 */
void drawAsterisc(u_int color, int length, int fCol, int fRow);

/** Draw a square
 *
 * \param color Color of the square
 * \param length Length of the square
 */
void drawSquare(u_int color, int length, int fCol, int fRow);
/*
static int fCol;
static int fRow;
*/
#endif
