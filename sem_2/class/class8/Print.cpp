#include "Print.h"
#include "Event.h"
#include <iostream>
#include <string>
using namespace std;
Print::Print(void)
{
	name = "";
	author = "";
}
Print::~Print(void) {}
Print::Print(string n, string a)
{
	name = n;
	author = a;
}
Print::Print(const Print& other)
{
	name = other.name;
	author = other.author;
}
void Print::SetName(string n)
{
	name = n;
}

void Print::SetAuthor(string a)
{
	author = a;
}
Print& Print::operator=(const Print& other)
{
	if (this != &other)
	{
		name = other.name;
		author = other.author;
		return *this;
	}
	return *this;
}

void Print::Show()
{
	cout << "\nНАЗВАНИЕ: " << name;
	cout << "\nАВТОР: " << author << endl;
}

void Print::Input()
{
	cout << "\nНазвание: "; cin >> name;
	cout << "\nАвтор: "; cin >> author;

}

void Print::HandlEvent(const Event& e)
{
	if (e.what == evMessage)
	{
		switch (e.command)
		{
		case cmGet: 
			cout << "Name: " << GetName() << endl;
			break;
		}
	}
}