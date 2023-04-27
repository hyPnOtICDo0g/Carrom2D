#include <math.h>
#include <pthread.h>
#include <GL/glut.h>

#include "scene.h"
#include "carrom.h"

struct GameState state;

int main(int argc, char **argv) {
	pthread_t createScene;
	struct CmdArgs threadData;
	threadData.argc = argc;
	threadData.argv = argv;
	// create a new shared game state
	state = *createNewGameState();
	// create a game scene by spawning a new thread
	pthread_create(&createScene, NULL, initScene, (void *) &threadData);
	pthread_join(createScene, NULL);
	return 0;
}
