#include <math.h>

#include "carrom.h"
#include "context.h"
#include "physics.h"

void hitStriker(struct GameState *gameState) {
	int currentPower = gameState->currentPower;
	float theta = gameState->theta;
	struct Coin *coins = gameState->coins;
	// update striker state to zero as it is in action
	gameState->strikerState = 0;
	coins[MAX_COIN_COUNT - 1].velocity.x = currentPower * cos((theta / 360.0) * 2 * M_PI);
	coins[MAX_COIN_COUNT - 1].velocity.y = currentPower * sin((theta / 360.0) * 2 * M_PI);
}

void coinCollision(int i, int j, struct Coin *coins) {
	// x and y coordinates
	float x1 = coins[i].center.x;
	float y1 = coins[i].center.y;
	float x2 = coins[j].center.x;
	float y2 = coins[j].center.y;

	// velocities in x and y direction
	float vx1 = coins[i].velocity.x;
	float vy1 = coins[i].velocity.y;
	float vx2 = coins[j].velocity.x;
	float vy2 = coins[j].velocity.y;

	// radius of the ith and jth coins
	float radius1 = coins[i].radius;
	float radius2 = coins[j].radius;

	// mass of the ith and jth coins
	float mass1 = coins[i].mass;
	float mass2 = coins[j].mass;

	if((vx1 == vx2) && (vy1 == vy2)) {
		// collision not possible due to equal velocities
		return;
	}
	// calculate distance between the centers of the two coins
	float centerDistance = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));

	if(centerDistance > radius1 + radius2) {
		// the absence of distance makes a collision impossible
		return;
	}
	else {
		// calculate the relative velocities of the two coins before the collision
		float u1 = ((x2 - x1) * vx1 + (y2 - y1) * vy1) / centerDistance;
		float u2 = ((x1 - x2) * vx2 + (y1 - y2) * vy2) / centerDistance;
		/*
			Calculate the new velocities of the two coins after the collision,
			which is done using the conservation of momentum and energy equations.
		*/
		float vr1 = (mass2 * (RESTITUITION * (u1 + u2)) + mass2 * u2 - mass1 * u1) / (mass1 + mass2);
		float vr2 = (mass1 * (RESTITUITION * (u2 + u1)) + mass1 * u1 - mass2 * u2) / (mass1 + mass2);
		// relative velocities must be in the same direction
		if(u1 + u2 > 0) {
			// use the previously calculated initial relative velocities
			float vr1xi = ((x2 - x1) * u1) / centerDistance;
			float vr1yi = ((y2 - y1) * u1) / centerDistance;
			float vr2xi = ((x1 - x2) * u2) / centerDistance;
			float vr2yi = ((y1 - y2) * u2) / centerDistance;
			// calculate the final relative velocities after the collision
			float vr1x = -((x2 - x1) * vr1) / centerDistance;
			float vr1y = -((y2 - y1) * vr1) / centerDistance;
			float vr2x = -((x1 - x2) * vr2) / centerDistance;
			float vr2y = -((y1 - y2) * vr2) / centerDistance;
			// update the velocities of the coins
			coins[i].velocity.x = (vx1 - vr1xi) + vr1x;
			coins[i].velocity.y = (vy1 - vr1yi) + vr1y;
			coins[j].velocity.x = (vx2 - vr2xi) + vr2x;
			coins[j].velocity.y = (vy2 - vr2yi) + vr2y;
		}
		else {
			return;
		}
	}
}

void coinPotFall(int i, struct Coin *coins) {
	float x1 = coins[i].center.x;
	float y1 = coins[i].center.y;
	float pot = 1 - POT_CIRCLE_RADIUS;

	// calculate the distance between the coin's center and the four pot locations
	float centerDistanceTr = sqrt(((x1 - pot) * (x1 - pot)) + ((y1 - pot) * (y1 - pot)));
	float centerDistanceTl = sqrt(((x1 + pot) * (x1 + pot)) + ((y1 - pot) * (y1 - pot)));
	float centerDistanceBr = sqrt(((x1 - pot) * (x1 - pot)) + ((y1 + pot) * (y1 + pot)));
	float centerDistanceBl = sqrt(((x1 + pot) * (x1 + pot)) + ((y1 + pot) * (y1 + pot)));

	// check if the coin is active
	if(coins[i].state == 1) {
		if(centerDistanceTr <= POT_CIRCLE_RADIUS) {
			// coin is considered to have fallen into the pot
			coins[i].center.x = pot;
			coins[i].center.y = pot;
		}
		else if(centerDistanceTl <= POT_CIRCLE_RADIUS) {
			coins[i].center.x = -1 * pot;
			coins[i].center.y = pot;
		}
		else if(centerDistanceBr <= POT_CIRCLE_RADIUS) {
			coins[i].center.x = pot;
			coins[i].center.y = -1 * pot;
		}
		else if(centerDistanceBl <= POT_CIRCLE_RADIUS) {
			coins[i].center.x = -1 * pot;
			coins[i].center.y = -1 * pot;
		}
		else {
			// it will not fall into any pot
			return;
		}
		coins[i].velocity.x = 0.0;
		coins[i].velocity.y = 0.0;
		coins[i].state = 0;
	}
	else {
		// it has already fallen into a pot
		return;
	}
}

void wallCollision(int i, struct Coin *coins) {
	float x1 = coins[i].center.x;
	float y1 = coins[i].center.y;
	// check if the coin has collided with either the left or right wall
	if(fabs(x1) >= (1 - coins[i].radius)) {
		// if the coin has collided with the left wall
		if(coins[i].center.x < 0) {
			// move the coin just outside the left wall
			coins[i].center.x = -(1 - coins[i].radius);
		}
		// if the coin has collided with the right wall
		if(coins[i].center.x > 0) {
			// move the coin just outside the right wall
			coins[i].center.x = (1 - coins[i].radius);
		}
		// simulate the loss of energy during the collision
		coins[i].velocity.x = RESTITUITION * -1 * coins[i].velocity.x;
	}
	// check if the coin has collided with either the top or bottom wall
	else if(fabs(y1) >= (1 - coins[i].radius)) {
		// the rest resembles the above code
		if(coins[i].center.y < 0) {
			coins[i].center.y = -(1 - coins[i].radius);
		}
		if(coins[i].center.y > 0) {
			coins[i].center.y = (1 - coins[i].radius);
		}
		coins[i].velocity.y = RESTITUITION * -1 * coins[i].velocity.y;
	}
	else {
		// collision with wall not possible
		return;
	}
}
