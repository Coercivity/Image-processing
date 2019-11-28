#include <iostream>
#include "Stack.h"

template<typename T>
inline Stack<T>::Stack()
{
	head = nullptr;
	Size = 0;
}

template<typename T>
Stack<T>::~Stack()
{
	while (Size)
	{
		Stack<T> *temp = head;
		delete temp;
	}
}

template<typename T>
void Stack<T>::push_back(T data)
{
		head  = new Stack<T>(data);
     	Size++;
}

template<typename T>
void Stack<T>::pop_front()
{

}

template<typename T>
void Stack<T>::viewStack()
{
	Stack<T> *current = head;
	while (!isEmpty)
	{
		std::cout << current->data;

	}
}
