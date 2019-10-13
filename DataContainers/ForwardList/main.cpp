#include<iostream>
using namespace std;

//#define INDEX_OPERATOR_CHECK
#define HARDCORE_CHECK
template<typename T>class List;

template<typename T>
class Element
{
	T Data;		//�������� ��������
	Element<T>* pNext;	//����� ���������� ��������
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr)
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
	friend class List<T>;
};

template<typename T>
int Element<T>::count = 0;

template<typename T>
class List
{
	Element<T>* Head;	//����� ������ ������
	int size;		//������ ������
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
	List(initializer_list<T> il):List()
	{
		//cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List<T>& other) :List()
	{
		for (Element<T>* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
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
	List<T>& operator=(const List<T>& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element<T>* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}

		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	T& operator[](int Index)

	{
		Element<T>* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//			Adding elements:
	void push_front(T Data)
	{
		//1)������� ����� �������:
		Element<T>* New = new Element<T>(Data);
		//2)"����������� ����� ������� � ������ (Head)":
		New->pNext = Head;
		//3)������ ��������� �� ����� �������.
		Head = New;
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		//1) ������� �� ����� ������:
		Element<T>* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//2) ��������� �������:
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	void insert(int Index, T Data)
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
		//1) ����� �� ������ �������:
		Element<T>* Temp = Head;
		//if(sizeof(Temp))
		for (int i = 0; i < Index-1; i++)Temp = Temp->pNext;
		//2) �������� ������� � ������:
		Element<T>* New = new Element<T>(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//			Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		//1) ���������� ����� ���������� ��������
		Element<T>* to_del = Head;
		//2) ��������� ������� �� ������:
		Head = Head->pNext;
		//3) ������� ������� �� ������:
		delete to_del;
		size--;
	}
	void pop_back()
	{
		//���� ������ ����, ������� �� ���� ������, 
		//������� ������� ������� �� ������:
		//if (Head == nullptr)return;
		if (Head == nullptr || Head->pNext == nullptr)
		{
			pop_front();
			return;
		}

		//1)����� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		//2)������� �������:
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
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element<T>* to_del = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete to_del;
		size--;
	}

	void print()
	{
		Element<T>* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ ��������
		//����� �������� ������, � ��������� ��������� ������.
		while (Temp != nullptr)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "���������� ��������� ������: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������: "; cin >> n;
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
	cout << "������� ������ ������������ ��������:  "; cin >> Index;
	cout << "������� �������� ������������ ��������:"; cin >> Data;
	list.insert(Index, Data);
	list.print();
	cout << "������� ������ ����������� ��������:  "; cin >> Index;
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
	List<int> list1 = { 3, 5, 8, 13, 21 };
	list1.print();
	/*List list3;
	list3 = list1;
	list3.print();
	List list2 = { 34, 55, 89 };
	list2.print();*/
	//List list3 = list1 + list2;	//������������ �������.
	//list3.print();
	//http://www.cplusplus.com/reference/initializer_list/initializer_list/
#endif // HARDCORE_CHECK

	List<double> dbl_list = { 2.5, 3.14, 8,2 };
	dbl_list.print();
}

//Team Viewer