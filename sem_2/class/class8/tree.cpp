#include "tree.h"
#include "Magazin.h"
#include <iostream>
#include <string>
using namespace std;

tree::~tree(void) {
	if (beg != 0) delete[] beg;
	beg = 0;
}

tree::tree()
{
	beg = nullptr;
	size = 0;
	cur = 0;
}

tree::tree(int n)
{
	beg = new Object * [n];
	cur = 0;
	size = n;
}
void tree::Add()
{
	Object* p = nullptr;
	cout << "1.Print" << endl;
	cout << "2.Magazin" << endl;
	int y;
	cin >> y;
	if (y == 1)
	{
		Print* a = new (Print);
		a->Input();
		p = a;
	}
	else if (y == 2)
	{
		Magazin* b = new Magazin;
		b->Input();
		p = b;
	}

	else
	{
		cout << "Неверный выбор!" << endl;
		return;
	}

	if (cur < size)
	{
		beg[cur] = p;
		cur++;
		cout << "Элемент добавлен.Теперь в группе " << cur << " элементов." << endl;
	}
	else
	{
		cout << "Группа заполнена! Невозможно добавить элемент." << endl;
		delete p;
	}

}
void tree::Show()
{
	if (cur == 0) { cout << "Группа пуста" << endl; return; }
	Object** p = beg;
	cout << "\n=== ГРУППА (всего: " << cur << ") ===" << endl;
	for (int i = 0; i < cur; i++)
	{
		(*p)->Show();
		p++;
	}
}
int tree::operator()()
{
	return cur;
}
void tree::Del()
{
	if (cur == 0) { cout << "Группа пуста, нечего удалять!" << endl; return; }
	cur--;
}

void tree::HandlEvent(const Event& e)
{
	if (e.what == evMessage)
	{
		Object** p = beg;
		for (int i = 0; i < cur; i++)
		{
			(*p)->HandlEvent(e);
			p++;
		}
	}
}