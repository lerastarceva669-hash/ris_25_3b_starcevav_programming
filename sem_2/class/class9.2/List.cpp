#include "List.h"
#include "error.h"
#include <iostream>
using namespace std;

List::List(int s)
{
    if (s < 0)
        throw NegativeSizeError(s);

    if (s == 0)
    {
        size = 0;
        beg = nullptr;
        return;
    }

    size = s;
    beg = new int[size];
    for (int i = 0; i < size; i++)
        beg[i] = 0;
}

List::List(int s, int* mas)
{
    if (s < 0)
        throw NegativeSizeError(s);

    if (s > 0 && mas == nullptr)
        throw NullPointerError();

    if (s == 0)
    {
        size = 0;
        beg = nullptr;
        return;
    }

    size = s;
    beg = new int[size];
    for (int i = 0; i < size; i++)
        beg[i] = mas[i];
}

List::List(const List& l)
{
    size = l.size;
    if (size > 0)
    {
        beg = new int[size];
        for (int i = 0; i < size; i++)
            beg[i] = l.beg[i];
    }
    else
    {
        beg = nullptr;
    }
}

List::~List()
{
    delete[] beg;
}

const List& List::operator=(const List& l)
{
    if (this == &l)
        return *this;

    delete[] beg;
    size = l.size;

    if (size > 0)
    {
        beg = new int[size];
        for (int i = 0; i < size; i++)
            beg[i] = l.beg[i];
    }
    else
    {
        beg = nullptr;
    }

    return *this;
}

int List::operator[](int i)
{
    if (i < 0 || i >= size)
        throw IndexError(i, size);

    return beg[i];
}

List List::operator*(const List& l)
{
    if (size == 0 || l.size == 0)
        throw EmptyListError();

    if (size != l.size)
        throw MultiplicationError(size, l.size);

    List result(size);
    for (int i = 0; i < size; i++)
        result.beg[i] = beg[i] * l.beg[i];

    return result;
}

List List::operator+(int n)
{
    if (n < 0)
        throw NegativeShiftError(n);

    if (n >= size)
        throw OutOfRangeShiftError(n, size);

    if (size - n == 0)
        throw EmptyListError();

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
    cout << "Enter " << l.size << " elements: ";
    for (int i = 0; i < l.size; i++)
        in >> l.beg[i];
    return in;
}