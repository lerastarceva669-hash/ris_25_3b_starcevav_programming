#include <iostream>
#include <clocale>
#include <cstdlib>
using namespace std;

int main()
{
	const int N = 4, M=3; //строки и столбцы
	int arr[N][M];
	int min_ell;
	int min_i;

	for (int i = 0; i < N; i++) // заполнение массива
	{
		for (int j = 0; j < M; j++)
		{
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < M - 1; ++i)
	{
		int min_ell = arr[1][i]; //вторая строка, идем по столбцам
		int min_i = i;

		for (int j = i + 1; j < M; ++j)
		{
			if (arr[1][j] < min_ell)
			{
				min_ell = arr[1][j];
				min_i = j;
			}
		}

		for (int k = 0; k < N; ++k)
		{
			int temp = arr[k][i];
			arr[k][i] = arr[k][min_i];
			arr[k][min_i] = temp;
		}
	}
	for (int i = 0; i < N;i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}


	return 0;
}
