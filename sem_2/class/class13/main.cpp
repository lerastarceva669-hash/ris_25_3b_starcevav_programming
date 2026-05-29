#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "C:\Users\Lera\source\repos\laba_3_class\laba_3_class.h"

using namespace std;

// Вывод очереди с приоритетами
void printPriorityQueue(priority_queue<Pair> pq, const string& msg) {
    cout << msg;
    vector<Pair> temp;
    while (!pq.empty()) {
        cout << pq.top() << " ";
        temp.push_back(pq.top());
        pq.pop();
    }
    cout << endl;
}

// Вывод вектора
void printVector(const vector<Pair>& v, const string& msg) {
    cout << msg;
    for (const auto& p : v) cout << p << " ";
    cout << endl;
}

// Преобразование priority_queue в vector
vector<Pair> pqToVector(priority_queue<Pair> pq) {
    vector<Pair> result;
    while (!pq.empty()) {
        result.push_back(pq.top());
        pq.pop();
    }
    return result;
}

// Преобразование vector в priority_queue
priority_queue<Pair> vectorToPq(const vector<Pair>& v) {
    priority_queue<Pair> pq;
    for (const auto& p : v) {
        pq.push(p);
    }
    return pq;
}


// Создание и заполнение очереди
priority_queue<Pair> createAndFillQueue() {
    priority_queue<Pair> pq;
    pq.push(Pair(5, 2.5));
    pq.push(Pair(3, 1.1));
    pq.push(Pair(8, 4.2));
    pq.push(Pair(3, 1.1));
    pq.push(Pair(1, 9.9));
    pq.push(Pair(7, 3.3));
    return pq;
}


void task3_replaceElements() {
    cout << "\n========== ТРЕБОВАНИЕ 3: Замена элементов ==========" << endl;

    // Создаем вектор для демонстрации
    vector<Pair> vec;
    vec.push_back(Pair(5, 2.5));
    vec.push_back(Pair(3, 1.1));
    vec.push_back(Pair(8, 4.2));
    vec.push_back(Pair(3, 1.1));
    vec.push_back(Pair(1, 9.9));
    vec.push_back(Pair(7, 3.3));
    printVector(vec, "Исходный вектор: ");

    // 3.1 replace_if - замена по условию
    replace_if(vec.begin(), vec.end(),
        [](const Pair& p) { return p.GetFirst() > 5; },
        Pair(0, 0.0));
    printVector(vec, "После replace_if (first>5 -> (0,0)): ");

    // 3.2 replace_copy_if - копирование с заменой
    vector<Pair> copyVec;
    replace_copy_if(vec.begin(), vec.end(),
        back_inserter(copyVec),
        [](const Pair& p) { return p.GetFirst() == 0; },
        Pair(99, 99.9));
    printVector(copyVec, "После replace_copy_if (first==0 -> (99,99.9)): ");

    // 3.3 fill - заполнение диапазона
    fill(vec.begin(), vec.begin() + 2, Pair(10, 10.0));
    printVector(vec, "После fill (первые 2 элемента -> (10,10)): ");
}


void task4_removeElements() {
    cout << "\n========== ТРЕБОВАНИЕ 4: Удаление элементов ==========" << endl;

    // Создаем вектор для демонстрации
    vector<Pair> vec;
    vec.push_back(Pair(5, 2.5));
    vec.push_back(Pair(3, 1.1));
    vec.push_back(Pair(8, 4.2));
    vec.push_back(Pair(3, 1.1));
    vec.push_back(Pair(1, 9.9));
    vec.push_back(Pair(7, 3.3));
    printVector(vec, "Исходный вектор: ");

    // 4.1 remove_if - удаление по условию
    auto newEnd = remove_if(vec.begin(), vec.end(),
        [](const Pair& p) { return p.GetSecond() < 2.0; });
    vec.erase(newEnd, vec.end());
    printVector(vec, "После remove_if (second<2.0): ");

    // 4.2 remove_copy_if - копирование без удаляемых элементов
    vector<Pair> removedCopy;
    remove_copy_if(vec.begin(), vec.end(),
        back_inserter(removedCopy),
        [](const Pair& p) { return p.GetFirst() == 3; });
    printVector(removedCopy, "После remove_copy_if (без элементов с first==3): ");
}

void task5_sortContainer() {
    cout << "\n========== ТРЕБОВАНИЕ 5: Сортировка контейнера ==========" << endl;

    // Создаем вектор для демонстрации
    vector<Pair> vec;
    vec.push_back(Pair(5, 2.5));
    vec.push_back(Pair(3, 1.1));
    vec.push_back(Pair(8, 4.2));
    vec.push_back(Pair(3, 1.1));
    vec.push_back(Pair(1, 9.9));
    vec.push_back(Pair(7, 3.3));
    printVector(vec, "Исходный вектор: ");

    // 5.1 Сортировка по возрастанию
    sort(vec.begin(), vec.end(),
        [](const Pair& a, const Pair& b) { return a.GetFirst() < b.GetFirst(); });
    printVector(vec, "Сортировка по возрастанию first: ");

    // 5.2 Сортировка по убыванию
    sort(vec.begin(), vec.end(),
        [](const Pair& a, const Pair& b) { return a.GetFirst() > b.GetFirst(); });
    printVector(vec, "Сортировка по убыванию first: ");
}


void task6_findElements() {
    cout << "\n========== ТРЕБОВАНИЕ 6: Поиск элементов ==========" << endl;

    // Создаем вектор для демонстрации
    vector<Pair> vec;
    vec.push_back(Pair(5, 2.5));
    vec.push_back(Pair(3, 1.1));
    vec.push_back(Pair(8, 4.2));
    vec.push_back(Pair(3, 1.1));
    vec.push_back(Pair(1, 9.9));
    vec.push_back(Pair(7, 3.3));
    printVector(vec, "Текущий вектор: ");

    // 6.1 find - поиск конкретного элемента
    Pair to_find(3, 1.1);
    auto it = find(vec.begin(), vec.end(), to_find);
    if (it != vec.end()) {
        cout << "find: найден элемент " << *it << endl;
    }
    else {
        cout << "find: элемент (3, 1.1) не найден" << endl;
    }

    // 6.2 find_if - поиск по условию
    auto it2 = find_if(vec.begin(), vec.end(),
        [](const Pair& p) { return p.GetFirst() == 8; });
    if (it2 != vec.end()) {
        cout << "find_if: найден элемент с first=8: " << *it2 << endl;
    }

    // 6.3 count - подсчет конкретного элемента
    int cnt = count(vec.begin(), vec.end(), Pair(3, 1.1));
    cout << "count: количество элементов (3, 1.1): " << cnt << endl;

    // 6.4 count_if - подсчет по условию
    int cnt3 = count_if(vec.begin(), vec.end(),
        [](const Pair& p) { return p.GetFirst() == 3; });
    cout << "count_if: количество элементов с first=3: " << cnt3 << endl;
}

priority_queue<Pair> task3_addAverageToEnd(priority_queue<Pair> pq) {
    cout << "\n========== ЗАДАНИЕ 3 ==========" << endl;
    cout << "Найти среднее арифметическое и добавить его в конец контейнера" << endl;

    // Преобразуем в вектор
    vector<Pair> vec = pqToVector(pq);
    printVector(vec, "Текущий контейнер: ");

    // Находим среднее арифметическое
    double sumFirst = 0, sumSecond = 0;
    for (const auto& p : vec) {
        sumFirst += p.GetFirst();
        sumSecond += p.GetSecond();
    }

    Pair avg(static_cast<int>(sumFirst / vec.size()), sumSecond / vec.size());
    cout << "Среднее арифметическое: " << avg << endl;

    // Добавляем в конец
    vec.push_back(avg);
    printVector(vec, "После добавления среднего арифметического: ");

    // Преобразуем обратно в очередь
    return vectorToPq(vec);
}

priority_queue<Pair> task4_removeByKeyRange(priority_queue<Pair> pq, int minKey, int maxKey) {
    cout << "\n========== ЗАДАНИЕ 4 ==========" << endl;
    cout << "Найти элементы с ключами из заданного диапазона и удалить их" << endl;
    cout << "Диапазон ключей (first): [" << minKey << ", " << maxKey << "]" << endl;

    // Преобразуем в вектор
    vector<Pair> vec = pqToVector(pq);
    printVector(vec, "Текущий контейнер: ");

    // Удаляем элементы с ключами из диапазона
    auto newEnd = remove_if(vec.begin(), vec.end(),
        [minKey, maxKey](const Pair& p) {
            return p.GetFirst() >= minKey && p.GetFirst() <= maxKey;
        });
    vec.erase(newEnd, vec.end());
    printVector(vec, "После удаления элементов из диапазона: ");

    // Преобразуем обратно в очередь
    return vectorToPq(vec);
}

priority_queue<Pair> task5_addSumMinMaxToEach(priority_queue<Pair> pq) {
    cout << "\n========== ЗАДАНИЕ 5 ==========" << endl;
    cout << "К каждому элементу добавить сумму минимального и максимального элементов" << endl;

    // Преобразуем в вектор
    vector<Pair> vec = pqToVector(pq);
    printVector(vec, "Текущий контейнер: ");

    if (vec.empty()) {
        cout << "Контейнер пуст!" << endl;
        return pq;
    }

    // Находим минимальный и максимальный элементы
    auto minIt = min_element(vec.begin(), vec.end(),
        [](const Pair& a, const Pair& b) {
            return a.GetFirst() < b.GetFirst();
        });
    auto maxIt = max_element(vec.begin(), vec.end(),
        [](const Pair& a, const Pair& b) {
            return a.GetFirst() < b.GetFirst();
        });

    cout << "Минимальный элемент: " << *minIt << endl;
    cout << "Максимальный элемент: " << *maxIt << endl;

    int sumFirst = minIt->GetFirst() + maxIt->GetFirst();
    double sumSecond = minIt->GetSecond() + maxIt->GetSecond();
    cout << "Сумма min+max: (" << sumFirst << ", " << sumSecond << ")" << endl;

    // Добавляем сумму к каждому элементу
    for_each(vec.begin(), vec.end(), [sumFirst, sumSecond](Pair& p) {
        p.SetFirst(p.GetFirst() + sumFirst);
        p.SetSecond(p.GetSecond() + sumSecond);
        });
    printVector(vec, "После добавления суммы min+max к каждому элементу: ");

    // Преобразуем обратно в очередь
    return vectorToPq(vec);
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаем и заполняем очередь
    priority_queue<Pair> myQueue = createAndFillQueue();
    printPriorityQueue(myQueue, "\nИсходная очередь: ");

    task3_replaceElements();
    task4_removeElements();
    task5_sortContainer();
    task6_findElements();


    // ВЫПОЛНЯЕМ ЗАДАНИЕ 3
    myQueue = task3_addAverageToEnd(myQueue);
    printPriorityQueue(myQueue, "Результат задания 3: ");

    // ВЫПОЛНЯЕМ ЗАДАНИЕ 4
    myQueue = task4_removeByKeyRange(myQueue, 3, 7);
    printPriorityQueue(myQueue, "Результат задания 4: ");

    // ВЫПОЛНЯЕМ ЗАДАНИЕ 5
    myQueue = task5_addSumMinMaxToEach(myQueue);
    printPriorityQueue(myQueue, "Результат задания 5: ");

    return 0;
}
