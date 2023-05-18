#include <stdlib.h>
#include <GL/glut.h>

#include "menu.h"
#include "input.h"
#include "scene.h"
#include "carrom.h"
#include "physics.h"
#include "display.h"
#include "utilities.h"

struct GameState *state;
struct BoardStatus *start;

int main(int argc, char **argv) {
	// create a new shared game state
	state = createNewGameState();
	// create a new empty game scene with the default setting of two players (0 and 1)
	start = initNewGame(state, 1);
	// initialize the GLUT library
	glutInit(&argc, argv);
	// register memory cleanup handler
	atexit(exitCurrentGame);
	// using two buffers to achieve smoother animation
	// enable multisample anti-aliasing (MSAA) to reduce jaggies
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
	/*
		Although `glutFullScreen` is currently being utilized,
		the following line is retained for the reshape function
		and potential future usage, such as providing the user
		with the option to personalize the window size.
	*/
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutCreateWindow("Multiplayer Carrom");
	// create game menu
	createGameMenu();
	// register callback functions
	glutDisplayFunc(display);
	glutTimerFunc(TRIGGER, trigger, VELOCITY);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	// poll the joystick for button input once every 16ms
	glutJoystickFunc(joystick, 16);
	glutFullScreen();
	glutMainLoop();
	return 0;
}
