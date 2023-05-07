#include <GL/glut.h>

#ifdef _WIN32
	#include <stdlib.h>
#endif

#include "input.h"
#include "scene.h"
#include "carrom.h"
#include "physics.h"
#include "display.h"
#include "utilities.h"

struct GameState state;
struct BoardStatus start;

int main(int argc, char **argv) {
	// create a new shared game state
	state = *createNewGameState();
	// create a new empty game scene
	start = *initNewGame(&state);
	// initialize the GLUT library
	#ifdef _WIN32
		/*
			The use of WinMain was dropped in favor of this alternative
			due to compilation issues, and this alternative gives access
			to main-ish argc and argv in graphical Windows applications.
		*/
		UNUSED(argc); UNUSED(argv);
		glutInit(&__argc, __argv);
	#else
		glutInit(&argc, argv);
	#endif
	// using two buffers to achieve smoother animation
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT);
	glutCreateWindow("Multiplayer Carrom");
	// blends incoming pixels with the existing pixels in the frame buffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// enable anti-aliasing to reduce jaggies
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	// register callback functions
	glutDisplayFunc(display);
	glutTimerFunc(TRIGGER, trigger, VELOCITY);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	// poll the joystick for button input once every 16ms
	glutJoystickFunc(joystick, 16);
	glutMainLoop();
	return 0;
}
