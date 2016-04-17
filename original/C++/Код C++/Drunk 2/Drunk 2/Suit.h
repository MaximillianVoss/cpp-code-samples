#pragma once
#include <string.h>
#include <vector>
using namespace std;
class Suit
{
public:
	enum  suits { Diamonds=1, Hearts=2, Clubs=3, Spades=4 };
	vector<string> strSuits = { "Diamonds", "Hearts", "Clubs", "Spades" };
	Suit()
	{
	}
	~Suit()
	{
	}
	string GetSuit(int suit)
	{
		if (suit > 0 && suit <= strSuits.size())
			return strSuits[suit-1];
	}
};

