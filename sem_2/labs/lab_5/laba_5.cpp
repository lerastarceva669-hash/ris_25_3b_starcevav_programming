#include <iostream>
#include <clocale>
using namespace std;

int max_sum(int arr[50][50], int n, int m)
{
	int max = -10000000;

	for (int i = 0; i < m-1; ++i)
	{
		int sum = 0;
		for (int k = 0; k < n-1; ++k)
		{
			sum += arr[k][i];
			if (sum >= max)
			{
				max = sum;
			}
		}
		--n;
		cout << "Сумма элементов " << i+1 << " столбца: " << sum<< endl;
	}
	return max;
}

void input_arr(int arr[50][50], int n, int m)
{
	cout << "Введите элементы массива:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}
}

void print_arr(int arr[50][50], int n, int m)
{
	cout << "Полученный массив:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << arr[i][j]<<'\t';
		}
		cout << endl;
	}

}

int main()
{
	setlocale(LC_ALL, "RU");
	int arr[50][50];
	int n, m;


	cout << "Введите количество строк и столбцов в массиве:\n";
	cin >> n >> m;

	input_arr(arr, n, m);

	print_arr(arr, n, m);

	int max = max_sum(arr, n, m);

	cout << "Максимальная сумма элементов: " << max;

	return 0;
}