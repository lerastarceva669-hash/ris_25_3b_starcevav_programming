#include <iostream>
#include <clocale>
using namespace std;

int part_lomuto(int* ar, int low, int high)
{
	int pivot = ar[high];
	int i = low - 1;

	for (int j = low; j < high; j++)
	{
		if (ar[j] <= pivot)
		{
			i++;
			swap(ar[i], ar[j]);
		}
	}

	swap(ar[i + 1], ar[high]);

	return i + 1;
}

void quick_sort(int* ar, int low, int high)
{
	if (low < high)
	{
		int pivot_index = part_lomuto(ar, low, high);

		quick_sort(ar, low, pivot_index - 1);
		quick_sort(ar, pivot_index + 1, high);
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

	quick_sort(mass, 0, n-1);
	cout << endl;
	cout << "Упорядоченный массив: ";
	for (int i = 0; i < n; i++)
	{
		cout << mass[i] << ' ';
	}

	return 0;
}