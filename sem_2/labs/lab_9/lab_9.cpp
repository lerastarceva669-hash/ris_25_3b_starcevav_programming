#include <iostream>
#include <clocale>
#include <fstream>
#include <string>

using namespace std;


int main()
{
	setlocale(LC_ALL, "RU");
	int N1, N2;
	cout << "Введите N1 и N2 (номера строк для копирования): ";
	cin >> N1 >> N2;

	ifstream in("C:\\Users\\Lera\\Desktop\\Fail1.txt");
	ofstream out("C:\\Users\\Lera\\Desktop\\Fail2.txt");
	string line;

	int curr_line = 1;
	int line_copi = 0;

	if (N1 < 1 || N2 < N1)
	{
		cout << "Неккоректные данные!" << endl;
		return -1;
	}

	if (!in.is_open() || !out.is_open())
	{
		cout << "Не удалось открыть файл!" << endl;
		return 1;
	}

	while (getline(in, line))
	{
		if (curr_line >= N1 && curr_line <= N2) //находится ли строка в диапазоне
		{
			if (!line.empty())
			{
				if (line.back() == 'A' || line.back() == 'А')
				{
					out << line << endl;
					line_copi++;
				}
			}
		}
		curr_line++;
	}
	in.close();
	out.close();

	//поиск строки с максимальным количеством А

	ifstream f_2("C:\\Users\\Lera\\Desktop\\Fail2.txt");
	int max_count = -1;
	int line_max = -1;
	int num_line = 1;

	if (!f_2.is_open())
	{
		cout << "Не удалось открыть файл!" << endl;
		return 1;
	}

	while (getline(f_2, line))
	{
		int A_count = 0;
		for (int i = 0; line[i] != '\0';i++)
		{
			if (line[i] == 'A' || line[i] == 'А') A_count++;

		}
		if (A_count > max_count)
		{
			max_count = A_count;
			line_max = num_line;
		}
		num_line++;
	}
	f_2.close();

	cout << "Скопировано строк: " << line_copi << endl;
	if (line_max != -1)
	{
		cout << "Номер строки с наибольшим количеством букв А: " << line_max << endl;
		cout << "Количество букв А: " << max_count << endl;
	}
	else
	{
		cout << "Файл пустой" << endl;
	}

	return 0;
}