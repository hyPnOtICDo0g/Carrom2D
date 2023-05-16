#ifndef UTILITIES_H
#define UTILITIES_H

#include <GL/glut.h>

#include "carrom.h"

// circumvent compiler warnings for unused variables in callback functions
#define UNUSED(x) (void)(x)

// check if sufficient memory is available, else terminate
void memCheck(void *ptr);

// gracefully exit the game
void exitCurrentGame(void);

// utility to deep copy a coin array
void copyCoinArrays(struct Coin *coinsFrom, struct Coin *coinsTo, int size);

// determine if the queen is in a pot or not
int isQueenActive(struct Coin *coins);

// return the number of active black coins
int numActiveBlack(struct Coin *coins);

// return the number of active white coins
int numActiveWhite(struct Coin *coins);

// fill circles with suitable colors on the board
void drawCircleFilled(GLfloat radius, GLfloat centerX, GLfloat centerY, GLint cda);

// draw a circular outline that spans between two points
void drawCircleOutline(GLfloat radius, GLfloat centerX, GLfloat centerY, GLint cda, GLint pointOne, GLint pointTwo);

#endif
