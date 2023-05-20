#include <stdlib.h>
#include <GL/glut.h>

#include "scene.h"
#include "carrom.h"
#include "context.h"
#include "drawable.h"
#include "utilities.h"

void copyCoinArrays(struct Coin *coinsFrom, struct Coin *coinsTo, int size) {
	for(int i = 0; i < size; i++) {
		coinsTo[i] = coinsFrom[i];
	}
}

void memCheck(void *ptr) {
	if(ptr == NULL) {
		exit(1);
	}
}

int numActiveWhite(struct Coin *coins) {
	int count = 0;
	for(int i = 0; i < (MAX_COIN_COUNT - 2) / 2; i++) {
		if(coins[i].state == 1) {
			count += 1;
		}
	}
	return count;
}


int numActiveBlack(struct Coin *coins) {
	int count = 0;
	for(int i = (MAX_COIN_COUNT - 2) / 2; i < (MAX_COIN_COUNT - 2); i++) {
		if(coins[i].state == 1) {
			count += 1;
		}
	}
	return count;
}

int isQueenActive(struct Coin *coins) {
	if(coins[MAX_COIN_COUNT - 2].state == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

void exitCurrentGame(void) {
	free(state->coins);
	free(start->coins);
	free(start);
	free(state);
}

void restartGame(int players) {
	// -1 indicates a regular restart with the same number of players
	if(players == -1) {
		players = state->numberOfPlayers + 1;
	}
	exitCurrentGame();
	state = createNewGameState();
	start = initNewGame(state, players - 1);
}
