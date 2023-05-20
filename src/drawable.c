#include <math.h>
#include <GL/freeglut.h>

#include "carrom.h"
#include "physics.h"
#include "drawable.h"
#include "utilities.h"

void drawBoardFrame(void) {
	glColor3f(BOARD_EDGE_COLOR);
	glBegin(GL_POLYGON);
		glVertex2f(-BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
		glVertex2f(-BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), -BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
		glVertex2f(-BOARD_SCALING_FACTOR, -BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
		glVertex2f(-BOARD_SCALING_FACTOR, BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2f(BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
		glVertex2f(BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), -BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
		glVertex2f(BOARD_SCALING_FACTOR, -BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
		glVertex2f(BOARD_SCALING_FACTOR, BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2f(-BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
		glVertex2f(BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
		glVertex2f(BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), BOARD_SCALING_FACTOR);
		glVertex2f(-BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), BOARD_SCALING_FACTOR);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2f(-BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), -BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
		glVertex2f(BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), -BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH));
		glVertex2f(BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), -BOARD_SCALING_FACTOR);
		glVertex2f(-BOARD_SCALING_FACTOR * (1 + BOARD_EDGE_WIDTH), -BOARD_SCALING_FACTOR);
	glEnd();
}


void drawBoardBackground(void) {
	glColor3f(BOARD_COLOR);
	glBegin(GL_POLYGON);
		glEdgeFlag(GL_TRUE);
		glVertex2f(-BOARD_SCALING_FACTOR, BOARD_SCALING_FACTOR);
		glVertex2f(BOARD_SCALING_FACTOR, BOARD_SCALING_FACTOR);
		glVertex2f(BOARD_SCALING_FACTOR, -BOARD_SCALING_FACTOR);
		glVertex2f(-BOARD_SCALING_FACTOR, -BOARD_SCALING_FACTOR);
		glEdgeFlag(GL_FALSE);
	glEnd();
}

void drawBoardBaseLines(void) {
	glColor3f(BOARD_LINE_COLOR);
	// top base line
	glBegin(GL_LINES);
		glVertex2f(-(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)), (BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH)));
		glVertex2f((BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)), (BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH)));
		glVertex2f(-(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)), (BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH)));
		glVertex2f((BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)), (BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH)));
	glEnd();
	// bottom base line
	glBegin(GL_LINES);
		glVertex2f(-(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)), -(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH)));
		glVertex2f((BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)), -(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH)));
		glVertex2f(-(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)), -(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH)));
		glVertex2f((BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)), -(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH)));
	glEnd();
	// left base line
	glBegin(GL_LINES);
		glVertex2f(-(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH)), -(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)));
		glVertex2f(-(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH)), (BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)));
		glVertex2f(-(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH)), -(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)));
		glVertex2f(-(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH)), (BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)));
	glEnd();
	// right base line
	glBegin(GL_LINES);
		glVertex2f((BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH)), -(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)));
		glVertex2f((BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH)), (BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)));
		glVertex2f((BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH)), -(BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)));
		glVertex2f((BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH)), (BOARD_SCALING_FACTOR * (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE)));
	glEnd();
}

void drawBoardCircles(void) {
	glColor3f(BOARD_LINE_COLOR);
	// display the center circle
	drawCircleOutline(BOARD_CIRCLE_RADIUS, 0.0, 0.0, CDA, -3, CDA);
	// outline the circles at both ends of the base line
	// left and bottom base lines
	drawCircleOutline((BOARD_LINES_WIDTH / 2.00), -(1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), (1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), CDA, -3, CDA);
	drawCircleOutline((BOARD_LINES_WIDTH / 2.00), (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), (1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), CDA, -3, CDA);
	drawCircleOutline((BOARD_LINES_WIDTH / 2.00), (1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), CDA, -3, CDA);
	drawCircleOutline((BOARD_LINES_WIDTH / 2.00), (1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), -(1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), CDA, -3, CDA);
	// right and top base lines
	drawCircleOutline((BOARD_LINES_WIDTH / 2.00), -(1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), -(1 - BOARD_LINES_LENGTH -(BOARD_LINES_WIDTH / 2.0)), CDA, -3, CDA);
	drawCircleOutline((BOARD_LINES_WIDTH / 2.00), (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), -(1 - BOARD_LINES_LENGTH -(BOARD_LINES_WIDTH / 2.0)), CDA, -3, CDA);
	drawCircleOutline((BOARD_LINES_WIDTH / 2.00), -(1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), CDA, -3, CDA);
	drawCircleOutline((BOARD_LINES_WIDTH / 2.00), -(1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), -(1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), CDA, -3, CDA);
	// fill the outlined circles with appropriate color
	// left and bottom base lines
	glColor3f(EDGE_DOT_COLOR);
	drawCircleFilled(EDGE_DOT_RADIUS, -(1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), -(1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH /2.0)), CDA);
	drawCircleFilled(EDGE_DOT_RADIUS, (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), -(1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), CDA);
	drawCircleFilled(EDGE_DOT_RADIUS, -(1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), CDA);
	drawCircleFilled(EDGE_DOT_RADIUS, -(1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), -(1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), CDA);
	// right and top base lines
 	drawCircleFilled(EDGE_DOT_RADIUS, -(1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), (1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), CDA);
	drawCircleFilled(EDGE_DOT_RADIUS, (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), (1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), CDA);
	drawCircleFilled(EDGE_DOT_RADIUS, (1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), (1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), CDA);
	drawCircleFilled(EDGE_DOT_RADIUS, (1 - BOARD_LINES_LENGTH - (BOARD_LINES_WIDTH / 2.0)), -(1 - BOARD_LINES_LENGTH - BOARD_LINES_WIDTH - BASE_LINE_SIZE), CDA);
	// draw and fill the pot with appropriate color
	glColor3f(POT_COLOR);
	drawCircleFilled(POT_CIRCLE_RADIUS, -(1 - POT_CIRCLE_RADIUS), (1 - POT_CIRCLE_RADIUS), CDA);
	drawCircleFilled(POT_CIRCLE_RADIUS, (1 - POT_CIRCLE_RADIUS), (1 - POT_CIRCLE_RADIUS), CDA);
	drawCircleFilled(POT_CIRCLE_RADIUS, (1 - POT_CIRCLE_RADIUS), -(1 - POT_CIRCLE_RADIUS), CDA);
	drawCircleFilled(POT_CIRCLE_RADIUS, -(1 - POT_CIRCLE_RADIUS), -(1 - POT_CIRCLE_RADIUS), CDA);
}

void drawBoardArrows(short position) {
	float radius = BOARD_CIRCLE_RADIUS / 2.0;
	float centerX = BOARD_SCALING_FACTOR * (ARROW_HEAD_POINT + (BOARD_CIRCLE_RADIUS / (2.0 * ROOT_TWO)));
	float centerY = centerX;
	glColor3f(BOARD_LINE_COLOR);

	switch(position) {
		case BOARD_TOP_LEFT:
			centerX *= -1;
			glBegin(GL_LINES);
				glVertex2f(-BOARD_SCALING_FACTOR * ARROW_HEAD_POINT, BOARD_SCALING_FACTOR * ARROW_HEAD_POINT);
				glVertex2f(-BOARD_SCALING_FACTOR * ARROW_BASE_POINT, BOARD_SCALING_FACTOR * ARROW_BASE_POINT);
			glEnd();

			glBegin(GL_TRIANGLES);
				glVertex2f(-(BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, (BOARD_SCALING_FACTOR * ARROW_BASE_POINT - ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
				glVertex2f(-(BOARD_SCALING_FACTOR * ARROW_BASE_POINT - ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, (BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
				glVertex2f(-(BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, (BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
			glEnd();

			drawCircleOutline(radius, centerX / BOARD_SCALING_FACTOR, centerY / BOARD_SCALING_FACTOR, CDA, -CDA / 2, CDA / 4 + ROUND_OFF_ERROR);

			glBegin(GL_TRIANGLES);
				glVertex2f(centerX - radius * BOARD_SCALING_FACTOR - ARROW_HEAD_SIZE / 2, centerY);
				glVertex2f(centerX - radius * BOARD_SCALING_FACTOR + ARROW_HEAD_SIZE / 2, centerY);
				glVertex2f(centerX - radius * BOARD_SCALING_FACTOR, centerY + ARROW_HEAD_SIZE / 2);
			glEnd();

			glBegin(GL_TRIANGLES);
				glVertex2f(centerX, centerY + radius * BOARD_SCALING_FACTOR + ARROW_HEAD_SIZE / 2);
				glVertex2f(centerX, centerY + radius * BOARD_SCALING_FACTOR - ARROW_HEAD_SIZE / 2);
				glVertex2f(centerX - ARROW_HEAD_SIZE / 2, centerY + radius * BOARD_SCALING_FACTOR);
			glEnd();
			break;

		case BOARD_TOP_RIGHT:
			glBegin(GL_LINES);
				glVertex2f(BOARD_SCALING_FACTOR * ARROW_HEAD_POINT, BOARD_SCALING_FACTOR * ARROW_HEAD_POINT);
				glVertex2f(BOARD_SCALING_FACTOR * ARROW_BASE_POINT, BOARD_SCALING_FACTOR * ARROW_BASE_POINT);
			glEnd();

			glBegin(GL_TRIANGLES);
				glVertex2f((BOARD_SCALING_FACTOR * ARROW_BASE_POINT - ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, (BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
				glVertex2f((BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, (BOARD_SCALING_FACTOR * ARROW_BASE_POINT - ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
				glVertex2f((BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, (BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
			glEnd();

			drawCircleOutline(radius, centerX / BOARD_SCALING_FACTOR, centerY / BOARD_SCALING_FACTOR, CDA, CDA / 4, CDA + ROUND_OFF_ERROR);

			glBegin(GL_TRIANGLES);
				glVertex2f(centerX + radius * BOARD_SCALING_FACTOR - ARROW_HEAD_SIZE / 2, centerY);
				glVertex2f(centerX + radius * BOARD_SCALING_FACTOR + ARROW_HEAD_SIZE / 2, centerY);
				glVertex2f(centerX + radius * BOARD_SCALING_FACTOR, centerY + ARROW_HEAD_SIZE / 2);
			glEnd();

			glBegin(GL_TRIANGLES);
				glVertex2f(centerX, centerY + radius * BOARD_SCALING_FACTOR + ARROW_HEAD_SIZE / 2);
				glVertex2f(centerX, centerY + radius * BOARD_SCALING_FACTOR - ARROW_HEAD_SIZE / 2);
				glVertex2f(centerX + ARROW_HEAD_SIZE / 2, centerY + radius * BOARD_SCALING_FACTOR);
			glEnd();
			break;

		case BOARD_BOTTOM_LEFT:
			centerX *= -1; centerY *= -1;
			glBegin(GL_LINES);
				glVertex2f(-BOARD_SCALING_FACTOR * ARROW_HEAD_POINT, -BOARD_SCALING_FACTOR * ARROW_HEAD_POINT);
				glVertex2f(-BOARD_SCALING_FACTOR * ARROW_BASE_POINT, -BOARD_SCALING_FACTOR * ARROW_BASE_POINT);
			glEnd();

			glBegin(GL_TRIANGLES);
				glVertex2f(-(BOARD_SCALING_FACTOR * ARROW_BASE_POINT - ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, -(BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
				glVertex2f(-(BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, -(BOARD_SCALING_FACTOR * ARROW_BASE_POINT - ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
				glVertex2f(-(BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, -(BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
			glEnd();

			drawCircleOutline(radius, centerX / BOARD_SCALING_FACTOR, centerY / BOARD_SCALING_FACTOR, CDA, -CDA / 4 - ROUND_OFF_ERROR, CDA / 2 + ROUND_OFF_ERROR);

			glBegin(GL_TRIANGLES);
				glVertex2f(centerX, centerY - radius * BOARD_SCALING_FACTOR - ARROW_HEAD_SIZE / 2);
				glVertex2f(centerX, centerY - radius * BOARD_SCALING_FACTOR + ARROW_HEAD_SIZE / 2);
				glVertex2f(centerX - ARROW_HEAD_SIZE / 2, centerY - radius * BOARD_SCALING_FACTOR);
			glEnd();

			glBegin(GL_TRIANGLES);
				glVertex2f(centerX - radius * BOARD_SCALING_FACTOR - ARROW_HEAD_SIZE / 2, centerY);
				glVertex2f(centerX - radius * BOARD_SCALING_FACTOR + ARROW_HEAD_SIZE / 2, centerY);
				glVertex2f(centerX - radius * BOARD_SCALING_FACTOR, centerY - ARROW_HEAD_SIZE / 2);
			glEnd();
			break;

		case BOARD_BOTTOM_RIGHT:
			centerY *= -1;
			glBegin(GL_LINES);
				glVertex2f(BOARD_SCALING_FACTOR * ARROW_HEAD_POINT, -BOARD_SCALING_FACTOR * ARROW_HEAD_POINT);
				glVertex2f(BOARD_SCALING_FACTOR * ARROW_BASE_POINT, - BOARD_SCALING_FACTOR * ARROW_BASE_POINT);
			glEnd();

			glBegin(GL_TRIANGLES);
				glVertex2f((BOARD_SCALING_FACTOR * ARROW_BASE_POINT - ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, -(BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
				glVertex2f((BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, -(BOARD_SCALING_FACTOR * ARROW_BASE_POINT - ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
				glVertex2f((BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99, -(BOARD_SCALING_FACTOR * ARROW_BASE_POINT + ARROW_HEAD_SIZE / 4 * ROOT_TWO) * 0.99);
			glEnd();

			drawCircleOutline(radius, centerX / BOARD_SCALING_FACTOR, centerY / BOARD_SCALING_FACTOR, CDA, -ROUND_OFF_ERROR, 3 * CDA / 4 + ROUND_OFF_ERROR);

			glBegin(GL_TRIANGLES);
				glVertex2f(centerX, centerY - radius * BOARD_SCALING_FACTOR - ARROW_HEAD_SIZE / 2);
				glVertex2f(centerX, centerY - radius * BOARD_SCALING_FACTOR + ARROW_HEAD_SIZE / 2);
				glVertex2f(centerX + ARROW_HEAD_SIZE / 2, centerY - radius * BOARD_SCALING_FACTOR);
			glEnd();

			glBegin(GL_TRIANGLES);
				glVertex2f(centerX + radius * BOARD_SCALING_FACTOR - ARROW_HEAD_SIZE / 2, centerY);
				glVertex2f(centerX + radius * BOARD_SCALING_FACTOR + ARROW_HEAD_SIZE / 2, centerY);
				glVertex2f(centerX + radius * BOARD_SCALING_FACTOR, centerY - ARROW_HEAD_SIZE / 2);
			glEnd();
			break;
	}
}

void drawSegment(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	glColor3f(WHITE);
	glLineWidth(SCORE_DISPLAY_LINE_WIDTH);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
	glLineWidth(DEFAULT_LINE_WIDTH);
}

void pickSegment(int segment, GLfloat x, GLfloat y) {
	// drawing function that emulates a seven-segment display
	/*
				 5
		   ┌───────────┐
		   │           │
		   │           │
		3  │           │ 1
		   │           │
		   │     6     │
		   ├───────────┤
		   │           │
		   │           │
		4  │           │ 2
		   │           │
		   │           │
		   └───────────┘
				 7
	 */
	switch(segment) {
		case 1:
			drawSegment(x, y + SCORE_BOARD_PADDING, x, y);
			break;

		case 2:
			drawSegment(x, y, x, y - SCORE_BOARD_PADDING);
			break;

		case 3:
			drawSegment(x - SCORE_BOARD_PADDING, y + SCORE_BOARD_PADDING, x - SCORE_BOARD_PADDING, y);
			break;

		case 4:
			drawSegment(x - SCORE_BOARD_PADDING, y, x - SCORE_BOARD_PADDING, y - SCORE_BOARD_PADDING);
			break;

		case 5:
			drawSegment(x, y + SCORE_BOARD_PADDING, x - SCORE_BOARD_PADDING, y + SCORE_BOARD_PADDING);
			break;

		case 6:
			drawSegment(x, y, x - SCORE_BOARD_PADDING, y);
			break;

		case 7:
			drawSegment(x, y - SCORE_BOARD_PADDING, x - SCORE_BOARD_PADDING, y - SCORE_BOARD_PADDING);
			break;
	}
}

void drawDigit(int digit, GLfloat x, GLfloat y) {
	switch(digit) {
		case 0:
			pickSegment(1, x, y);
			pickSegment(2, x, y);
			pickSegment(3, x, y);
			pickSegment(4, x, y);
			pickSegment(5, x, y);
			pickSegment(7, x, y);
			break;

		case 1:
			pickSegment(1, x, y);
			pickSegment(2, x, y);
			break;

		case 2:
			pickSegment(5, x, y);
			pickSegment(1, x, y);
			pickSegment(6, x, y);
			pickSegment(4, x, y);
			pickSegment(7, x, y);
			break;

		case 3:
			pickSegment(5, x, y);
			pickSegment(1, x, y);
			pickSegment(6, x, y);
			pickSegment(2, x, y);
			pickSegment(7, x, y);
			break;

		case 4:
			pickSegment(3, x, y);
			pickSegment(1, x, y);
			pickSegment(6, x, y);
			pickSegment(2, x, y);
			break;

		case 5:
			pickSegment(3, x, y);
			pickSegment(5, x, y);
			pickSegment(6, x, y);
			pickSegment(2, x, y);
			pickSegment(7, x, y);
			break;

		case 6:
			pickSegment(3, x, y);
			pickSegment(5, x, y);
			pickSegment(6, x, y);
			pickSegment(2, x, y);
			pickSegment(7, x, y);
			pickSegment(4, x, y);
			break;

		case 7:
			pickSegment(1, x, y);
			pickSegment(5, x, y);
			pickSegment(2, x, y);
			break;

		case 8:
			pickSegment(3, x, y);
			pickSegment(5, x, y);
			pickSegment(6, x, y);
			pickSegment(2, x, y);
			pickSegment(7, x, y);
			pickSegment(1, x, y);
			pickSegment(4, x, y);
			break;

		case 9:
			pickSegment(3, x, y);
			pickSegment(5, x, y);
			pickSegment(6, x, y);
			pickSegment(2, x, y);
			pickSegment(7, x, y);
			pickSegment(1, x, y);
			break;
	}
}

void drawStringAtPos(GLfloat xPos, GLfloat yPos, const unsigned char *string) {
	glRasterPos2f(xPos, yPos);
	glutBitmapString(GLUT_BITMAP_9_BY_15, string);
}

void drawCircleFilled(GLfloat radius, GLfloat centerX, GLfloat centerY, GLint cda) {
	GLint i; GLfloat angle;
	GLfloat effectiveRadius = BOARD_SCALING_FACTOR * radius;
	glBegin(GL_POLYGON);
		for(i = 0; i < cda; i++) {
			angle = 2 * M_PI * i / cda;
			glVertex2f((BOARD_SCALING_FACTOR * centerX + effectiveRadius * cos(angle)), (BOARD_SCALING_FACTOR * centerY + effectiveRadius * sin(angle)));
		}
	glEnd();
}

void drawCircleOutline(GLfloat radius, GLfloat centerX, GLfloat centerY, GLint cda, GLint pointOne, GLint pointTwo) {
	GLint i; GLfloat angle;
	GLfloat effectiveRadius = BOARD_SCALING_FACTOR * radius;
	glBegin(GL_LINE_STRIP);
		for(i = pointOne; i < pointTwo; i++) {
			angle = 2 * M_PI * i / cda;
			glVertex2f((BOARD_SCALING_FACTOR * centerX + effectiveRadius * cos(angle)), (BOARD_SCALING_FACTOR * centerY + effectiveRadius * sin(angle)));
		}
	glEnd();
}
