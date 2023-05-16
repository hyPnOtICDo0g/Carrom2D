#include <stdlib.h>
#include <GL/glut.h>

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
	// create a new empty game scene
	start = initNewGame(state);
	// initialize the GLUT library
	glutInit(&argc, argv);
	// register memory cleanup handler
	atexit(exitCurrentGame);
	// using two buffers to achieve smoother animation
	// enable multisample anti-aliasing (MSAA) to reduce jaggies
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
	glutCreateWindow("Multiplayer Carrom");
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
