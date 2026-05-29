#include <iostream>
#include <clocale>
#include <string>
using namespace std;

struct Node //узел
{
	string data;
	Node* pointer_to_next_node = nullptr;
};

struct Stack //список
{
	Node* head_node = nullptr;
};

void pushBack(Stack& stack, const string& data) //список и данные, добавление элемента в конец списка
{
	Node* new_node = new Node;
	new_node->data = data; // присваиваем полю узла дата данные

	if (stack.head_node == nullptr)
	{
		stack.head_node = new_node;
	}
	else
	{
		Node* current_node = stack.head_node;
		while (current_node->pointer_to_next_node != nullptr)
			current_node = current_node->pointer_to_next_node;
		current_node->pointer_to_next_node = new_node;
	}
}

void push(Stack& stack, const string& data) //список и данные, добавление элемента
{
	Node* new_node = new Node;
	new_node->data = data; // присваиваем полю узла дата данные

	new_node->pointer_to_next_node = stack.head_node;
	stack.head_node = new_node;
}

//удаление первого узла (головы)
void pop(Stack& stack)
{
	if (stack.head_node == nullptr) return;

	Node* node_to_delete = stack.head_node;
	stack.head_node = stack.head_node->pointer_to_next_node;

	delete node_to_delete;

}

//функция удаления по ключу
void DeleteKey(Stack& mainStack, const string& key)
{
	Stack tmpStack;

	while (mainStack.head_node != nullptr)
	{
		if (mainStack.head_node->data != key) {
			push(tmpStack, mainStack.head_node->data);
		}
		pop(mainStack);
	}

	while (tmpStack.head_node != nullptr)
	{
		push(mainStack, tmpStack.head_node->data);
		pop(tmpStack);
	}
}

//функция вставки k элементов перед заданным номером
void k_stack(Stack& mainStack, const string& data, int pos, int k)
{
	if (pos <= 0) return;

	int size = 0;
	Node* current = mainStack.head_node;
	while (current != nullptr)
	{
		size++;
		current = current->pointer_to_next_node;
	}

	if (pos > size + 1) return;

	Stack tempStack;
	int cur_pos = 1;


	while (mainStack.head_node != nullptr && cur_pos < pos)
	{
		push(tempStack, mainStack.head_node->data);
		pop(mainStack);
		cur_pos++;
	}
	
	fillStack(mainStack, k);
	while (tempStack.head_node != nullptr)
	{
		push(mainStack, tempStack.head_node->data);
		pop(tempStack);
	}
}


//функция вывода 
void printStack(const Stack& stack)
{
	Node* current_node = stack.head_node;
	cout << "Стек сверху вниз: " << endl;
	while (current_node != nullptr)
	{
		cout << current_node->data << ' ' << endl;
		current_node = current_node->pointer_to_next_node;
	}
	cout << endl;
}

//заполнение стека элементами
void fillStack(Stack& stack, int k)
{
	string temp;
	cout << "Введите элементы для добавление в стек: " << endl;
	for (int i = 0; i < k; i++)
	{
		cout << i + 1 << "-й элемент: ";
		cin >> temp;
		push(stack, temp);
	}
}

int main()
{
	setlocale(LC_ALL, "RU");
	system("chcp 1251");
	system("cls");
	Stack stack1;

	int choice, n, kol, num;
	string element, key, temp;

	cout << "Укажите количество элементов для добавления в стек: ";
	cin >> n;
	fillStack(stack1, n);
	printStack(stack1);
	cout << "Введите элемент для добавления в стек: ";
	cin >> element;
	push(stack1, element);
	printStack(stack1);
	cout << "Удаление элемента сверху: " << endl;
	pop(stack1);
	printStack(stack1);
	cout << "Введите значение элемента для удаления: " << endl;
	cin >> key;
	DeleteKey(stack1, key);
	cout << "Стек после удаления элемента со значением \"" << key << "\":" << endl;
	printStack(stack1);
	cout << "Введите количество элементов, которые хотите вставить: " << endl;
	cin >> kol;
	cout << "Введите номер элемента, перед которым хотите их вставить: " << endl;
	cin >> num;
	

	return 0;
}