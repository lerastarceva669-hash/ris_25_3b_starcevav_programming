#include <iostream>
#include <clocale>
#include <string>
using namespace std;

void search_str(string& str, string& podstr, int s, int s1)
{
	for (int i = 0; i <= s-s1; i++)
	{
		cout << "Шаг: " << i + 1 << "; позиция в тексте: " << i<<endl;
		cout << "Строка: " << str << endl;
		cout << "Шаблон: " << podstr;

		bool f = true;
		int j = 0;

		while (j < s1 && f)
		{
			if (str[i + j] != podstr[j])
			{
				cout << str[i + j] << " and " << podstr[j] << " - совпадение" << endl;
				j++;
			}
		}
		if (f)
			cout << "Полное совпадение на позиции " << i << endl;
	}
}


int main()
{
	setlocale(LC_ALL, "RU");
	string stroka, podstroka;

	cout << "Введите основную строку: ";
	getline(cin, stroka);
	cout << "Введите подстроку: ";
	getline(cin, podstroka);
	int s = 0, s1 = 0;

	for (int i = 0; stroka[i] != '\0'; i++)
	{
		s++;
	}

	for (int i = 0; podstroka[i] != '\0'; i++)
	{
		s1++;
	}

	if (s1 > s) return -1;

	search_str(stroka, podstroka, s, s1);
	return 0;
}
