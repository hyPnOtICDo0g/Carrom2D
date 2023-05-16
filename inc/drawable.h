#ifndef DRAWABLE_H
#define DRAWABLE_H

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
