#include<iostream>
using namespace std;

//#define INDEX_OPERATOR_CHECK
#define HARDCORE_CHECK

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class List;
};

int Element::count = 0;

class List
{
	Element* Head;	//Адрес начала списка
	int size;		//Размер списка
public:
	int get_size()const
	{
		return this->size;
	}

	List()
	{
		this->Head = nullptr;
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(int size):List()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		while (size--)push_front(0);

	}
	List(initializer_list<int> il):List()
	{
		//cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		for (Element* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		cout << "CopyConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Operators:
	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}

		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	int& operator[](int Index)

	{
		Element* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//			Adding elements:
	void push_front(int Data)
	{
		//1)Создаем новый элемент:
		Element* New = new Element(Data);
		//2)"Привязываем новый элемент к Голове (Head)":
		New->pNext = Head;
		//3)Голову переводим на новый элемент.
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		//1) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//2) Добавляем элемент:
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		if (Index >= size)
		{
			push_back(Data);
			return;
		}
		//1) Дойти до нужной позиции:
		Element* Temp = Head;
		//if(sizeof(Temp))
		for (int i = 0; i < Index-1; i++)Temp = Temp->pNext;
		//2) Добавить элемент в список:
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//			Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		//1) Запоминаем адрес удаляемого элемента
		Element* to_del = Head;
		//2) Исключаем элемент из списка:
		Head = Head->pNext;
		//3) Удаляем элемент из памяти:
		delete to_del;
		size--;
	}
	void pop_back()
	{
		//ЕСЛИ список пуст, удалять из него нечего, 
		//поэтому сразуже выходим из метода:
		//if (Head == nullptr)return;
		if (Head == nullptr || Head->pNext == nullptr)
		{
			pop_front();
			return;
		}

		//1)Дойти до конца списка:
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//2)Удалить элемент:
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		if (Index == 0)
		{
			pop_front();
			return;
		}
		if (Index == size - 1)
		{
			pop_back();
			return;
		}
		if (Index >= size)
		{
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* to_del = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete to_del;
		size--;
	}

	void print()
	{
		Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого
		//можно получить доступ, к элементам структуры данных.
		while (Temp != nullptr)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	//List list;
	/*for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}*/
	//list.push_back(123);
	//list.print();
	/*list.pop_back();
	list.pop_front();*/

	/*List list2;
	for (int i = 0; i < 3; i++)list2.push_back(rand());
	list2.print();
	int Index;
	int Data;
	cout << "Введите индекс добавляемого элемента:  "; cin >> Index;
	cout << "Введите значение добавляемого элемента:"; cin >> Data;
	list.insert(Index, Data);
	list.print();
	cout << "Введите индекс удавляемого элемента:  "; cin >> Index;
	list.erase(Index);
	list.print();*/

#ifdef INDEX_OPERATOR_CHECK
	List list(n);
	list.print();
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << "\t";
	}
	cout << endl;
#endif // INDEX_OPERATOR_CHECK

#ifdef HARDCORE_CHECK
	List list1 = { 3, 5, 8, 13, 21 };
	list1.print();
	/*List list3;
	list3 = list1;
	list3.print();
	List list2 = { 34, 55, 89 };
	list2.print();*/
	//List list3 = list1 + list2;	//Конкатенация списков.
	//list3.print();
	//http://www.cplusplus.com/reference/initializer_list/initializer_list/
#endif // HARDCORE_CHECK


}

//Team Viewer