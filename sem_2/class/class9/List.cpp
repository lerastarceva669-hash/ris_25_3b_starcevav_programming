#include "List.h"
#include <iostream>
#include <clocale>
using namespace std;

List::List(int s)
{
	if (s < 0) throw invalid_argument("Ошибка: размер списка не может быть отрицательным");
	size = s;
	beg = new int[size];
	for (int i = 0; i < size;i++)
		beg[i] = 0;
}

List::List(const List& l)
{
	size = l.size;
	beg = new int[size];
	for (int i = 0; i < size;i++)
		beg[i] = l.beg[i];
}

List::~List() { delete[] beg; }

List::List(int s, int* mas)
{
	if (s < 0) throw invalid_argument("Ошибка: размер списка не может быть отрицательным");
	if(mas == nullptr && s > 0) throw invalid_argument("Ошибка: передан нулевой указатель на массив");
	size = s;
	beg = new int[size];
	for (int i = 0; i < size;i++)
		beg[i] = mas[i];
}

const List& List::operator=(const List& l)
{
	if (this == &l) return *this;
	delete[] beg;

	size = l.size;
	beg = new int[size];
	for (int i = 0; i < size; i++)
		beg[i] = l.beg[i];
	return *this;
}


int List::operator [](int i)
{
	if (i < 0 || i >= size)
		throw out_of_range("Ошибка: индекс выходит за границы списка");
	return beg[i];
}

List List::operator*(const List& l)
{
	int newSize = (size < l.size) ? size : l.size;

	if (newSize == 0) throw logic_error("Ошибка: один из списков пуст, умножение невозможно");;
	List result(newSize);

	for (int i = 0; i < newSize; i++)
		result.beg[i] = beg[i] * l.beg[i];
	return result;
}

List List::operator+(int n)
{
	if (n < 0)
		throw invalid_argument("Ошибка: смещение не может быть отрицательным");

	if (n >= size)
		throw out_of_range("Ошибка: смещение выходит за границы списка");

	List result(size - n);

	for (int i = 0; i < size - n; i++)
		result.beg[i] = beg[i + n];

	return result;
}

ostream& operator<<(ostream& out, const List& l)
{
	out << "[ ";
	for (int i = 0; i < l.size; i++)
		out << l.beg[i] << " ";
	out << "]";
	return out;
}

istream& operator>>(istream& in, List& l)
{
	cout << "Введите " << l.size << " элементов: ";
	for (int i = 0; i < l.size; i++)
		in >> l.beg[i];
	return in;
}