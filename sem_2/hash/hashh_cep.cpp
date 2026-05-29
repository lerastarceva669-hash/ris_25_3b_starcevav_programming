
#include <iostream>
#include <clocale>
#include <string>
#include <cmath>
#include <ctime>




using namespace std;
static int collision_cnt = 0;

string name[5] = { "Василий", "Дмитрий","Николай","Михаил","Анатолий" };


string surname[5] = { "Иванов", "Костенко","Щукин","Смирнов","Петров" };


string patronymic[5] = { "Александрович", "Вячеславович","Дмитриевич","Кириллович","Степанович" };


string dates[5] = { "31.12.1999", "22.09.2007","25.02.2009","12.12.2000","13.05.1987" };


string adress[5] = { "Луначарского, 26", "Свиязева, 9","Дедюкина, 20","Крисанова, 89","Попова, 10" };

int getRandomNumber()
{
	return rand() % 5;
}

string getRandomName()
{
	return (surname[getRandomNumber()] + " " + name[getRandomNumber()] + " " + patronymic[getRandomNumber()]);
}

string getRandomAdress()
{
	return adress[getRandomNumber()];
}

string getRandomDate()
{
	return dates[getRandomNumber()];
}



struct Human
{
	string name;
	string birth_date;
	string adress;

	Human() : name(""), birth_date(""), adress("") {}

	void createRandom()
	{
		name = getRandomName();
		birth_date = getRandomDate();
		adress = getRandomAdress();
	}

	void show()
	{
		cout << "ФИО:\t\t" << name
			<< "\nДата рождения:\t" << birth_date
			<< "\nАдрес:\t\t" << adress << endl << endl;
		return;
	}

};

struct Node
{
	Human data;
	Node* next = nullptr;
};

struct List
{
	Node* head_node = nullptr;

	void addToBegin(const Human& human)
	{
		Node* newNode = new Node;
		newNode->data = human;
		newNode->next = head_node;
		head_node = newNode;
	}

	void addToEnd(const Human& human)
	{
		Node* newNode = new Node;
		newNode->data = human;
		newNode->next = nullptr;

		if (head_node == nullptr) {
			head_node = newNode;
			return;
		}

		Node* current = head_node;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
	}

	Node* find(const string& name) {
		Node* current = head_node;
		while (current != nullptr) {
			if (current->data.name == name) {
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}

	int remove(const string& name)
	{
		if (head_node == nullptr) return -1;

		if (head_node->data.name == name) {
			Node* temp = head_node;
			head_node = head_node->next;
			delete temp;
			return 1;
		}

		Node* current = head_node;
		while (current->next != nullptr) {
			if (current->next->data.name == name) {
				Node* temp = current->next;
				current->next = current->next->next;
				delete temp;
				return 1;
			}
			current = current->next;
		}

		return -1;
	}

	void clear() {
		Node* current = head_node;
		while (current != nullptr) {
			Node* temp = current;
			current = current->next;
			delete temp;
		}
		head_node = nullptr;
	}

	int getSize() {
		int count = 0;
		Node* current = head_node;
		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}

	void show() {
		if (head_node == nullptr) {
			cout << "пусто";
			return;
		}
		Node* current = head_node;
		int pos = 0;
		while (current != nullptr) {
			cout << "\n    [" << pos++ << "] " << current->data.name;
			current = current->next;
		}
	}

	void showDetailed() {
		if (head_node == nullptr) {
			cout << "пусто";
			return;
		}

		Node* current = head_node;
		int pos = 0;
		while (current != nullptr) {
			cout << "\n  [" << pos++ << "] " << current->data.name;
			cout << "\n       Дата рождения: " << current->data.birth_date;
			cout << "\n       Адрес: " << current->data.adress;
			current = current->next;
		}
	}
};

struct HashTable
{
	List* arr;
	int size;

	int stringToNumber(const string& fio)
	{
		int k = 0;
		for (char c : fio)
		{
			k = k * 31 + (unsigned char)c;
		}
		return abs(k);
	}

	int hashFunc(const string& s)
	{
		int number = stringToNumber(s);
		return number % size;
	}

	void createTable(int s)
	{
		size = s;
		arr = new List[size];
	}
	void clearTable()
	{
		for (int i = 0; i < size; i++)
		{
			arr[i].clear();
		}
		delete[] arr;
		arr = nullptr;
		size = 0;
	}

	void show()
	{
		cout << "\n=== ХЭШ-ТАБЛИЦА (МЕТОД ЦЕПОЧЕК) ===" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << "Ячейка " << i << " [размер " << arr[i].getSize() << "]: ";
			arr[i].show();
			cout << endl;
		}
		cout << "=============================================================" << endl;
	}

	void showDetailed() {
		cout << "\n=== ДЕТАЛЬНЫЙ ВЫВОД ХЭШ-ТАБЛИЦЫ ===" << endl;
		for (int i = 0; i < size; i++) {
			cout << "\nЯчейка " << i << " [размер " << arr[i].getSize() << "]: ";
			arr[i].showDetailed();
			cout << endl;
		}
		cout << "====================================" << endl;
	}

	void add(const Human& to_add)
	{
		int index = hashFunc(to_add.name);

		Node* ex = arr[index].find(to_add.name);

		if (ex != nullptr)
		{
			ex->data = to_add;
			cout << "Обновлен: " << to_add.name << " в цепочке " << index << endl;
			return;
		}

		// Добавляем в начало списка
		int oldSize = arr[index].getSize();
		arr[index].addToBegin(to_add);

		// Если в списке было больше 0 элементов - коллизия
		if (oldSize > 0) {
			collision_cnt++;
		}

		cout << "Добавлен: " << to_add.name << " → индекс " << index
			<< " (размер цепочки: " << arr[index].getSize() << ")" << endl;

	}

	int findeIndex(const string& to_find)
	{
		int index = hashFunc(to_find);
		Node* node = arr[index].find(to_find);

		if (node != nullptr) {
			cout << "Найден в цепочке " << index << endl;
			return index;
		}

		return -1;

	}

	Human* find(const string& to_find) {
		int index = hashFunc(to_find);
		Node* node = arr[index].find(to_find);

		if (node != nullptr) {
			return &node->data;
		}

		return nullptr;
	}


	void pop(const string& to_delete)
	{
		int index = hashFunc(to_delete);

		if (arr[index].remove(to_delete))
		{
			cout << "Удален: " << to_delete << " из цепочки " << index << endl;
		}
		else cout << "Не найден для удаления: " << to_delete << endl;
	}

};




int main()
{
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "RUS");


	srand(time(0));

	HashTable ht;
	ht.createTable(7);

	cout << "========= ДОБАВЛЕНИЕ ЭЛЕМЕНТОВ ===========" << endl;

	for (int i = 0; i < 10; i++)
	{
		Human h;
		h.createRandom();
		cout << "Добавляем [" << i + 1 << "]: " << h.name << endl;
		ht.add(h);
	}

	cout << "\n =========== СОДЕРЖИМОЕ ТАБЛИЦЫ ==============" << endl;
	ht.show();

	cout << "\n =========== ПОИСК ЭЛЕМЕНТА ====================" << endl;
	cout << "Введите ФИО для поиска: ";
	string search_name;
	cin.ignore();
	getline(cin, search_name);
	Human* found = ht.find(search_name);

	if (found != nullptr)
	{
		cout << "\n Элемент найден" << endl;
		found->show();
	}
	else cout<< "\n Элемент не найден" << endl;


	cout << "\n============= УДАЛЕНИЕ ЭЛЕМЕНТА =============" << endl;
	ht.pop("Иванов Василий Александрович");

	cout << "\n ================ТАБЛИЦА ПОСЛЕ УДАЛЕНИЯ ==========" << endl;
	ht.show();

	cout << "\nКоличество коллизий: " << collision_cnt << endl;

	ht.clearTable();


	return 0;
}