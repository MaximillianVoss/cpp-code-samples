#pragma once
#include "Card.h"
#include "Queue.h"
//класс описывает колоду карт
class Deck
{
private:
	Queue tempQueue;
public:
	Queue queue; //здесь хран€тс€ карты
	Deck()
	{
		
	}
	Deck(bool fillDeck)
	{
		if (fillDeck)
		{
			for (int i = 1;i <= 4;i++)
			{
				for (int j = 1;j <= 9;j++)
				{
					queue.Push(Card(j, i));
				}
			}
		}
	}
	///<summary>
	///ѕолучает карту с указанным номером
	///</summary>
	///<param name="index">
	/// Ќомер карты
	///</param>
	Card GetCard(int index)
	{
		for (int i = 0;i < queue.GetSize() - index;i++)
		{
			tempQueue.Push(queue.Pop());
		}
		Card result = queue.Pop();
		for (int i = 0;i<tempQueue.GetSize();i++)
		{
			queue.Push(tempQueue.Pop());
		}
		return result;
	}
};

