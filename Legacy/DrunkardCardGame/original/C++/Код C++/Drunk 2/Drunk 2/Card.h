#pragma once
#include "CardNames.h"
#include "Suit.h"
class Card
{
public:
	int name; //название карты
	//int suit; //масть карты
	Card()
	{
	}
	///<summary>
	///—оздает карту с указанными названием, мастью и приоритетом
	///</summary>
	///<param name="_name">
	///название карты
	///</param>
	///<param name="_suit">
	///масть карты
	///</param>
	///<param name="_priority">
	///приоритет карты
	///</param>
	Card(int _name, int _suit)
	{
		name = _name;
		//suit = _suit;
	}
	///<summary>
	///¬ыводит карту на экран
	///</summary>
	void Print()
	{
		Suit s;CardNames cn;
		//printf(" %10s %10s \n", s.GetSuit(suit).c_str(), cn.GetName(name).c_str());
		printf(" %10s \n", cn.GetName(name).c_str());
	}
	///<summary>
	///ѕровер€ет текущую карту и указанную карту на равенство
	///</summary>
	///<param name="card">
	///  арта дл€ сравнени€
	///</param>
	bool IsEqual(Card card)
	{
		if (card.name == name) return true;
		return false;
	}
};

