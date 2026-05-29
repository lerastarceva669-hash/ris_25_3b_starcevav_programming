#include "laba_3_class.h"

#include <iostream>
#include <string>
#include <clocale>
#include <cmath>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	cout << "=======================================================================================" << endl;
	cout << "\t\tЛабораторная работа 3. Реализация работы программы." << endl;
	cout << "=======================================================================================" << endl;

	cout << "----------------------------------------------" << endl;
	cout << "Конструктор без параметров." << endl;
	Pair prog_1;
	cout << "a = " << prog_1 << endl;
	cout << "----------------------------------------------" << endl;


	cout << "----------------------------------------------" << endl;
	cout << "Конструктор с параметрами." << endl;
	Pair a(3, 5);
	Pair b(2, 8);

	cout << "first = " << a << endl;
	cout << "second = " << b << endl;
	cout << "Вычитание: " << a - b << endl;

	cout << "Добавление int константы 5 к first: " << endl;
	cout << "first + 5 = " << a + 5 << endl;
	cout << "5 + first = " << 5 + a << endl;

	cout << "Добавление double константы 5.5 к first: " << endl;
	cout << "first + 5.5 = " << a + 5.5 << endl;
	cout << "5.5 + first = " << 5.5 + a << endl;

	cout << "Добавление int константы 5 к second: " << endl;
	cout << "second + 5 = " << b + 5 << endl;
	cout << "5 + second = " << 5 + b << endl;

	cout << "Добавление double константы 5.5 к first: " << endl;
	cout << "second + 5.5 = " << b + 5.5 << endl;
	cout << "5.5 + second = " << 5.5 + b << endl;
	cout << "----------------------------------------------" << endl;

	cout << "----------------------------------------------" << endl;
	cout << "Конструктор копирования." << endl;
	Pair prog_2 = a;
	prog_2.SetFirst(22);
	prog_2.SetSecond(10.5);
	cout << "a = " << prog_2 << endl;

	cout << "----------------------------------------------" << endl;

	return 0;
}