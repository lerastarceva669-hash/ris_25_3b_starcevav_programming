#include "List.h"
#include <iostream>
#include <clocale>


using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	system("chcp 1251 > nul");

	try
	{
		int arr1[] = { 1, 2, 3, 4, 5 };
		int arr2[] = { 5, 4, 3, 2, 1 };

		List list1(5, arr1);
		List list2(5, arr2);

		cout << "Список 1: " << list1 << endl;
		cout << "Список 2: " << list2 << endl;
		cout << "Размер list1: " << (int)list1 << endl;
		cout << "Размер list2: " << (int)list2 << endl;

		cout << "\nЭлемент с индексом 2: " << list1[2] << endl;

		List list3 = list1 * list2;
		cout << "Умножение (list1 * list2): " << list3 << endl;

		List list4 = list1 + 2;
		cout << "list1 + 2 (сдвиг на 2 вправо): " << list4 << endl;

		cout << "\n=== Демонстрация исключений ===\n" << endl;



		// 1. Выход за границы индекса
		cout << "Попытка доступа к индексу 10: ";
		cout << list1[10] << endl;
	
	}

	catch (const out_of_range& e) { cout << e.what() << endl; }

	try
	{
		// 2. Отрицательный размер
		cout << "\nПопытка создания списка с отрицательным размером: ";
		List list5(-5);
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		// 3. Нулевой указатель
		cout << "\nПопытка создания списка с нулевым указателем: ";
		List list6(5, nullptr);
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		// 4. Умножение с пустыми списками
		cout << "\nПопытка умножения пустых списков: ";
		List list7;
		List list8;
		List list9 = list7 * list8;
	}
	catch (const logic_error& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		// 5. Отрицательное смещение
		cout << "\nПопытка сдвига на -1: ";
		int arr3[] = { 1, 2, 3 };
		List list10(3, arr3);
		List list11 = list10 + (-1);
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		// 6. Смещение за границы
		cout << "\nПопытка сдвига на 10 (список из 5 элементов): ";
		int arr4[] = { 1, 2, 3, 4, 5 };
		List list12(5, arr4);
		List list13 = list12 + 10;
	}
	catch (const out_of_range& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}