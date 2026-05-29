#pragma once
#include "Pair.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int make_file(const char* f_name)
{
	fstream stream(f_name, ios::out | ios::trunc);
	if (!stream) return -1;

	int n;
	Pair p;
	cout << "Введите количество пар: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "\nПара " << i + 1 << endl;
		cin >> p;
		stream << p << endl;
	}
	stream.close();
	cout << "Файл создан. Записано " << n << " пар." << endl;
	return n;
}

int print_file(const char* f_name)
{
	fstream stream(f_name, ios::in);
	if (!stream) return -1;

	Pair p;
	int count = 0;
	cout << "\nСодержимое файла " << f_name << endl;

	while (stream >> p) { cout << ++count << ". " << p << endl; }

	if (count == 0)
	{
		cout << "Файл пуст!" << endl;
	}

	stream.close();
	return count;
}

int delete_less_than(const char* f_name, const Pair& p)
{
	fstream stream(f_name, ios::in);
	if (!stream) return -1;

	const char* temp_name = "temp.txt";
	fstream temp_stream(temp_name, ios::out | ios::trunc);
	if (!temp_stream) return -1;

	Pair current;
	int removed = 0;
	int total = 0;

	while (stream >> current)
	{
		total++;
		if (current < p)
		{
			removed++; 
		}
		else
		{
			temp_stream << current << endl; 
		}
	}
	stream.close();
	temp_stream.close();

	fstream in_temp(temp_name, ios::in);
	fstream out_original(f_name, ios::out | ios::trunc);

	Pair temp_pair;
	while (in_temp >> temp_pair)
	{
		out_original << temp_pair << endl;
	}

	in_temp.close();
	out_original.close();

	remove(temp_name);

	cout << "Всего записей: " << total << endl;
	cout << "Удалено записей: " << removed << endl;
	cout << "Осталось записей: " << total - removed << endl;

	return removed;
}

int increase_by_value(const char* f_name, const Pair& value, double L)
{
	fstream stream(f_name, ios::in);
	if (!stream) return -1;

	const char* temp_name = "temp.txt";
	fstream temp_stream(temp_name, ios::out | ios::trunc);
	if (!temp_stream) return -1;

	Pair current;
	int modified = 0;

	while (stream >> current)
	{
		if (current == value)
		{
			current = current + L; 
			modified++;
		}
		temp_stream << current << endl;
	}

	stream.close();
	temp_stream.close();

	fstream in_temp(temp_name, ios::in);
	fstream out_original(f_name, ios::out | ios::trunc);

	Pair temp_pair;
	while (in_temp >> temp_pair)
	{
		out_original << temp_pair << endl;
	}

	in_temp.close();
	out_original.close();

	remove(temp_name);

	cout << "Изменено записей: " << modified << endl;
	return modified;
}

int add_after_position(const char* f_name, int position, int K)
{
	fstream stream(f_name, ios::in);
	if (!stream) return -1;

	const char* temp_name = "temp.txt";
	fstream temp_stream(temp_name, ios::out | ios::trunc);
	if (!temp_stream) return -1;

	Pair current;
	int current_pos = 0;
	bool inserted = false;

	while (stream >> current)
	{
		temp_stream << current << endl;
		current_pos++;

		if (current_pos == position && !inserted)
		{

			for (int i = 0; i < K; i++)
			{
				cout << "\n--- Новая запись " << i + 1 << " ---" << endl;
				Pair new_pair;
				cin >> new_pair;
				temp_stream << new_pair << endl;
			}
			inserted = true;
		
		}
	}

	if (position == current_pos && !inserted)
	{
		for (int i = 0; i < K; i++)
		{
			cout << "\n--- Новая запись " << i + 1 << " ---" << endl;
			Pair new_pair;
			cin >> new_pair;
			temp_stream << new_pair << endl;
		}
		inserted = true;
	}

	stream.close();
	temp_stream.close();

	if (!inserted)
	{
		cout << "Позиция " << position << " не найдена!" << endl;
		remove(temp_name);
		return -1;
	}

	fstream in_temp(temp_name, ios::in);
	fstream out_original(f_name, ios::out | ios::trunc);

	Pair temp_pair;
	while (in_temp >> temp_pair)
	{
		out_original << temp_pair << endl;
	}

	in_temp.close();
	out_original.close();

	remove(temp_name);

	cout << "Добавлено " << K << " записей после позиции " << position << endl;
	return K;

}

int add_to_end(const char* f_name, const Pair& p)
{
	fstream stream(f_name, ios::out | ios::app);
	if (!stream) return -1;

	stream << p << endl;
	stream.close();

	return 1;
}

int clear_file(const char* f_name)
{
	fstream stream(f_name, ios::out | ios::trunc);
	if (!stream) return -1;

	stream.close();
	cout << "Файл очищен." << endl;
	return 0;
}

