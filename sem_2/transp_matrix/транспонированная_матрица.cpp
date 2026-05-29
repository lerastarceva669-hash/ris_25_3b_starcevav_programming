#include <iostream>
#include <clocale>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	int n, k;
	int matrix[10][10];
	int transp[10][10];
	cout << "Введите количество строк и столбцов: "; cin >> n >> k;

	cout << "Введите элементы матрицы: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cin >> matrix[i][j];
		}
	}
	cout << "Исходная матрица: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			transp[j][i] = matrix[i][j];
		}
	}
	cout << "Транспонированная матрица: " << endl;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {
			cout << transp[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}
	