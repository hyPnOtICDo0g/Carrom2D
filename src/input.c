#include <math.h>
#include <GL/freeglut.h>

#include "input.h"
#include "scene.h"
#include "context.h"
#include "physics.h"
#include "utilities.h"

void keyboard(unsigned char key, int x, int y) {
	UNUSED(x); UNUSED(y);
	// treat the exit process separately as it is independent of the striker's state
	if(key == ESC) {
		glutLeaveMainLoop();
		return;
	}
	// handle game input only if striker is stationary
	if(state->strikerState) {
		switch(key) {
			case 'a':
				shiftStrikerLeft(state, start);
				break;

			case 'd':
				shiftStrikerRight(state, start);
				break;

			case SPACE:
				hitStriker(state);
				break;

		}
	}
}

void joystick(unsigned int buttonMask, int x, int y, int z) {
	UNUSED(z);
	if(state->strikerState) {
		if(buttonMask & GLUT_JOYSTICK_LEFT_BUMPER) {
			shiftStrikerLeft(state, start);
		}
		if(buttonMask & GLUT_JOYSTICK_RIGHT_BUMPER) {
			shiftStrikerRight(state, start);
		}
		if(buttonMask & GLUT_JOYSTICK_BUTTON_B) {
			hitStriker(state);
		}
		if(buttonMask & GLUT_JOYSTICK_BUTTON_D) {
			increaseStrikerPower(state);
		}
		if(buttonMask & GLUT_JOYSTICK_BUTTON_A) {
			decreaseStrikerPower(state);
		}
		if (x && y) {
			// calculate the angle of the striker based on the joystick's x and y axis
			state->theta = RADIANS_PER_DEGREE * atan2(-y, x);
		}
	}
}

void special(int key, int x, int y) {
	UNUSED(x); UNUSED(y);
	// handle input only if striker is stationary
	if(state->strikerState) {
		switch(key) {
			// increase the angle of the striker
			case GLUT_KEY_LEFT:
				state->theta += 1;
				break;
			// decrease the angle of the striker
			case GLUT_KEY_RIGHT:
				state->theta -= 1;
				break;
			// increase the power
			case GLUT_KEY_UP:
				increaseStrikerPower(state);
				break;
			// decrease the power
			case GLUT_KEY_DOWN:
				decreaseStrikerPower(state);
				break;
		}
	}
}
