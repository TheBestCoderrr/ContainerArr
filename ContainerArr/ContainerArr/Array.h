#pragma once
#include <iostream>

using namespace std;

template<typename type>
class Node
{
public:
	explicit Node(type v, Node* n = nullptr, Node* p = nullptr) :value(v), next(n), prev(p) {};
	type getValue() const { return value; }
	void setValue(type v) { value = v; }
	Node* getNext() const { return next; }
	void setNext(Node* n) { next = n; }

	Node* getPrev() const { return prev; }
	void setPrev(Node* p) { prev = p; }

	void Print() const { cout << value << "\t"; }

private:
	type value;
	Node* next;
	Node* prev;
};

template<typename type>
class Array
{
private:
	Node<type>* head;
	Node<type>* tail;
	size_t counter;
public:
	Array();
	Array(const Array& other);
	~Array();

	size_t size() const;
	bool  empty() const;
	void push_back(type v);
	void push_front(type v);
	void pop_back();
	void pop_front();
	void clear();
	bool ValidIndex(size_t index) const;
	Node<type>* findNodeByIndex(size_t index) const;
	Node<type>* findNodeByValue(type v, Node<type>* start = nullptr) const;
	void SetAt(size_t index, type v);
	type GetAt(size_t index) const;
	void insert(size_t index, type v);
	void pop_position(size_t index);
	int Replace(type fv, type v);
	void Reverse();
	void Print() const;
	void PrintReverse() const;

	Array& operator=(const Array& other) noexcept;
	Array operator+(const Array& R) const;
	Array& operator+=(const Array& R);
	type operator[](const type index) noexcept;
};

template<typename type>
Array<type>::Array() : head(nullptr), tail(nullptr), counter(0) {}

template<typename type>
Array<type>::Array(const Array& other)
{
	Node<type>* cur = other.head;
	while (cur) {
		push_back(cur->getValue());
		cur = cur->getNext();
	}
}

template<typename type>
Array<type>::~Array() { clear(); }

template<typename type>
size_t Array<type>::size() const{ return counter; }

template<typename type>
bool Array<type>::empty() const { return counter == 0; }

template<typename type>
void Array<type>::push_back(type v)
{
	Node<type>* temp = new Node<type>(v, nullptr, tail);
	if (tail)
		tail->setNext(temp);
	else
		head = temp;
	tail = temp;
	++counter;
}

template<typename type>
void Array<type>::push_front(type v)
{
	Node<type>* temp = new Node<type>(v, head);
	if (head)
		head->setPrev(temp);
	else
		tail = temp;
	head = temp;
	++counter;
}

template<typename type>
void Array<type>::pop_back()
{
	if (!tail) return;
	Node<type>* delNode = tail;
	tail = tail->getPrev();
	if (tail)
		tail->setNext(nullptr);
	else
		head = nullptr;
	delete delNode;
	--counter;
}

template<typename type>
void Array<type>::pop_front()
{
	if (!head) return;
	Node<type>* delNode = head;
	head = head->getNext();
	if (head)
		head->setPrev(nullptr);
	else
		tail = nullptr;
	delete delNode;
	--counter;
}

template<typename type>
void Array<type>::clear() { while (head) pop_front(); }

template<typename type>
bool Array<type>::ValidIndex(size_t index) const { return index >= 0 && index < counter; }

template<typename type>
Node<type>* Array<type>::findNodeByIndex(size_t index) const
{
	if (!ValidIndex(index)) return nullptr;
	size_t n = 0;
	Node<type>* cur = head;
	while (cur)
	{
		if (n == index) break;
		cur = cur->getNext();
		n++;
	}
	return cur;
}

template<typename type>
Node<type>* Array<type>::findNodeByValue(type v, Node<type>* start) const
{
	Node<type>* cur = start ? start : head;
	while (cur)
	{
		if (cur->getValue() == v) break;
		cur = cur->getNext();
	}
	return cur;
}

template<typename type>
void Array<type>::SetAt(size_t index, type v)
{
	Node<type>* cur = findNodeByIndex(index);
	cur->setValue(v);
}

template<typename type>
type Array<type>::GetAt(size_t index) const { return findNodeByIndex(index)->getValue(); }

template<typename type>
void Array<type>::insert(size_t index, type v)
{
	if (index > counter) return;
	if (index == 0) { push_front(v); return; }
	if (index == counter) { push_back(v); return; }
	Node<type>* prev = findNodeByIndex(index - 1);
	Node<type>* temp = new Node<type>(v, prev->getNext(), prev);
	prev->setNext(temp);
	temp->getNext()->setPrev(temp);
	++counter;
}

template<typename type>
void Array<type>::pop_position(size_t index)
{
	if (index >= counter) return;
	if (index == 0) { pop_front(); return; }
	if (index == counter - 1) { pop_back(); return; }
	Node<type>* prev = findNodeByIndex(index - 1);
	Node<type>* temp = prev->getNext();
	prev->setNext(temp->getNext());
	temp->getNext()->setPrev(prev);
	delete temp;
	--counter;
}

template<typename type>
int Array<type>::Replace(type fv, type v)
{
	Node<type>* cur = head;
	int count = 0;
	while (cur) {
		if (cur->getValue() == fv) {
			count++;
			cur->setValue(v);
		}
		cur = cur->getNext();
	}
	return count > 0 ? count : -1;
}

template<typename type>
void Array<type>::Reverse()
{
	Node<type>* temp;
	Node<type>* cur = head;
	while (cur) {
		temp = cur->getNext();
		cur->setNext(cur->getPrev());
		cur->setPrev(temp);
		cur = cur->getPrev();
	}
	swap(head, tail);
}

template<typename type>
void Array<type>::Print() const
{
	Node<type>* cur = head;
	while (cur) {
		cout << cur->getValue() << ' ';
		cur = cur->getNext();
	}
	cout << endl;
}

template<typename type>
void Array<type>::PrintReverse() const
{
	Node<type>* cur = tail;
	while (cur) {
		cout << cur->getValue() << ' ';
		cur = cur->getPrev();
	}
	cout << endl;
}

template<typename type>
Array<type>& Array<type>::operator=(const Array& other) noexcept
{
	if (this != &other) {
		clear();
		Node<type>* cur = other.head;
		while (cur)
		{
			push_back(cur->getValue());
			cur = cur->getNext();
		}
	}
	return *this;
}

template<typename type>
Array<type> Array<type>::operator+(const Array& R) const
{
	Array<type> result = *this;
	Node<type>* cur = R.head;
	while (cur) {
		result.push_back(cur->getValue());
		cur = cur->getNext();
	}
	return result;
}

template<typename type>
inline Array<type>& Array<type>::operator+=(const Array& R)
{
	Node<type>* cur = R.head;
	while (cur) {
		push_back(cur->getValue());
		cur = cur->getNext();
	}
	return *this;
}

template<typename type>
type Array<type>::operator[](const type index) noexcept
{
	if (ValidIndex(index)) return findNodeByIndex(index)->getValue();
	exit(-1);
}

