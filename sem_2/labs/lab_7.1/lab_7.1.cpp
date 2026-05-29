#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;


int st_n(int num, int n) {
	if (n == 0) return 1;
	if (num == 0) return 0;

	return pow(num, n);
}

double st_n(double num, int n) {
	if (n == 0) return 1;
	if (num == 0) return 0;

	return pow(num, 1.0/n);
}

int main() {
	setlocale(LC_ALL, "ru");

	int num, n, n_2;
	double num_2;

	cout << "Введите ваше число: "; cin >> num;
	cout << "Введите степень, в которую хотите возвести это число: "; cin >> n;
	cout << "Число " << num << " в степени " << n << ": " << st_n(num, n) << endl;

	cout << "Введите ваше число: "; cin >> num_2;
	cout << "Введите степень, которую хотите извлечь: "; cin >> n_2;
	cout << "Корень степени " << n_2 << " из числа " << num_2 << ": " << st_n(num_2, n_2) << endl;
	return 0;
}