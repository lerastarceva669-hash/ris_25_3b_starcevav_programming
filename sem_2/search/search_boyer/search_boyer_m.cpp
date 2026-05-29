#include <iostream>
#include <clocale>

using namespace std;

int boyer_moore(const string& stroka, const string& podstroka)
{
	int stroka_len = stroka.length();
	int podstroka_len = podstroka.length();

	if (stroka_len == 0 || podstroka_len == 0)
	{
		return -1;
	}

	if (podstroka_len > stroka_len) {
		return -1;
	}

	int arr[100];

	for (int i = 0; i < 100; i++)
	{
		arr[i] = podstroka_len;
	}

	for (int i = 0; i < podstroka_len - 1; i++)
	{
		arr[podstroka[i]] = podstroka_len - 1 - i;
	}

	int pos = podstroka_len - 1;

	while (pos < stroka_len)
	{
		int i = podstroka_len - 1;

		while (i >= 0 && podstroka[i] == stroka[pos - (podstroka_len - 1 - i)])
			i--;

		if (i == -1)
		{
			return pos - podstroka_len + 1;
		}

		pos += arr[stroka[pos - (podstroka_len - 1 - i)]];
	}

	return -1;
}

int main()
{
	setlocale(LC_ALL, "RU");
	string stroka, podstroka;
	int pos;

	cin >> stroka >> podstroka;

	pos = boyer_moore(stroka, podstroka);

	if (pos == -1) {
		cout << "Подстрока не найдена." << endl;
	}
	else {
		cout << "Подстрока найдена на позиции: " << pos << endl;
	}
	return 0;
}