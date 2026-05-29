#include <iostream>
#include <clocale>
using namespace std;

int search_line(int mass[], int key, int n)
{
	int count = 0;
	int i = 0;
	for (i; i < n; i++)
	{
		if (mass[i] == key) ++count;
	}

	return count;
}

int main()
{
	setlocale(LC_ALL, "RU");
	int size, key, count = 0;
	int arr[50];

	cout << "Введите размер массива: ";
	cin >> size;

	cout << "Введите элементы массива: " << endl;
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}

	cout << "Массив:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	cout << "Введите ключ: ";
	cin >> key;

	count = search_line(arr, key, size);
	cout << "Элемент " << key << " встретился " << count << " раз в массиве";
	return 0;
}