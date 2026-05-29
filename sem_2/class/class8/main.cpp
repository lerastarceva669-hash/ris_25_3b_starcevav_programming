#include "Magazin.h"
#include "Dialog.h"
#include "Print.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	setlocale(LC_ALL, "RU");
	system("chcp 1251 > nul");
	system("cls");

	//создание отдельных объектов
	cout << "\n--- Тест 1: Создание объектов ---" << endl;
	Magazin mag1("Наука и жизнь", "Иванов", 128);
	Magazin mag2("Вокруг света", "Петров", 96);
	Print print1("Книга", "Сидоров");

	mag1.Show();
	cout << endl;
	mag2.Show();
	cout << endl;
	print1.Show();

	cout << "\n--- Тест 2: Оператор присваивания ---" << endl;
	Magazin mag3;
	mag3 = mag1;
	mag3.Show();

	// Тест 3: Работа с группой Tree
	cout << "\n--- Тест 3: Работа с группой Tree ---" << endl;
	tree group(2);  // Создаем группу из 2 элементов
	cout << "\nРазмер группы: " << group() << endl;
	group.Show();

	// Тест 4: Добавление элемента
	cout << "\n--- Тест 4: Добавление элемента ---" << endl;
	Magazin mag4("Техника", "Кузнецов", 64);
	group.Add();
	cout << "После добавления, размер: " << group() << endl;
	group.Show();

	// Тест 5: Удаление элемента
	cout << "\n--- Тест 5: Удаление элемента ---" << endl;
	group.Del();
	cout << "После удаления, размер: " << group() << endl;
	group.Show();

	// Тест 6: Копирование
	cout << "\n--- Тест 6: Копирование группы ---" << endl;
	tree group2 = group;
	group2.Show();

	// Тест 7: Диалоговый режим
	cout << "\n--- Тест 7: Диалоговый режим ---" << endl;
	cout << "Доступные команды:" << endl;
	cout << "  m<N> - создать группу из N элементов" << endl;
	cout << "  +    - добавить элемент" << endl;
	cout << "  -    - удалить элемент" << endl;
	cout << "  s    - показать все элементы" << endl;
	cout << "  z    - показать названия" << endl;
	cout << "  q    - выход" << endl;

	Dialog dialog;
	dialog.Execute();

	cout << "\nПрограмма завершена." << endl;

	return 0;


}

