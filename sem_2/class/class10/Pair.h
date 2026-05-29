#pragma once

#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <fstream>
using namespace std;

class Pair
{
private:
	int first;
	double second;
public:
	Pair();
	Pair(int, double);
	Pair(const Pair& p);
	Pair operator=(const Pair& p);

	~Pair();

	int getFirst() const;
	double getSecond() const;
	void setFirst(int f);
	void setSecond(double s);

	Pair operator-(const Pair& p) const;
	Pair operator+(double k) const;
	bool operator<(const Pair& p) const;
	bool operator==(const Pair& p) const;

	friend ostream& operator<<(ostream& out, const Pair& p);
	friend istream& operator>>(istream& in, Pair& p);

	friend fstream& operator<<(fstream& fout, const Pair& p);
	friend fstream& operator>>(fstream& fin, Pair& p);
	
};

#endif