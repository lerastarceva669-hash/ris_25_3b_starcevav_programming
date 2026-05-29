#include <iostream>
#include <clocale>
#include <string>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	system("chcp 1251");
	system("cls");

	string str;
	cout << "Введите строку: ";
	getline(cin, str);
	str += " ";

	char masNum[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	char masSim[] = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
		'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
		'G', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'А', 'а', 'Б', 'б', 'В' ,'в' ,'Г' ,'г' ,'Д' ,'д' ,'Е' ,'е' ,'Ж' ,'ж' ,'З' ,'з' ,'И', 'и',
		 'Й', 'й' ,'К' ,'к' ,'Л' ,'л' ,'М' ,'м' ,'Н' ,'н' ,'О' ,'о' ,'П' ,'п' ,'Р' ,'р' ,'С' ,'с' ,'Т' ,'т' ,'У' ,'у',
		'Ф' ,'ф' ,'Х' ,'х' ,'Ц' ,'ц' ,'Ч','ч' ,'Ш' ,'ш' ,'Щ','щ' ,'ъ' ,'ы' ,'ь', 'Э' ,'э' ,'Ю' ,'ю','Я' ,'я' };

	int a = 0; //индекс первого элемента
	int i = 0; //параметр цикла
	bool flag = true;

	//проверка всех символов строки
	while (str[i] != '\0') {
		for (int j = 0; j < (sizeof(masSim) / sizeof(masSim[0])) && flag; j++) {
			if (str[i] == masSim[j] or str[i] == ' ') {
				flag = false;
			}
		}

		for (int j = 0; j < (sizeof(masNum) / sizeof(masNum[0])) && flag; j++) {
			if (str[i] == masNum[j]) {
				flag = false;
			}
		}

		if (flag) {
			while (str[a] != ' ')
				str.erase(a, 1);
			str.erase(a, 1);//удаляем пробел
			i = a;
		}
		else i++;

		if (str[i] == ' ') {
			a = i + 1;

		}
		flag = true;
	}
	cout << str;

	return 0;
}