#pragma once
#include <iostream>
#include <set>
#include <algorithm>

class Pair
{
private:
    int first;
    double second;
public:
    Pair() { first = 0; second = 0.0; }
    Pair(int First, double Second) { first = First; second = Second; }
    int getFirst() const { return first; }
    double getSecond() const { return second; }
    void setFirst(int First) { first = First; }
    void setSecond(double Second) { second = Second; }

    bool operator<(const Pair& p) const
    {
        if (first != p.first)
            return first < p.first;
        return second < p.second;
    }

    bool operator==(const Pair& p) const
    {
        return (first == p.first && second == p.second);
    }

    Pair operator+(const Pair& p) const
    {
        return Pair(first + p.first, second + p.second);
    }

    Pair operator/(int divisor) const
    {
        return Pair(first / divisor, second / divisor);
    }

    Pair operator*(const Pair& p) const
    {
        return Pair(first * p.first, second * p.second);
    }
    Pair& operator=(const Pair& p)
    {
        if (this != &p) { first = p.first; second = p.second; }
        return *this;
    }

    friend std::istream& operator>>(std::istream& is, Pair& p)
    {
        std::cout << "Введите first и second: ";
        is >> p.first >> p.second;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& out, const Pair& p)
    {
        out << "(" << p.first << ":" << p.second << ")";
        return out;
    }
};

template <typename T>
class List
{
private:
    std::multiset<T> container;

public:
    List() {}

    List(const std::multiset<T>& ms) : container(ms) {}

    ~List() {}

    // Добавление элемента
    void addElement(const T& elem)
    {
        container.insert(elem);
    }

    // Удаление элемента по значению
    void removeElement(const T& elem)
    {
        auto it = container.find(elem);
        if (it != container.end())
        {
            container.erase(it);
        }
    }
    // Задание 3: Найти среднее арифметическое и добавить его в конец контейнера
    void addAverage()
    {
        if (container.empty()) return;

        T sum = T(0., 0.0);

        int count = container.size();

        for (const auto& elem : container)
        {
            sum = sum + elem;
        }

        T average = sum / count;
        container.insert(average);
    }

    // Задание 4: Найти элементы с ключами из заданного диапазона и удалить их
    void removeByRange(const T& minKey, const T& maxKey)
    {
        auto it = container.begin();
        while (it != container.end())
        {
            if (!(*it < minKey) && !(maxKey < *it))
            {
                it = container.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    // Задание 5: К каждому элементу добавить сумму минимального и максимального элементов
    void addSumMinMax()
    {
        if (container.size() < 2) return;

        T minElem = *container.begin();
        T maxElem = *container.rbegin();

        T sum(minElem.getFirst() + maxElem.getFirst(),
            minElem.getSecond() + maxElem.getSecond());

        std::multiset<T> newContainer;
        for (const auto& elem : container)
        {
            T newElem(elem.getFirst() + sum.getFirst(),
                elem.getSecond() + sum.getSecond());
            newContainer.insert(newElem);
        }
        container = newContainer;
    }

    void print() const
    {
        std::cout << "Контейнер: ";
        for (const auto& elem : container)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    int getSize() const { return container.size(); }

    std::multiset<T> getContainer() const { return container; }
};
