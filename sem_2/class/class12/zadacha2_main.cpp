#include <iostream>
#include <clocale>
#include <set>
#include <vector>
#include <algorithm>
#include "C:\Users\Lera\source\repos\laba_3_class\laba_3_class.h"

using namespace std;

void addAverage(multiset<Pair>& ms)
{
	int sumFirst = 0;
	double sumSecond = 0.0;

	for (const auto& p : ms)
	{
		sumFirst += p.GetFirst();
		sumSecond += p.GetSecond();
	}
	size_t msSize = ms.size();
	int avgFirst = sumFirst / static_cast<int>(msSize);
	double avgSecond = sumSecond / msSize;

	Pair avgPair(avgFirst, avgSecond);
	ms.insert(avgPair);
}

void removeElements(multiset<Pair>& ms, int firstMin, int firstMax)
{
	auto it = ms.begin();
	while (it != ms.end())
	{
		if (it->GetFirst() >= firstMin && it->GetFirst() <= firstMax)
		{
			it = ms.erase(it);
		}
		else
		{
			++it;
		}
	}
}


void addMinMax(multiset <Pair>& ms)
{
	if (ms.empty()) return;

	auto minElem = *ms.begin();
	auto maxElem = *prev(ms.end());

	Pair sumPair(minElem.GetFirst() + maxElem.GetFirst(),
		minElem.GetSecond() + maxElem.GetSecond());

	multiset<Pair> newCont;
	for (const auto& p : ms) {
		Pair newElem(p.GetFirst() + sumPair.GetFirst(),
			p.GetSecond() + sumPair.GetSecond());
		newCont.insert(newElem);
	}

	ms = newCont;
}


void printMultiset(const multiset<Pair>& ms)
{
	cout << "Multiset elements: ";
	for (const auto& item:ms)
	{
		cout << item << " ";
	}

	cout << " (size: " << ms.size() << ")" << endl;
}


int main()
{
	multiset<Pair> myContainer;

	myContainer.insert(Pair(1, 1.1));
	myContainer.insert(Pair(2, 2.2));
	myContainer.insert(Pair(3, 3.3));
	myContainer.insert(Pair(4, 4.4));
	myContainer.insert(Pair(5, 5.5));

	cout << "Initial container:" << endl;
	printMultiset(myContainer);

	addAverage(myContainer);
	cout << "\nAfter adding average:" << endl;
	printMultiset(myContainer);

	removeElements(myContainer, 2, 4);
	cout << "\nAfter removing range [2, 4]:" << endl;
	printMultiset(myContainer);

	addMinMax(myContainer);
	cout << "\nAfter adding (min+max) to each element:" << endl;
	printMultiset(myContainer);

    return 0;
}