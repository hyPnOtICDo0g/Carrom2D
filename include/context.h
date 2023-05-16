#ifndef CONTEXT_H
#define CONTEXT_H

/*
	Global variables to store and manage the overall game state, utilized to
	maintain the game context across callback functions having fixed argument types.
*/

extern struct BoardStatus *start;

extern struct GameState *state;

#endif
