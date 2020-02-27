#include "stdafx.h"
#include "BinarySearch.h"

#pragma region Constructors
BinarySearch::BinarySearch()
{
}
BinarySearch::~BinarySearch()
{
}
#pragma endregion

#pragma region Methods
bool BinarySearch::Search(int * a, int value, int start, int end)
{
	int middleIndex = start + (end - start) / 2;
	if (a[middleIndex] == value)
		return true;
	else if (end - start == 1)
		return false;
	if (a[middleIndex] > value)
		return Search(a, value, start, middleIndex);
	else
		return Search(a, value, middleIndex, end);
}
#pragma endregion


