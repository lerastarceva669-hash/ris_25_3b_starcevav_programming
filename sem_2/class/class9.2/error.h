#pragma once
#include <string>
#include <iostream>
using namespace std;

class Error
{
protected:
	string msg;
public:
	Error() { msg = "Неизвестная ошибка!\n"; }
	virtual ~Error() {}
	virtual void what() { cout << msg; }
};

class IndexError : public Error //ошибка в индексе 
{
public:
	IndexError()
	{
		msg = "Ошибка индекса: выход за границы списка!\n";
	}

	IndexError(int index, int size)
	{
		msg = "Ошибка индекса";
	}

	virtual void what() { cout << msg; }
};


class SizeError : public Error
{
public:
	SizeError()
	{
		msg = "Ошибка размера: недопустимый размер списка!\n";
	}

	virtual void what() { cout << msg; }
};

class NegativeSizeError : public SizeError
{
public:
	NegativeSizeError()
	{
		msg = "Ошибка отрицательного размера: размер списка не может быть отрицательным!\n";
	}

	NegativeSizeError(int size)
	{
		msg = "Ошибка отрицательного размера: размер = " + to_string(size) +
			" является отрицательным!\n";
	}

	virtual void what() { cout << msg; }
};

// Ошибка нулевого указателя
class NullPointerError : public SizeError
{
public:
	NullPointerError()
	{
		msg = "Ошибка нулевого указателя: указатель на массив равен null!\n";
	}

	virtual void what() { cout << msg; }
};


// Ошибка пустого списка
class EmptyListError : public Error
{
public:
	EmptyListError()
	{
		msg = "Ошибка пустого списка: операция не может быть выполнена над пустым списком!\n";
	}

	virtual void what() { cout << msg; }
};


class MultiplicationError : public Error
{
public:
	MultiplicationError()
	{
		msg = "Ошибка умножения: невозможно умножить списки разного размера!\n";
	}

	MultiplicationError(int size1, int size2)
	{
		msg = "Ошибка умножения: размеры списков отличаются (размер1 = " +
			to_string(size1) + ", размер2 = " + to_string(size2) + ")!\n";
	}

	virtual void what() { cout << msg; }
};

// Ошибка смещения (для оператора +n)
class ShiftError : public Error
{
public:
	ShiftError()
	{
		msg = "Ошибка смещения: недопустимая операция смещения!\n";
	}

	virtual void what() { cout << msg; }
};


// Ошибка отрицательного смещения
class NegativeShiftError : public ShiftError
{
public:
	NegativeShiftError()
	{
		msg = "Ошибка отрицательного смещения: значение смещения не может быть отрицательным!\n";
	}

	NegativeShiftError(int n)
	{
		msg = "Ошибка отрицательного смещения: смещение = " + to_string(n) + " является отрицательным!\n";
	}

	virtual void what() { cout << msg; }
};

// Ошибка смещения за границы
class OutOfRangeShiftError : public ShiftError
{
public:
	OutOfRangeShiftError()
	{
		msg = "Ошибка смещения за границы: смещение превышает размер списка!\n";
	}

	OutOfRangeShiftError(int n, int size)
	{
		msg = "Ошибка смещения за границы: смещение = " + to_string(n) +
			" превышает размер списка = " + to_string(size) + "!\n";
	}

	virtual void what() { cout << msg; }
};