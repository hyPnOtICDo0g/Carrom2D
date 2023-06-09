#ifndef SCENE_H
#define SCENE_H

#include "carrom.h"

// allocate memory for the global game state
struct GameState *createNewGameState(void);

// set the initial characteristics of the striker based on the turn value
void initStriker(struct GameState *gameState, int turn);

// initialize the positions and velocities of the coins on the board
void initCarromCoins(struct GameState *gameState);

// initialize a new board state with all objects in their initial positions
void initNewBoard(struct GameState *gameState, struct BoardStatus *status);

// set the necessary game variables to start a new game
struct BoardStatus *initNewGame(struct GameState *gameState, int players);

// shift striker to the left side of the board
void shiftStrikerLeft(struct GameState *gameState, struct BoardStatus *status);

// shift striker to the right side of the board
void shiftStrikerRight(struct GameState *gameState, struct BoardStatus *status);

// increase the power with which the striker is hit
void increaseStrikerPower(struct GameState *gameState);

// decrease the power with which the striker is hit
void decreaseStrikerPower(struct GameState *gameState);

#endif
