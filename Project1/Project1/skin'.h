#pragma once
template<typename T>
class Stack {

public:

	Stack();	//конструктор по умолчанию
	~Stack();	//деструктор для осовбождения памяти
	int getSize() { return Size; }	//метод возвращающий размер списка
	void add(T);	
	void viewStack();	//метод просмотра списка
	T& operator[](const int);	//перегрузка оператора []
	
private:
	template<typename T>
	class Node { 
	public:
		T data;
		Node *pnext;
		Node(T data = T(), Node *pnext = nullptr) {

			this->data = data;
			this->pnext = pnext;
		}
	};
	int Size;
	Node<T> *head;
};