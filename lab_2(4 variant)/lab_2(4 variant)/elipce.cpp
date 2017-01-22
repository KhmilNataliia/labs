#include<GL\freeglut.h>;
#include <Windows.h>

void elipce(int a, int b, int *X, int *Y, int col)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int A, B, R, U, D, V, I, x, y;
	int step = 5;
	A = a*a;
	B = b*b;
	R = A*B;
	x=step*a+10; y=550-2*step*b;
	col = 0;
	X[col] = x;
	Y[col] = y;
	col++;
	I = a + b;
	//1 part
	D = B + A*(2 * b - 1)*(2 * b - 1) - 4 * R;
	U = 8 * B;
	V = 8 * A*(b - 1);
	for (int i = 0; i < I; i++)
	{
		if (D < 0)
		{
			D = D + U;
			U = U + 8 * B;
			x = x + step;
			X[col] = x;
			Y[col] = y;
			col++;
		}
		else
		{
			D = D - V;
			V = V - 8 * A;
			y = y + step;
			X[col] = x;
			Y[col] = y;
			col++;
		}
	}
	//2 part
	D = B + A*(2 * b - 1)*(2 * b - 1) - 4 * R;
	U = 8 * B;
	V = 8 * A*(b - 1);
	for (int i = 0; i < I; i++)
	{
		if (D < 0)
		{
			D = D + U;
			U = U + 8 * B;
			x = x - step;
			X[col] = x;
			Y[col] = y;
			col++;
		}
		else
		{
			D = D - V;
			V = V - 8 * A;
			y = y + step;
			X[col] = x;
			Y[col] = y;
			col++;
		}
	}
	int x_0 = X[col - 1];
	int y_0 = Y[col - 1];
	int pos = col;
	col--;
	D = B + A*(2 * b - 1)*(2 * b - 1) - 4 * R;
	U = 8 * B;
	V = 8 * A*(b - 1);
	for (int i = 0; i < I; i++)
	{
		if (D < 0)
		{
			D = D + U;
			U = U + 8 * B;
			x = x + step;
			X[col] = x;
			Y[col] = y;
			col--;
		}
		else
		{
			D = D - V;
			V = V - 8 * A;
			y = y - step;
			X[col] = x;
			Y[col] = y;
			col--;
		}
	}
	x = x_0;
	y = y_0;
	col = pos;
	//3part
	D = B + A*(2 * b - 1)*(2 * b - 1) - 4 * R;
	U = 8 * B;
	V = 8 * A*(b - 1);
	for (int i = 0; i < I; i++)
	{
		if (D < 0)
		{
			D = D + U;
			U = U + 8 * B;
			x = x - step;
			X[col] = x;
			Y[col] = y;
			col++;
		}
		else
		{
			D = D - V;
			V = V - 8 * A;
			y = y - step;
			X[col] = x;
			Y[col] = y;
			col++;
		}
	}
	//4 part
	D = B + A*(2 * b - 1)*(2 * b - 1) - 4 * R;
	U = 8 * B;
	V = 8 * A*(b - 1);
	for (int i = 0; i < I; i++)
	{
		if (D < 0)
		{
			D = D + U;
			U = U + 8 * B;
			x = x + step;
			X[col] = x;
			Y[col] = y;
			col++;
		}
		else
		{
			D = D - V;
			V = V - 8 * A;
			y = y - step;
			X[col] = x;
			Y[col] = y;
			col++;
		}
	}
	 x_0 = X[col - 1];
     y_0 = Y[col - 1];
	 pos = col;
	col--;
	D = B + A*(2 * b - 1)*(2 * b - 1) - 4 * R;
	U = 8 * B;
	V = 8 * A*(b - 1);
	for (int i = 0; i < I; i++)
	{
		if (D < 0)
		{
			D = D + U;
			U = U + 8 * B;
			x = x - step;
			X[col] = x;
			Y[col] = y;
			col--;
		}
		else
		{
			D = D - V;
			V = V - 8 * A;
			y = y + step;
			X[col] = x;
			Y[col] = y;
			col--;
		}
	}
	x = x_0;
	y = y_0;
	col = pos;
	
}
