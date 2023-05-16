#ifndef DRAWABLE_H
#define DRAWABLE_H

// a singular constant to proportionally scale the entire board
#define BOARD_SCALING_FACTOR 0.75

// display the edges of the board
void drawBoardFrame(void);

// display the background of the board
void drawBoardBackground(void);

// display the base lines of the board, where the striker is positioned
void drawBoardBaseLines(void);

// display all the circular objects on the board
void drawBoardCircles(void);

// display the arrows on the board
void drawBoardArrows(short position);

#endif
