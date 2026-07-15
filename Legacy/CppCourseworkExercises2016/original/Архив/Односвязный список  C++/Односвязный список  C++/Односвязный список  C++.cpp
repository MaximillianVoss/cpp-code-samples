// Односвязный список  C++.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string>
using namespace std;
struct item
{
	string value;//хранится чсленное значение
	item *next;//указатель на следующий эллемент
};
class List
{
public:
	item *head;
	List()//конструктор
	{
		head = NULL;//начало списка
	}
	~List()//деструктор
	{
		while (head != NULL)//цикл удаления поледовательно всех эллементов списка
		{
			item *second = head->next;
			delete head;
			head = second;
		}
	}
	void Add(string value)//добавления строкового значения 
	{
		item *newItem = new item();
		newItem->value = value;
		if (head == NULL)//если список пуст, то помещаем ссылку на созданый элемент
			head = newItem;
		else
		{
			item* current = head;
			while (current->next != NULL)
			{
				current = current->next;//постепенное перебор эдементов списка
			}
			current->next = newItem;//последнему элементу списка указываем ссылку на созданный элемент
		}

	}
	void Print(char *message)
	{		
		printf(message);
		Print();
	}
	void Print()
	{
		item *next = head;
		while (next != NULL)
		{
			printf("%s ", next->value.c_str());
			next = next->next;
		}
		printf("\n");
	}
	item* Pop()//возвращает последний элемент списка, прерывая связь с предыдущими.
	{
		item * current = head;
		if (current != NULL)
		{
			while (current->next != NULL && current->next->next != NULL)
			{
				current = current->next;
			}
			item *last = NULL;
			if (current->next != NULL)
			{
				last = current->next;
				current->next = NULL;//обрываем связь с предыдущим эллементом.
			}
			else
			{
				last = current;//если список из 1 элемента, то заносим в last первый элемент.
				head = NULL;//если head пустой указатель то список пуст
			}
			return last;//возращаем извлеченный элемент
		}
		else
			return current;//возвращаем пустой указатель
	}
	int GetSize()//проверка кол-ва элементов в списке
	{
		if (head == NULL) {
			return 0;
		}
		else
		{
			int length = 0;
			item * current = head;
			while (current != NULL)
			{
				current = current->next;
				length++;
			}
			return length;
		}
	}
	void Reverse()//функция инверсии списка
	{
		List *temp = new List();
		while (GetSize() > 0)
		{
			temp->Add(Pop()->value);
		}
		head = temp->head;
	}
};



int main()
{
	setlocale(LC_ALL, "rus");
	List *firstList = new List();
	for (int i = 0;i < 10;i++)
	{
		firstList->Add(to_string(i));
	}
	firstList->Print("Исходный список:\n");
	firstList->Reverse();
	firstList->Print("Инвертированный список:\n");
	system("pause");
	return 0;
}

