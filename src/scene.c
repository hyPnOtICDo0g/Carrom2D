#include "input.h"
#include "scene.h"
#include "carrom.h"
#include "display.h"
#include "physics.h"
#include "utilities.h"

struct BoardStatus start;

struct GameState *createNewGameState(void) {
	// allocate memory for six coins
	struct Coin *coins = (struct Coin *) malloc(MAX_COIN_COUNT * sizeof(struct Coin));
	// allocate memory for global game state
	struct GameState *gameState = (struct GameState *) malloc(sizeof(struct GameState));
	memCheck(gameState); memCheck(coins);
	gameState->coins = coins;
	return gameState;
}

void initStriker(struct GameState *gameState, int turn) {
	struct Coin *coins = gameState->coins;
	// set the angle the striker is facing to 90 degrees
	float theta = 90.0 * ((1 + turn) % 4);
	// set the striker at the side of the player who goes first
	coins[MAX_COIN_COUNT - 1].center.x = (turn % 2) * (2 - turn) * ((1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.00)));
	coins[MAX_COIN_COUNT - 1].center.y = -((turn + 1) % 2) * (1 - turn) * ((1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.00)));
	coins[MAX_COIN_COUNT - 1].velocity.x = 0;
	coins[MAX_COIN_COUNT - 1].velocity.y = 0;
	// striker is initially stationary
	coins[MAX_COIN_COUNT - 1].state = 1;
	coins[MAX_COIN_COUNT - 1].mass = STRIKER_MASS;
	coins[MAX_COIN_COUNT - 1].radius = STRIKER_RADIUS;
	gameState->theta = theta;
}

void initCarromCoins(struct GameState *gameState) {
	int i; struct Coin *coins = gameState->coins;

	// placing the queen at the center of the board
	coins[MAX_COIN_COUNT - 2].center.x = 0;
	coins[MAX_COIN_COUNT - 2].center.y = 0;

	// place the rest of the coins within the central circle
	for(i = 0; i < MAX_COIN_COUNT - 2; i++) {
		// coordinate representation of the coins' placement
		/*
			. . . + . . .
			. . . + . . .
			. . . W . . .
			+ + B Q W + +
			. . . B . . .
			. . . + . . .
			. . . + . . .
		*/
		coins[i].center.x = (float) (((i + 1) % 2 - (i % 4)) * ((i + 1) % 2) * 2 * (1 + (i / 4)) * COIN_RADIUS);
		coins[i].center.y = (float) ((i % 2 - (i + 3) % 4)) * ((i % 2) * 2 * (1 + (i / 4)) * COIN_RADIUS);
	}

	for(i = 0; i < MAX_COIN_COUNT - 1; i++) {
		coins[i].velocity.x = 0;
		coins[i].velocity.y = 0;
		// coins are initially on the board
		coins[i].state = 1;
		coins[i].mass = COIN_MASS;
		coins[i].radius = COIN_RADIUS;
	}
}

struct BoardStatus *initNewGame(struct GameState *gameState) {
	struct Coin *coins = (struct Coin *) malloc(MAX_COIN_COUNT * sizeof(struct Coin));
	struct BoardStatus *boardStatus = (struct BoardStatus *) malloc(sizeof(struct BoardStatus));
	memCheck(coins); memCheck(boardStatus);
	// `boardStatus` requires a copy of the coin array
	copyCoinArrays(coins, gameState->coins, MAX_COIN_COUNT);
	gameState->glWidth = INITIAL_WINDOW_WIDTH;
	gameState->glHeight = INITIAL_WINDOW_HEIGHT;
	// striker is initially stationary
	gameState->strikerState = 1;
	gameState->currentPower = 0;
	gameState->numberOfPlayers = 4;

	initCarromCoins(gameState);
	initStriker(gameState, 0);

	boardStatus->turn = 0;
	boardStatus->currentTeam = 1;
	boardStatus->pointsTeamOne = 0;
	boardStatus->pointsTeamTwo = 0;
	boardStatus->coins = coins;
	return boardStatus;
}

void *initScene(void *args) {
	struct BoardStatus *init = initNewGame(&state);
	start = *init;
	glutInit(&(((struct CmdArgs *) args)->argc), ((struct CmdArgs *) args)->argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT);
	glutCreateWindow("Multiplayer Carrom");
	glutDisplayFunc(display);
	glutTimerFunc(TRIGGER, trigger, VELOCITY);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return NULL;
}
