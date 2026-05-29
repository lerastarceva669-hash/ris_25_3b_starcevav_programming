#include <iostream>
#include <clocale>
using namespace std;

int n, arr[50], temp;

int main()
{
	setlocale(LC_ALL, "RU");
	cout << "Введите размер массива: ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < n; i++)
	{
		cout << "Шаг " << i + 1 << endl;
		for (int k = 0; k < i; k++) {
			cout << arr[k] << " ";
		}
		cout << " | ";
		for (int k = i; k < n; k++) {
			cout << arr[k] << " ";
		}
		cout << endl;
	
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < n;i++) {
		cout << arr[i] << " ";
	}
	return 0;


}