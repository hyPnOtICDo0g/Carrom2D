#include <math.h>
#include <GL/glut.h>

#include "rules.h"
#include "context.h"
#include "display.h"
#include "physics.h"
#include "drawable.h"
#include "utilities.h"

void display(void) {
	carromBoard();
	carromCoins(state);
	strikerDirection(state);
	powerReader(state);
	scoreBoard(start);
	teamTurnPanel(start);
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(GLint width, GLint height) {
	glLoadIdentity();

	if(width > height) {
		glScalef(((float) height / (float) width), 1.0, 1.0);
	}
	else {
		glScalef(1.0, ((float) width / (float) height), 1.0);
	}

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

void trigger(int value) {
	int i, j;
	struct Coin *coins = state->coins;
	float reciprocalVelocity = 1.0 / (float) value;

	if(state->strikerState == 0) {
		for(i = 0; i < MAX_COIN_COUNT; i ++) {
			for(j = i + 1; j < MAX_COIN_COUNT; j++) {
				if((coins[i].state == 1) && (coins[j].state == 1)) {
					coinCollision(i, j, coins);
				}
			}
		}
		for(i = 0; i < MAX_COIN_COUNT; i++) {
			if(coins[i].state == 1) {
				wallCollision(i, coins);
			}
		}
		for(i = 0; i < MAX_COIN_COUNT; i++) {
			if(coins[i].state == 1) {
				coinPotFall(i, coins);
			}
		}
		// updating the positions of the coins
		for(i = 0; i < MAX_COIN_COUNT; i++) {
			if(coins[i].state == 1) {

				coins[i].center.x = (float) (coins[i].center.x + coins[i].velocity.x * reciprocalVelocity);
				coins[i].center.y = (float) (coins[i].center.y + coins[i].velocity.y * reciprocalVelocity);

				if(coins[i].velocity.x > 0) {
					coins[i].velocity.x -= (float) ((float) (G * FRICTION) * reciprocalVelocity);
				}
				else {
					coins[i].velocity.x += (float) ((float) (G * FRICTION) * reciprocalVelocity);
				}
				if(coins[i].velocity.y > 0) {
					coins[i].velocity.y -= (float) ((float) (G * FRICTION) * reciprocalVelocity);
				}
				else {
					coins[i].velocity.y += (float) ((float) (G * FRICTION) * reciprocalVelocity);
				}
			}
		}
		// change the state of the striker to make it stationary
		state->strikerState = 1;

		for(i = 0; i < MAX_COIN_COUNT; i++) {
			if(fabs(coins[i].velocity.x) <= COIN_STOP_LIMIT && fabs(coins[i].velocity.y) <= COIN_STOP_LIMIT) {
				coins[i].velocity.x = 0;
				coins[i].velocity.y = 0;
			}
			else {
				state->strikerState = 0;
			}
		}
		// if the striker is stationary, then proceed to the next player
		if(state->strikerState == 1) {
			initNewTurn(state, start);
		}
	}
	// call the display callback function to render the new frame
	glutPostRedisplay();
	// continue triggering further updates
	glutTimerFunc(TRIGGER, trigger, VELOCITY);
}

void carromBoard(void) {
	glClearColor(BACKGROUND_COLOR);
	glClear(GL_COLOR_BUFFER_BIT);
	drawBoardBackground();
	drawBoardBaseLines();
	drawBoardCircles();
	drawBoardFrame();
	for(int i = BOARD_BOTTOM_LEFT; i <= BOARD_TOP_RIGHT; i++) {
		drawBoardArrows(i);
	}
}

void carromCoins(struct GameState *gameState) {
	int i; struct Coin *coins = gameState->coins;
	// place coins in their initial positions
	for(i = 0; i < (MAX_COIN_COUNT - 2) / 2; i++) {
		// if the coin is in the pot, color it black
		if(coins[i].state == 0) {
			glColor3f(POT_COLOR);
			drawCircleFilled(coins[i].radius, coins[i].center.x, coins[i].center.y, CDA);
		}
		else {
			// display white coins
			glColor3f(WHITE_COIN_COLOR);
			drawCircleFilled(coins[i].radius, coins[i].center.x, coins[i].center.y, CDA);
		}
	}

	for(i = (MAX_COIN_COUNT - 2) / 2; i < MAX_COIN_COUNT - 2; i++) {
		if(coins[i].state == 0) {
			glColor3f(POT_COLOR);
			drawCircleFilled(coins[i].radius, coins[i].center.x, coins[i].center.y, CDA);
		}
		else {
			// display black coins
			glColor3f(BLACK_COIN_COLOR);
			drawCircleFilled(coins[i].radius, coins[i].center.x, coins[i].center.y, CDA);
		}
	}

	if(coins[MAX_COIN_COUNT - 2].state == 0) {
		glColor3f(POT_COLOR);
		drawCircleFilled(coins[MAX_COIN_COUNT - 2].radius, coins[MAX_COIN_COUNT - 2].center.x, coins[MAX_COIN_COUNT - 2].center.y, CDA);
	}
	else {
		// display queen
		glColor3f(QUEEN_COIN_COLOR);
		drawCircleFilled(coins[MAX_COIN_COUNT - 2].radius, coins[MAX_COIN_COUNT - 2].center.x, coins[MAX_COIN_COUNT - 2].center.y, CDA);
	}

	if(coins[MAX_COIN_COUNT - 1].state == 0) {
		glColor3f(POT_COLOR);
		drawCircleFilled(coins[MAX_COIN_COUNT - 1].radius, coins[MAX_COIN_COUNT - 1].center.x, coins[MAX_COIN_COUNT - 1].center.y, CDA);
	}
	else {
		// display striker
		glColor3f(STRIKER_COLOR);
		drawCircleFilled(coins[MAX_COIN_COUNT - 1].radius, coins[MAX_COIN_COUNT - 1].center.x, coins[MAX_COIN_COUNT - 1].center.y, CDA);
	}
}

void strikerDirection(struct GameState *gameState) {
	float theta = gameState->theta;
	struct Coin *coins = gameState->coins;

	if(gameState->strikerState == 1) {
		float strikerX = BOARD_SCALING_FACTOR * coins[MAX_COIN_COUNT - 1].center.x;
		float strikerY = BOARD_SCALING_FACTOR * coins[MAX_COIN_COUNT - 1].center.y;

		float pointerEndX = strikerX + BOARD_SCALING_FACTOR * (STRIKER_POINTER_LENGTH * cos((theta * (float) (2 * M_PI)) / 360.0));
		float pointerEndY = strikerY + BOARD_SCALING_FACTOR * (STRIKER_POINTER_LENGTH * sin((theta * (float) (2 * M_PI)) / 360.0));

		glColor3f(BOARD_LINE_COLOR);
		glBegin(GL_LINES);
			glVertex2f(strikerX, strikerY);
			glVertex2f(pointerEndX, pointerEndY);
		glEnd();
	}
}

void powerReader(struct GameState *gameState) {
	int currentPower = gameState->currentPower;
	// 25% power
	if(currentPower == POWER_READER_VARIATION) {
		glColor3f(POWER_READER_ON_25);
	}
	// 50% power
	else if(currentPower == POWER_READER_VARIATION * 2) {
		glColor3f(POWER_READER_ON_50);
	}
	// 75% power
	else if(currentPower == POWER_READER_VARIATION * 3) {
		glColor3f(POWER_READER_ON_75);
	}
	// 100% power
	else {
		glColor3f(POWER_READER_ON_100);
	}

	glBegin(GL_POLYGON);
		glVertex2f(BOARD_SCALING_FACTOR + POWER_READER_WIDTH, BOARD_SCALING_FACTOR * (-1.0 + 2.0 * ((float) currentPower / (float) MAX_POWER_READER)) / 2.0);
		glVertex2f(BOARD_SCALING_FACTOR + 2 * POWER_READER_WIDTH, BOARD_SCALING_FACTOR * (-1.0 + (2.0 * ((float) currentPower / (float) MAX_POWER_READER))) / 2.0);
		glVertex2f(BOARD_SCALING_FACTOR + 2 * POWER_READER_WIDTH, -BOARD_SCALING_FACTOR / 2.0);
		glVertex2f(BOARD_SCALING_FACTOR + POWER_READER_WIDTH, -BOARD_SCALING_FACTOR / 2.0);
	glEnd();

	glColor3f(POWER_READER_OFF);
	glBegin(GL_POLYGON);
		glVertex2f(BOARD_SCALING_FACTOR + POWER_READER_WIDTH, BOARD_SCALING_FACTOR / 2.0);
		glVertex2f(BOARD_SCALING_FACTOR + 2 * POWER_READER_WIDTH, BOARD_SCALING_FACTOR / 2.0);
		glVertex2f(BOARD_SCALING_FACTOR + 2 * POWER_READER_WIDTH, BOARD_SCALING_FACTOR * (-1.0 + (2.0 * ((float) currentPower / (float) MAX_POWER_READER))) / 2.0);
		glVertex2f(BOARD_SCALING_FACTOR + POWER_READER_WIDTH, BOARD_SCALING_FACTOR * (-1.0 + (2.0 * ((float) currentPower / (float) MAX_POWER_READER))) / 2.0);
	glEnd();
}

void scoreBoard(struct BoardStatus *boardStatus) {
	int score;
	float x = -1.03, y = 0;

	// render a background for the score display
	glColor3f(LIGHT_GREY);
	glBegin(GL_QUADS);
		glVertex2f(-1.67, 0.33);
		glVertex2f(-1.67, -0.33);
		glVertex2f(-1, -0.33);
		glVertex2f(-1, 0.33);
	glEnd();

	if(boardStatus->currentTeam == 1) {
		score = boardStatus->pointsTeamOne;
	}
	else {
		score = boardStatus->pointsTeamTwo;
	}

	if(score == 0) {
		drawDigit(0, x, y);
	}
	else {
		// extract each digit and display them individually
		while(score != 0) {
			drawDigit(score % 10, x, y);
			score /= 10;
			x -= 0.4;
		}
		x = -1.03;
	}
	drawStringAtPos(-1.385, -0.3, (const unsigned char *) "SCORE");
}

void teamTurnPanel(struct BoardStatus *boardStatus) {
	float x = 1.69, y = 0.77, digitX = 1.47, digitY = 0.5;

	// render a background for the player number display
	glColor3f(LIGHT_GREY);
	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x, y - 0.59);
		glVertex2f(x - 0.65, y - 0.59);
		glVertex2f(x - 0.65, y);
	glEnd();
	drawDigit(boardStatus->turn + 1, digitX, digitY);
	drawStringAtPos(1.31, 0.2, (const unsigned char *) "PLAYER");

	// render a background for the team number display
	glColor3f(LIGHT_GREY);
	glBegin(GL_QUADS);
		glVertex2f(x, -(y + 0.06));
		glVertex2f(x, -(y - 0.53));
		glVertex2f(x - 0.65, -(y - 0.53));
		glVertex2f(x - 0.65, -(y + 0.06));
	glEnd();
	drawDigit(boardStatus->currentTeam, digitX, -digitY);
	drawStringAtPos(1.33, -0.8, (const unsigned char *) "TEAM");
}
