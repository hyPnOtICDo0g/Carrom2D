#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/glut.h>

// a singular constant to proportionally scale the entire board
#define BOARD_SCALING_FACTOR 0.75

/* GENERAL COLOR CONSTANTS */

#define OPACITY 1.0
#define RED 1.0, 0.0, 0.0
#define BLUE 0.0, 0.0, 1.0
#define WHITE 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0
#define YELLOW 1.0, 1.0, 0.0
#define GREY 0.149, 0.149, 0.149
#define LIGHT_BROWN 0.9, 0.47, 0.1411
#define LIGHT_GREY 0.271, 0.271, 0.271
#define DARK_BROWN 0.647, 0.164, 0.164

/* GENERAL DIMENSION CONSTANTS */

#define DEFAULT_LINE_WIDTH 1

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

// mimic the process of drawing a line segment on the LCD screen of a calculator
void drawSegment(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

// select the specific line segment required for the drawing
void pickSegment(int segment, GLfloat x, GLfloat y);

// display a double digit score
void drawDigit(int digit, GLfloat x, GLfloat y);

// display a string at a specified position
void drawStringAtPos(GLfloat xPos, GLfloat yPos, const unsigned char *string);

// fill circles with suitable colors on the board
void drawCircleFilled(GLfloat radius, GLfloat centerX, GLfloat centerY, GLint cda);

// draw a circular outline that spans between two points
void drawCircleOutline(GLfloat radius, GLfloat centerX, GLfloat centerY, GLint cda, GLint pointOne, GLint pointTwo);

#endif
