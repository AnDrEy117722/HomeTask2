#pragma once

#include <iostream>
using namespace std;

template <class Type>
class DoubleLinkedList
{

	typedef struct Node
	{
		Type value{};
		Node* prev = nullptr;
		Node* next = nullptr;
	}
	Node;
	Node* head = nullptr;
	Node* end = nullptr;
	int length = 0;

	void mergesort(Node** firstElement);
	void frontBackSplit(Node* source, Node** frontRef, Node** backRef);
	Node* sortedMerge(Node* a, Node* b);

	bool (*funcComparator)(Type a, Type b);

public:

	DoubleLinkedList();
	void addFirst(Type element);
	void addLast(Type element);
	void addAfterElement(Type prev_element, Type element);
	void addInPosition(Type element, int position);
	void remove(Type element);
	void move(Type firstElement, Type secondElement);
	void sort(bool (*funcComparator)(Type a, Type b));
	void sort();

	void printList();
	void printListReverse();
	int getLength() { return length; }

};

template <class Type>
DoubleLinkedList<Type>::DoubleLinkedList() {

	head = new Node;
	end = new Node;
	funcComparator = [](Type a, Type b) {return a >= b; };

}

template <class Type>
void DoubleLinkedList<Type>::addFirst(Type element) {

	Node* node = new Node;
	node->value = element;
	if (head->next == nullptr) {
		head->next = node;
		end->prev = node;
	}
	else
	{
		node->next = head->next;
		Node* node_next = node->next;
		node_next->prev = node;
		head->next = node;
	}
	length++;

}

template <class Type>
void DoubleLinkedList<Type>::addLast(Type element) {

	Node* node = new Node;
	node->value = element;
	if (head->next == nullptr) {
		head->next = node;
		end->prev = node;
	}
	else
	{
		node->prev = end->prev;
		Node* node_prev = node->prev;
		node_prev->next = node;
		end->prev = node;
	}
	length++;

}

template <class Type>
void DoubleLinkedList<Type>::addAfterElement(Type prev_element, Type element) {

	Node* node = new Node;
	node->value = element;
	if (head->next == nullptr) {
		cout << "List is empty, element " << element << " is first" << endl;
		head->next = node;
		end->prev = node;
	}
	else
	{
		Node* prev_element_node = head->next;
		while (prev_element_node->value != prev_element)
		{
			if (prev_element_node->next != nullptr)
				prev_element_node = prev_element_node->next;
			else {
				cout << "\nElement " << element << " doesn't exist" << endl;
				return;
			}
		}
		if (prev_element_node->next != nullptr) {
			Node* next_element_node = prev_element_node->next;
			prev_element_node->next = node;
			next_element_node->prev = node;
			node->next = next_element_node;
			node->prev = prev_element_node;
		}
		else {
			prev_element_node->next = node;
			node->prev = prev_element_node;
			end->prev = node;
		}
		
	}
	length++;

}

template <class Type>
void DoubleLinkedList<Type>::addInPosition(Type element, int position) {

	if (position >= length) {
		cout << "\nInsertion point doesn't exist" << endl;
		return;
	}
	if (position < 0) {
		cout << "\nError! Position doesn't valid" << endl;
		return;
	}

	if (position == length - 1) {
		addLast(element);
		return;
	}
	if (position == 0) {
		addFirst(element);
		return;
	}

	Node* node = new Node;
	node->value = element;
	Node* next_element_node = head->next;
	for (int i = 0; i < position; ++i) {
		next_element_node = next_element_node->next;
	}

	Node* prev_element_node = next_element_node->prev;
	prev_element_node->next = node;
	next_element_node->prev = node;
	node->next = next_element_node;
	node->prev = prev_element_node;

	length++;

}

template <class Type>
void DoubleLinkedList<Type>::remove(Type element) {

	if (head->next == nullptr) {
		cout << "List is empty, element " << element << " doesn't exist" << endl;
		return;
	}
	else
	{
		Node* element_node = head->next;
		while (element_node->value != element)
		{
			if (element_node->next != nullptr)
				element_node = element_node->next;
			else {
				cout << "\nElement " << element << " doesn't exist" << endl;
				return;
			}
		}
		if (element_node->next != nullptr && element_node->prev != nullptr) {
			Node* next_element_node = element_node->next;
			Node* prev_element_node = element_node->prev;
			prev_element_node->next = next_element_node;
			next_element_node->prev = prev_element_node;
		}
		else if (element_node->next != nullptr) {
			Node* next_element_node = element_node->next;
			next_element_node->prev = nullptr;
			head->next = next_element_node;
		} 
		else if (element_node->prev != nullptr) {
			Node* prev_element_node = element_node->prev;
			prev_element_node->next = nullptr;
			end->prev = prev_element_node;
		}
		else {
			head->next = nullptr;
			end->prev = nullptr;
		}
		delete element_node;
	}
	length--;

}

template <typename Type>
void DoubleLinkedList<Type>::move(Type firstElement, Type secondElement) {

	if (head->next == nullptr) {
		cout << "Error! List is empty" << endl;
		return;
	}
	else
	{
		if (firstElement == secondElement)
			return;
		Node* firstElement_node = head->next;
		Node* secondElement_node = head->next;
		bool flag_firstElementIsExist = false;
		bool flag_secondElementIsExist = false;
		while (firstElement_node->value != firstElement || secondElement_node->value != secondElement)
		{
			if (!flag_firstElementIsExist) {
				if (firstElement_node->value == firstElement)
					flag_firstElementIsExist = true;
				if (firstElement_node->next != nullptr && firstElement_node->value != firstElement)
					firstElement_node = firstElement_node->next;
				if (firstElement_node->next == nullptr && firstElement_node->value != firstElement) {
					cout << "\nElement " << firstElement << " doesn't exist" << endl;
					return;
				}
			}
			if (!flag_secondElementIsExist) {
				if (secondElement_node->value == secondElement)
					flag_secondElementIsExist = true;
				if (secondElement_node->next != nullptr && secondElement_node->value != secondElement)
					secondElement_node = secondElement_node->next;
				if (secondElement_node->next == nullptr && secondElement_node->value != secondElement) {
					cout << "\nElement " << secondElement << " doesn't exist" << endl;
					return;
				}
			}
			
		}

		Node* next_firstElement_node = firstElement_node->next;
		Node* prev_firstElement_node = firstElement_node->prev;
		Node* next_secondElement_node = secondElement_node->next;
		Node* prev_secondElement_node = secondElement_node->prev;
		//Первый элемент стоит перед вторым
		if (firstElement_node->next == secondElement_node) {
			//Первый элемент не является первым в списке, второй элемент не является последним
			if (prev_firstElement_node != nullptr && next_secondElement_node != nullptr) {
				prev_firstElement_node->next = secondElement_node;
				next_secondElement_node->prev = firstElement_node;
			}
			//Первый элемент является первым в списке, второй элемент не является последним
			else if (prev_firstElement_node == nullptr && next_secondElement_node != nullptr) {
				next_secondElement_node->prev = firstElement_node;
				head->next = secondElement_node;
			}
			//Первый элемент не является первым в списке, второй элемент является последним
			else if (prev_firstElement_node != nullptr && next_secondElement_node == nullptr) {
				prev_firstElement_node->next = secondElement_node;
				end->prev = firstElement_node;
			}
			//Первый элемент является первым в списке, второй элемент является последним
			else if (prev_firstElement_node == nullptr && next_secondElement_node == nullptr) {
				head->next = secondElement_node;
				end->prev = firstElement_node;
			}
			firstElement_node->next = next_secondElement_node;
			firstElement_node->prev = secondElement_node;
			secondElement_node->next = firstElement_node;
			secondElement_node->prev = prev_firstElement_node;
		}
		//Второй элемент стоит перед первым
		else if (secondElement_node->next == firstElement_node) {
			//Второй элемент не является первым в списке, первый элемент не является последним
			if (prev_secondElement_node != nullptr && next_firstElement_node != nullptr) {
				prev_secondElement_node->next = firstElement_node;
				next_firstElement_node->prev = secondElement_node;
			}
			//Второй элемент является первым в списке, первый элемент не является последним
			else if (prev_secondElement_node == nullptr && next_firstElement_node != nullptr) {
				next_firstElement_node->prev = secondElement_node;
				head->next = firstElement_node;
			}
			//Второй элемент не является первым в списке, первый элемент является последним
			else if (prev_secondElement_node != nullptr && next_firstElement_node == nullptr) {
				prev_secondElement_node->next = firstElement_node;
				end->prev = secondElement_node;
			}
			//Второй элемент является первым в списке, первый элемент является последним
			else if (prev_secondElement_node == nullptr && next_firstElement_node == nullptr) {
				head->next = firstElement_node;
				end->prev = secondElement_node;
			}
			secondElement_node->next = next_firstElement_node;
			secondElement_node->prev = firstElement_node;
			firstElement_node->next = secondElement_node;
			firstElement_node->prev = prev_secondElement_node;
		}
		//Первый и второй элемент не являются соседями
		else {
			//Слева и справа от первого и второго элемента есть соседи
			if (firstElement_node->next != nullptr && firstElement_node->prev != nullptr &&
				secondElement_node->next != nullptr && secondElement_node->prev != nullptr) {
				next_firstElement_node->prev = secondElement_node;
				prev_firstElement_node->next = secondElement_node;
				next_secondElement_node->prev = firstElement_node;
				prev_secondElement_node->next = firstElement_node;
			}
			//Слева и справа от второго элемента есть соседи, первый элемент является последним в списке
			else if (firstElement_node->next == nullptr && firstElement_node->prev != nullptr &&
				secondElement_node->next != nullptr && secondElement_node->prev != nullptr) {
				prev_firstElement_node->next = secondElement_node;
				next_secondElement_node->prev = firstElement_node;
				prev_secondElement_node->next = firstElement_node;
				end->prev = secondElement_node;
			}
			//Слева и справа от первого элемента есть соседи, второй элемент является последним в списке
			else if (firstElement_node->next != nullptr && firstElement_node->prev != nullptr &&
				secondElement_node->next == nullptr && secondElement_node->prev != nullptr) {
				next_firstElement_node->prev = secondElement_node;
				prev_firstElement_node->next = secondElement_node;
				prev_secondElement_node->next = firstElement_node;
				end->prev = firstElement_node;
			}
			//Слева и справа от второго элемента есть соседи, первый элемент является первым в списке
			else if (firstElement_node->next != nullptr && firstElement_node->prev == nullptr &&
				secondElement_node->next != nullptr && secondElement_node->prev != nullptr) {
				next_firstElement_node->prev = secondElement_node;
				next_secondElement_node->prev = firstElement_node;
				prev_secondElement_node->next = firstElement_node;
				head->next = secondElement_node;
			}
			//Слева и справа от первого элемента есть соседи, второй элемент является первым в списке
			else if (firstElement_node->next != nullptr && firstElement_node->prev != nullptr &&
				secondElement_node->next != nullptr && secondElement_node->prev == nullptr) {
				next_firstElement_node->prev = secondElement_node;
				prev_firstElement_node->next = secondElement_node;
				next_secondElement_node->prev = firstElement_node;
				head->next = firstElement_node;
			}
			//Второй элемент является первым в списке, первый элемент является последним в списке
			else if (firstElement_node->next == nullptr && firstElement_node->prev != nullptr &&
				secondElement_node->next != nullptr && secondElement_node->prev == nullptr) {
				prev_firstElement_node->next = secondElement_node;
				next_secondElement_node->prev = firstElement_node;
				head->next = firstElement_node;
				end->prev = secondElement_node;
			}
			//Первый элемент является первым в списке, второй элемент является последним в списке
			else if (firstElement_node->next != nullptr && firstElement_node->prev == nullptr &&
				secondElement_node->next == nullptr && secondElement_node->prev != nullptr) {
				next_firstElement_node->prev = secondElement_node;
				prev_secondElement_node->next = firstElement_node;
				head->next = secondElement_node;
				end->prev = firstElement_node;
			}
			firstElement_node->next = next_secondElement_node;
			firstElement_node->prev = prev_secondElement_node;
			secondElement_node->next = next_firstElement_node;
			secondElement_node->prev = prev_firstElement_node;
		}
	}

}

template <class Type>
void DoubleLinkedList<Type>::sort(bool (*Comparator)(Type a, Type b)) {

	if (head->next == nullptr) {
		cout << "\nError! List is empty." << endl;
		return;
	}
	if (length == 1)
		return;
	funcComparator = Comparator;
	mergesort(&(head->next));

	Node* node = head->next;
	while (node->next != nullptr)
	{
		node = node->next;
	}
	end->prev = node;

}

template <class Type>
void DoubleLinkedList<Type>::sort() {

	if (head->next == nullptr) {
		cout << "\nError! List is empty." << endl;
		return;
	}
	if (length == 1)
		return;

	funcComparator = [](Type a, Type b) {return a >= b; };
	mergesort(&(head->next));

	Node* node = head->next;
	while (node->next != nullptr)
	{
		node = node->next;
	}
	end->prev = node;

}

template <class Type>
void DoubleLinkedList<Type>::mergesort(Node** firstElement) {

	if ((*firstElement)->next == nullptr)
		return;

	Node* a = nullptr;
	Node* b = nullptr;

	// разделить `firstElement` на подсписки `a` и `b`
	frontBackSplit(*firstElement, &a, &b);

	mergesort(&a);
	mergesort(&b);

	*firstElement = sortedMerge(a, b);
	head->next = *firstElement;

}

template <class Type>
void DoubleLinkedList<Type>::frontBackSplit(Node* source, Node** frontRef, Node** backRef) {

	// если длина меньше 2, обрабатывать отдельно
	if (source == nullptr || source->next == nullptr)
	{
		*frontRef = source;
		*backRef = nullptr;
		return;
	}

	Node* slow = source;
	Node* fast = source->next;

	// продвигаем `fast` на два узла и продвигаем `slow` на один узел
	while (fast != nullptr)
	{
		fast = fast->next;
		if (fast != nullptr)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	// `slow` находится перед средней точкой в списке, поэтому разделим его на две части
	*frontRef = source;
	*backRef = slow->next;
	slow->next = nullptr;
	(*backRef)->prev = nullptr;
}

template <class Type>
typename DoubleLinkedList<Type>::Node* DoubleLinkedList<Type>::sortedMerge(Node* a, Node* b) {

	// базовые случаи
	if (a == nullptr) {
		return b;
	}
	else if (b == nullptr) {
		return a;
	}

	Node* result = nullptr;

	// выбираем `a` или `b` и повторяем
	if (funcComparator(b->value, a->value))
	{
		result = a;
		result->next = sortedMerge(a->next, b);
		(result->next)->prev = a;
	}
	else {
		result = b;
		result->next = sortedMerge(a, b->next);
		(result->next)->prev = b;
	}

	return result;

}

template <class Type>
void DoubleLinkedList<Type>::printList() {

	Node* node = head->next;
	if (node == nullptr) {
		cout << "List is empty" << endl;
		return;
	}
	while (node->next != nullptr)
	{
		cout << node->value << " ";
		node = node->next;
	}
	cout << node->value << endl;
}

template <class Type>
void DoubleLinkedList<Type>::printListReverse() {

	Node* node = end->prev;
	if (node == nullptr) {
		cout << "List is empty" << endl;
		return;
	}
	while (node->prev != nullptr)
	{
		cout << node->value << " ";
		node = node->prev;
	}
	cout << node->value << endl;
}
