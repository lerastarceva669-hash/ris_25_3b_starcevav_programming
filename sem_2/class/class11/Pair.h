#pragma once
#ifndef PAIR_H
#define PAIR_H

#include <iostream>

class Pair
{
private:
    int first;   // первое число
    double second;  // второе число
public:
    Pair();
    Pair(int f, double s);
    Pair(const Pair& other);

    ~Pair(){}

    int getFirst() const;
    double getSecond() const;

    void setFirst(int f);
    void setSecond(double s);

    Pair operator+(const Pair& other) const;

    Pair operator-(const Pair& other) const;

    Pair operator=(const Pair& other);

    Pair operator/(double delitel) const;


    friend std::ostream& operator<<(std::ostream& os, const Pair& p);

};
#endif