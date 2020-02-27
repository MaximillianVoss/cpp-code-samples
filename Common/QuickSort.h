
#pragma once
#include "pch.h"
template<typename T>
///<summary>
/// Быстрая сортировка для примитивных типов
///</summary>
class QuickSort
{
private:

#pragma region Поля

#pragma endregion

#pragma region Методы
	/// <summary>
	/// разбиение
	/// исходник:
	/// https://appdividend.com/2019/05/02/quick-sort-in-c-tutorial-with-example-c-quick-sort-program/
	/// </summary>
	/// <param name="a">указатель на массив</param>
	/// <param name="start"></param>
	/// <param name="end"></param>
	/// <returns></returns>
	int partition(T* a, int start, int end)
	{
		int pivot = a[end];
		int P_index = start;
		int i, t;
		for (i = start; i < end; i++)
		{
			if (a[i] <= pivot)
			{
				t = a[i];
				a[i] = a[P_index];
				a[P_index] = t;
				P_index++;
			}
		}
		t = a[end];
		a[end] = a[P_index];
		a[P_index] = t;
		return P_index;
	}
#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	void Quicksort(vector<T> a, int start, int end)
	{
		if (start < end)
		{
			int P_index = partition(a, start, end);
			Quicksort(a, start, P_index - 1);
			Quicksort(a, P_index + 1, end);
		}
	}
	void Quicksort(T* a, int start, int end)
	{
		if (start < end)
		{
			int P_index = partition(a, start, end);
			Quicksort(a, start, P_index - 1);
			Quicksort(a, P_index + 1, end);
		}
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	QuickSort() {};
	~QuickSort() {};
#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion



};

