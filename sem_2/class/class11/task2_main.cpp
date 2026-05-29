#include <iostream>
#include <list>
#include <algorithm>
#include "Pair.h"
using namespace std;

// Находим среднее арифметическое всех пар в списке
void dobavitSrednee(list<Pair>& spisok)
{
    if (spisok.empty()) 
    {
        cout << "Ошибка: список пуст!" << endl;
        return;
    }

    double summaFirst = 0;
    double summaSecond = 0;

    for (const Pair& p : spisok)
    {
        summaFirst += p.getFirst();
        summaSecond += p.getSecond();
    }

    double sredneeFirst = summaFirst / spisok.size();
    double sredneeSecond = summaSecond / spisok.size();

    Pair srednee((int)sredneeFirst, sredneeSecond);
    spisok.push_back(srednee);

    cout << "Среднее арифметическое = " << srednee << " добавлено в конец" << endl;
    cout << "  (среднее first=" << sredneeFirst << " -> " << (int)sredneeFirst
        << ", среднее second=" << sredneeSecond << ")" << endl;
}

void udalitPoKlyuchu(list<Pair>& spisok, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    int udaleno = 0;
    auto it = spisok.begin();

    while (it != spisok.end()) {
        if (it->getFirst() >= a && it->getFirst() <= b) {
            it = spisok.erase(it);
            udaleno++;
        }
        else {
            ++it;
        }
    }
    cout << "Удалено " << udaleno << " пар, у которых first в [" << a << ", " << b << "]" << endl;
}

// Находим минимальную и максимальную пару (по сумме first+second),
// складываем их, и прибавляем эту сумму к каждой паре
void pribavitSummuMinMax(list<Pair>& spisok) {
    if (spisok.size() < 2) {
        cout << "Ошибка: нужно хотя бы 2 элемента!" << endl;
        return;
    }

    auto minIt = min_element(spisok.begin(), spisok.end());
    auto maxIt = max_element(spisok.begin(), spisok.end());
    Pair summaMinMax = (*minIt) + (*maxIt);
    cout << "Минимальная пара: " << *minIt << endl;
    cout << "Максимальная пара: " << *maxIt << endl;
    cout << "Их сумма = " << summaMinMax << " прибавляется к каждой паре" << endl;
    for (Pair& p : spisok) {
        p = p + summaMinMax;
    }
}

void vyvestiSpisok(const list<Pair>& spisok, const string& nazvanie = "") {
    if (!nazvanie.empty()) {
        cout << nazvanie;
    }

    for (const Pair& p : spisok) {
        cout << p << " ";
    }
    cout << endl;
}


int main() {
    setlocale(LC_ALL, "Russian");
    list<Pair> mojSpisok;
    mojSpisok.push_back(Pair(1, 2.5));   // (1, 2.5)
    mojSpisok.push_back(Pair(3, 4.2));   // (3, 4.2)
    mojSpisok.push_back(Pair(5, 6.7));   // (5, 6.7)
    mojSpisok.push_back(Pair(7, 8.1));   // (7, 8.1)
    mojSpisok.push_back(Pair(2, 5.3));   // (2, 5.3)
    mojSpisok.push_back(Pair(4, 1.8));   // (4, 1.8)

    cout << "========== ЗАДАЧА 2: список пар (int, double) ==========" << endl;
    vyvestiSpisok(mojSpisok, "Исходный список: ");

    // ШАГ 3: ЗАДАНИЕ 3
    cout << "\n--- ЗАДАНИЕ 3: Добавить среднее арифметическое ---" << endl;
    dobavitSrednee(mojSpisok);
    vyvestiSpisok(mojSpisok, "Результат: ");

    // ШАГ 4: ЗАДАНИЕ 4
    cout << "\n--- ЗАДАНИЕ 4: Удалить пары с first в [2, 5] ---" << endl;
    udalitPoKlyuchu(mojSpisok, 2, 5);  // теперь параметры - целые числа
    vyvestiSpisok(mojSpisok, "Результат: ");

    // ШАГ 5: ЗАДАНИЕ 5
    cout << "\n--- ЗАДАНИЕ 5: Прибавить сумму min и max к каждой паре ---" << endl;
    pribavitSummuMinMax(mojSpisok);
    vyvestiSpisok(mojSpisok, "Результат: ");

    return 0;
}
