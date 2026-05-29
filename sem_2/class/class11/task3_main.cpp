#include <iostream>
#include <list>
#include <algorithm>
#include <numeric> 

using namespace std;

template <typename T>
class TList {
private:
	list<T> data;
public:
	void add(const T& element) {
		data.push_back(element);
	}
    void print(const string& title = "") const {
        if (!title.empty()) {
            cout << title;
        }
        for (const T& element : data) {
            cout << element << " ";
        }
        cout << endl;
    }
    size_t size() const {
        return data.size();
    }

    void clear() {
        data.clear();
    }
    void addAverage() {
        if (data.empty()) {
            cout << "Ошибка: список пуст, нельзя найти среднее!" << endl;
            return;
        }
        T sum = data.front();  
        auto it = data.begin();
        ++it;  
        for (; it != data.end(); ++it) {
            sum = sum + *it;  
        }
        T average = sum / data.size(); 

        data.push_back(average);

        cout << "Среднее арифметическое = " << average << " добавлено в конец" << endl;
    }

    void removeByRange(const T& a, const T& b) {
        T left = a;
        T right = b;

        if (left > right) { 
            swap(left, right);
        }

        int removed = 0;
        auto it = data.begin();
        hile(it != data.end()) {
            if (*it >= left && *it <= right) { 
                it = data.erase(it);
                removed++;
            }
            else {
                ++it;
            }
        }

        cout << "Удалено " << removed << " элементов в диапазоне [" << left << ", " << right << "]" << endl;
    }

    void addSumMinMax() {
        if (data.size() < 2) {
            cout << "Ошибка: нужно хотя бы 2 элемента!" << endl;
            return;
        }

        auto minIt = min_element(data.begin(), data.end());
        auto maxIt = max_element(data.begin(), data.end());
        T sumMinMax = (*minIt) + (*maxIt); 
        cout << "Минимальный элемент: " << *minIt << endl;
        cout << "Максимальный элемент: " << *maxIt << endl;
        cout << "Их сумма = " << sumMinMax << " прибавляется к каждому элементу" << endl;

        for (T& element : data) {
            element = element + sumMinMax;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    TList<double> doubleList;

    doubleList.add(1.5);
    doubleList.add(2.3);
    doubleList.add(3.7);
    doubleList.add(4.1);
    doubleList.add(5.9);
    doubleList.add(2.8);
    doubleList.add(3.2);

    doubleList.print("Исходный список double: ");

    // ШАГ 3: ЗАДАНИЕ 3 - Добавить среднее
    cout << "\n--- ЗАДАНИЕ 3: Добавить среднее арифметическое ---" << endl;
    doubleList.addAverage();
    doubleList.print("Результат: ");

    // ШАГ 4: ЗАДАНИЕ 4 - Удалить из диапазона
    cout << "\n--- ЗАДАНИЕ 4: Удалить числа в диапазоне [2, 4] ---" << endl;
    doubleList.removeByRange(2.0, 4.0);
    doubleList.print("Результат: ");

    // ШАГ 5: ЗАДАНИЕ 5 - Прибавить сумму min и max
    cout << "\n--- ЗАДАНИЕ 5: Прибавить сумму min и max к каждому элементу ---" << endl;
    doubleList.addSumMinMax();
    doubleList.print("Результат: ");

    TList<int> intList;

    intList.add(10);
    intList.add(25);
    intList.add(30);
    intList.add(45);
    intList.add(50);
    intList.add(22);
    intList.add(38);

    intList.print("Исходный список int: ");

    cout << "\n--- ЗАДАНИЕ 3: Добавить среднее арифметическое ---" << endl;
    intList.addAverage();
    intList.print("Результат: ");

    // ШАГ 4: ЗАДАНИЕ 4 - Удалить из диапазона
    cout << "\n--- ЗАДАНИЕ 4: Удалить числа в диапазоне [20, 40] ---" << endl;
    intList.removeByRange(20, 40);
    intList.print("Результат: ");

    // ШАГ 5: ЗАДАНИЕ 5 - Прибавить сумму min и max
    cout << "\n--- ЗАДАНИЕ 5: Прибавить сумму min и max к каждому элементу ---" << endl;
    intList.addSumMinMax();
    intList.print("Результат: ");

    return 0;
}