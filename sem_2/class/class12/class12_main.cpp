#include <iostream>
#include <clocale>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;


void addAverage(multiset<double>& ms)
{
	if (ms.empty()) return;

	double sum = 0.0;
	for (double val : ms) sum += val;
	double aver = sum / ms.size();

	ms.insert(aver);
}

void removeElements(multiset<double>& ms, double low, double high)
{
	auto start = ms.lower_bound(low); //указывает на первое вхождение low, нижняя граница, при том, что оно >=
	auto end = ms.upper_bound(high); //указывает на первое вхождение high при том, что оно >

	ms.erase(start, end); //удаляет диапазон от start до end не включая end
}

void addMinMax(multiset <double>& ms)
{
	if (ms.empty()) return;

	double minVal = *ms.begin(); //первый элемент минимальный
	double maxVal = *ms.rbegin(); //последний элемент максимальный
	double sumMM = minVal + maxVal;

	// multiset нельзя изменять напрямую, поэтому создаём новые значения
	vector<double> newValues;

	for (double val : ms) {
		newValues.push_back(val + sumMM);
	}

	ms.clear();
	ms.insert(newValues.begin(), newValues.end());
}

void printMultiset(const multiset<double>& ms)
{
	cout << "Multiset elements: ";
	for (double val : ms)
	{
		cout << val << " ";
	}

	cout << " (size: " << ms.size() << ")" << endl;
}


int main()
{
	multiset<double> myContainer;

	myContainer.insert(5.5);
	myContainer.insert(2.1);
	myContainer.insert(8.3);
	myContainer.insert(2.1);
	myContainer.insert(4.7);

	cout << "Initial container:" << endl;
	printMultiset(myContainer);

	addAverage(myContainer);
	cout << "\nAfter adding average:" << endl;
	printMultiset(myContainer);

	removeElements(myContainer, 2.5, 5.0);
	cout << "\nAfter removing range [2.5, 5.0]:" << endl;
	printMultiset(myContainer);

	addMinMax(myContainer);
	cout << "\nAfter adding (min+max) to each element:" << endl;
	printMultiset(myContainer);

	return 0;


}

