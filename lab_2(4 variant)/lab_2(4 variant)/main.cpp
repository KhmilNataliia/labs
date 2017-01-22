#include <iostream>
#include <stdio.h>
#include <stdlib.h>
/*#include "glew.h"
#include "freeglut.h"
#include "wglew.h*/
#include <GL\freeglut.h>;
#include "Windows.h"
#include "elipce.h"
using namespace std;

void reshape(int w, int h);
int X[1000];
int Y[1000];
int col;
void display();

int a, b;

int main(int argc,char **argv)
{
	cout << "the formula of elipce is: x^2/a^2+y^2/b^2=1" << endl;
	cout << "please,enter koefitient a=";
	cin >> a;
	cout << "and koefitient b=";
	cin >> b;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(10, 10);
	glutInitWindowSize(600,600);
	glutCreateWindow("rastr_elipce");
	glutReshapeFunc(reshape);
	elipce(a, b, X,Y, col);
	col = 4 * (a + b) + 1;
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < col; i++)
	{
		glColor3f(0.0, 1.0, 1.0);
		glVertex2i(X[i], Y[i]);
	}
	glEnd();

	glutSwapBuffers();
}