#pragma once
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstddef>
#include <iterator>
/// <summary>
/// Содержит стандартные сортировки
/// </summary>
class Sorts
{
private:
	/// <summary>
	/// функция сравнения элементов массива
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="x2"></param>
	/// <returns></returns>
	int Compare(const void * a, const void * b);
public:
	Sorts();
	~Sorts();
	/// <summary>
	/// сортировка пузырьком: 
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="length">размер</param>
	void BubbleSort(int * a, size_t length);
	/// <summary>
	/// Быстрая сортировка
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="n">размер</param>
	void QuickSort(int * a, size_t n);
	/// <summary>
	/// Сортировка вставками
	/// </summary>
	/// <param name="a"></param>
	/// <param name="n"></param>
	void InsertionSort(int * a, size_t n);
	/// <summary>
	/// Наглядно тетсирует все сортировки в классе
	/// и выводит таблицу сравнений
	/// </summary>
	void Test();
	template<typename T>
	/// <summary>
	/// Сортировка слиянием
	/// </summary>
	/// <param name="array">массив</param>
	/// <param name="size">размер</param>
	void MergerSort(T array[], size_t size);
};

