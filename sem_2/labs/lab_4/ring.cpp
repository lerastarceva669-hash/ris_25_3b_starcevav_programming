#include <iostream>
#include <clocale>
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	int arr[100];
	int n;
	int k;
	cout << "Введите размер массива: ";
	cin >> n;

	if (n <= 0 || n >= 101) {
		while (n <= 0 || n >= 101) {
			cout << "Введите другой массив: ";
			cin >> n;
		}
	}

	cout << "Введите k-начало печати: ";
	cin >> k;
	
	if (k <= 0 || k >= n) {
		while (k <= 0 || k >= n) {
			cout << "Введите другой размер: ";
			cin >> k;
		}
	}

	cout << "Исходный массив: ";
	for (int i = 0; i < n; i++) {
		arr[i] = -100 + rand() % 100;
		cout << arr[i] << ' ';
	}

	cout << endl;
	cout << "Массив с k-ого элемента влево: ";
	for (int i = k - 1; i >= k -2; --i) {
		cout << arr[i] << ' ';
	}
	cout << endl;

	int temp = 0;
	for (int i = 1; i < n-1; i++){
		arr[temp] = arr[i];
		temp++;
	}

	cout << "Массив после удаления первого и последнего элементов: ";
	for (int i = 0; i < temp; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;

	if (k > temp)
		cout << "В массиве нет k-ого элемента";
	else {
		cout << "Массив с k-ого элемента вправо: ";
		for (int i = k - 1; i < k + 1; i++) {
			cout << arr[i] << ' ';
		}
	}

	return 0;
}