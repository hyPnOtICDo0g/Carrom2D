#ifndef UTILITIES_H
#define UTILITIES_H

// check if sufficient memory is available, else terminate
void memCheck(void *ptr);

// utility to deep copy a coin array
void copyCoinArrays(struct Coin *coinsFrom, struct Coin *CoinsTo, int size);

#endif
