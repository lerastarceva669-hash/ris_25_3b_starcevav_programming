#include <iostream>
#include <clocale>
using namespace std;

void sort_fast(int* ar, int size)
{
	int i = 0; 
	int j = size - 1;
	int mid = ar[size/2];

	while (i <= j)
	{
		while (ar[i] < mid) i++;
		while (ar[j] > mid) j--;

		if (i <= j)
		{
			int temp = ar[i];
			ar[i] = ar[j];
			ar[j] = temp;

			i++;
			j--;
		}
	}
	
	if (j > 0) sort_fast(ar, j + 1);
	if (i < size) sort_fast(ar + i, size - i);
}


int main()
{
	setlocale(LC_ALL, "RU");
	int n;
	int mass[50];
	cout << "Введите размер массива: "; cin >> n;
	cout << "Введите элементы массива: ";
	for (int i = 0; i < n; i++)
	{
		cin >> mass[i];
	}
	cout << "Исходный массив: ";
	for (int i = 0; i < n; i++)
	{
		cout << mass[i] << ' ';
	}

	sort_fast(mass, n);
	cout << endl;
	cout << "Упорядоченный массив: ";
	for (int i = 0; i < n; i++)
	{
		cout << mass[i] << ' ';
	}

	return 0;
}