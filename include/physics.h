#ifndef PHYSICS_H
#define PHYSICS_H

#include "carrom.h"

/* PHYSICS CONSTANTS */

#define G 9.80
#define FRICTION 3.0		// board friction coefficient
#define COIN_MASS 5.25
#define RESTITUITION 1		// board restitution coefficient
#define STRIKER_MASS 15		// striker mass in grams

/*
	The speed at which the coins will move visually from the center to
	the other edge in one second is determined by VELOCITY and TRIGGER.
*/

#define TRIGGER 10			// duration in milliseconds for a callback function to be executed
#define VELOCITY 1700

/* MATH CONSTANTS */

#define CDA 50				// circle drawing approximation
#define ROOT_TWO 1.414
#define ROUND_OFF_ERROR 2	// rounding error
#define COIN_STOP_LIMIT 8	// prevent coins from infinitely moving due to excessive computation
#define RADIANS_PER_DEGREE 57.29577951308232087679

// calculate the force at which the striker has to be struck
void hitStriker(void);

// simulate the physical interactions between coins during a collision
void coinCollision(int i, int j, struct Coin *coins);

// simulate a coin fall into the pot and assess whether it drops or not
void coinPotFall(int i, struct Coin *coins);

// simulate a coin collision with the walls of the carrom board
void wallCollision(int i, struct Coin *coins);

#endif
