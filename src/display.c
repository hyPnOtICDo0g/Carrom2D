#include <GL/glut.h>

#include "display.h"

void display(void) {
	glRotatef(0.0, 0.0, 0.0, 1.0);
	board(); coins();
	strikerDirection();
	glRotatef(0.0, 0.0, 0.0, 1.0);
	powerReader();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(GLint width, GLint height) {
	glLoadIdentity();

	if(width > height) {
		glScalef((float) ((float) height / (float) width), 1.0, 1.0);
	}
	else {
		glScalef(1.0, (float) ((float) width / (float) height), 1.0);
	}

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}
