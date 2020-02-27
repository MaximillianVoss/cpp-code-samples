#include "stdafx.h"
#include "Random.h"


Random::Random()
{
}


Random::~Random()
{
}

vector<int> Random::GetArrayInt(int min, int max, int count, bool onlyPositive)
{
	vector<int> items;
	for (int i = 0; i < count; i++)
		items.push_back(GetInt(min, max, onlyPositive));
	return items;
}

vector<int> Random::GetArrayInt(int min, int max, int count)
{
	return GetArrayInt(min, max, count, true);
}

int Random::GetInt(int min, int max, bool onlyPositive)
{
	bool negative = false;
	if (!onlyPositive)
		negative = rand() % 2;
	int value = rand() % max;
	if (value < min)
		value += min;
	if (negative)
		value *= -1;
	return value;
}

int Random::GetInt(int min, int max)
{
	return GetInt(min, max, true);
}

