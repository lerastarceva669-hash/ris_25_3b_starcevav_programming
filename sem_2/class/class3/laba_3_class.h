#pragma once

#include <iostream>
using namespace std;

class Pair
{
private:
    int first;
    double second;

public:
    Pair();
    Pair(const int& first_val, const double& second_val);
    Pair(const Pair& p);
    ~Pair();

    void SetFirst(int first);
    void SetSecond(double second);
    int GetFirst() const;
    double GetSecond() const;

    Pair operator+(const int& first) const;
    Pair operator+(const double& second) const;
    Pair operator-(const Pair& p) const;
    Pair operator=(const Pair& p);
    bool operator<(const Pair& other) const;
    bool operator>(const Pair& other) const;
    bool operator==(const Pair& other) const;


    friend Pair operator+(int first, const Pair& p);
    friend Pair operator+(double second, const Pair& p);
    friend ostream& operator<<(ostream& out, const Pair& p);
};