#ifndef INPUT_H
#define INPUT_H

// keyboard callback function to handle keyboard input
void keyboard(unsigned char key, int x, int y);

// joystick callback function to handle game controller input
void joystick(unsigned int buttonMask, int x, int y, int z);

#endif
