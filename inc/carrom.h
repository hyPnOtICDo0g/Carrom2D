#ifndef CARROM_H
#define CARROM_H

#include <GL/glut.h>

/*
	C Implementation of the Classic Carrom Game in OpenGL
	Based on Multiplayer Carrom by Shantanu Chaudhary and Chainn Singh

	Terminology used in this game is sourced from the
	Carrom Wikipedia page: https://en.wikipedia.org/wiki/Carrom

	Constants such as mass, radius, etc. defined below, serve as
	scaling factors that can be adjusted to alter the game scene
*/

/* GENERAL COLOR CONSTANTS */

#define WHITE 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0
#define RED 1.0, 0.0, 0.0
#define BLUE 0.0, 0.0, 1.0
#define YELLOW 1.0, 1.0, 0.0
#define LIGHT_BROWN 0.9, 0.47, 0.1411
#define DARK_BROWN 0.647, 0.164, 0.164
#define OPACITY 1.0

/* BOARD AND COIN CONSTANTS */

#define BOARD_LINE_COLOR BLACK
#define BOARD_COLOR LIGHT_BROWN
#define BOARD_EDGE_COLOR DARK_BROWN
#define BACKGROUND_COLOR WHITE, OPACITY

#define STRIKER_COLOR BLUE
#define QUEEN_COIN_COLOR RED
#define WHITE_COIN_COLOR WHITE
#define BLACK_COIN_COLOR BLACK

#define POT_COLOR BLACK
#define EDGE_DOT_COLOR RED

#define EDGE_DOT_RADIUS 0.03
#define BASE_LINE_SIZE 0.10
#define POT_CIRCLE_RADIUS 0.0601

#define BOARD_EDGE_WIDTH 0.10
#define BOARD_LINES_WIDTH 0.0909
#define BOARD_CIRCLE_RADIUS 0.20
#define BOARD_LINES_LENGTH 0.2743

/*
	queen: 1
	white: 2
	black: 2
	striker: 1
	number of coins: 6
*/

#define MAX_COIN_COUNT 6
#define COIN_RADIUS 0.0429
#define STRIKER_RADIUS 0.0559
#define STRIKER_POINTER_LENGTH 0.25


#define ARROW_HEAD_SIZE 0.04
#define ARROW_HEAD_POINT 0.25
#define ARROW_BASE_POINT 0.7

/* POWER METER CONSTANTS */

#define POWER_METER_ON YELLOW
#define POWER_METER_OFF WHITE

#define POWER_METER_WIDTH 0.10

#define MIN_POWER_METER 1
#define MAX_POWER_METER 150

/* POINTS CONSTANTS */

#define MAX_BLACK_POINTS 1
#define MAX_WHITE_POINTS 2
#define MAX_QUEEN_POINTS 5
#define STRIKER_POINT_LOSS 1

// struct definition of a generic tuple (used for coordinates)
struct tuple {
	float x;                // x coordinate
	float y;                // y coordinate
};

// struct definition of a carrom coin
struct Coin {
	float mass;             // coin mass
	float radius;           // coin radius
	struct tuple center;    // center of a coin (h, k)
	struct tuple velocity;  // coin velocity in the x and y directions
	short state;            // state of a coin; set to 1 when active (on board) and 0 when inactive (in pot)
};

// struct definition of the board status in a carrom game
struct BoardStatus {
	int turn;               // turn of the next player in a game
	int currentTeam;        // current team (of two players) playing a game
	int pointsTeamOne;      // total points scored by team one
	int pointsTeamTwo;      // total points scored by team two
	struct Coin *coins;     // keep track of coins on the board
};

// struct definition of the current state of the game
struct GameState {
	float theta;            // angle of the striker in the direction it is pointing towards
	GLint glWidth;          // width of the game window
	GLint glHeight;         // height of the game window
	int strikerState;       // state of the striker; set to 1 when the striker is in action and 0 when stationary
	int currentPower;       // force with which the striker is intended to be struck
	int numberOfPlayers;    // number of players playing the game; 2 or 4
	struct Coin *coins;     // keep track of coins on the board
};

// global variables to keep track of the game variables

extern struct BoardStatus start;

extern struct GameState state;

#endif
