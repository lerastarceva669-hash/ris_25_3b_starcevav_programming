#pragma once
#include <iostream>
#include <clocale>
#include "error.h"
using namespace std;

class List
{
	int size;
	int* beg;

public:
	List() { size = 0; beg = 0; }
	List(int s);
	List(int s, int* mas);
	List(const List& l);
	~List();
	const List& operator=(const List& l);
	int operator[](int i);
	//умножение элементов
	List operator*(const List& l);
	// +n переход вправо к элементу с номером n
	List operator+(int n);
	//определение размера списка
	operator int() const { return size; }

	friend ostream& operator<<(ostream& out, const List& l);
	friend istream& operator>>(istream& in, List& l);



};

