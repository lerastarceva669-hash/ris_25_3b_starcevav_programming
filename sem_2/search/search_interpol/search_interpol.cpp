#include <iostream>
#include <clocale>
using namespace std;

int search_interpol(int* mass, int key, int n)
{
	int left = 0;
	int right = n - 1;

	while (right >= left)
	{
		int middle = left + (((key - mass[left]) * (right - left)) / (mass[right] - mass[left]));

		if (mass[middle] == key) return middle + 1;
		else
		{
			if (mass[middle] < key) left = middle + 1;
			else right = middle - 1;
		}
	}
	return -1;
}

int main()
{
	setlocale(LC_ALL, "RU");
	int size, key, count = 0;
	int arr[50];

	cout << "Введите размер массива: ";
	cin >> size;

	cout << "Введите элементы массива: ";
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}

	cout << "Массив: ";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ' ';
	}

	cout << "\nВведите ключ: ";
	cin >> key;

	int num = search_interpol(arr, key, size);
	cout << "Элемент " << key << " встретился в " << num << " позиции";
	return 0;
}
