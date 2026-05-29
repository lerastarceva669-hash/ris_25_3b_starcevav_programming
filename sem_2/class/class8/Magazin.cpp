#include "Magazin.h"
#include <iostream>
#include <string>
using namespace std;

Magazin::Magazin(void) :Print() { page = 0; }
Magazin::~Magazin(void){}
Magazin::Magazin(string n, string a, int p) :Print(n, a) { page = p; }
Magazin::Magazin(const Magazin& m):Print(m) { name = m.name; author = m.author; page = m.page; }
void Magazin::SetPage(int p) { page = p; }

Magazin& Magazin::operator=(const Magazin& m)
{
	if (&m == this) return *this;
	Print::operator=(m);
	page = m.page;
	return *this;
}
void Magazin::Show()
{
	Print::Show();
	cout << "\nСТРАНИЦЫ: " << page<<endl;

}

void Magazin::Input()
{
	Print::Input();
	cout << "\nСтраницы: "; cin >> page;

}