#include <math.h>

#include "carrom.h"
#include "context.h"
#include "physics.h"

void hitStriker(void) {
	int currentPower = state.currentPower;
	float theta = state.theta;
	struct Coin *coins = state.coins;
	// update striker state to zero as it is in action
	state.strikerState = 0;
	coins[MAX_COIN_COUNT - 1].velocity.x = currentPower * cos((theta / 360.0) * 2 * M_PI);
	coins[MAX_COIN_COUNT - 1].velocity.y = currentPower * sin((theta / 360.0) * 2 * M_PI);
}
