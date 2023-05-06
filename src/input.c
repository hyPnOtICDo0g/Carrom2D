#include <math.h>

#include "input.h"
#include "scene.h"
#include "context.h"
#include "physics.h"
#include "utilities.h"

void keyboard(unsigned char key, int x, int y) {
	UNUSED(x); UNUSED(y);
	// handle input only if striker is stationary
	if(state.strikerState) {
		switch(key) {
			case 'a':
				shiftStrikerLeft(&state, &start);
				break;

			case 'd':
				shiftStrikerRight(&state, &start);
				break;

			// space key to strike the striker
			case 32:
				hitStriker();
				break;
		}
	}
}

void joystick(unsigned int buttonMask, int x, int y, int z) {
	UNUSED(z);
	if(state.strikerState) {
		if(buttonMask & GLUT_JOYSTICK_LEFT_BUMPER) {
			shiftStrikerLeft(&state, &start);
		}
		if(buttonMask & GLUT_JOYSTICK_RIGHT_BUMPER) {
			shiftStrikerRight(&state, &start);
		}
		if(buttonMask & GLUT_JOYSTICK_BUTTON_A){
			hitStriker();
		}
		if (x && y){
			// calculate the angle of the striker based on the joystick's x and y axis
			state.theta = RADIANS_PER_DEGREE * atan2(-y, x);
		}
	}
}

void special(int key, int x, int y) {
	UNUSED(x); UNUSED(y);
	// handle input only if striker is stationary
	if(state.strikerState) {
		switch(key){
			// increase the angle of the striker
			case GLUT_KEY_LEFT:
				state.theta += 1;
				break;
			// decrease the angle of the striker
			case GLUT_KEY_RIGHT:
				state.theta -= 1;
				break;
		}
	}
}
