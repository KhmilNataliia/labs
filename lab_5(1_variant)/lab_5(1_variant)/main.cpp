#include<iostream>
#include<fstream>

using namespace std;


class matrix
{
public:
	int n, m;
	class List
	{
	public:
		int data;
		List* next;
	};
	List* *mtx = new List*[n];
	List** create(int n, int m)
	{
		int i;
		List* temp;
		for (int j = 0; j < n; j++)
		{
			mtx[j] = new List;
			mtx[j]->data = 0;
			temp = mtx[j];
			for (i = 1; i < m; i++)
			{
				temp->next = new List;
				temp->next->data = 0;
				temp = temp->next;
			}
			temp->next = NULL;
		}
		return mtx;
	}
	void write(int y, int x, int val)
	{
		List* temp = mtx[y];
		int i = 0;
		while (i < x) { temp = temp->next; i++; }
		temp->data = val;
	}
	int read(int y, int x)
	{
		int val;
		List* temp = mtx[y];
		int i = 0;
		while (i < x) { temp = temp->next; i++; }
		val = temp->data;
		return val;
	}
};


int main()
{
	fstream fin;
	fin.open("matrix.txt");
	matrix mtx;
	fin >> mtx.n;
	fin >> mtx.m;
	mtx.mtx = mtx.create(mtx.n,mtx.m);
	int val;
	for (int i = 0; i < mtx.n; i++)
	{
		for (int j = 0; j < mtx.m; j++)
		{
			fin >> val;
			mtx.write(i, j, val);
		}
	}
	cout << "the size of matrix is:" << mtx.n << "x" << mtx.m << endl;
	cout << endl;
	cout << "the matrix:" << endl;
	for (int i = 0; i < mtx.n; i++)
	{
		for (int j = 0; j < mtx.m; j++)
		{
			val = mtx.read(i, j);
			cout << val << "  ";
		}
		cout << endl;
	}
	cout << endl;
	system("pause");
}