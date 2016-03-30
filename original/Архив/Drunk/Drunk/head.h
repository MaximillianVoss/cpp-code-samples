#pragma once

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <time.h>

using namespace std;

static const int CARDS = 36;
static const int DECK = 9;
static const int PLAYERS = 2;
static const int SUITS = 4;

class CardDeck //класс карты
{
private:
	string name; //название карты
	string suit; //масть карты
	int priority; //приоритет карты
public:
	CardDeck() { this->priority = 0; } //конструктор по умолчанию
	CardDeck(string anotherName, string anotherSuit, int anotherPriopity); //конструктор по умолчанию с данными для полей
																		   //CardDeck(const CardDeck &anotherCard);
	~CardDeck() {} //деструктор
	string getName() { return this->name; } //геттер
	string getSuit() { return this->suit; } //геттер
	int getPriority() { return this->priority; } //геттер
	void setName(string name) { this->name = name; } //сеттер
	void setSuit(string suit) { this->suit = suit; } //сеттер
	void setPriority(const int priority) { this->priority = priority; } //сеттер
	void printCard() { cout << this->getName() << " " << this->getSuit() << endl; } //вывод названия и масти 1 карты в консоль
	void printCard(ofstream &out) { out << this->getName() << " " << this->getSuit() << endl; } //вывод названия и масти 1 карты в файл
};

class List //массив карт
{
private:
	CardDeck *cDeck; //сам массив
	int size; //его максимально возможный размер
	int top; //его размер в данный момент времени
public:
	List(); //конструктор по умолчанию
	List(const int &anotherSize); //конструктор по умолчанию с данным для поля size
	List(const List &anotherList); //конструктор копирования
	~List() { delete[] cDeck; } //деструктор - delete[] здесь нужен, поскольку в конструкторе есть выделение памяти для cDeck через new
	void change(int smth); //***
	CardDeck getRandomCardDeck(int limit, int &smth); //***
	CardDeck getTopOfDeck() { return this->cDeck[this->top]; } //возвращает верхний элемент массива cDeck
	int getSize() { return this->size; } //геттер
	int getTop() { return this->top; } //геттер
	bool isEmpty() { return (this->getTop() == -1) ? true : false; } //проверка массива карт на пустоту
	bool isFull() { return ((this->getTop() + 1) == this->getSize()) ? true : false; } //проверка массива карт на полноту
	void setTop(const int top) { this->top = top; } //сеттер
	CardDeck pop(); //удаление карты из массива
	void printList(); //вывод полного массива карт в консоль
	void printList(ofstream &out); //вывод полного массива карт в файл
	void push(const CardDeck); //добавление карты в массив
};

void defineCardDeck(List &cardDeck);

int testLuck(int limit); //функция, возвращающая случайное число от 0 до limit

void defineCardsOfPlayers(List &cardDeck, List &playerFirst, List &playerSecond);

void makeAMove(List &destination, List &playerFirst, List &playerSecond, const int move);
void makeAMove_Console(List &destination, List &playerFirst, List &playerSecond, const int move);