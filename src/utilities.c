#include <stdlib.h>

#include "carrom.h"
#include "utilities.h"

void copyCoinArrays(struct Coin *CoinsTo, struct Coin *coinsFrom, int size) {
	int i;
	for(i = 0; i < size; i++) {
		CoinsTo[i] = coinsFrom[i];
	}
}

void memCheck(void *ptr) {
	if(ptr == NULL) {
		// printf("warning: insufficient memory\n");
		exit(1);
	}
}
