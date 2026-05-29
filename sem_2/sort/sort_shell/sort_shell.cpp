#include <iostream>
#include <clocale>
using namespace std;


void sort_shell(int* ar, int size)
{
	for (int step = size / 2; step > 0; step /= 2)
	{
		for (int i = step; i < size; i++)
		{
			int temp = ar[i];
			int j;


			for (j = i; j >= step && ar[j - step] > temp; j -= step)
			{
				ar[j] = ar[j - step];
			}
			ar[j] = temp;
		}
	}
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

	sort_shell(mass, n);

	cout << endl;
	cout << "Упорядоченный массив: ";
	for (int i = 0; i < n; i++)
	{
		cout << mass[i] << ' ';
	}

	return 0;
}