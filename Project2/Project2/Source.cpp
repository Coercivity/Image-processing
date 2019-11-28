#include<iostream>
#include<locale>
#include"List.h"
using namespace std;
//основна€ программа
int main()
{
	int i = 1;
	list *L = NULL;
	list *L1 = NULL;
	char ch;
	setlocale(LC_ALL, "Russian");
	cout << "\n ¬водите элементы списка L1 сплошной строкой;"
		"\n в конце - точка:";
	cout << "\n ";
	cin >> ch;
	while (ch != '.')
	{
		L = sozdspis(ch, i, L);
		i++;
		cin >> ch;
	}
	cout << "\n ¬водите элементы списка L2 сплошной строкой;"
		"\n в конце - точка:";
	cout << "\n ";
	cin >> ch;
	while (ch != '.')
	{
		L1 = sozdspis(ch, i, L1);
		i++;
		cin >> ch;
	}
	viewsp(L1);
	cin.get();
	system("pause");
	return 1;
}
