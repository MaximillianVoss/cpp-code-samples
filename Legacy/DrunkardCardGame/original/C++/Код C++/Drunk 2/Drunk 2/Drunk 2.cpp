// Drunk 2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Card.h"
#include "Deck.h"
#include <Windows.h>
#include <time.h>
#define QUEUE_SIZE 36
#define PLAYERS_COUNT 2
///<summary>
///Заполняет колоды игроков
///</summary>
///<param name="first">
///колода первого игрока
///</param>
///<param name="second">
///колода второго игрока
///</param>
void GetDecks(Deck *first, Deck *second)
{
	Deck *mainDeck = new Deck(true);
	srand(time(NULL));
	for (size_t i = 0; i < QUEUE_SIZE/PLAYERS_COUNT; i++)
	{
		int size = mainDeck->queue.GetSize();
		first->queue.Push(mainDeck->GetCard(rand() % size + 1));
		size = mainDeck->queue.GetSize();
		second->queue.Push(mainDeck->GetCard(rand() % size + 1));
	}
}
///<summary>
///Выполняет один ход с учетом правил
///</summary>
///<param name="first">
///колода первого игрока
///</param>
///<param name="second">
///колода второго игрока
///</param>
void Step(Deck *first, Deck *second)
{
		first->queue.Print("first player card deck before move");
		second->queue.Print("second player card deck before move");
		Deck *dropDeck = new Deck();
		Card firstCard, secondCard;
		do
		{
			firstCard = first->queue.Pop();
			secondCard = second->queue.Pop();
			dropDeck->queue.Push(firstCard);
			dropDeck->queue.Push(secondCard);
		} while 
			(secondCard.name == firstCard.name 
			&& !dropDeck->queue.IsFull() 
			&& first->queue.GetSize()>0 
			&& second->queue.GetSize()>0);

		if (secondCard.name < firstCard.name)
		{
			while (dropDeck->queue.GetSize() > 0)
			{
				first->queue.Push(dropDeck->queue.Pop());
			}
		}
		else
		{
			while (dropDeck->queue.GetSize() > 0)
			{
				second->queue.Push(dropDeck->queue.Pop());
			}
		}
		first->queue.Print("first player card deck after move");
		second->queue.Print("second player card deck after move");
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Deck *first = new Deck();
	Deck *second = new Deck();
	GetDecks(first, second);
	while (!first->queue.IsFull() && !second->queue.IsFull())
	{
		Step(first, second);
	}
	if (first->queue.IsFull())
		printf("first player has won!\n");
	if (second->queue.IsFull())
		printf("second player has won!\n");
	system("pause");
	return 0;
}

