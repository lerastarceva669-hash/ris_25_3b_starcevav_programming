#include <iostream>
#include <clocale>
#include "lab7.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	List<Pair> myList;
    myList.addElement(Pair(5, 2.5));
    myList.addElement(Pair(3, 1.2));
    myList.addElement(Pair(7, 4.8));
    myList.addElement(Pair(5, 3.1));
    myList.addElement(Pair(2, 0.5));
    myList.addElement(Pair(8, 6.3));

    myList.print();
    cout << "Размер контейнера: " << myList.getSize() << endl << endl;

    cout << "2. Задание 3: Найти среднее арифметическое и добавить его в конец:" << endl;
    myList.addAverage();
    myList.print();
    cout << "Размер контейнера: " << myList.getSize() << endl << endl;

    cout << "3. Задание 4: Удалить элементы с ключами из диапазона [3, 7]:" << endl;
    Pair minRange(3, 0.0);
    Pair maxRange(7, 999.9);
    myList.removeByRange(minRange, maxRange);
    myList.print();
    cout << "Размер контейнера: " << myList.getSize() << endl << endl;

    cout << "4. Задание 5: К каждому элементу добавить сумму min и max элементов:" << endl;

    List<Pair> myList2;
    myList2.addElement(Pair(10, 1.5));
    myList2.addElement(Pair(20, 2.5));
    myList2.addElement(Pair(30, 3.5));
    myList2.addElement(Pair(40, 4.5));

    cout << "Исходный контейнер: ";
    myList2.print();

    myList2.addSumMinMax();
    cout << "После добавления суммы min и max: ";
    myList2.print();


	return 0;
}