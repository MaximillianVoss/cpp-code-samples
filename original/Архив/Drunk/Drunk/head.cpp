#include "stdafx.h"
#include "head.h"

CardDeck::CardDeck(string anotherName, string anotherSuit, int anotherPriopity)
{
	this->name = anotherName;
	this->suit = anotherSuit;
	this->priority = anotherPriopity;
}

List::List() {
	this->size = CARDS;
	this->cDeck = new CardDeck[this->size];
	this->top = -1;
}

List::List(const int &anotherSize)
{
	this->size = anotherSize;
	this->cDeck = new CardDeck[this->size];
	this->top = -1;
}

List::List(const List &anotherList)
{
	this->size = anotherList.size;
	this->top = anotherList.top;
	this->cDeck = new CardDeck[this->size];
	for (int i = 0; i < this->top; i++)
		this->cDeck[i] = anotherList.cDeck[i];
}

void List::change(int smth) //присваиваем пол€м элемента номер smth из массива карт значени€ следующего, smth+1
{
	this->cDeck[smth].setName(this->cDeck[smth + 1].getName());
	this->cDeck[smth].setSuit(this->cDeck[smth + 1].getSuit());
	this->cDeck[smth].setPriority(this->cDeck[smth + 1].getPriority());
}

CardDeck List::getRandomCardDeck(int limit, int &smth) //возвращает случайную карту из массива карт
{
	smth = testLuck(limit);
	return this->cDeck[smth];
}

CardDeck List::pop()
{
	if (this->isEmpty())
		return this->cDeck[top];
	else
		return this->cDeck[top--];
}

void List::printList()
{
	if (this->isEmpty())
		return;
	for (int i = this->getTop(); i > -1; i--)
		this->cDeck[i].printCard();
}

void List::printList(ofstream &out)
{
	if (this->isEmpty())
		return;
	for (int i = this->getTop(); i > -1; i--)
		this->cDeck[i].printCard(out);
}

void List::push(const CardDeck cDeck)
{
	if (this->isFull())
		return;
	else {
		this->top++;
		for (int i = this->getTop(); i > 0; i--)
		{
			this->cDeck[i].setName(this->cDeck[i - 1].getName());
			this->cDeck[i].setSuit(this->cDeck[i - 1].getSuit());
			this->cDeck[i].setPriority(this->cDeck[i - 1].getPriority());
		}
		this->cDeck[0] = cDeck;
	}
}

void defineCardDeck(List &cardDeck)
{
	string massOfNames[DECK] = { "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
	string massOfSuits[SUITS] = { "spades", "clubs", "diamonds", "hearts" };
	for (int i = DECK - 1; i >= 0; i--)
		for (int j = SUITS - 1; j >= 0; j--)
			cardDeck.push(CardDeck(massOfNames[i], massOfSuits[j], i + 1));
}

int testLuck(int limit)
{
	return rand() % limit;
}

void defineCardsOfPlayers(List &cardDeck, List &playerFirst, List &playerSecond)
{
	int limit = CARDS, smth;
	for (int i = CARDS / 2 - 1; i > -1; i--)
	{
		playerFirst.push(cardDeck.getRandomCardDeck(limit, smth));
		if (smth != cardDeck.getSize())
			for (int j = smth; j < cardDeck.getTop(); j++)
				cardDeck.change(j);
		cardDeck.setTop(cardDeck.getTop() - 1);
		limit--;
		playerSecond.push(cardDeck.getRandomCardDeck(limit, smth));
		if (smth != cardDeck.getSize())
			for (int j = smth; j < cardDeck.getTop(); j++)
				cardDeck.change(j);
		cardDeck.setTop(cardDeck.getTop() - 1);
		limit--;
	}
	cout << endl << "Cards of Player 1:" << endl;
	playerFirst.printList();
	cout << endl << "Cards of Player 2:" << endl;
	playerSecond.printList();
}

void makeAMove(List &destination, List &playerFirst, List &playerSecond, int move)
{
	int counter = 0, min = 1, max = 9, *massOfPrioritets = new int[CARDS / 2]; //создаЄм массив int - массив приоритетов карт
	ofstream out("outputOfDrunkard.txt", ios_base::app); //открываем файл через поток вывода out со свойством ios_base::app
	if (!out.is_open()) //провер€ем, можно ли открыть файл
	{
		cout << "File can't be opened! Error." << endl;
		return;
	}
	out << "*** Move " << move << " ***" << endl << endl;
	do
	{
		destination.push(playerFirst.getTopOfDeck()); //кладЄм в массив раздачи верхнюю карту игрока 1
		massOfPrioritets[counter] = playerFirst.getTopOfDeck().getPriority();
		counter++;
		playerFirst.pop(); //удал€ем верхнюю карту у игрока 1, поскольку он выложил еЄ на середину стола
		destination.push(playerSecond.getTopOfDeck()); //кладЄм в массив раздачи верхнюю карту игрока 2
		massOfPrioritets[counter] = playerSecond.getTopOfDeck().getPriority();
		counter++;
		playerSecond.pop(); //удал€ем верхнюю карту у игрока 2
	} while (massOfPrioritets[counter - 1] == massOfPrioritets[counter - 2]); //цикл до тех пор, пока приоритеты последних 2 карт, выложенных на середину стола, не будут отличными
	///
	out << "Destination:" << endl;
	destination.printList(out); //раздача - карты, лежащие на середине стола
	///
	if ((massOfPrioritets[counter - 2] > massOfPrioritets[counter - 1]) && !((massOfPrioritets[counter - 2] == max)
		&& ((massOfPrioritets[counter - 1]) == min))) //здесь учитываем тот момент, кто 6 побеждает у “уза
		while (!destination.isEmpty())
		{
			playerFirst.push(destination.getTopOfDeck());
			destination.pop();
		}
	else
		while (!destination.isEmpty())
		{
			playerSecond.push(destination.getTopOfDeck());
			destination.pop();
		}
	///
	out << endl << "Cards of Player 1 (" << playerFirst.getTop() + 1 << "):" << endl;
	playerFirst.printList(out);
	out << endl << "Cards of Player 2 (" << playerSecond.getTop() + 1 << "):" << endl;
	playerSecond.printList(out);
	out << endl;	
	out.close(); //закрываем файл, т.к. работа с ним закончена
	///
	delete[] massOfPrioritets;
}

void makeAMove_Console(List &destination, List &playerFirst, List &playerSecond, int move)
{
	int counter = 0, min = 1, max = 9, *massOfPrioritets = new int[CARDS / 2]; //создаЄм массив int - массив приоритетов карт
	cout << "*** Move " << move << " ***" << endl << endl;
	do
	{
		destination.push(playerFirst.getTopOfDeck()); //кладЄм в массив раздачи верхнюю карту игрока 1
		massOfPrioritets[counter] = playerFirst.getTopOfDeck().getPriority();
		counter++;
		playerFirst.pop(); //удал€ем верхнюю карту у игрока 1, поскольку он выложил еЄ на середину стола
		destination.push(playerSecond.getTopOfDeck()); //кладЄм в массив раздачи верхнюю карту игрока 2
		massOfPrioritets[counter] = playerSecond.getTopOfDeck().getPriority();
		counter++;
		playerSecond.pop(); //удал€ем верхнюю карту у игрока 2
	} while (massOfPrioritets[counter - 1] == massOfPrioritets[counter - 2]); //цикл до тех пор, пока приоритеты последних 2 карт, выложенных на середину стола, не будут отличными

	cout << "Destination:" << endl;
	destination.printList(); //раздача - карты, лежащие на середине стола

	if ((massOfPrioritets[counter - 2] > massOfPrioritets[counter - 1]) && !((massOfPrioritets[counter - 2] == max)
		&& ((massOfPrioritets[counter - 1]) == min))) //здесь учитываем тот момент, кто 6 побеждает у “уза
		while (!destination.isEmpty())
		{
			playerFirst.push(destination.getTopOfDeck());
			destination.pop();
		}
	else
		while (!destination.isEmpty())
		{
			playerSecond.push(destination.getTopOfDeck());
			destination.pop();
		}

	cout << endl << "Cards of Player 1 (" << playerFirst.getTop() + 1 << "):" << endl;
	playerFirst.printList();
	cout << endl << "Cards of Player 2 (" << playerSecond.getTop() + 1 << "):" << endl;
	playerSecond.printList();
	cout << endl;
	delete[] massOfPrioritets;
}