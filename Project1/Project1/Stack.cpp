#include "List.h"
#include<iostream>

template<typename T>
inline List<T>::List()
{
	Size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List()
{
	//std::cout << "уничтожено" <<Size <<" элементов" << std::endl;
	while (Size)
	{
		Node<T> *temp = head;
		head = head->pnext;  

		delete temp; //освобождение пам€ти 
		Size--;
	}
	
}

template<typename T>
void List<T>::add(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T> *current = this->head; 
		while (current->pnext != nullptr)
		{
			current = current->pnext;
		}
		current->pnext = new Node<T>(data);
	}
	Size++; 
}

template<typename T>
void List<T>::viewList()
{
	Node<T> *current = this->head;
	while (current!= nullptr)
	{
		std::cout << current->data << " ";
		current = current->pnext;
	}
	
}

template<typename T>
T & List<T>::operator[](const int index) 
{
	int counter = 0;
	Node<T> *current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pnext;
		counter++;
	}
}

template<typename T>
void List<T>::insertList(List& other, const int index)
{
	
	Node<T> *previous = this->head;

	for (int i = 0; i < index; i++)
	{
		previous = previous->pnext;
	}

	for (int i = other.getSize() - 1; i >= 0 ; i--) {//сообразно размеру добавл€емого списка, итерируемс€  
		Node<T> *newNode = new Node<T>(other[i], previous->pnext);//выдел€€ пам€ть под новые элементы списка и добавл€€ их.

		previous->pnext = newNode;

		Size++;
	}
}

template<typename T>
bool List<T>::CheckE(T data)
{
	Node<T> *current = this->head;
	while (current != nullptr)
	{
		if (current->data == data)
		{
			return true;
		}
		
		current = current->pnext;			
	}
	return false;
}

template<typename T>
int List<T>::IndexE(T data) //ѕоиск индекса числа E
{
	int index, currentIndex = 0;
	Node<T> *current = this->head;
	while (current != nullptr)
	{

		if (current->data == data)
		{
			index = currentIndex;
		}
		currentIndex++;
		current = current->pnext;
	}
	return index;
}
