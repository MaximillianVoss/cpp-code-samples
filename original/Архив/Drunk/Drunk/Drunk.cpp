// Drunk.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "head.h"

int main()
{
	srand(time(NULL)); //для правильной работы рандома
	cout << "The game with " << PLAYERS << " players and " << CARDS << " cards." << endl;
	List cardDeck = List(CARDS); //объявление массива колоды карт
	defineCardDeck(cardDeck); //заполнение его значениями карт по упорядочиванию мастей и приоритетов
	cout << endl << "Card deck is:" << endl;
	cardDeck.printList(); //вывод этого массива на экран
	List playerFirst = List(CARDS); //объявление массива колоды карт в руке у первого игрока
	List playerSecond = List(CARDS); //объявление массива колоды карт в руке у второго игрока
	defineCardsOfPlayers(cardDeck, playerFirst, playerSecond); //раздача игрокам карт случайным образом
	int move = 1; //счётчик количества ходов игры
	List destination = List(CARDS / 2); //объявление массива карт раздачи, т.е. выкладываемого в течение хода на середину стола
	char c ='\n';
	while (!(playerFirst.isFull()) && !(playerSecond.isFull()) && c=='\n') //вечный цикл - выполняется, пока не достигает break
	{
		
		makeAMove_Console(destination, playerFirst, playerSecond, move); //делаем ход
		move++; //увеличиваем счётчик номера хода
		printf("Press enter to continue, any key to finish game and view results:\n");
		c=getchar();
	}

	if (playerFirst.isFull()) //если у игрока 1 массив карт полон, т.е. если он победил
		cout << endl << "Winner = Player 1" << endl << "Moves: " << move << endl;
	else if (playerSecond.isFull())//в противном случае, т.е. если победил игрок 2
		cout << endl << "Winner = Player 2" << endl << "Moves: " << move << endl;
	else
	{
			cout << endl << "Moves:" << move << endl;
			printf("Player 1 card deck (%i cards):\n", playerFirst.getTop());
			playerFirst.printList();
			cout << endl;
			printf("Player 2 card deck: (%i cards):\n", playerSecond.getTop());
			playerSecond.printList();
			cout << endl;
	}

	system("pause");
	return 0;
}