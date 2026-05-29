#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <numeric>
#include "C:\Users\Lera\source\repos\laba_3_class\laba_3_class.h"
using namespace std;

void printContainer(const list<Pair>& cont, const string& m)
{
	cout << m << endl;
	for (const auto& p : cont)
	{
		cout << p << " ";
	}
	cout << endl;
}

list<Pair> createAndFillContainer()
{
	list<Pair> lst;
	lst.push_back(Pair(5, 2.5));
	lst.push_back(Pair(3, 1.1));
	lst.push_back(Pair(8, 4.2));
	lst.push_back(Pair(3, 1.1));
	lst.push_back(Pair(1, 9.9));
	lst.push_back(Pair(7, 3.3));
	return lst;
}

void replaceElements(list<Pair>& lst)
{
	replace_if(lst.begin(), lst.end(),[](const Pair& p)
		{ return p.GetFirst() > 5; },
		Pair(0, 0.0));
	printContainer(lst, "После replace_if (first>5 -> (0,0)):");

	list<Pair> lst_copy;

	replace_copy_if(lst.begin(), lst.end(),
		back_inserter(lst_copy),
		[](const Pair& p) { return p.GetFirst() == 0; },
		Pair(99, 99.9));
	printContainer(lst_copy, "После replace_copy_if (first==0 -> (99,99.9)):");
}

void removeElements(list<Pair>& lst)
{
	lst.remove_if([](const Pair& p) { return p.GetSecond() < 2.0; });
	printContainer(lst, "После remove_if (second<2.0):");

	list<Pair> lst_removed;
	remove_copy_if(lst.begin(), lst.end(),
		back_inserter(lst_removed),
		[](const Pair& p) { return p.GetFirst() == 3; });
	printContainer(lst_removed, "После remove_copy_if (без элементов с first==3):");
}

void sortContainer(std::list<Pair>& lst) {
	// Сортировка по возрастанию
	lst.sort(std::less<Pair>());
	printContainer(lst, "Сортировка по возрастанию:");

	// Сортировка по убыванию
	lst.sort(std::greater<Pair>());
	printContainer(lst, "Сортировка по убыванию:");

	// Возвращаем возрастающий порядок для следующих операций
	lst.sort(std::less<Pair>());
}

// 5. Поиск элементов (find, count_if)
void findElements(const std::list<Pair>& lst) {
	// find - поиск конкретного элемента
	Pair to_find(3, 1.1);
	auto it = std::find(lst.begin(), lst.end(), to_find);
	if (it != lst.end()) {
		cout << "Найден элемент " << *it << "\n";
	}
	else {
		cout << "Элемент (3, 1.1) не найден\n";
	}

	// count_if - подсчет элементов по условию
	int count_3 = std::count_if(lst.begin(), lst.end(),
		[](const Pair& p) { return p.GetFirst() == 3; });
	cout << "Количество элементов с first=3: " << count_3 << "\n\n";
}

void addAverageToEnd(std::list<Pair>& lst) {
	if (lst.empty()) return;

	double sum_first = 0, sum_second = 0;
	for (const auto& p : lst) {
		sum_first += p.GetFirst();
		sum_second += p.GetSecond();
	}

	Pair avg(static_cast<int>(sum_first / static_cast<double>(lst.size())),
		sum_second / lst.size());
	lst.push_back(avg);

	printContainer(lst, "После добавления среднего арифметического в конец:");
}

void addSumMinMaxToEach(std::list<Pair>& lst) {
	if (lst.empty()) return;

	auto min_it = std::min_element(lst.begin(), lst.end());
	auto max_it = std::max_element(lst.begin(), lst.end());
	int sum_first = min_it->GetFirst() + max_it->GetFirst();
	double sum_second = min_it->GetSecond() + max_it->GetSecond();

	std::for_each(lst.begin(), lst.end(), [sum_first, sum_second](Pair& p) {
		p.SetFirst(p.GetFirst() + sum_first);
		p.SetSecond(p.GetSecond() + sum_second);
		});


	printContainer(lst, "После добавления суммы min+max к каждому элементу:");
}

void demonstrateFill(std::list<Pair>& lst) {
	if (lst.size() >= 3) {
		auto it_start = lst.begin();
		advance(it_start, 1);
		auto it_end = lst.begin();
		advance(it_end, 3);

		fill(it_start, it_end, Pair(100, 100.0));
		printContainer(lst, "После fill (заполнение 2-го и 3-го элементов):");
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	list<Pair> myList = createAndFillContainer();
	printContainer(myList, "Исходный контейнер:");

	// 2. Замена элементов
	replaceElements(myList);

	myList = createAndFillContainer();

	// 3. Удаление элементов
	removeElements(myList);

	myList = createAndFillContainer();

	// 4. Сортировка
	sortContainer(myList);

	// 5. Поиск
	findElements(myList);

	// 6. Добавление среднего арифметического
	addAverageToEnd(myList);

	// 7. Добавление суммы min+max к каждому элементу
	addSumMinMaxToEach(myList);

	// 8. Дополнительная демонстрация fill
	std::list<Pair> testList = createAndFillContainer();
	demonstrateFill(testList);

	return 0;
}