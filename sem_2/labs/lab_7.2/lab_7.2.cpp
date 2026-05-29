#include <iostream>
#include <clocale>
#include <cstdarg>
using namespace std;


int ten(const char* vosm)
{
	int res = 0;
	int num;

	for (int i = 0; vosm[i] != '\0'; i++)
	{
		char c = vosm[i];
		
		switch (c)
		{
			case '0': num = 0; break;
			case '1': num = 1; break;
			case '2': num = 2; break;
			case '3': num = 3; break;
			case '4': num = 4; break;
			case '5': num = 5; break;
			case '6': num = 6; break;
			case '7': num = 7; break;
			default:
				cout << "Ошибка!" << endl;
				return -1;
		}

		res = res * 8 + num;
	}
	return res;
}

void transl(int count, ...)
{
	va_list args;
	va_start(args, count);

	for (int i = 0; i < count; i++)
	{
		const char* num_8 = va_arg(args, const char*);
		int num_10 = ten(num_8);

		if (num_10 != -1)
		{
			cout << num_8 << " (8) = " << num_10 << " (10)" << endl;
		}

	}
	va_end(args);
}

int main()
{
	setlocale(LC_ALL, "RU");
	cout << "Вызов с 3 параметрами: " << endl;
	transl(3, "12", "777", "1234");

	cout << "Вызов с 4 параметрами: " << endl;
	transl(4, "15", "376", "3222", "7777");

	cout << "Вызов с 7 параметрами: " << endl;
	transl(7, "40", "17", "654", "", "7702", "216", "77777");

	return 0;
}