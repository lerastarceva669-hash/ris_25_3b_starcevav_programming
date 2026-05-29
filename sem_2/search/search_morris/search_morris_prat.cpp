#include <iostream>
#include <clocale>

using namespace std;

void prefix_f(string& stroka, int* d)
{
	d[0] = 0;
	int j = 0, i = 1;
	while (i < stroka.length())
	{
		if (stroka[i] == stroka[j])
		{
			d[i] = j + 1;
			i++; j++;
		}
		else if (j == 0)
		{
			d[i] = 0;
			i++;
		}
		else j = d[j - 1];
	}
}

void search_morris(string& text, string& patt)
{
	int* d = new int[patt.length()];

	prefix_f(patt, d);
	int i = 0, j = 0;

	while (i < text.length())
	{
		if (patt[j] == text[i]) { i++; j++; }
		if (j == patt.length())
		{
			cout << "Образ найден по индексу: " << i - patt.length() << endl;
			j = d[j - 1];
		}
		else if (i < text.length() && patt[j] != text[i])
		{
			if (j == 0) i++;
			else j = d[j - 1];
		}
	}

	delete[] d; // освобождение памяти
}

int main()
{
	setlocale(LC_ALL, "RU");
	string stroka, obraz;
	int pos;

	cin >> stroka >> obraz;
	search_morris(stroka, obraz);

	return 0;
}