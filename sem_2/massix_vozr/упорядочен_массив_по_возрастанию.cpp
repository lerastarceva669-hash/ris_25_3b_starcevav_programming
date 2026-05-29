#include <iostream>
#include <clocale>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	int n, arr[50];
	bool flag = true;

	cout << "Введите размер массива: "; cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << "Искодный массив:" << endl;
	for (int i = 0; i < n; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
	for (int i = 1; i < n && flag; ++i) {
		if (arr[i] < arr[i - 1]) flag = false;
	}

	if (flag) cout << "Массив упорядочен";
	else cout << "Массив не упорядочен";
	return 0;
}