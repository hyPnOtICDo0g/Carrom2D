#include <math.h>

#include "scene.h"
#include "carrom.h"
#include "physics.h"
#include "utilities.h"

struct GameState *createNewGameState(void) {
	// allocate memory for six coins
	struct Coin *coins = (struct Coin *) malloc(MAX_COIN_COUNT * sizeof(struct Coin));
	// allocate memory for global game state
	struct GameState *gameState = (struct GameState *) malloc(sizeof(struct GameState));
	memCheck(gameState); memCheck(coins);
	gameState->coins = coins;
	return gameState;
}

void initNewBoard(struct GameState *gameState, struct BoardStatus *start) {
	initCarromCoins(gameState);
	start->turn = 0;
	start->currentTeam = 1;
	initStriker(gameState, start->turn);
	copyCoinArrays(gameState->coins, start->coins, MAX_COIN_COUNT);
}

void initStriker(struct GameState *gameState, int turn) {
	struct Coin *coins = gameState->coins;
	// set the angle the striker is facing, to 90 degrees
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

struct BoardStatus *initNewGame(struct GameState *gameState, int players) {
	struct Coin *coins = (struct Coin *) malloc(MAX_COIN_COUNT * sizeof(struct Coin));
	struct BoardStatus *boardStatus = (struct BoardStatus *) malloc(sizeof(struct BoardStatus));
	memCheck(coins); memCheck(boardStatus);
	// `boardStatus` requires a copy of the coin array
	// striker is initially stationary
	gameState->strikerState = 1;
	gameState->currentPower = MIN_POWER_READER;
	gameState->numberOfPlayers = players;

	initCarromCoins(gameState);
	initStriker(gameState, 0);
	copyCoinArrays(gameState->coins, coins, MAX_COIN_COUNT);

	boardStatus->turn = 0;
	boardStatus->currentTeam = 1;
	boardStatus->pointsTeamOne = 0;
	boardStatus->pointsTeamTwo = 0;
	boardStatus->coins = coins;
	return boardStatus;
}

void shiftStrikerLeft(struct GameState *gameState, struct BoardStatus *start) {
	int turn = start->turn;
	struct Coin *coins = gameState->coins;
	// set striker boundary upto the red dot
	float strikerBoundary = 1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE;
	// for players with turns 0 and 2 (actual turns are 1 and 3)
	if(turn % 2 == 0) {
		/*
			If the striker is within it's boundary, shift it by increments of 0.02
			based on a player's turn (the side of the board it is placed on).
		*/
		if(fabs(coins[MAX_COIN_COUNT - 1].center.x) <= strikerBoundary) {
			coins[MAX_COIN_COUNT - 1].center.x -= (1 - turn) * 0.02;
		}
		else {
			// if a player attempts to cause the striker to go out of bounds, prevent it
			if(coins[MAX_COIN_COUNT - 1].center.x > 0) {
				// the southern side of the board
				if(turn == 0) {
					coins[MAX_COIN_COUNT - 1].center.x -= 0.02;
				}
			}
			else {
				// the northern side of the board
				if(turn == 2) {
					coins[MAX_COIN_COUNT - 1].center.x += 0.02;
				}
			}
		}
	}
	// for players with turns 1 and 3 (actual turns are 2 and 4)
	else {
		if(fabs(coins[MAX_COIN_COUNT - 1].center.y) <= strikerBoundary) {
			coins[MAX_COIN_COUNT - 1].center.y -= (2 - turn) * 0.02;
		}
		else {
			if(coins[MAX_COIN_COUNT - 1].center.y > 0) {
				// the eastern side of the board
				if(turn == 1) {
					coins[MAX_COIN_COUNT - 1].center.y -= 0.02;
				}
			}
			else {
				// the western side of the board
				if(turn == 3) {
					coins[MAX_COIN_COUNT - 1].center.y += 0.02;
				}
			}
		}
	}
}

void shiftStrikerRight(struct GameState *gameState, struct BoardStatus *start) {
	int turn = start->turn;
	struct Coin *coins = gameState->coins;
	float strikerBoundary = 1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE;
	/*
		Reversing the mathematical operations (i.e. subtracting instead of adding) in the
		`shiftStrikerLeft` function, the striker can be moved to the right side of the board.
	*/
	if(turn % 2 == 0) {
		if(fabs(coins[MAX_COIN_COUNT - 1].center.x) <= strikerBoundary) {
			coins[MAX_COIN_COUNT - 1].center.x += (1 - turn) * 0.02;
		}
		else {
			if(coins[MAX_COIN_COUNT - 1].center.x < 0) {
				if(turn == 0) {
					coins[MAX_COIN_COUNT - 1].center.x += 0.02;
				}
			}
			else {
				if(turn == 2) {
					coins[MAX_COIN_COUNT - 1].center.x -= 0.02;
				}
			}
		}
	}
	else {
		if(fabs(coins[MAX_COIN_COUNT - 1].center.y) <= strikerBoundary) {
			coins[MAX_COIN_COUNT - 1].center.y += (2 - turn) * 0.02;
		}
		else {
			if(coins[MAX_COIN_COUNT - 1].center.y < 0) {
				if(turn == 1) {
					coins[MAX_COIN_COUNT - 1].center.y += 0.02;
				}
			}
			else {
				if(turn == 3) {
					coins[MAX_COIN_COUNT - 1].center.y -= 0.02;
				}
			}
		}
	}
}

void increaseStrikerPower(struct GameState *gameState) {
	if(gameState->currentPower == MAX_POWER_READER) {
		gameState->currentPower = MAX_POWER_READER;
	}
	else {
		gameState->currentPower += POWER_READER_VARIATION;
	}
}

void decreaseStrikerPower(struct GameState *gameState) {
	if(gameState->currentPower == MIN_POWER_READER) {
		gameState->currentPower = MIN_POWER_READER;
	}
	else {
		gameState->currentPower -= POWER_READER_VARIATION;
	}
}
