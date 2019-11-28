#pragma once
template<typename T>
class Stack {
public:
	Stack();
	~Stack();
	void push_back(T);
	void pop_front();
	void viewStack();
	int isEmpty() { return(head == nullptr) };
	int GetSize() { return Size };
private:
	T data;
	Stack *head;
	int Size;
};