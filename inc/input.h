#ifndef INPUT_H
#define INPUT_H

#define ESC 27
#define SPACE 32

// LB and RB buttons on a Xbox 360 controller
#define GLUT_JOYSTICK_LEFT_BUMPER 0x0010
#define GLUT_JOYSTICK_RIGHT_BUMPER 0x0020

// keyboard callback function to handle keyboard input
void keyboard(unsigned char key, int x, int y);

// joystick callback function to handle game controller input
void joystick(unsigned int buttonMask, int x, int y, int z);

// special callback function to handle special key input, i.e. arrow keys
void special(int key, int x, int y);

#endif
