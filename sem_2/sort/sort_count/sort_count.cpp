#include <iostream>
#include <clocale>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	int n;

	cout << "Введите размер массива: "; cin >> n;
	int* mass = new int[n];

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

	int min_el = mass[0];
	int max_el = mass[0];

	for (int i = 1; i < n; i++)
	{
		if (min_el > mass[i]) min_el = mass[i];
		if (max_el < mass[i]) max_el = mass[i];
	}

	int size = max_el - min_el + 1;

	int* mas_tmp = new int[size]();

	for (int i = 0; i < n; i++) //массив счетчиков
	{
		mas_tmp[mass[i] - min_el]++;
	}

	int index = 0;
	for (int i = 0; i < n; i++)
	{
		while (mas_tmp[i] > 0)
		{
			mass[index] = i + min_el;
			index++;
			mas_tmp[i]--;
		}
	}
	cout << endl;
	cout << "Отсортированный массив: ";
	for (int i = 0; i < n; i++)
	{
		cout << mass[i] << ' ';
	}
	cout << endl;

	delete[] mass;
	delete[] mas_tmp;

	return 0;
}