#ifndef SCENE_H
#define SCENE_H

#include "carrom.h"

/* OpenGL Constants */

#define INITIAL_WINDOW_WIDTH 800
#define INITIAL_WINDOW_HEIGHT 700
#define BOARD_SCALING_FACTOR 0.75	// one constant to scale the entire board

// an additional struct definition for storing command-line arguments
struct CmdArgs {
	int argc;
	char **argv;
};

// allocate memory for the global game state
struct GameState *createNewGameState(void);

// set the initial characteristics of the striker based on the turn value
void initStriker(struct GameState *gameState, int turn);

// initialize the positions and velocities of the coins on the board
void initCarromCoins(struct GameState *gameState);

// set the necessary game variables to start a new game
struct BoardStatus *initNewGame(struct GameState *gameState);

// the start routine passed to pthread_create() which creates a scene with all game objects
void *initScene(void *args);

#endif
