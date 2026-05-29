#include <iostream>
#include <clocale>
using namespace std;

int part_hoar(int* ar, int low, int high)
{
	int pivot = ar[high/2];

	int i = low;
	int j = high;

	while (ar[i] < pivot) i++;
	while (ar[j] > pivot) j--;

	if (i >= j) return j;

	swap(ar[i], ar[j]);
}

void quick_sort(int* ar, int low, int high)
{
	if (low < high)
	{
		int pivot_index = part_hoar(ar, low, high);

		quick_sort(ar, low, pivot_index);
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

	quick_sort(mass, 0, n - 1);
	cout << endl;
	cout << "Упорядоченный массив: ";
	for (int i = 0; i < n; i++)
	{
		cout << mass[i] << ' ';
	}

	return 0;
}