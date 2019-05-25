#pragma once
#include <iostream>
//#include "Dijkstra.h"
template <class T>
class list_element
{
public:
	list_element* next;
	T data;
	~list_element() {};
	list_element() {
		next = nullptr;
	}
	list_element(T user_data) {
		next = nullptr;
		data = user_data;
	}
};
template <class T>
class list
{
private:
	list_element<T>*head;
	list_element<T>*tail;
	size_t size_of_list;
public:
	template<class T>	friend ostream& operator<< <T> (ostream&, list<T>&);
	list();
	list(T user_data);
	~list() { this->clear(); }
	void push_back(T user_data);
	void push_front(T user_data);
	void pop_back();
	void pop_front();
	void insert(T user_data, int index);
	T at(int index);
	void remove(int index);
	size_t get_size();
	void clear();
	void set(T user_data, int index);
	bool is_empty();
};

template <class T>
list<T>::list()
{
	head = nullptr;
	tail = nullptr;
	size_of_list = 0;
}

template <class T>
list<T>::list(T user_data)
{
	head = new list_element<T>*;
	head->data = user_data;
	tail = head;
	size_of_list = 0;
}

template <class T>
void list<T>::push_back(T user_data)// creates new element at the end of list
{
	list_element<T>* new_element = new list_element<T>;
	new_element->data = user_data;
	if (!this->head)
		head = new_element;
	else
		tail->next = new_element;
	size_of_list++;
	tail = new_element;
}

template <class T>
void list<T>::push_front(T user_data)// creates new element at the top of list
{
	list_element<T>* new_element = new list_element<T>;
	new_element->data = user_data;
	new_element->next = head;
	head = new_element;
	size_of_list++;
	if (!tail)
		tail = new_element;
}

template <class T>
void list<T>::pop_back()// removes last element of the list
{
	if (!head)
		throw Head_is_null();
	if (!(head->next))
		this->clear();
	else
	{
		list_element<T>* current = head;
		while (current->next->next)
			current = current->next;
		delete tail;
		current->next = nullptr;
		tail = current;
		size_of_list--;
	}
}

template <class T>
void list<T>::pop_front()// removes first element of the list
{
	if (!head)
		throw Head_is_null();
	size_of_list--;
	list_element<T>* temporary = head;
	if (head == tail)
		tail = nullptr;
	head = head->next;
	delete temporary;
}

template <class T>
void list<T>::insert(T user_data, int index)//inserts new element at user-specified place
{
	if (index <= 0 || index > (size_of_list + 1))
		throw Wrong_index_of_element();
	list_element<T>* new_element = new list_element<T>;
	new_element->data = user_data;
	if (index == 1)
		this->push_front(user_data);
	else
		if (index == size_of_list + 1)
			this->push_back(user_data);
		else
		{
			list_element<T>* temporary = head;
			for (int i = 0; i < index - 2; ++i)
				temporary = temporary->next;
			size_of_list++;
			new_element->next = temporary->next;
			temporary->next = new_element;
		}
}

template <class T>
T list<T>::at(int index)//returns data from user-specified element
{
	if (!head)
		throw Head_is_null();
	if (index <= 0 || index > size_of_list)
		throw Wrong_index_of_element();
	list_element<T>* current = head;
	for (int i = 0; i < index - 1; ++i)
		current = current->next;
	return current->data;
}

template <class T>
void list<T>::remove(int index)//removes element from user-specified place
{
	if (!head)
		throw Head_is_null();
	if (index <= 0 || index > size_of_list)
		throw Wrong_index_of_element();
	if (index == 1)
		this->pop_front();
	else
		if (index == size_of_list)
			this->pop_back();
		else
		{
			list_element<T>* current = head;
			list_element<T>* temporary = head;
			for (int i = 0; i < index - 2; ++i)
				current = current->next;
			temporary = current->next->next;
			delete current->next;
			current->next = temporary;
			size_of_list--;
		}
}

template <class T>
size_t list<T>::get_size()//returns size of list
{
	return size_of_list;
}

template <class T>
void list<T>::clear()//clears all list
{
	if (head)
	{
		list_element<T>* temporary = head;
		while (temporary != nullptr)
		{
			temporary = head->next;
			delete head;
			head = temporary;
		}
		head = nullptr;
		tail = nullptr;
		size_of_list = 0;
	}

}

template <class T>
void list<T>::set(T user_data, int index)//sets user-specified data at user-specified place
{
	if (!head)
		throw Head_is_null();
	if (index <= 0 || index > size_of_list)
		throw Wrong_index_of_element();
	list_element<T>* temporary = head;
	for (int i = 0; i < index - 1; ++i)
		temporary = temporary->next;
	temporary->data = user_data;
}

template <class T>
bool list<T>::is_empty()//returns true if list is empty else returns false
{
	return(!head);
}

template<class T>
ostream& operator<< (ostream& output_stream, list<T> &lis)
{
	if (!lis.head)
		cout << "";
	else
	{
		list_element<T>*current = lis.head;
		while (current)
		{
			cout  << "" << current->data << "\n";
			current = current->next;
		}
		cout << endl;
	}
	return output_stream;
}