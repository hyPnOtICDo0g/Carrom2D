#ifndef CARROM_H
#define CARROM_H

#include "drawable.h"

/*
	C port of the Classic Carrom Game in OpenGL, based on
	Multiplayer Carrom by Shantanu Chaudhary and Chainn Singh.

	Terminology used in this game is sourced from the
	Carrom Wikipedia page: https://en.wikipedia.org/wiki/Carrom

	Constants such as mass, radius, etc. defined below, serve as
	scaling factors that can be adjusted to alter the game scene.
*/

/* BOARD AND COIN CONSTANTS */

#define BOARD_LINE_COLOR BLACK
#define BOARD_COLOR LIGHT_BROWN
#define BOARD_EDGE_COLOR DARK_BROWN
#define BACKGROUND_COLOR GREY, OPACITY

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
	total: 6
*/

#define MAX_COIN_COUNT 6
#define COIN_RADIUS 0.0429
#define STRIKER_RADIUS 0.0559
#define STRIKER_POINTER_LENGTH 0.25

#define ARROW_HEAD_SIZE 0.04
#define ARROW_HEAD_POINT 0.25
#define ARROW_BASE_POINT 0.7

#define BOARD_BOTTOM_LEFT 0
#define BOARD_BOTTOM_RIGHT 1
#define BOARD_TOP_LEFT 2
#define BOARD_TOP_RIGHT 3

/* POWER READER CONSTANTS */

#define MIN_POWER_READER 25
#define MAX_POWER_READER 100
#define POWER_READER_OFF WHITE
#define POWER_READER_ON_25 YELLOW
#define POWER_READER_ON_50 1.0, 0.624, 0.0
#define POWER_READER_ON_75 1.0, 0.376, 0.0
#define POWER_READER_ON_100 RED
#define POWER_READER_WIDTH 0.10
#define POWER_READER_VARIATION 25

/* SCORE DISPLAY CONSTANTS */

#define SCORE_BOARD_PADDING 0.21
#define SCORE_DISPLAY_LINE_WIDTH 10

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
	int strikerState;       // state of the striker; set to 0 when the striker is in action and 1 when stationary
	int currentPower;       // force with which the striker is intended to be struck
	int numberOfPlayers;    // number of players playing the game; 2 or 4
	struct Coin *coins;     // keep track of coins on the board
};

#endif
