#include "laba_3_class.h"

#include <string>
#include <clocale>
#include <cmath>
using namespace std;


Pair::Pair()
{
    this->first = 0;
    this->second = 0.0;
}

Pair::Pair(const int& first_val, const double& second_val)
{
    this->first = first_val;
    this->second = second_val;
}

Pair::Pair(const Pair& p)
{
    this->first = p.first;
    this->second = p.second;
}

Pair::~Pair() {}

void Pair::SetFirst(int first)
{
    this->first = first;
}

void Pair::SetSecond(double second)
{
    this->second = second;
}

int Pair::GetFirst() const
{
    return this->first;
}

double Pair::GetSecond() const
{
    return this->second;
}

Pair Pair::operator+(const int& first) const
{
    return Pair(this->first + first, this->second);
}

Pair Pair::operator+(const double& second) const
{
    return Pair(this->first, this->second + second);
}

Pair Pair::operator-(const Pair& p) const
{
    return Pair(this->first - p.first, this->second - p.second);
}

Pair Pair::operator=(const Pair& p)
{
    first = p.first;
    second = p.second;
    return *this;
}

bool Pair::operator<(const Pair& other) const
{
    if (first != other.first)
        return first < other.first;
    return second < other.second;
}

bool Pair::operator>(const Pair& other) const {
    return other < *this;
}

bool Pair::operator==(const Pair& other) const {
    return first == other.first && second == other.second;
}

Pair operator+(int first, const Pair& p)
{
    return p + first;
}

Pair operator+(double second, const Pair& p)
{
    return p + second;
}

ostream& operator<<(ostream& out, const Pair& p)
{
    out << '(' << p.first << ':' << p.second << ')';
    return out;
}



