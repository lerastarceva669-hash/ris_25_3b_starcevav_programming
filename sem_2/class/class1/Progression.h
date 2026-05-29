#pragma once
#ifndef PROGRESSION_H
#define PROGRESSION_H

#include <iostream>
#include <string>
#include <cmath>

class Progression
{
private:
    double first;
    int second;
    bool flag;
public:
    Progression();
    Progression(double first_v, int second_v);
    void Init(double first_v, int second_v);
    void Read();
    void Show();
    long double Element(int j);
    bool Flag_Data();
    double get_first();
    int get_second();
};

// Глобальная функция
Progression make_progression(double first_v, int second_v);

#endif