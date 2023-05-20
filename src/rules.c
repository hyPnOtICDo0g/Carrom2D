#include <stdbool.h>

#include "rules.h"
#include "scene.h"
#include "carrom.h"
#include "utilities.h"

void initNewTurn(struct GameState *gameState, struct BoardStatus *start) {
	int currentTeam = start->currentTeam, initialPoints, finalPoints;
	struct Coin *initialCoins = start->coins, *finalCoins = gameState->coins;

	// check the state of the striker
	if(finalCoins[MAX_COIN_COUNT - 1].state == 0) {
		/*
			If the striker is found to be in the pot, subtract one point
			from the current team's score and remove all coins scored at that shot.
		*/
		if(currentTeam == 1) {
			start->pointsTeamOne -= STRIKER_POINT_LOSS;
		}
		else {
			start->pointsTeamTwo -= STRIKER_POINT_LOSS;
		}

		// determine if the score is negative
		if(start->pointsTeamOne < 0) {
			// if the condition is true, then set it to zero
			start->pointsTeamOne = 0;
		}

		if(start->pointsTeamTwo < 0) {
			start->pointsTeamTwo = 0;
		}

		revertCoinsOnFoul(initialCoins, finalCoins);
		finalize(gameState, start, false);
	}
	// if the striker is not found to be in the pot
	else {
		if(currentTeam == 1) {
			initialPoints = start->pointsTeamOne;
			// add points obtained from each coin to the total score
			start->pointsTeamOne += MAX_BLACK_POINTS * (numActiveBlack(initialCoins) - numActiveBlack(finalCoins));
			start->pointsTeamOne += MAX_WHITE_POINTS * (numActiveWhite(initialCoins) - numActiveWhite(finalCoins));
			start->pointsTeamOne += MAX_QUEEN_POINTS * (isQueenActive(initialCoins) - isQueenActive(finalCoins));
			finalPoints = start->pointsTeamOne;
		}
		else {
			initialPoints = start->pointsTeamTwo;
			start->pointsTeamTwo += MAX_BLACK_POINTS * (numActiveBlack(initialCoins) - numActiveBlack(finalCoins));
			start->pointsTeamTwo += MAX_WHITE_POINTS * (numActiveWhite(initialCoins) - numActiveWhite(finalCoins));
			start->pointsTeamTwo += MAX_QUEEN_POINTS * (isQueenActive(initialCoins) - isQueenActive(finalCoins));
			finalPoints = start->pointsTeamTwo;
		}

		if(initialPoints == finalPoints) {
			finalize(gameState, start, false);
		}
		else {
			finalize(gameState, start, true);
		}
	}
}

void revertCoinsOnFoul(struct Coin *initialCoins, struct Coin *finalCoins) {
	for(int i = 0; i < MAX_COIN_COUNT - 1; i++) {
		if(initialCoins[i].state != finalCoins[i].state) {
			finalCoins[i].state = 1;
			finalCoins[i].velocity.x = 0;
			finalCoins[i].velocity.y = 0;
			finalCoins[i].center.x = (float) (((i + 1) % 2 - (i % 4)) * ((i + 1) % 2) * 2 * (1 + (i / 4)) * COIN_RADIUS);
			finalCoins[i].center.y = (float) ((i % 2 - (i + 3) % 4)) * ((i % 2) * 2 * (1 + (i / 4)) * COIN_RADIUS);
		}
	}
}

void finalize(struct GameState *gameState, struct BoardStatus *start, bool strikerState) {
	struct Coin *coins = gameState->coins;
	int numberOfCoinsLeft = numActiveWhite(coins) + numActiveBlack(coins) + isQueenActive(coins);
	// if either team scores more than 50 points, initiate a game reset
	if(start->pointsTeamOne > 50 || start->pointsTeamTwo > 50) {
		restartGame(-1);
		return;
	}
	// if all coins are scored, then number of coins on the board is zero
	if(numberOfCoinsLeft == 0) {
		initNewBoard(gameState, start);
		return;
	}
	else {
		int numberOfPlayers = gameState->numberOfPlayers;
		int turn = start->turn;
		/*
			The striker state can be false if:
			- it is found to be in the pot
			- the player has not scored any points
		*/
		if(strikerState == false) {
			if(numberOfPlayers == 0) {
				turn = 0;
			}
			else if(numberOfPlayers < 3) {
				turn = (turn + 2) % 4;
				start->currentTeam = (int) (turn / 2) + 1;
			}
			else {
				turn = (turn + 1) % 4;
				start->currentTeam = (turn % 2) + 1;
			}
		}
		// update the turn for the next player
		start->turn = turn;
		// set the striker's position based on the turn calculated
		initStriker(gameState, turn);
		// copy the updated position of the coins
		copyCoinArrays(gameState->coins, start->coins, MAX_COIN_COUNT);
	}
}
