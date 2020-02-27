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
	int Compare(T a, T b) {
		if (a == b)
			return 0;
		if (a > b)
			return 1;
		return -1;
	}
	T* Swap(T* a, int i1, int i2) {
		if (i1 < 0 || i2 < 0)
			throw exception(Constants::Strings::Errors::Lists::incorrectIndex);
		else {
			T temp = a[i1];
			a[i1] = a[i2];
			a[i2] = temp;
			return a;
		}
	}
	int Partition(T* a, int startIndex, int endIndex, Direction direction)
	{
		T pivot = a[endIndex];
		int pivotIndex = startIndex;
		int i, t;
		for (i = startIndex; i < endIndex; i++)
		{
			if (Compare(a[i], pivot) == -1 && direction == Direction::ascending)
			{
				a = this->Swap(a, i, pivotIndex);
				pivotIndex++;
			}
			if (Compare(a[i], pivot) == 1 && direction == Direction::descending)
			{
				a = this->Swap(a, i, pivotIndex);
				pivotIndex++;
			}
		}
		a = this->Swap(a, endIndex, pivotIndex);
		return pivotIndex;
	}
	vector<T>QuickSort(vector<T>items, int startIndex, int endIndex, Direction direction) {
		if (startIndex < endIndex)
		{
			int P_index = this->Partition(&items[0], startIndex, endIndex, direction);
			items = this->QuickSort(items, startIndex, P_index - 1, direction);
			items = this->QuickSort(items, P_index + 1, endIndex, direction);
		}
		return items;
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
		return this->QuickSort(items, 0, items.size() - 1, direction);
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
