#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "scene.h"
#include "carrom.h"
#include "context.h"
#include "utilities.h"

void copyCoinArrays(struct Coin *coinsFrom, struct Coin *coinsTo, int size) {
	for(int i = 0; i < size; i++) {
		coinsTo[i] = coinsFrom[i];
	}
}

void memCheck(void *ptr) {
	if(ptr == NULL) {
		// printf("warning: insufficient memory\n");
		exit(1);
	}
}

int numActiveWhite(struct Coin *coins) {
	int count = 0;
	for(int i = 0; i < (MAX_COIN_COUNT - 2) / 2; i++) {
		if(coins[i].state == 1) {
			count += 1;
		}
	}
	return count;
}


int numActiveBlack(struct Coin *coins) {
	int count = 0;
	for(int i = (MAX_COIN_COUNT - 2) / 2; i < (MAX_COIN_COUNT - 2); i++) {
		if(coins[i].state == 1) {
			count += 1;
		}
	}
	return count;
}

int isQueenActive(struct Coin *coins) {
	if(coins[MAX_COIN_COUNT - 2].state == 1) {
		return 1;
	}
	else {
		return 0;
	}
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

void exitGame(void) {
	free(state->coins);
	free(start->coins);
	free(start);
	free(state);
}
