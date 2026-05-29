#include "Pair.h"
#include <iomanip>

Pair::Pair() { first = 0, second = 0.0; }
Pair::Pair(int f, double s) { first = f; second = s; }
Pair::Pair(const Pair& p) { first = p.first; second = p.second; }
Pair::~Pair(){}

int Pair::getFirst() const { return first; }
double Pair::getSecond() const { return second; }
void Pair::setFirst(int f) { first = f; }
void Pair::setSecond(double s) { second = s; }

Pair Pair::operator-(const Pair& p) const
{
	return Pair(first - p.first, second - p.second);
}

Pair Pair::operator=(const Pair& p)
{
	if (this != &p) {
		first = p.first;
		second = p.second;
	}
	return *this;
}

Pair Pair::operator+(double k) const
{
	Pair result(*this);

	if (k == static_cast<int>(k)) result.first += static_cast<int>(k);
	else result.second += k;

	return result;
}

bool Pair::operator<(const Pair& other) const {
	if (first != other.first)
		return first < other.first;
	return second < other.second;
}


bool Pair::operator==(const Pair& p) const
{
	return (first == p.first) && (second == p.second);
}

istream& operator>>(istream& in, Pair& p)
{
	cout << "Введите первое число (целое): ";
	in >> p.first;
	cout << "Введите второе число (вещественное): ";
	in >> p.second;
	return in;
}

ostream& operator<<(ostream& out, const Pair& p)
{
	out << p.first << ":" << p.second;
	return out;
}

fstream& operator>>(fstream& fin, Pair& p)
{
	
	fin >> p.first;
	fin >> p.second;
	return fin;
}

fstream& operator<<(fstream& fout, const Pair& p)
{
	fout << p.first << ":" << p.second;
	return fout;
}
