
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
	T GetMiddle(vector<T>items) {
		return items[items.size() / 2];
	}
	vector<T> GetHalfLeft(vector<T>items) {
		return vector<T>(items.begin(), items.begin() + items.size() / 2);
	}
	vector<T> GetHalfRight(vector<T>items) {
		return vector<T>(items.begin() + items.size() / 2 + 1, items.end());
	}
	int SubFind(vector<T>items, T item, int start = 0) {
		if (items.size() > 0)
		{
			if (item == this->GetMiddle(items))
				return start + items.size() / 2;
			else {
				if (items.size() == 1)
					return -1;
				if (this->GetMiddle(items) > item)
					return this->SubFind(GetHalfLeft(items), item, start);
				else
					return this->SubFind(GetHalfRight(items), item, start + items.size() / 2 + 1);
			}
		}
		else
			return -1;
	}
#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	int	Find(vector<T>items, T item) {
		Sorts<T> sorts;
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
