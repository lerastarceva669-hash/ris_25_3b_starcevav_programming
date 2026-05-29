#include <iostream>
#include <fstream>
#include <clocale>
#include <cstring>
#include <iomanip>

using namespace std;

struct Car
{
	char brand[50];
	int year;
	double price;
	char color[50];
};

void printFile(const char* f)
{
	ifstream in(f);
	if (!in)
	{
		cout << "Ошибка чтения" << endl;
		return;
	}

	Car car;
	int count = 0;
	cout << left << setw(15) << "Марка"
		<< setw(12) << "Год"
		<< setw(12) << "Цена"
		<< setw(12) << "Цвет" << endl;
	cout << endl;

	while (in.getline(car.brand, 50)) {
		in >> car.year;
		in.ignore();

		in >> car.price;
		in.ignore();
		in.getline(car.color, 50);
		cout << left << setw(15) << car.brand
			<< setw(12) << car.year
			<< setw(12) << fixed << setprecision(2) << car.price
			<< car.color << endl;
		cout << endl;
		count++;
	}
	cout << "Всего: " << count << endl;
	in.close();
}

void deleteElem(const char* f, int year)
{
	const char* temp_file = "C:\\Users\\Lera\\source\\repos\\lab_8\\temp_lab8.txt";
	ifstream in(f);
	if (!in)
	{
		cout << "Ошибка чтения" << endl;
		return;
	}

	ofstream temp_f(temp_file);
	if (!temp_f)
	{
		cout << "Ошибка чтения" << endl;
		return;
	}

	Car car;
	int del_count = 0;
	int k_count = 0;

	while (in.getline(car.brand, 50)) {
		in >> car.year;
		in.ignore();
		in >> car.price;
		in.ignore();
		in.getline(car.color, 50);

		if (car.year >= year) {
			temp_f << car.brand << endl;
			temp_f << car.year << endl;
			temp_f << car.price << endl;
			temp_f << car.color << endl;
			k_count++;
		}
		else {
			del_count++;
		}
	}
	cout << "Удалено: " << del_count << ", осталось: " << k_count << endl;

	in.close();
	temp_f.close();
	remove(f);
	rename (temp_file, f);
	
}

void addToBegin(const char* f, const Car& newCar)
{
	const char* temp_file = "temp_lab8.txt";
	ifstream in(f);
	if (!in)
	{
		cout << "Ошибка чтения" << endl;
		return;
	}

	ofstream temp_f("temp_lab8.txt");
	if (!temp_f)
	{
		cout << "Ошибка чтения" << endl;
		return;
	}

	temp_f << newCar.brand << endl;
	temp_f << newCar.year << endl;
	temp_f << newCar.price << endl;
	temp_f << newCar.color << endl;

	Car c;
	int copi = 0;
	while (in.getline(c.brand, 50))
	{
		in >> c.year;
		in.ignore();
		in >> c.price;
		in.ignore();
		in.getline(c.color, 50);

		temp_f << c.brand << endl;
		temp_f << c.year << endl;
		temp_f << c.price << endl;
		temp_f << c.color << endl;
		copi++;
	}
	in.close();
	temp_f.close();

	remove(f);
	rename(temp_file, f);
	cout << "Добавлено в начало. Скопировано: " << copi << endl;
}

int main()
{
	setlocale(LC_ALL, "RU");

	const char* f = "C:\\Users\\Lera\\source\\repos\\lab_8\\Fail_lab_8.txt";

	ifstream in(f);
	if (!in) {
		cout << "Error" << endl;
		return 1;
	}
	in.close();

	cout << "Содержимое файла: " << endl;
	printFile(f);
	
	//удаление элементов
	int year;
	cout << "Введите год для удаления: ";
	cin >> year;
	deleteElem(f, year);

	//печать после удаления
	cout << "Содержимое файла после удаления: " << endl;
	printFile(f);

	//добавление нового элементе в начало файла
	cout << "Добавление нового элемента в начало: " << endl;

	Car newCar;
	cout << "Введите марку автомобиля: ";
	cin.ignore();
	cin.getline(newCar.brand, 50);

	cout << "Введите год выпуска: ";
	cin >> newCar.year;

	cout << "Введите цену: ";
	cin >> newCar.price;

	cout << "Введите цвет: ";
	cin.ignore();
	cin.getline(newCar.color, 50);

	addToBegin(f, newCar);

	//Печать файла после добавления
	cout << "Содержимое файла после добавления: " << endl;
	printFile(f);
	return 0;
}