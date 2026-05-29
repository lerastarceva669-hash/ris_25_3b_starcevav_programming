#include <iostream>
#include <string>
#include <clocale>
#include <cmath>
using namespace std;

class Pay
{
private:
	string name;
	double salary;
	int prize; //премия

public:

	Pay(string Name, double Salary, int Prize)
	{
		cout << "Конструктор с параметрами. " << endl;
		name = Name;
		salary = Salary;
		prize = Prize;
	}

	Pay()
	{
		cout << "Конструктор без параметрами. " << endl;
		this->name = "-";
		this->salary = 0;
		this->prize = 0;
	}

	Pay(const Pay& p)
	{
		cout << "Коструктор копирования. " << endl;
		this->name = p.name;
		this->salary = p.salary;
		this->prize = p.prize;
	}

	void SetName(string Name)
	{
		name = Name;
	}
	void SetSalary(double Salary)
	{
		salary = Salary;
	}
	void SetPrize(int Prize)
	{
		prize = Prize;
	}

	string GetName()
	{
		return this->name;
	}
	double GetSalary()
	{
		return this->salary;
	}
	int GetPrize()
	{
		return this->prize;
	}

	void Print()
	{
		cout << "ФИО: " << name << endl;
		cout << "Оклад: " << salary << endl;
		cout << "Премия: " << prize <<"%" << endl;
	}

	~Pay()
	{
		cout << "Деструктор." << endl;
	}
};


int main()
{
	setlocale(LC_ALL, "RU");
	cout << "==========================================================================" << endl;
	cout << "Лабараторная работа 2. Демонстрация работы программы." << endl;
	cout << "==========================================================================" << endl;

	cout << "Вызов конструктора с параметрами." << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	Pay prog1("Петров Петр Петрович", 50000, 10);
	prog1.Print();
	cout << "---------------------------------------------------------------------------" << endl;

	cout << "Вызов конструктора без параметров." << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	Pay prog2;
	prog2.Print();
	cout << "---------------------------------------------------------------------------" << endl;

	cout << "Вызов конструктора-копирования." << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	Pay prog3 = prog1;

	prog3.SetName("Кириллов Кирилл Кириллович");
	prog3.SetSalary(200000);
	prog3.SetPrize(30);

	prog3.Print();
	cout << "---------------------------------------------------------------------------" << endl;


	return 0;
}