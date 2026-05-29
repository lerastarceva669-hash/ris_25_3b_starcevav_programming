#include "List.h"
#include "error.h"
#include <iostream>
#include <clocale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    system("chcp 1251 > nul");

    cout << "=== Работа класса СПИСОК ===\n\n";

    // 1. Нормальная работа
    try
    {
        int a1[] = { 1, 2, 3, 4, 5 };
        int a2[] = { 5, 4, 3, 2, 1 };

        List list1(5, a1);
        List list2(5, a2);

        cout << "Список 1: " << list1 << endl;
        cout << "Список 2: " << list2 << endl;
        cout << "Размер: " << (int)list1 << endl;
        cout << "Элемент [2]: " << list1[2] << endl;
        cout << "Умножение: " << (list1 * list2) << endl;
        cout << "Сдвиг +2: " << (list1 + 2) << endl;
    }
    catch (Error& e) { e.what(); }

    cout << "\n=== Исключения ===\n";

    // 2. Ошибка индекса
    try
    {
        int arr[] = { 1, 2, 3 };
        List list(3, arr);
        cout << list[10] << endl;
    }
    catch (IndexError& e) { e.what(); }

    // 3. Отрицательный размер
    try
    {
        List list(-5);
    }
    catch (NegativeSizeError& e) { e.what(); }

    // 4. Нулевой указатель
    try
    {
        List list(5, nullptr);
    }
    catch (NullPointerError& e) { e.what(); }

    // 5. Разные размеры при умножении
    try
    {
        int a1[] = { 1, 2 };
        int a2[] = { 1, 2, 3 };
        List list1(2, a1);
        List list2(3, a2);
        List res = list1 * list2;
    }
    catch (MultiplicationError& e) { e.what(); }

    // 6. Пустые списки
    try
    {
        List list1, list2;
        List res = list1 * list2;
    }
    catch (EmptyListError& e) { e.what(); }

    // 7. Отрицательное смещение
    try
    {
        int arr[] = { 1, 2, 3 };
        List list(3, arr);
        List res = list + (-1);
    }
    catch (NegativeShiftError& e) { e.what(); }

    // 8. Смещение за границы
    try
    {
        int arr[] = { 1, 2, 3 };
        List list(3, arr);
        List res = list + 10;
    }
    catch (OutOfRangeShiftError& e) { e.what(); }

    cout << "\nПрограмма завершена.\n";
    return 0;
}