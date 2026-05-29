#include <iostream>
#include <clocale>
#include <string>
using namespace std;

struct Node
{
	string key;
	Node* next = nullptr;
};

struct Queue
{
	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
};

void PushBack(Queue* queue, string str)
{
	if (queue->size != 0)
	{
		Node* new_node = new Node;
		queue->size++;
		new_node->key = str;
		new_node->next = nullptr;
		queue->tail->next = new_node;
		queue->tail = new_node;
	}
	else
	{
		Node* new_node = new Node;
		queue->size = 1;
		new_node->key = str;
		queue->head = new_node;
		queue->tail = new_node;
	}
}

void pop(Queue* queue)
{
	Node* temp = queue->head;
	queue->head = temp->next;
	queue->size--;
	delete temp;
}

void pop_key(Queue* queue, string k)
{
	if (queue->size == 0)
	{
		cout << "Очередь пуста!" << endl;
		return;
	}
	int count = 1;
	while (count <= queue->size)
	{
		if (queue->head->key != k)
		{
			PushBack(queue, queue->head->key);
			pop(queue);
			count++;
		}
		else
		{
			pop(queue);
		}
	}
}


auto create(int size)
{
	Queue* queue = new Queue;
	string str;

	cout << "Введите ключи элементов: " << endl;

	for (int i = 1; i <= size; i++)
	{
		cout << i << '\t';
		cin >> str;
		PushBack(queue, str);
	}
	return queue;
}

int main()
{
	setlocale(LC_ALL, "RU");
	Queue queue;

	create(5);


	return 0;
}