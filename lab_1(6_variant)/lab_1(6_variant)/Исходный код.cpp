#include <iostream>;
#include <fstream>;
#include <vector>;
#include <algorithm>;
using namespace std;

int m, n, k;

struct line
{
	int i, j;
	double Vmin, Vmax, V_av;
	int B[100], A[100];
};

double S_a[100], S_b[100];

double optimal(int **mtx);


int main()
{
	int i, j;
	ifstream fin;
	fin.open("pay_matrix.txt");
	fin >> m >> n;

	int** matrix = new int*[m];
	for (int i = 0; i < m; i++)
		matrix[i] = new int[n];

	for (int i(0); i < m; i++)
	{
		for (int j(0); j < n; j++)
		{
			fin >> matrix[i][j];
		}
	}
	cout << "input the number of sets K=";
	cin >> k;
	double cost_of_game = optimal(matrix);
	cout << "the cost of game is=" << cost_of_game << endl;
	cout << "the optimal mixed strategies of players are:" << endl;
	cout << "S_A=(";
	for (int i = 0; i < m; i++)
		cout << S_a[i] << "; ";
	cout << ")" << endl;
	cout << "S_B=(";
	for (int i = 0; i < n; i++)
		cout << S_b[i] << "; ";
	cout << ")" << endl;
	system("pause");
}

double optimal(int **mtx)
{
	line lines[1000];
	double etalon_min = 0;
	double etalon_max = 0;
	memset(S_a, 0, sizeof(S_a));
	memset(S_b, 0, sizeof(S_b));
	int min = 0; int max = 0;
	for (int i = 0; i < m; i++) //filling first line
	{
		for (int j = 0; j < n; j++)
		{
			if (mtx[i][j]>etalon_max)
			{
				etalon_max = mtx[i][j];
				max = i;
			}
		}
	}
	etalon_min = etalon_max;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (mtx[i][j]<etalon_min)
			{
				etalon_min = mtx[i][j];
				min = j;
			}
		}
	}
	lines[0].j = min;
	lines[0].i = max;
	for (int i = 0; i < n; i++)
	{
		lines[0].B[i] = mtx[max][i];
		if (etalon_max>mtx[max][i])
			etalon_max = mtx[max][i];
	}
	for (int i = 0; i < m; i++)
	{
		lines[0].A[i] = mtx[i][min];
		if (etalon_min < mtx[i][min])
			etalon_min = mtx[i][min];
	}
	lines[0].Vmax = etalon_min;
	lines[0].Vmin = etalon_max;
	lines[0].V_av = (lines[0].Vmax + lines[0].Vmin) / 2;
	S_a[lines[0].i]++;
	S_b[lines[0].j]++;
	for (int i = 1; i < k; i++)//filling k-th line
	{
		 etalon_max = 0;
		int min = 0; int max = 0;
		for (int l = 0; l < m; l++)
		{
			if (etalon_max < lines[i - 1].A[l])
			{
				etalon_max = lines[i - 1].A[l];
				max = l;
			}
		}
		lines[i].i = max;
		etalon_max = 1000;
		for (int j = 0; j < n; j++)
		{
			lines[i].B[j] =lines[i-1].B[j]+ mtx[max][j];
			if (etalon_max>lines[i].B[j])
				etalon_max = lines[i].B[j];
		}
		etalon_min = 10000;
		for (int j = 0; j < n; j++)
		{
			if (etalon_min > lines[i].B[j])
			{
				etalon_min = lines[i].B[j];
				min = j;
			}

		}
		lines[i].j = min;
		etalon_min = 0;
		for (int j = 0; j < m; j++)
		{
			lines[i].A[j] =lines[i-1].A[j]+ mtx[j][min];
			if (etalon_min < lines[i].A[j])
				etalon_min = lines[i].A[j];
		}
		lines[i].Vmax = etalon_min/(i+1);
		lines[i].Vmin = etalon_max/(i+1);
		lines[i].V_av = (lines[i].Vmax + lines[i].Vmin) / 2;
		S_a[lines[i].i]++;
		S_b[lines[i].j]++;
	}
	for (int i = 0; i < m; i++)
		S_a[i] = S_a[i] / k;
	for (int i = 0; i < n; i++)
	S_b[i] = S_b[i] / k;
	return lines[k - 1].V_av;
}