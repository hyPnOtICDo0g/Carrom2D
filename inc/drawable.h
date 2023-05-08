#ifndef DRAWABLE_H
#define DRAWABLE_H

#define BOTTOM_LEFT 0
#define BOTTOM_RIGHT 1
#define TOP_LEFT 2
#define TOP_RIGHT 3

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
