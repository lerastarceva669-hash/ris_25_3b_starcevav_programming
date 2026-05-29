#include <iostream>
#include <string>
#include <clocale>
#include <cmath>
#include <cstdlib>
using namespace std;

class Object
{
public:
	Object() {};
	virtual ~Object() {};
	virtual void output() = 0;
};

class Person : public Object
{
	friend istream& operator>>(istream& in, Person& p);
	friend ostream& operator<<(ostream& out, const Person& p);

protected:
	string name;
	int age;
public:
	Person() { name = ""; age = 0; }
	Person(string Name, int Age) { name = Name; age = Age; }
	Person(Person& p) { name = p.name; age = p.age; }
	~Person() {};

	string GetName() { return name; }
	int GetAge() { return age; }
	void SetName(string Name) { name = Name; }
	void SetAge(int Age) { age = Age; }

	Person& operator=(const Person& p) { name = p.name; age = p.age; return *this; }
	void output() override
	{
		cout << "\nИмя: " << name;
		cout << "\nВозраст: " << age << endl;
	}

};

class Student : public Person
{
	friend istream& operator>>(istream& in, Student& s);
	friend ostream& operator<<(ostream& out, const Student& s);
protected:
	string subject;
	int mark;
public:
	Student() { subject = ""; mark = 0; }
	Student(string Name, int Age, string Subject, int Mark):Person(Name, Age) { this->SetSubject(Subject); this->SetMark(Mark); }
	Student(Student& s):Person(s) { subject = s.subject; mark = s.mark; }
	~Student() {};

	string GetSubject() { return subject; }
	int GetMark() { return mark; }
	void SetSubject(string& Subject) { subject = Subject; }
	void SetMark(int& Mark)
	{
		if (Mark < 1 || Mark > 5)
		{
			cout << "Invalid Mark: " << Mark << endl;
			this->mark = 0;
			return;
		}
		this->mark = Mark;
	}

	void CheckMark()
	{
		if (mark == 1 || mark == 2)
		{
			cout << "Студент " << name << " имеет неудовлетворительную оценку " << mark << " по предмету " << subject << "!" << endl;
		}
		else {
			cout << "Студент " << name << " имеет удовлетворительную оценку " << mark << " по предмету " << subject << "!" << endl;
		}
	}

	void output() override
	{
		cout << "\nИмя: " << name;
		cout << "\nВозраст: " << age;
		cout << "\nПредмет: " << subject;
		cout << "\nОценка: " << mark << endl;
	}
};

class Vector
{
	friend ostream& operator<<(ostream& out, const Vector& v);
private:
	Object** beg; // указатель на первый элемент
	int size;
	int cur; //текущая позиция
public:
	Vector() { beg = 0; size = 0; cur = 0; }
	~Vector() { if (beg != 0) delete[] beg; beg = 0; }
	Vector(int n)
	{
		beg = new Object* [n];
		cur = 0;
		size = n;
	}

	void add(Object* p)
	{
		if (cur < size)
		{
			beg[cur] = p;
			cur++;
		}
	}
};

istream& operator>>(istream& in, Person& p)
{
	cout << "Введите имя: ";
	getline(in, p.name);
	cout << "\nВведите возраст: ";
	(in >> p.age).ignore();
	cout << endl;
	return in;
}

ostream& operator<<(ostream& out, const Person& p)
{
	out << "Имя: " << p.name;
	out << "\nВозраст: " << p.age;
	cout << endl;
	return out;

}

istream& operator>>(istream& in, Student& s)
{
	cout << "Введите имя: ";
	getline(in, s.name);
	cout << "\nВведите возраст: ";
	(in >> s.age).ignore();
	cout << "\nВведите предмет: ";
	in >> s.subject;
	cout << "\nВведите оценку: ";
	in >> s.mark;
	cout << endl;
	return in;
}

ostream& operator<<(ostream& out, const Student& s)
{
	out << "Имя: " << s.name;
	out << "\nВозраст: " << s.age;
	out << "\nПредмет: " << s.subject;
	out << "\nОценка: " << s.mark;
	cout << endl;
	return out;

}

ostream& operator<<(ostream& out, const Vector& v)
{
	if (v.size == 0) out << "\nПустой вектор!";
	else
	{
		Object** p = v.beg;
		for (int i = 0; i < v.cur;i++)
		{
			(*p)->output();
			p++;
		}
	}
	return out;
}

int main()
{
	setlocale(LC_ALL, "RU");
	system("chcp 1251 > nul");
	system("cls");

	cout << "===============================================================================" << endl;
	cout << "\t\tЛабораторная работа 5. Реализация работы программы." << endl;
	cout << "===============================================================================" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "Конструктор без параметров." << endl;
	Person person;
	cout << person << endl;
	Student student;
	cout << student << endl;
	cout << "--------------------------------------------------------------------------------------" << endl;

	cout << "--------------------------------------------------------------------------------------" << endl;
	cout << "Конструктор с парaметрами." << endl<<endl;
	Vector vec(4);
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

	Object* p = &person1;
	vec.add(p);
	p = &student1;
	vec.add(p);
	cout << "\n======Vector======" << endl;
	cout << vec;
	cout << "-------------------------------------------------------------------------------------" << endl;

	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "\tДемонстрация работы метода, выдающего сообщение о неудовлетворительной оценке." << endl;
	Student stud1("Михаил", 24, "Физика", 5);
	cout << stud1 << endl;
	stud1.CheckMark();
	Student stud2("Егор", 19, "Физика", 2);
	cout << stud2 << endl;
	stud2.CheckMark();

	cout << "-------------------------------------------------------------------------------------" << endl;


	return 0;
}