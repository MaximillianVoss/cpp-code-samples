#pragma once
#include "pch.h"
#include "Enums.h"
template<typename T>
///<summary>
/// Основные сортировки
///</summary>
class Sorts
{
private:

#pragma region Поля

#pragma endregion

#pragma region Методы
	/// <summary>
	/// Сравнивает два элемента:
	/// "0"  -если элементы равны
	/// "1"  -если A больше
	/// "-1" -если B больше
	/// </summary>
	/// <param name="a">первый элемент</param>
	/// <param name="b">второй элемент</param>
	/// <returns></returns>
	int Compare(T& a, T& b) {
		if (a == b)
			return 0;
		if (a > b)
			return 1;
		return -1;
	}
	void Swap(vector<T>& items, size_t i1, size_t i2) {
		if (i1 >= items.size() || i2 >= items.size())
			throw exception(Constants::Strings::Errors::Lists::incorrectIndex);
		T temp = items[i1];
		items[i1] = items[i2];
		items[i2] = temp;
	}
	bool ShouldMoveBeforePivot(T& value, T& pivot, Direction direction)
	{
		const int compareResult = this->Compare(value, pivot);
		if (direction == Direction::descending)
			return compareResult == 1;
		return compareResult == -1;
	}
	size_t Partition(vector<T>& items, size_t startIndex, size_t endIndex, Direction direction)
	{
		T pivot = items[endIndex];
		size_t pivotIndex = startIndex;
		for (size_t i = startIndex; i < endIndex; i++)
			if (this->ShouldMoveBeforePivot(items[i], pivot, direction))
				this->Swap(items, i, pivotIndex++);
		this->Swap(items, endIndex, pivotIndex);
		return pivotIndex;
	}
	void QuickSort(vector<T>& items, size_t startIndex, size_t endIndex, Direction direction) {
		if (startIndex >= endIndex)
			return;

		const size_t pivotIndex = this->Partition(items, startIndex, endIndex, direction);
		if (pivotIndex > startIndex)
			this->QuickSort(items, startIndex, pivotIndex - 1, direction);
		if (pivotIndex < endIndex)
			this->QuickSort(items, pivotIndex + 1, endIndex, direction);
	}
#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	/// <summary>
/// сортировка пузырьком: 
/// </summary>
/// <param name="a">массив</param>
/// <param name="length">размер</param>
	void BubbleSort(int* a, size_t length);
	/// <summary>
	/// Сортировка вставками
	/// </summary>
	/// <param name="a"></param>
	/// <param name="n"></param>
	void InsertionSort(int* a, size_t n);
	/// <summary>
	/// Сортировка слиянием
	/// </summary>
	/// <param name="array">массив</param>
	/// <param name="size">размер</param>
	void MergerSort(T array[], size_t size);
	/// <summary>
	/// Быстрая сортировка
	/// </summary>
	/// <param name="items">массив для сортировки</param>
	/// <param name="direction">направление сортировки:по возрастанию/убыванию</param>
	/// <returns></returns>
	vector<T>QuickSort(vector<T>items, Direction direction = Direction::ascending)
	{
		// Public API keeps returning a sorted copy; callers do not lose the original vector.
		if (items.size() < 2)
			return items;
		this->QuickSort(items, 0, items.size() - 1, direction);
		return items;
	}


#pragma endregion

#pragma region Конструкторы/Деструкторы
	Sorts() {};
	~Sorts() {};
#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion



};
