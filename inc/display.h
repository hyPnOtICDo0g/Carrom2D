#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glut.h>

// display callback function is used to redraw the scene
void display(void);

// timer callback function is used to refresh the positions of coins
void trigger(int value);

// reshape callback function scales the scene when window shape changes
void reshape(GLint width, GLint height);

#endif
