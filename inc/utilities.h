#ifndef UTILITIES_H
#define UTILITIES_H

// check if sufficient memory is available, else terminate
void memCheck(void *ptr);

// utility to deep copy a coin array
void copyCoinArrays(struct Coin *coinsFrom, struct Coin *CoinsTo, int size);

// determine if the queen is in a pot or not
int isQueenActive(struct Coin *coins);

// return the number of active black coins
int numActiveBlack(struct Coin *coins);

// return the number of active white coins
int numActiveWhite(struct Coin *coins);

#endif
