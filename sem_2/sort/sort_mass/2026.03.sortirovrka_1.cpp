#include <iostream>
#include <clocale>
using namespace std;

int n, arr[50];
int main()
{
	setlocale(LC_ALL, "RU");
	cout << "Введите размер массива: ";
	cin >> n;

	for (int i = 0; i < n; i++) { 
		cin >> arr[i];
	}

	cout << "Неотсортированный массив: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;


	for (int i = 1; i < n; i++)
	{
		cout << "Шаг " << i << endl;
		for (int k = 0; k < i; k++) {
			cout << arr[k] << " ";
		}
		cout << " | ";

		for (int k = i; k < n; k++) {
			cout << arr[k] << " ";
		}
		cout << endl;  

		for (int j = i; j > 0; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}



	cout << endl;
	cout << "Отсортированыый массив: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	return 0;
}