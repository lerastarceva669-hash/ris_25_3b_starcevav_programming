#include <iostream>
#include <queue>    
#include <vector>    
#include <algorithm> 

using namespace std;

template <typename T>
class TQueue {
private:
    priority_queue<T> data;

public:

    void push(const T& element) {
        data.push(element);
    }
    void pop() {
        if (!data.empty()) {
            data.pop();
        }
    }
    T top() const {
        return data.top();
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

    void clear() {
        while (!data.empty()) {
            data.pop();
        }
    }

    void print(const string& title = "") const {
        if (!title.empty()) {
            cout << title;
        }

        priority_queue<T> copy = data;

        vector<T> temp;

        while (!copy.empty()) {
            cout << copy.top() << " ";
            temp.push_back(copy.top());
            copy.pop();
        }
        cout << endl;
    }

    void addAverage() {
        if (data.empty()) {
            cout << "Ошибка: очередь пуста, нельзя найти среднее!" << endl;
            return;
        }

        vector<T> temp;
        while (!data.empty()) {
            temp.push_back(data.top());
            data.pop();
        }

        T sum = temp[0];  
        for (size_t i = 1; i < temp.size(); i++) {
            sum = sum + temp[i];
        }
        T average = sum / temp.size();  

        temp.push_back(average);


        for (const T& element : temp) {
            data.push(element);
        }

        cout << "Среднее арифметическое = " << average << " добавлено" << endl;
    }

    void removeByRange(const T& a, const T& b) {
        T left = a;
        T right = b;

        if (left > right) {  // нужен оператор >
            swap(left, right);
        }

        vector<T> temp;
        while (!data.empty()) {
            temp.push_back(data.top());
            data.pop();
        }

        int removed = 0;
        auto it = temp.begin();
        while (it != temp.end()) {
            if (*it >= left && *it <= right) { 
                it = temp.erase(it);
                removed++;
            }
            else {
                ++it;
            }
        }

        for (const T& element : temp) {
            data.push(element);
        }

        cout << "Удалено " << removed << " элементов в диапазоне [" << left << ", " << right << "]" << endl;
    }


    void addSumMinMax() {
        vector<T> temp;
        while (!data.empty()) {
            temp.push_back(data.top());
            data.pop();
        }

        if (temp.size() < 2) {
            cout << "Ошибка: нужно хотя бы 2 элемента!" << endl;
            for (const T& element : temp) {
                data.push(element);
            }
            return;
        }

        auto minIt = min_element(temp.begin(), temp.end());  
        auto maxIt = max_element(temp.begin(), temp.end());  

        T sumMinMax = (*minIt) + (*maxIt); 

        cout << "Минимальный элемент = " << *minIt << endl;
        cout << "Максимальный элемент = " << *maxIt << endl;
        cout << "Их сумма = " << sumMinMax << " прибавляется к каждому" << endl;

        for (T& element : temp) {
            element = element + sumMinMax;  
        }

        for (const T& element : temp) {
            data.push(element);
        }
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    cout << "============================================================" << endl;
    cout << "ЗАДАЧА 5: Параметризованный класс TQueue" << endl;
    cout << "На основе адаптера priority_queue (очередь с приоритетами)" << endl;
    cout << "============================================================" << endl;

    
    cout << "\n========== ЧАСТЬ 1: TQueue<double> ==========" << endl;

    TQueue<double> doubleQueue;

    doubleQueue.push(1.5);
    doubleQueue.push(2.3);
    doubleQueue.push(3.7);
    doubleQueue.push(4.1);
    doubleQueue.push(5.9);
    doubleQueue.push(2.8);
    doubleQueue.push(3.2);

    doubleQueue.print("Исходная очередь (от большего к меньшему): ");

    cout << "\n--- ЗАДАНИЕ 3: Добавить среднее арифметическое ---" << endl;
    doubleQueue.addAverage();
    doubleQueue.print("Результат: ");

    cout << "\n--- ЗАДАНИЕ 4: Удалить числа в диапазоне [2, 4] ---" << endl;
    doubleQueue.removeByRange(2.0, 4.0);
    doubleQueue.print("Результат: ");

    cout << "\n--- ЗАДАНИЕ 5: Прибавить сумму min и max к каждому ---" << endl;
    doubleQueue.addSumMinMax();
    doubleQueue.print("Результат: ");

    
    cout << "\n\n========== ЧАСТЬ 2: TQueue<int> ==========" << endl;

    TQueue<int> intQueue;

    intQueue.push(10);
    intQueue.push(25);
    intQueue.push(30);
    intQueue.push(45);
    intQueue.push(50);
    intQueue.push(22);
    intQueue.push(38);

    intQueue.print("Исходная очередь int: ");

    cout << "\n--- ЗАДАНИЕ 3: Добавить среднее арифметическое ---" << endl;
    intQueue.addAverage();
    intQueue.print("Результат: ");

    cout << "\n--- ЗАДАНИЕ 4: Удалить числа в диапазоне [20, 40] ---" << endl;
    intQueue.removeByRange(20, 40);
    intQueue.print("Результат: ");

    cout << "\n--- ЗАДАНИЕ 5: Прибавить сумму min и max к каждому ---" << endl;
    intQueue.addSumMinMax();
    intQueue.print("Результат: ");

    return 0;
}