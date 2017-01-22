
#include<iostream>

#include<fstream>

//#ifndef _OPENMP;

//#endif _OPENMP;

#include <omp.h>



using namespace std;

const int max = 12;

double mtx[max][max + 1];
double mtx2[max][max + 1];
double help_mtx[6][7];
double x[max];
int n,m;

void reculc(int f, int e);
void res_mtx();
void help_matrix();
void help_res();
void res(int f, int e);
void res_simple(int f, int e);
void input();
void output();

int main()
{
	input();
	if (n <max)
		res_simple(0, n);
	else
	{
		m = n / 3;
#pragma omp parallel sections

		{
         #pragma omp section
			reculc(0, m);

         #pragma omp section
			reculc(m, 2 * m);

         #pragma omp section
			reculc(2 * m, n);

		}
		res_mtx();
		help_matrix();
		help_res();
#pragma omp parallel sections
		{
#pragma omp section
			res(0, m);
#pragma omp section
			res(m, 2 * m);
#pragma omp section
			res(2 * m, n);
		}
	}
	output();
	system("pause");
}

void output()
{
	for (int i = 0; i < n; i++)
	{
		cout << "X" << i << "="; printf("%.4lf", x[i]); cout << ";" << endl;
	}
}

void input()
{
	ifstream fin;
	fin.open("problems.txt");
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		if (i != 0) {
			fin >> mtx[i][i - 1]; mtx2[i][i-1] = mtx[i][i-1];
		}
		fin >> mtx[i][i];
		mtx2[i][i] = mtx[i][i];
		if (i != n - 1) {
			fin >> mtx[i][i + 1];    mtx2[i][i+1] = mtx[i][i+1];
		}
		fin >> mtx[i][n];
		mtx2[i][n] = mtx[i][n];
	}
}

void res_simple(int f, int e)
{
	double a[max];
	double b[max];
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(a));
	a[0] = -mtx[0][1] / mtx[0][0];
	b[0] = mtx[0][n] / mtx[0][0];
	for (int i = 1; i < n; i++)
	{
		a[i] = -mtx[i][i  + 1] / (mtx[i ][i  - 1] * a[i - 1] + mtx[ i][ i]);
		b[i] = (mtx[i ][n] - mtx[i ][i  - 1] * b[i - 1]) / (mtx[i ][i - 1] * a[i - 1] + mtx[i ][ i]);
	}
	x[n - 1] = (mtx[n - 1][n] - mtx[n - 1][n - 2] * b[n- 2]) / (mtx[n - 1][n - 2] * a[n-2] + mtx[n - 1][n - 1]);
	for (int i = n- 2; i >= 0; i--)
	{
		x[i] = a[i] * x[i + 1] + b[i];
	}
}

void res(int f, int e)
{
	double a[max/3+2];
	double b[max/3+2];
	a[0] = -mtx2[f][1] / mtx2[f][f];
	b[0] = mtx2[f][n] / mtx2[f][f];
	for (int i = 1; i < e-f; i++)
	{
		a[i] = -mtx2[i+f][i+f + 1] / (mtx2[i+f][i+f - 1] * a[i - 1] + mtx2[f+i][f+i]);
		b[i] = (mtx2[i+f][n] - mtx2[i+f][i+f - 1] * b[i - 1]) / (mtx2[i+f][i+f - 1] * a[i - 1] + mtx2[i+f][f+i]);
	}
	//x[e - 1] = (mtx[e - 1][n] - mtx[e - 1][e - 2] * b[e - 2]) / (mtx[e - 1][e - 2] * a[e - 2] + mtx[e - 1][e - 1]);
	for (int i = e - 2; i >=f; i--)
	{
		x[i] = a[i] * x[i + 1] + b[i];
	}
}

void help_res()
{
	double a[5];
	double b[5];
	a[0] = -help_mtx[0][1] / help_mtx[0][0];
	b[0] = help_mtx[0][6] / help_mtx[0][0];
	for (int i = 1; i < 5; i++)
	{
		a[i] = -help_mtx[i][i + 1] / (help_mtx[i][i - 1] * a[i - 1] + help_mtx[i][i]);
		b[i] = (help_mtx[i][6] - help_mtx[i][i - 1] * b[i - 1]) / (help_mtx[i][i - 1] * a[i - 1] + help_mtx[i][i]);
	}
	x[n - 1] = (mtx[n - 1][n] - mtx[n - 1][n - 2] * b[4]) / (mtx[n - 1][n - 2] * a[4] + mtx[n - 1][n - 1]);
	x[2 * m] = a[4] * x[n - 1] + b[4];
	x[2 * m - 1] = a[3] * x[2 * m] + b[3];
	x[m] = a[2] * x[2 * m - 1] + b[2];
	x[m - 1] = a[1] * x[m] + b[1];
	x[0] = a[0] * x[m - 1] + b[0];
}

void help_matrix()
{
	help_mtx[0][0] = mtx[0][0];  help_mtx[0][1] = mtx[0][1]; help_mtx[0][6] = mtx[0][n];
	help_mtx[1][1] = mtx[m - 1][m - 1];  help_mtx[1][2] = mtx[m - 1][m]; help_mtx[1][6] = mtx[m-1][n];
	help_mtx[2][1] = mtx[m][m - 1]; help_mtx[2][2] = mtx[m][m]; help_mtx[2][3] = mtx[m][m + 1]; help_mtx[2][6] = mtx[m][n];
	help_mtx[3][2] = mtx[2 * m - 1][2 * m - 2]; help_mtx[3][3] = mtx[2 * m - 1][2 * m - 1]; help_mtx[3][4] = mtx[2 * m - 1][2 * m]; help_mtx[3][6] = mtx[2*m-1][n];
	help_mtx[4][3] = mtx[2 * m][2 * m - 1]; help_mtx[4][4] = mtx[2 * m][2 * m]; help_mtx[4][6] = mtx[2*m][n];
	help_mtx[5][4] = mtx[n - 1][n - 2]; help_mtx[5][5] = mtx[n - 1][n - 1]; help_mtx[5][6] = mtx[n-1][n];
}

void res_mtx()
{
	for (int i = 0; i < m; i++)
	{
		mtx[i][i + 1] = mtx[i][m];
		if (i!=m-1) mtx[i][m] = 0;
	}
	for (int i = m; i < 2 * m; i++)
	{
		mtx[i][i - 1] = mtx[i][m - 1];
		if (i != m) mtx[i][m - 1] = 0;
		mtx[i][i + 1] = mtx[i][2 * m];
		if (i != 2 * m - 1) mtx[i][2 * m] = 0;
	}
	for (int i = 2 * m; i < n; i++)
	{
		mtx[i][i - 1] = mtx[i][2 * m - 1];
		if (i != 2 * m) mtx[i][2 * m - 1] = 0;
	}
}

void reculc(int f, int e)
{
	double c;
	for (int i = f + 1; i < e; i++)
	{
		c = mtx[i][i - 1] / mtx[i - 1][i - 1];
		for (int j = 0; j < n + 1; j++)
			mtx[i][j] = mtx[i][j] - mtx[i - 1][j] * c;
	}
	for (int i = e - 2; i >= f; i--)
	{
		c = mtx[i][i + 1] / mtx[i + 1][i + 1];
		for (int j = 0; j < n + 1; j++)
			mtx[i][j] -= mtx[i + 1][j] * c;
	}
}