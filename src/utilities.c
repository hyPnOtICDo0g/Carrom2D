#include <stdlib.h>

#include "carrom.h"
#include "utilities.h"

void copyCoinArrays(struct Coin *coinsTo, struct Coin *coinsFrom, int size) {
	int i;
	for(i = 0; i < size; i++) {
		coinsTo[i] = coinsFrom[i];
	}
}

void memCheck(void *ptr) {
	if(ptr == NULL) {
		// printf("warning: insufficient memory\n");
		exit(1);
	}
}

int numActiveWhite(struct Coin *coins) {
	int i, count = 0;
	for(i = 0; i < (MAX_COIN_COUNT - 2) / 2; i++) {
		if(coins[i].state == 1) {
			count += 1;
		}
	}
	return count;
}


int numActiveBlack(struct Coin *coins) {
	int i, count = 0;
	for(i = (MAX_COIN_COUNT - 2) / 2; i < (MAX_COIN_COUNT - 2); i++) {
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
