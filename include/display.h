#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glut.h>

#include "carrom.h"

// display callback function used to redraw the scene
void display(void);

// reshape callback function scales the scene when window shape changes
void reshape(GLint width, GLint height);

// timer callback function used to refresh the positions of coins
void trigger(int value);

// display the static parts of a scene such as the board and its edges
void carromBoard(void);

// display the current positions of the carrom coins
void carromCoins(struct GameState *gameState);

// displaying the direction in which the striker must be struck
void strikerDirection(struct GameState *gameState);

// display the power reader that shows the force applied to the striker
void powerReader(struct GameState *gameState);

// display the scores obtained by either team during their individual turns
void scoreBoard(struct BoardStatus *boardStatus);

// display the team and player number while it is their turn
void teamTurnPanel(struct BoardStatus *boardStatus);

#endif
