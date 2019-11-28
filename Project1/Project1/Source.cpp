#include <iostream>
#include "List.cpp"

using namespace std;

int main()
{
	
	setlocale(LC_ALL, "ru");
	int num, E, L1_am, L_am;
	List<int> L;
	List<int> L1;

	cout << "¬ведите количество элементов списка L-> ";
	cin >> L_am;
	cout << "¬ведите количество элементов списка L1-> ";
	cin >> L1_am;

	cout << "¬ведите число E, за которым в список L будут вставлены все элементы списка L1-> ";
	cin >> E;

	cout << "¬водите " << L_am << " элементов списка L сплошной строкой:" << endl;
	for (int i = 0; i < L_am; i++)
	{
		cin >> num;
		L.add(num);
	}

	cout << "¬водите " << L1_am << " элементов списка L1 сплошной строкой:" << endl;
	for (int i = 0; i < L1_am; i++)
	{
		cin >> num;
		L1.add(num);
	}
	
	
	
	cout << "¬веденный список L:" << endl;
	L.viewList(); //просмотр списка L
	cout << endl;

	cout << "¬веденный список L1:" << endl;
	L1.viewList(); //просмотр списка L1
	cout << endl;

	if (L.CheckE(E))//проверка на существование элемента E в списке
	{
		L.insertList(L1, L.IndexE(E)); //добавление в конец списка L элементы списка L1
		cout << "–езультатирующий список L+L1:" << endl;
		L.viewList();// просмотр результирующего списка
		cout << endl;
	}
	else
	{
		cout << "„исло E = " << E << " отсутствует в списке L" << endl;
		cout << "–езультатирующий список L:" << endl;
		L.viewList();// просмотр результирующего списка
		cout << endl;
	}
	return 0;
}

