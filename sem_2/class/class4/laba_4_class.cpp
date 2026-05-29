#include <iostream>
#include <string>
#include <clocale>
#include <cmath>
#include <cstdlib>
using namespace std;

class Person
{
protected:
	string name;
	int age;

public:
	Person() { this->name = ""; this->age = 0; }
	Person(const string& name, const int& age) { this->SetName(name); this->SetAge(age); }
	Person(const Person& p) { this->name = p.name; this->age = p.age; }
	~Person() {};

	void SetName(const string& name) { this->name = name; };
	void SetAge(const int& age)
	{
		if (age < 0)
		{
			cout << "Error! Age: " << age << endl;
			return;
		}
		this->age = age;
	}
	string GetName() { return this->name; }
	int GetAge() { return this->age; }
	

	Person& operator=(const Person& p)
	{
		this->name = p.name;
		this->age = p.age;
		return *this;
	}

	friend istream& operator>>(istream& in, Person& p)
	{
		string temp;
		int a;

		cout << "Имя: "; in >> temp;
		p.SetName(temp);
		cout << "Возраст: "; in >> a;
		p.SetAge(a);

		return in;
	}

	friend ostream& operator<<(ostream& out, Person& p)
	{
		out << "Имя: " << p.name << endl;
		out << "Возраст: " << p.age << endl;
		return out;
	}
};

class Student : public Person
{
protected:
	string subject;
	int mark;
public:
	Student() { this->subject = ""; this->mark = 0; }
	Student(const string& name, const int& age, const string& subject, const int& mark) : Person(name, age)
	{
		this->SetSubject(subject);
		this->SetMark(mark);
	}
	Student(const Student& s) : Person(s)
	{
		this->subject = s.subject;
		this->mark = s.mark;
	}
	~Student() {};

	void SetSubject(const string& subject) { this->subject = subject; }
	void SetMark(const int& mark)
	{
		if (mark <= 0 || mark >= 6)
		{
			cout << "Error! Mark: " << mark << endl;
			this->mark = 0;
			return;
		}
		this->mark = mark;
	}
	string GetSubject() { return this->subject; }
	int GetMark() { return this->mark; }

	friend istream& operator>>( istream& in, Student& s)
	{
		string temp;
		int a;

		Person* p_s = &s;
		in >> *p_s;

		cout << "Предмет: "; in >> temp;
		s.SetSubject(temp);
		cout << "Оценка: "; in >> a;
		s.SetMark(a);

		cout << endl;
		return in;
	}

	friend ostream& operator<<(ostream& out, Student& s)
	{
		Person* p_s = &s;
		out << *p_s;
		out << "Предмет: " << s.subject << endl;
		out << "Оценка: " << s.mark << endl;
		return out;
	}
};

void PrintPersonInfo(Person p)
{
	cout << "Функция получила объект Person: " << endl;
	cout << p << endl;
	cout << "Имя полученного объекта: " << p.GetName() << endl;
	cout << "Возраст полученного объекта: " << p.GetAge() << endl;

}

Person CreateDefPerson()
{
	cout << "Функция CreateDefPerson создает новый объект Person" << endl;
	Person defPerson("Кристина", 18);
	return defPerson;
}



int main()
{
	setlocale(LC_ALL, "RU");
	system("chcp 1251 > nul");
	system("cls");
	cout << "===============================================================================" << endl;
	cout << "\t\tЛабораторная работа 4. Реализация работы программы." << endl;
	cout << "===============================================================================" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "Конструктор без параметров." << endl;
	Person person;
	cout << person<<endl;
	cout << "-----------------------------------------------------------------------" << endl;

	cout << "-----------------------------------------------------------------------" << endl;
	cout << "Конструктор с парaметрами." << endl;
	Person person1("Иван", 23);

	Student student1("Валерия", 19, "Математика", 4);
	Student student2;

	cout << "======Person======" << endl;
	cout << person1 << endl;

	cout << "======Student======" << endl;
	cout << student1 << endl;

	cout << "======Ввод student======" << endl;
	cin >> student2;
	cout << "======Вывод student======" << endl;
	cout << student2 << endl;
	cout << "-----------------------------------------------------------------------" << endl;

	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "\t\tДемонстрация работы функций с объекстами базового класса Person" << endl;
	Person pers1("Василь", 24);
	cout << "Функция, получающая объект класса Person. " << endl;
	cout << "Исходный объект: "<< endl;
	cout << pers1 << endl;
	PrintPersonInfo(pers1);
	cout << endl;
	cout << "Функция, возвращающая объект класса Person. " << endl;
	Person newPerson1 = CreateDefPerson();
	cout << "Возвращенный объект: " << endl;
	cout << newPerson1 << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;

	return 0;
}