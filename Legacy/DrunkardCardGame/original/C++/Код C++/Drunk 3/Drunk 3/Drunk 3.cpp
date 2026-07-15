
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#define FIRST_PLAYER 1;
#define SECOND_PLAYER 2;
#define DRAW 3;
using namespace std;
unsigned __int64 playedRounds = 0;

#pragma region Класс карты
class card {
public:
	card(int val = 0) {
		next = NULL;
		value = val;
	}
	void setValue(int i); // Записывает значние в карту
	int getValue(); // Получает значение карты
	int getQuaint();
	void printCard(); // Вывод карты
	void setNext(card &adr); // Записать адрес следующей карты
	card* getNext(); // Получить адрес следующей карты
private:
	int value; // Знаение карты
	card *next; // Адрес следующей карты
};

int card::getQuaint() {
	return value / 4;
}

card* card::getNext() {
	return next;
}

void card::setNext(card &adr) {
	next = &adr;
}

void card::setValue(int i) {
	value = i;
}

int card::getValue() {
	return value;
}

void card::printCard() {
	switch (value / 4 + 6) {
	case 6: case 7: case 8: case 9: case 10: cout << value / 4 + 6; break; // Вычисление значения карты по ее номеру от 0 до 35
	case 11: cout << "J"; break;
	case 12: cout << "Q"; break;
	case 13: cout << "K"; break;
	case 14: cout << "A"; break;
	}
	switch (value % 4 + 3) // Вычисление масти карты по ее номеру
	{
	case 3: cout << (char)3; break;
	case 4: cout << (char)4; break;
	case 5: cout << (char)5; break;
	case 6: cout << (char)6; break;
	}
	cout << "\n";
}
#pragma endregion

#pragma region Класс игрока
// Один указатль в очереди
class player {
public:
	player() {
	}
	void enqueue(card* tmp); // Добавить карту в руку игрока (в очередь)
	card* dequeue(); // Получить карту из руки игрока (из очереди)
	int empty(); // Остались ли у игрока еще карты
	void clear(); // Очистить руку игрока
	void printPlayer(); // Вывести все карты игрока (для тестирования)
	void addTable(card* first, card* last); //Добавить все карты со стола в руку игрока
	card* findTail();
	card* getFirstCard();
private:
	card *firstCard = NULL; // Ссылка на первую карту в очереди
};

card* player::getFirstCard() {
	return firstCard;
}

card* player::findTail() {
	card* tmp;
	tmp = firstCard;
	while (tmp->getNext() != firstCard) {
		tmp = tmp->getNext();
	}
	return tmp;
}

void player::addTable(card* first, card* last) {
	last->setNext(*firstCard);
	findTail()->setNext(*first);
}
#pragma endregion

#pragma region Класс колоды
class deck {
public:
	void initDeck(); // Инициализировать карты в колоде
	void printDeck(); // Вывести колоду
	void shuffleDeck(); // Перетасовать колоду
	void dealCards(player *p1, player *p2); // Раздать карты игрокам
private:
	static const int L = 16; // Количество карт в колоде
	card cardDeck[L]; // Массив карт
};

void deck::dealCards(player *p1, player *p2) {
	int i;
	for (i = 0; i < L; i++) {
		if (i % 2) {
			p1->enqueue(&cardDeck[i]);
		}
		else {
			p2->enqueue(&cardDeck[i]);
		}
	}
	cout << i;
}

void deck::shuffleDeck() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < L; i++) {
		int random = rand() % L;
		card change = cardDeck[i];
		cardDeck[i] = cardDeck[random];
		cardDeck[random] = change;
	}
}

void deck::printDeck() {
	for (int i = 0; i < L; i++) {
		cardDeck[i].printCard();
	}
}

void deck::initDeck() {
	for (int i = 0; i < L; i++)
	{
		cardDeck[i] = i;
	}
}
#pragma endregion

#pragma region Для тестирования колоды игрока 
void player::printPlayer() {
	card *tmp = firstCard;
	do {
		switch (tmp->getValue() / 4 + 6) {
		case 6: case 7: case 8: case 9: case 10: cout << tmp->getValue() / 4 + 6; break;
		case 11: cout << "J"; break;
		case 12: cout << "Q"; break;
		case 13: cout << "K"; break;
		case 14: cout << "A"; break;
		}
		switch (tmp->getValue() % 4 + 3)
		{
		case 3: cout << (char)3; break;
		case 4: cout << (char)4; break;
		case 5: cout << (char)5; break;
		case 6: cout << (char)6; break;
		}
		cout << " ";
		tmp = tmp->getNext();
	} while (tmp != firstCard);
}

void player::clear() {
	firstCard = NULL;
}

card* player::dequeue() {
	card *tmp = firstCard;
	if (firstCard->getNext() == firstCard) {
		clear();
	}
	else {
		findTail()->setNext(*firstCard->getNext());
		firstCard = firstCard->getNext();
	}
	return tmp;
}

void player::enqueue(card* tmp){
	if (firstCard == NULL) {
		firstCard = tmp;
		firstCard->setNext(*firstCard);
	}
	else {
		tmp->setNext(*firstCard);
		findTail()->setNext(*tmp);
	}
}

int player::empty() {
	return firstCard == NULL;
}
#pragma endregion

#pragma region Логика
int playRound(player *player1, player *player2, player *table) { // Цикл одного раунда. Пока карты идентичны, игроки выкладывают карты
	card *firstCard, *secondCard;
	int isEnd = 0; // Переменная хранит победителя раунда
	do { 
		// Пока не определен победитель или у одного из игроков не закончились карты.
		firstCard = player1->dequeue();
		cout << "\nFirst player card:\n";
		firstCard->printCard();
		if (!player1->empty()) {
			player1->printPlayer();
		}
		secondCard = player2->dequeue();
		cout << "\nSecond player card:\n";
		secondCard->printCard();
		if (!player2->empty()) {
			player2->printPlayer();
		}
		table->enqueue(secondCard);
		table->enqueue(firstCard);
		cout << "\nOn table:\n";
		table->printPlayer();
		
		if (firstCard->getQuaint() != secondCard->getQuaint()) {
			if (firstCard->getQuaint() > secondCard->getQuaint()) {
				isEnd = 1;
			}
			else isEnd = 2;
		}
		else {
			if (player1->empty() && !player2->empty()) {
				player1->enqueue(player2->dequeue());
			}
			if (player2->empty() && !player1->empty()) {
				player2->enqueue(player1->dequeue());
			}
		}
	} while (!isEnd && !player1->empty() && !player2->empty());
	return isEnd;
}

int checkPlayerEmpty(player *player1, player *player2) {
	if (player1->empty() && player2->empty()) {
		return DRAW;
	}
	else {
		if (player1->empty()) 
			return SECOND_PLAYER;		
		if (player2->empty()) 
			return FIRST_PLAYER;		
	}
	return 0;
}

void emptyTable(player *player1, player *player2, player *table, int roundWinner) {
	if (roundWinner == 1) {
		player1->addTable(table->getFirstCard(), table->findTail());
	}
	else {
		player2->addTable(table->getFirstCard(), table->findTail());
	}
	table->clear();
}

void gameLoop(player *player1, player *player2, player *table) {
	int winner = 0, roundWinner = 0;
	while (winner == 0) {
		roundWinner = playRound(player1, player2, table);
		if ((winner = checkPlayerEmpty(player1, player2)) != 0 || winner == 3) break;
		if (roundWinner == 1) cout << "First player won this round!" << endl;
		else cout << "Second player won this round!" << endl;
		cout << playedRounds << endl;
		cout << "-----------------------------------" << endl;
		emptyTable(player1, player2, table, roundWinner);
		playedRounds++;
	}
	if (winner == 3) cout << "It's DRAW!";
	else {
		if (winner == 1) cout << "First player won!";
		else cout << "Second player won!";
	}
}
#pragma endregion

int main() {
	deck playDeck;
	player player1, player2;
	player table;
	playDeck.initDeck();
	playDeck.shuffleDeck();
	playDeck.printDeck();
	system("pause");
	playDeck.dealCards(&player1, &player2);
	//----------Цикл игры (в отдельную функцию!)---------
	gameLoop(&player1, &player2, &table);
	//---------------------------------------------------
	system("pause");
}