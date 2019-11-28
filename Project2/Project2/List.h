#pragma once
struct list
{
	char data;	
	int numb;		
	list *link;
};

list *sozdspis(char, int, list*);
void viewsp(list*);
