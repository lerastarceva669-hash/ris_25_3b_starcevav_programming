#include "Progression.h"
using namespace std;

Progression::Progression() {
    first = 0;
    second = 1;
    flag = true;
}
Progression::Progression(double first_v, int second_v) {
    Init(first_v, second_v);
}
void Progression::Init(double first_v, int second_v) {
    if (second_v <= 0) {
        cout << "Ошибка! " << endl;
        flag = false;
        first = 0;
        second = 1;
    }
    else {
        first = first_v;
        second = second_v;
        flag = true;
    }
}

void Progression::Read()
{
    cout << "Введите первый элемент прогрессии a0: ";
    cin >> first;
    cout << "Введите постоянный член прогрессии r: ";
    cin >> second;
    while (second <= 0)
    {
        cout << "Ошибка! Постоянный член прогрессии - целое положительное число! Введите другое значение: ";
        cin >> second;
    }
    flag = true;
}

void Progression::Show()
{
    if (!flag)
    {
        cout << "Ошибка! Данные некорректны!" << endl;
        return;
    }
    else
    {
        cout << "Первый элемент прогрессии а0: " << first << endl;
        cout << "Постоянный член прогрессии r: " << second << endl;
    }
}

long double Progression::Element(int j)
{
    if (!flag)
    {
        cout << "Ошибка! Некорректные данные!" << endl;
        return -1;
    }
    else
    {
        return first * pow(second, j);
    }
}

bool Progression::Flag_Data()
{
    return flag;
}

double Progression::get_first()
{
    return first;
}

int Progression::get_second()
{
    return second;
}

Progression make_progression(double first_v, int second_v)
{
    Progression p(first_v, second_v);
    return p;
}