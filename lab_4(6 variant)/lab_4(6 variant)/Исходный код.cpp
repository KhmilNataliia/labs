#include<iostream>
#include<GL\freeglut.h>
#include "Windows.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<dos.h>
#include <stdio.h>
#include <conio.h>




using namespace std;

void display();
void rect();

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void drawcircle(float x, float y, float r, int col)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < col; i++)
	{
		float angle = 2 * 3.14*float(i) / float(col);
		float dx = r*cosf(angle);
		float dy = r*sinf(angle);
		glVertex2f(x + dx, y + dy);
	}
	if (r>=0) drawcircle(x, y, r - 0.1, col);
	glEnd();
}


const float R = 40;
const float R2 = 60;
const int COL = 100;
float alpha;
float Y[10000];
int x,speed,Vx,Vy,V;
int j = 0;
float L,x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4,X_1,Y_1,X_2,Y_2,X_3,Y_3,X_4,Y_4;
double al;

void way(int speed, float alpha)
{
	x = 0;
	Y[x] = R2+x*(sin(alpha) / cos(alpha)) - (9.8*x*x) / (2 * speed*speed*cos(alpha)*cos(alpha));
	while ((Y[x] >= R)&&(x<2000))
	{
		x++;
		Y[x] = R2+5*x*(sin(alpha) / cos(alpha)) - (9.8*x*25*x) / (2 * speed*speed*cos(alpha)*cos(alpha));
	}
}



void Timer(int)
{
	display();
	 glutTimerFunc((speed-V)/1000, Timer, 0);
	glutSwapBuffers();
}

void fly()
{
	glTranslated( 5*j,( Y[j] - Y[0]), 0);
	glPushMatrix();
		glColor3f(0, 0, 0);
		if (j<=x) drawcircle( R2, R2, R, COL);
		if (Y[j] > Y[j - 1]) Vy = (Vy - 10);
		else Vy = Vy + 10;
		V = int(sqrt(Vx*Vx + Vy*Vy));
		glPopMatrix();
		glutSwapBuffers();
		j++;
}


void rect()
{
	glColor3f(0.2, 0.2, 0.2);
	glLineWidth(10 * R);
	glBegin(GL_QUADS);
	glVertex2f(X_1+R2, Y_1+R2);
	glVertex2f(X_2+R2, Y_2+R2);
	glVertex2f(X_3+R2, Y_3+R2);
	glVertex2f(X_4+R2, Y_4+R2);
	glEnd();
	glLineWidth(1);

}

void  display()
{

	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity(); 
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.2, 0.2, 0.2);
	rect();
	drawcircle(R2, R2, R2, COL);
		fly();
		if (j < x) glutTimerFunc(0, Timer, 0);
		glutSwapBuffers();
		glColor3f(0.2, 0.2, 0.2);
		glLineWidth(10 * R);
		glBegin(GL_QUADS);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(X_1 + R2 - 5 * j, Y_1 + R2 - (Y[j] - Y[0]));
		glVertex2f(X_2 + R2 - 5 * j, Y_2 + R2 - (Y[j] - Y[0]));
		glVertex2f(X_3 + R2 - 5 * j, Y_3 + R2 - (Y[j] - Y[0]));
		glVertex2f(X_4 + R2 - 5 * j, Y_4 + R2 - (Y[j] - Y[0]));
		glEnd();
		glLineWidth(1);
		glColor3f(0.2, 0.2, 0.2);
		drawcircle(R2 - 5 * j, R2 - (Y[j] - Y[0]), R2, COL);
}


int main(int agrc, char **agrv)
{
	cout << "input the value of starting speed=";
	cin >> speed;
	cout << "input the edge=";
	cin >> alpha;
	al = alpha;
	alpha = alpha*3.14 / 180;
	j = 0;
	L = 3* R;
	x_1 = R2;
	y_1 = R2-R;
	x_2 = R2;
	y_2 = R2+R ;
	x_3 = R2 + L;
	y_3 = R2 +R;
	x_4 = R2 + L;
	y_4 =R2-R;
	X_1 = (x_1-R2)*cos(alpha) - (y_1-R2)*sin(alpha);
	Y_1 = (x_1-R2)*sin(alpha) + (y_1-R2)*cos(alpha);
	X_2 = (x_2-R2)*cos(alpha) - (y_2-R2)*sin(alpha);
	Y_2 = (x_2-R2)*sin(alpha) + (y_2-R2)*cos(alpha);
	X_3 = (x_3-R2)*cos(alpha) - (y_3-R2)*sin(alpha);
	Y_3 = (x_3-R2)*sin(alpha) + (y_3-R2)*cos(alpha);
	X_4 = (x_4-R2)*cos(alpha) - (y_4-R2)*sin(alpha);
	Y_4 = (x_4-R2)*sin(alpha) + (y_4-R2)*cos(alpha);
	way(speed, alpha);
	Vx = int(speed*cos(alpha));
	Vy = int(speed*sin(alpha));
	glutInit(&agrc, agrv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(2000, 990); 
	glutInitWindowPosition(0,0 ); 
	glutCreateWindow("bomb"); 
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	glutReshapeFunc(reshape);
		glutDisplayFunc(display);
		glutTimerFunc(speed, Timer, 0);
	glutMainLoop();

	return 0;
}