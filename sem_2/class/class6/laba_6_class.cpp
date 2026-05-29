#include <iostream>
#include <string>
#include <clocale>
#include <cmath>
#include <cstdlib>
using namespace std;

class Iterator
{
	friend class List;
private:
	int* elem;
public:
	Iterator() { elem = 0; }
	Iterator(const Iterator& t) { elem = t.elem; };
	Iterator& operator=(const Iterator& i)
	{
		elem = i.elem;
		return *this;
	}
	bool operator==(const Iterator& i)
	{
		return elem == i.elem;
	}
	bool operator!=(const Iterator& i)
	{
		return elem != i.elem;
	}
	Iterator& operator++() { ++elem; return *this; }
	Iterator& operator--() { --elem; return *this; }

	Iterator& operator+(int p)
	{
		Iterator res = *this;
		res.elem += p;
		return res;
	}
	Iterator& operator-(int p)
	{
		Iterator res = *this;
		res.elem -= p;
		return res;
	}
	int& operator*() { return *elem; }


};

class List
{
	//перегруженные функции ввода-вывода
	friend ostream& operator<<(ostream& out, const List& l);
	friend istream& operator>>(istream& in, List& l);

private:
	int size;
	int* data; //указатель на динамический массив значений
	Iterator beg; //указатель на первый элемент
	Iterator end; // указатель на последний элемент 

public:
	//конструктор без параметров
	List()
	{
		size = 0;
		data = nullptr;
	}
	//коструктор с параметрами
	List(int s, int k = 0)
	{
		size = s;
		data = new int[size];
		for (int i = 0; i < size; i++)
		{
			data[i] = k;
		}
		beg.elem = &data[0];
		end.elem = &data[size];
	}
	//конструктор копирования
	List(const List& l)
	{
		size = l.size;
		data = new int[size];
		for (int i = 0; i < size; i++)
		{
			data[i] = l.data[i];
		}
		beg = l.beg;
		end = l.end;
	}
	//деструктор
	~List()
	{
		delete[] data;
		data = 0;
	}
	//операция присваивания
	List& operator=(const List& l)
	{
		if (this == &l) return *this;
		size = l.size;
		if (data != 0) delete[] data;
		data = new int[size];
		for (int i = 0; i < size; i++)
		{
			data[i] = l.data[i];
		}
		beg = l.beg;
		end = l.end;
		return *this;
	}
	//операция доступа по индексу
	int& operator[](int index)
	{
		if (index >= 0 && index < size) return data[index];
		else { cout << "\nError! Index > size!"; static int er = 0; return er; }
	}

	//операция для получения длины вектора
	int operator()()
	{
		return size;
	}

	//операция умножения элементов списка
	List operator*(const List& l)
	{
		int size_temp = min(size, l.size);
		List temp(size_temp);
		for (int i = 0; i < size_temp; ++i)
		{
			temp[i] = data[i] * l.data[i];
		}
		return temp;
	}

	Iterator first()
	{
		Iterator it;
		it.elem = data;
		return it;
	}
	Iterator last()
	{
		Iterator it;
		it.elem = data + size;
		return it;
	}


};

ostream& operator<<(ostream& out, const List& l)
{
	for (int i = 0; i < l.size; ++i)
	{
		out << l.data[i] << " ";
	}
	return out;
}
istream& operator>>(istream& in, List& l)
{
	for (int i = 0; i < l.size; ++i)
	{
		in >> l.data[i];
	}
	return in;
}

int main()
{
	setlocale(LC_ALL, "RU");
	system("chcp 1251 > nul");
	system("cls");

	List a(10);
	cout << "Создали список a из 10 элементов" << endl;
	cout << "Список а: " << a << endl;
	cout << "Введите элементы списка: " << endl; cin >> a;
	cout << "Список а: " << a << endl;
	cout << "Длина списка a: " << a() << endl;
	cout << "Первый элемент списка списка a: " << *(a.first()) << endl;
	cout << "Последний элемент списка списка a: " << *(a.last() - 1) << endl;
	a[2] = 100;
	cout << "Присвоили новое значение элементу под номером 3 - 100:" << endl;
	cout << "Список а: " << a << endl;
	cout << "Создали список b из 10 элементов" << endl;
	List b(10);
	cout << "Список b: " << b << endl;
	b = a;
	cout << "Присвоили списку b значения списка a" << endl;
	cout << "Список b: " << b << endl;
	List c(10);
	cout << "Создали список c из 10 элементов" << endl;
	cout << "Введите элементы списка c: " << endl; cin >> c;
	cout << "Список c: " << c << endl;
	cout << endl;
	List d = c * b;
	cout << "Создали список d из 10 элементов, значения c * b" << endl;
	cout << "Список d: " << d << endl;
	cout << "Итераторы." << endl;
	Iterator it = d.first();
	cout << "Первый элемент списка d: " << *it << endl;
	++it;
	cout << "Второй элемент списка d: " << *it << endl;
	it = it + 4;
	cout << "Шестой элемент списка d: " << *it << endl;
	cout << "Список d: " << d << endl;
	for (it = d.first(); it != d.last(); ++it)
	{
		cout << *it << " ";
	}

	return 0;
}