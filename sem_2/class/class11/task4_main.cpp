#include <iostream>
#include <queue>     
#include <vector>    
#include <algorithm> 
#include <numeric> 
using namespace std;

void addAverage(priority_queue<double>& queue) {
    if (queue.empty()) {
        cout << "Ошибка: очередь пуста!" << endl;
        return;
    }

    vector<double> temp;
    while (!queue.empty()) {
        temp.push_back(queue.top());  // top() - смотрим верхний
        queue.pop();                   // pop() - удаляем верхний
    }

    double sum = 0;
    for (double val : temp) {
        sum += val;
    }

    // ШАГ 3: Вычисляем среднее
    double average = sum / temp.size();

    // ШАГ 4: Добавляем среднее в вектор
    temp.push_back(average);

    // ШАГ 5: Засовываем все элементы обратно в очередь
    for (double val : temp) {
        queue.push(val);
    }

    cout << "Среднее арифметическое = " << average << " добавлено в очередь" << endl;
}

void removeByRange(priority_queue<double>& queue, double a, double b) {
    // Проверяем границы (если a > b, меняем местами)
    if (a > b) {
        swap(a, b);
    }

    // ШАГ 1: Вытаскиваем все элементы из очереди в вектор
    vector<double> temp;
    while (!queue.empty()) {
        temp.push_back(queue.top());
        queue.pop();
    }

    // ШАГ 2: Удаляем элементы, которые в диапазоне [a, b]
    int removed = 0;
    auto it = temp.begin();
    while (it != temp.end()) {
        if (*it >= a && *it <= b) {
            it = temp.erase(it);  // удаляем и переходим к следующему
            removed++;
        }
        else {
            ++it;
        }
    }

    // ШАГ 3: Засовываем оставшиеся элементы обратно в очередь
    for (double val : temp) {
        queue.push(val);
    }

    cout << "Удалено " << removed << " элементов в диапазоне [" << a << ", " << b << "]" << endl;
}

void addSumMinMax(priority_queue<double>& queue) {
    // ШАГ 1: Вытаскиваем все элементы из очереди в вектор
    vector<double> temp;
    while (!queue.empty()) {
        temp.push_back(queue.top());
        queue.pop();
    }

    // Проверяем, что элементов достаточно
    if (temp.size() < 2) {
        cout << "Ошибка: нужно хотя бы 2 элемента!" << endl;
        // Возвращаем элементы обратно
        for (double val : temp) {
            queue.push(val);
        }
        return;
    }

    // ШАГ 2: Находим минимальный и максимальный элементы
    double minimum = *min_element(temp.begin(), temp.end());
    double maximum = *max_element(temp.begin(), temp.end());

    // ШАГ 3: Сумма min и max
    double sumMinMax = minimum + maximum;

    cout << "Минимальный элемент = " << minimum << endl;
    cout << "Максимальный элемент = " << maximum << endl;
    cout << "Их сумма = " << sumMinMax << " прибавляется к каждому элементу" << endl;

    // ШАГ 4: Прибавляем сумму к каждому элементу
    for (double& val : temp) {
        val += sumMinMax;
    }

    // ШАГ 5: Засовываем элементы обратно в очередь
    for (double val : temp) {
        queue.push(val);
    }
}

// ==============================================================
// ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ: ВЫВОД ОЧЕРЕДИ НА ЭКРАН
// ==============================================================
void printQueue(priority_queue<double> queue, const string& title = "") {
    // ВНИМАНИЕ! Мы передаем queue по КОПИИ, чтобы не испортить оригинал
    // (потому что для вывода нужно удалять элементы из очереди)

    if (!title.empty()) {
        cout << title;
    }

    // Временный вектор для хранения элементов
    vector<double> temp;

    // Вытаскиваем и выводим все элементы
    while (!queue.empty()) {
        cout << queue.top() << " ";
        temp.push_back(queue.top());
        queue.pop();
    }
    cout << endl;

    // Обратите внимание: оригинальная очередь не изменилась,
    // потому что мы работали с КОПИЕЙ
}

int main() {
    // Включаем русский язык
    setlocale(LC_ALL, "Russian");

    // ========== ШАГ 1: СОЗДАЕМ АДАПТЕР КОНТЕЙНЕРА ==========
   // priority_queue - это очередь с приоритетами
   // Самый большой элемент всегда вверху!
    priority_queue<double> myQueue;

    // ========== ШАГ 2: ЗАПОЛНЯЕМ ЕГО ЭЛЕМЕНТАМИ ==========
    // Добавляем элементы (порядок добавления НЕ важен)
    myQueue.push(1.5);
    myQueue.push(2.3);
    myQueue.push(3.7);
    myQueue.push(4.1);
    myQueue.push(5.9);
    myQueue.push(2.8);
    myQueue.push(3.2);

    // Выводим очередь
    printQueue(myQueue, "Исходная очередь (от большего к меньшему): ");
    cout << "(В очереди с приоритетом элементы хранятся ОТ БОЛЬШЕГО К МЕНЬШЕМУ)" << endl;

    // ========== ШАГ 3: ЗАДАНИЕ 3 - ДОБАВИТЬ СРЕДНЕЕ ==========
    cout << "\n--- ЗАДАНИЕ 3: Добавить среднее арифметическое ---" << endl;
    addAverage(myQueue);
    printQueue(myQueue, "Результат: ");

    // ========== ШАГ 4: ЗАДАНИЕ 4 - УДАЛИТЬ ИЗ ДИАПАЗОНА ==========
    cout << "\n--- ЗАДАНИЕ 4: Удалить числа в диапазоне [2, 4] ---" << endl;
    removeByRange(myQueue, 2.0, 4.0);
    printQueue(myQueue, "Результат: ");

    // ========== ШАГ 5: ЗАДАНИЕ 5 - ПРИБАВИТЬ СУММУ MIN И MAX ==========
    cout << "\n--- ЗАДАНИЕ 5: Прибавить сумму min и max к каждому элементу ---" << endl;
    addSumMinMax(myQueue);
    printQueue(myQueue, "Результат: ");

    return 0;
}
