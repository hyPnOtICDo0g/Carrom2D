#ifndef RULES_H
#define RULES_H

#include <stdbool.h>

#include "carrom.h"

// decide the next turn based on carrom rules
void initNewTurn(struct GameState *gameState, struct BoardStatus *start);

// revert the coin positions to their initial state on a foul, i.e. the striker falls into a pot
void revertCoinsOnFoul(struct Coin *initialCoins, struct Coin *finalCoins);

// update the board state once a player has completed their turn
void finalize(struct GameState *gameState, struct BoardStatus *start, bool strikerState);

#endif
