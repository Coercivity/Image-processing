#include <iostream>
#include "List.h"


void viewsp(list *head)
{
	list *tec = head;
	do
	{
		std::cout << tec->data;
		tec = tec->link;
	} while (tec != head);
}

list *sozdspis(char ch, int k, list *head)
{
	list *tec,
		*nov = new(list);

	nov->data = ch;
	nov->numb = k;
	nov->link = NULL;
	if (head)               //список не пуст
	{
		tec = head;
		while (tec->link)
			tec = tec->link;
		tec->link = nov;
	}
	else                     //список пуст
		head = nov;
	return head;
}

