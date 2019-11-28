#pragma once
template<typename T>
class List {

public:

	List();	//конструктор по умолчанию
	~List();	//деструктор для осовбождения памяти
	int getSize() { return Size; }	//метод возвращающий размер списка
	void add(T);	//метод добавления элемента в список
	void viewList();	//метод просмотра списка
	T& operator[](const int);	//перегрузка оператора []
	void insertList(List&, const int);	//метод вставки в список элементов другого списка
	int IndexE(T); //Метод нахождения индекса последнего числа E
	bool CheckE(T);//метод, проверяющий нахождение элемента в списке

private:
	template<typename T>
	class Node { //вложенный класс, являющийся элемнтарной единицей списка
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