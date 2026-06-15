
#pragma once
#include "pch.h"
#include "Sorts.h"
template<typename T>
///<summary>
/// Бинарный поиск для примитивных типов
///</summary>
class BinarySearch
{
private:

#pragma region Поля

#pragma endregion

#pragma region Методы
	int SubFind(vector<T>& items, T item) {
		if (items.empty())
			return -1;

		size_t left = 0;
		size_t right = items.size() - 1;
		while (left <= right)
		{
			const size_t middle = left + (right - left) / 2;
			if (items[middle] == item)
				return static_cast<int>(middle);
			if (items[middle] > item) {
				if (middle == 0)
					break;
				right = middle - 1;
			}
			else
				left = middle + 1;
		}
		return -1;
	}
#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	int	Find(vector<T>items, T item) {
		Sorts<T> sorts;
		// Legacy behavior: Find returns the index in the sorted copy, not in the original vector.
		items = sorts.QuickSort(items);
		return this->SubFind(items, item);
	}
	bool IsExist(vector<T>items, T item) {
		return this->Find(items, item) != -1;
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы

#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion

	BinarySearch() {};
	~BinarySearch() {};

};
