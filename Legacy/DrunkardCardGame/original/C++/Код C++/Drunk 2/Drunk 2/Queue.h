#pragma once
#define QUEUE_SIZE 36
#include "Card.h"
class Queue
{
private:
	//конец очереди
	int end;
	Card cards[QUEUE_SIZE];
public:	
	Queue()
	{
		end = 0;
	}
	///<summary>
	///Добавляет карту в очередь
	///</summary>
	///<param name="_card">
	/// Карта для добавления
	///</param>
	void Push(Card _card)
	{
		if (end < QUEUE_SIZE)
		{
			cards[end] = _card;
			end++;
		}
	}
	///<summary>
	///BИзвлекает карту из очереди
	///</summary>
	Card Pop()
	{
		if (end > 0)
		{
			end--;
			return cards[end];
		}
	}
	///<summary>
	///Извлекает карту из очереди не удаляя ее
	///</summary>
	Card Pick()
	{
		return cards[end];
	}
	///<summary>
	///Возвращает размер очереди
	///</summary>
	int GetSize()
	{
		return end;
	}
	///<summary>
	///Проверяет переполнена очередь или нет
	///</summary>
	bool IsFull()
	{
		if (end == QUEUE_SIZE) return true;
		else return false;
	}
	///<summary>
	///Выводит элементы очереди на экран
	///</summary>
	void Print()
	{
		for (int i = 0;i < end;i++)
		{
			cards[i].Print();
		}
	}
	///<summary>
	///Выводит элементы очереди на экран
	///</summary>
	///<param name="message">
	/// Сообщение перед выводом очереди на экран
	///</param>
	void Print(char * message)
	{
		printf("%s:\n", message);
		Print();
	}
};

