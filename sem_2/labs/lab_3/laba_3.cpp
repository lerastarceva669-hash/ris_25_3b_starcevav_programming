#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;


const double e = 0.0001;
double x; // аргумент функции
int n; //количество членов

//функция рекурсивно вычисляет n-й член ряда
double C_n(double& x, int& n, int i, double a)
{
	if (i == n) {
		return a;
	}

	else {
		double next_a = a * (-4 * x * x) / ((2 * i + 1) * (2 * i + 2));
		return C_n(x, n, i + 1, next_a);
	}
}


//функция, которая выводит наш ответ
double C_y(double& x)
{
	return ((pow(e, x) - pow(e, -x))) / 2;
}

int main() {

	setlocale(LC_ALL, "RU");
	cout << "Введите значение аргумента х: ";
	cin >> x;
	cout << endl;
	cout << "Введите номер члена, до которого нужно дойти: ";
	cin >> n;
	cout << endl;

	//проверка на n
	while (n < 1)
	{
		cout << "Введите другое число: ";
		cin >> n;
		cout << endl;
	}

	cout << "При аргументе " << x << " и количестве " << n << " членов" << endl;
	cout << n << " член ряда: " << C_n(x, n, 1, -4 * x * x / 2) << endl;
	cout << "Значение функции: " << C_y(x) << endl;

	return 0;
}