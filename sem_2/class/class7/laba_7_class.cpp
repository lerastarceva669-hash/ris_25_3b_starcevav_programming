#include <iostream>
#include <string>
#include <clocale>
#include <cmath>
#include <cstdlib>
using namespace std;

class Pair
{
private:
	int first;
	double second;
public:
	Pair() { first = 0; second = 0.0; }
	Pair(int First, double Second) { first = First; second = Second; }
	int getFirst() { return first; }
	double getSecond() { return second; }
	void setFirst(int First) { first = First; }
	void setSecond(double Second) { second = Second; }

	Pair operator*(const Pair& p) const
	{
		return Pair(first * p.first, second * p.second);
	}
	Pair& operator=(const Pair& p)
	{
		if (this != &p) { first = p.first; second = p.second; }
		return *this;
	}
	friend istream& operator>>(istream& is, Pair& p)
	{
		cout << "Введите first и second: ";
		is >> p.first >> p.second;
		return is;
	}
	friend ostream& operator<<(ostream& out, const Pair& p)
	{
		out << p.first << ":" << p.second;
		return out;
	}
};

template <typename T>
class List
{
private:
	T* data;
	int size;

public:
	List() { data = nullptr; size = 0; }
	List(int s, T k) { size = s; data = new T[size]; for (int i = 0; i < size;i++) data[i] = k; }
	List(const List& l)
	{
		size = l.size;
		data = new T[size];
		for (int i = 0; i < size; i++) data[i] = l.data[i];
	}
	~List() { delete[] data; data = 0; }

	List& operator=(const List& l)
	{
		if (this == &l) return *this;
		size = l.size;
		if (data != 0) delete[] data;
		data = new T[size];
		for (int i = 0; i < size; i++) { data[i] = l.data[i]; }
		return *this;
	}

	T& operator[](int index)
	{
		if (index < 0 || index >= size)
		{
			cout << "Error! Index " << index << " invalid!" << endl;
			exit(1);
		}
		return data[index];
	}

	int operator() () const { return size; }

	List<T> operator*(const List<T>& l)
	{
		if (size != l.size) { cout << "Ошибка! Списки имеют разные размеры!" << endl; exit(1); }
		List <T> result(size, T());
		for (int i = 0; i < size; ++i) { result[i] = data[i] * l.data[i]; }
		return result;
	}

	template<typename U>
	friend ostream& operator<<(ostream& out, const List<U>& l);
	template<typename U>
	friend istream& operator>>(istream& in, List<U>& l);

};
template<typename T>
ostream& operator<<(ostream& out, const List<T>& l)
{
	for (int i = 0; i < l.size; ++i)
	{
		out << l.data[i] << " ";
	}
	return out;
}

template<typename T>
istream& operator>>(istream& in, List<T>& l)
{
	for (int i = 0; i < l.size; ++i)
	{
		in >> l.data[i];
	}
	return in;
}



int main()
{
	setlocale(LC_ALL, "RU");
	system("chcp 1251 > nul");
	system("cls");

	//для типа int
	List<int> list1(5, 0);
	cout << "Создали list1 размером 5 из нулей: ";
	cout << list1 << endl;
	cout << "Введите значения массива: ";
	cin >> list1;
	cout << "Обновленный массив list1: " << list1 << endl;

	List<int> list2(10, 1);
	cout << "Создали list2 размером 10 из единиц"<<endl;
	cout << "Доступ по индексу list1[2]: " << list2[2] << endl;
	cout << "Длина списка: " << list1() << endl;
	List<int> list3 = list1 * list2;
	cout << "Операция умножения list1*list2: " << list3 << endl;

	//для типа float
	List<float> flist1(5, 0);
	cout << "Создали flist1 размером 5 из нулей: ";
	cout << flist1 << endl;
	cout << "Введите значения массива: ";
	cin >> flist1;
	cout << "Обновленный массив flist1: " << flist1 << endl;

	List<float> flist2(10, 1);
	cout << "Создали flist2 размером 10 из нулей: ";
	cout << flist2 << endl;
	flist2 = flist1;
	cout << "Операция присвоения flist1 = flist2: " << flist2 << endl;
	cout << "Доступ по индексу flist1[2]: " << flist2[2] << endl;
	cout << "Длина списка: " << flist1() << endl;
	List<float> flist3 = flist1 * flist2;
	cout << "Операция умножения flist1*flist2: " << flist3 << endl;

	//для типа double
	List<double> dlist1(5, 0);
	cout << "Создали dlist1 размером 5 из нулей: ";
	cout << dlist1 << endl;
	cout << "Введите значения массива: ";
	cin >> dlist1;
	cout << "Обновленный массив dlist1: " << dlist1 << endl;

	List<double> dlist2(10, 1);
	cout << "Создали dlist2 размером 10 из нулей: ";
	cout << dlist2 << endl;
	dlist2 = dlist1;
	cout << "Операция присвоения dlist1 = dlist2: " << dlist2 << endl;
	cout << "Доступ по индексу dlist1[2]: " << dlist2[2] << endl;
	cout << "Длина списка: " << dlist1() << endl;
	List<double> dlist3 = dlist1 * dlist2;
	cout << "Операция умножения dlist1*dlist2: " << dlist3 << endl;

	//для пользовательского типа Pair
	List<Pair> plist1(5, Pair(1, 1.0));
	cout << "\nСоздали plist1 размером 5: " << plist1 << endl;
	cout << "Введите элементы списка Pair (first second):\n";
	cin >> plist1;
	cout << "plist1: " << plist1 << endl;

	List<Pair> plist2(5, Pair(2, 2.7));
	cout << "plist2: " << plist2 << endl;

	List<Pair> plist3 = plist1 * plist2;
	cout << "Умножение plist1 * plist2: " << plist3 << endl;

	return 0;
}