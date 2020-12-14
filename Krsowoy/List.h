#pragma once
#include "Header.h"

template<typename T>
struct Node {
	T data;
	Node<T>* next = NULL;
	Node<T>* prev = NULL;
};

template<typename T>
class list {
private:
	int Size;
	Node<T>* head;
	Node<T>* tail;
public:

	list() :head(NULL), tail(NULL), Size(0) {}
	~list();
	//void Insert(T data, int position);
	void Delete(int index);
	void Display();
	void Display(int index);
	T& operator[](int index);
	Node<T>*& getHead();
	Node<T>*& getTail();
	void Push_Tail(T data);
	void Push_Front(T data);
	bool is_Empty();
	int getSize();
	T Pop_head();
	T Pop_tail();
	void Clear();
};

template<typename T>
inline list<T>::~list()
{
	Clear();
}

template<typename T>
inline void list<T>::Delete(int index)
{
	Node<T>* temp = head;
	if (index < 0 || index > Size)
		return;
	if (index == 1) {
		Pop_head();
		return;
	}
	else if (index == Size) {
		Pop_tail();
		return;
	}
	else
	{
		for (int i = 1; i < index; i++) {
			temp = temp->next;
		}
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	delete temp;
	Size--;
}

template<typename T>
inline void list<T>::Display()
{
}

template<typename T>
inline void list<T>::Display(int index)
{
}

template<typename T>
inline T& list<T>::operator[](int index)
{
	// TODO: вставьте здесь оператор return
	Node<T>* curr = head;
	if (index >= Size || index < 0)
		return curr->data;

	for (int i = 0; i < index; i++) {
		curr = curr->next;
	}
	return curr->data;
}

template<typename T>
inline Node<T>*& list<T>::getHead()
{
	// TODO: вставьте здесь оператор return
	return head;
}

template<typename T>
inline Node<T>*& list<T>::getTail()
{
	// TODO: вставьте здесь оператор return
	return tail;
}

template<typename T>
inline void list<T>::Push_Tail(T data)
{
	if (Size == 0) {
		head = new Node<T>;
		head->prev = nullptr;
		head->next = nullptr;
		head->data = data;
		tail = head;
		Size++;
		return;
	}
	Node<T>* temp = new Node<T>;
	temp->data = data;
	temp->prev = tail;
	temp->next = nullptr;
	tail->next = temp;
	tail = temp;
	Size++;
}

template<typename T>
inline void list<T>::Push_Front(T data)
{
	if (Size == 0) {
		head = new Node<T>;
		head->prev = NULL;
		head->next = NULL;
		head->data = data;
		tail = head;
		Size++;
		return;
	}

	Node<T>* temp = new Node<T>;
	temp->data = data;
	temp->prev = nullptr;
	temp->next = head;
	head->prev = temp;
	head = temp;
	Size++;
}

template<typename T>
inline bool list<T>::is_Empty()
{
	return Size == 0;
}

template<typename T>
inline int list<T>::getSize()
{
	return Size;
}

template<typename T>
inline T list<T>::Pop_head()
{
	if (!(head)) return T();
	T data = head->data;
	Node<T>* temp = head;
	head = head->next;
	if (head) head->prev = nullptr;
	delete temp;
	Size--;
	return data;
}

template<typename T>
inline T list<T>::Pop_tail()
{
	if (!(tail)) return T();
	T data = tail->data;
	Node<T>* temp = tail;
	tail = tail->prev;
	if (tail)
		tail->next = nullptr;
	delete temp;
	Size--;
	return data;
}

template<typename T>
inline void list<T>::Clear()
{
	while (head) {
		Pop_head();
	}
}
