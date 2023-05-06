#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glut.h>

// display callback function used to redraw the scene
void display(void);

// timer callback function used to refresh the positions of coins
void trigger(int value);

// reshape callback function scales the scene when window shape changes
void reshape(GLint width, GLint height);

// display the static parts of a scene such as the board and its edges
void board(void);

// display the current positions of the carrom coins
void coins(void);

// displaying the direction in which the striker must be struck
void strikerDirection(void);

// display the power reader that shows the force applied to the striker
void powerReader(void);

#endif
