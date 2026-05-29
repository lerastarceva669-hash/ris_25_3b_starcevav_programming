#include <iostream>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <numeric>
using namespace std;

// Задание 3: Найти среднее арифметическое и добавить его в конец
void addAverage(list<double>& lst) {
    if (lst.empty()) {
        cout << "Контейнер пуст, нельзя вычислить среднее!" << endl;
        return;
    }
    double sum = accumulate(lst.begin(), lst.end(), 0.0);
    double avg = sum / lst.size();
    lst.push_back(avg);
    cout << "Среднее арифметическое: " << avg << " добавлено в конец" << endl;
}

// ЗАДАНИЕ 4: Удалить элементы из заданного диапазона
void removeByKeyRange(list<double>& lst, double a, double b) {
    if (a > b) swap(a, b); 

    int removed = 0;  

    auto it = lst.begin();
    while (it != lst.end()) {
        if (*it >= a && *it <= b) {  
            it = lst.erase(it);      
            removed++;
        }
        else {
            ++it; 
        }
    }

    cout << "Удалено " << removed << " элементов из диапазона [" << a << ", " << b << "]" << endl;
}

// ЗАДАНИЕ 5: К каждому элементу добавить сумму min и max
void addSumMinMax(list<double>& lst) {
    if (lst.size() < 2) {
        cout << "Ошибка: нужно хотя бы 2 элемента!" << endl;
        return;
    }

    double minVal = *min_element(lst.begin(), lst.end());
    double maxVal = *max_element(lst.begin(), lst.end());
    double sumMinMax = minVal + maxVal;  // их сумма

    cout << "Минимум: " << minVal << ", Максимум: " << maxVal << endl;
    cout << "Их сумма = " << sumMinMax << " (прибавим к каждому элементу)" << endl;

    for (auto& val : lst) {
        val += sumMinMax;
    }
}

// Вспомогательная функция для вывода списка на экран
void printList(const list<double>& lst, const string& title = "") {
    if (!title.empty()) cout << title;
    for (double val : lst) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian"); 

    cout << "========== ЗАДАЧА 1: Работа со списком чисел ==========\n" << endl;

    list<double> myList;

    myList.push_back(1.5);
    myList.push_back(2.3);
    myList.push_back(3.7);
    myList.push_back(4.1);
    myList.push_back(5.9);
    myList.push_back(2.8);
    myList.push_back(3.2);

    printList(myList, "Исходный список: ");
    cout << endl;

    cout << "--- ЗАДАНИЕ 3: Добавить среднее арифметическое ---" << endl;
    addAverage(myList);
    printList(myList, "Результат: ");
    cout << endl;

    cout << "--- ЗАДАНИЕ 4: Удалить числа из диапазона [2, 4] ---" << endl;
    removeByKeyRange(myList, 2.0, 4.0);
    printList(myList, "Результат: ");
    cout << endl;

    cout << "--- ЗАДАНИЕ 5: Прибавить сумму min и max к каждому числу ---" << endl;
    addSumMinMax(myList);
    printList(myList, "Результат: ");

    return 0;
}
