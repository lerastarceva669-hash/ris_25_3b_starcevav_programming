#include "Pair.h"
using namespace std;

Pair::Pair() { first = 0; second = 0.0; }
Pair::Pair(int f, double s) { first = f; second = s; }
Pair::Pair(const Pair& p) { first = p.first; second = p.second; }
Pair::~Pair(){}

int Pair::getFirst() const { return first; }
double Pair::getSecond() const { return second; }

void Pair::setFirst(int f) { first = f; }
void Pair::setSecond(double s) { second = s; }

Pair Pair::operator+(const Pair& p) const
{
	return Pair(first + p.first, second + p.second);
}

Pair Pair::operator-(const Pair& p) const
{
	return Pair(first - p.first, second - p.second);

}

Pair Pair::operator=(const Pair& p)
{
	first = p.first;
	second = p.second;
	return *this;
}

Pair Pair::operator/(double delitel) const {
	if (delitel == 0) {
		return Pair(0, 0.0);
	}
	return Pair(first / delitel, second / delitel);
}

ostream& operator<<(ostream& os, const Pair& p) 
{
	os << "(" << p.first << ":" << p.second << ")";
	return os;
}