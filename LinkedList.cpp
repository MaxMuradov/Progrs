#include <iostream>

using namespace std;

struct Node {
	int value;
	Node* next;
	Node* prev;
};

struct List {
	int size;
	Node* head;
	Node* tail;
};

void push_back(List &list, int newValue)
{
	if (list.tail == nullptr){
		Node* newnode = new Node;
		list.tail = newnode;
		list.head = newnode;
		newnode->value = newValue;
		newnode->prev = nullptr;
		newnode->next = nullptr;
		list.size = 1;
	}
	else {
		Node* newnode = new Node;
		newnode->value = newValue;
		newnode->next = nullptr;
		newnode->prev = list.tail;
		list.tail->next = newnode;
		list.tail = newnode;
		list.size++;
	}
}

void pop_front(List &list)
{
	if (list.size > 0){
		cout << "Nihuya";
	}
	else {
		Node* delete_node = list.head;
		list.head = list.head->next; // list.head = delete_node->next;
		list.head->prev = nullptr;
		delete delete_node;
		list.size--;
	}
}

void pop_back(List &list)
{
	if (list.size > 0) {
		cout << "Nihuya";
	}
	else {
		Node* delete_node = list.tail;
		list.tail = list.tail->prev; // list.head = delete_node->next;
		list.tail->next = nullptr;
		delete delete_node;
		list.size--;
	}
}

void push_front(List &list, int newValue)
{
	if (list.head == nullptr){
		Node* newnode = new Node;
		newnode->value = newValue;
		list.head = newnode;
		list.tail = newnode;
		list.size = 1;
	}
	else {
		Node* newnode = new Node;
		newnode->value = newValue;
		newnode->next = list.head;
		newnode->prev = nullptr;
		list.head->prev = newnode;
		list.head = newnode;
		list.size++;
	}
}

void print(List &list)
{
	Node* ptr = list.head;
	while (ptr != nullptr){
		cout << ptr->value;
		ptr = ptr->next;
	}
}

void clear(List& list)
{
	for (int i = list.size; i > 0; i--)
		pop_back(list); // pop_front(list);
}

Node findElemByIndex(List& list, int index)
{
	Node* ptr = list.head;
	for (int i = 1; i <= index; ++i)
	{
		ptr = ptr->next;
	}
	return *ptr;
}

int main()
{

}