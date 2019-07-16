#include "stdafx.h"
#include "Matrix.h"
#pragma once
class SortsAdvanced
{
private:
#pragma region Структура для результатов	
	/// <summary>
	///Струткура для хранения 
	///конкретного результата сортировки
	/// </summary>
	struct Result {
		/// <summary>
		/// название сортировки 
		/// </summary>
		string name;
		/// <summary>
		/// количесвто сравнений
		/// </summary>
		int cmpsValue;
		/// <summary>
		/// количесвто перестановок
		/// </summary>
		int swapsValue;
		/// <summary>
		/// Создает результат с указанными параметрами
		/// </summary>
		/// <param name="_name">имя</param>
		/// <param name="cmps">количесвто сравнений</param>
		/// <param name="swaps">количесвто перестановок</param>
		Result(string _name, int cmps, int swaps)
		{
			name = _name;
			cmpsValue = cmps;
			swapsValue = swaps;
		}
	};
#pragma endregion
	/// <summary>
	/// сравнивает два элемента
	/// </summary>
	/// <param name="a">первый элемент</param>
	/// <param name="b">второй элемент</param>
	/// <param name="cmpsCounter">счетчик сравнений</param>
	/// <returns>true если первый больше второго</returns>
	bool cmp(int a, int b, int & cmpsCounter);

public:
	SortsAdvanced();
	~SortsAdvanced();
	/// <summary>
	/// Сортировка пузырьком
	/// сортировка происходит по абсолютному значению
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="cmpsCounter">счетчик сравнений</param>
	/// <param name="swapsCounter">счетчик перестановок</param>
	void BubbleSort_Abs(vector<int>& a, int & cmpsCounter, int & swapsCounter);
	/// <summary>
	/// Сортировка выбором
	/// сортировка происходит по абсолютному значению
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="cmpsCounter">счетчик сравнений</param>
	/// <param name="swapsCounter">счетчик перестановок</param>
	void SelectSort_Abs(vector<int>& a, int & cmpsCounter, int & swapsCounter);
	/// <summary>
	/// Сортировка вставками
	/// сортировка происходит по абсолютному значению
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="cmpsCounter">счетчик сравнений</param>
	/// <param name="swapsCounter">счетчик перестановок</param>
	void Insertsort_Abs(vector<int>& a, int & cmpsCounter, int & swapsCounter);
	/// <summary>
	/// Сортировка Шелла
	/// сортировка происходит по абсолютному значению
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="cmpsCounter">счетчик сравнений</param>
	/// <param name="swapsCounter">счетчик перестановок</param>
	void ShellSort_Abs(vector<int>& a, int & cmpsCounter, int & swapsCounter);
	/// <summary>
	/// Быстрая сортировка
	/// сортировка происходит по абсолютному значению
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="cmpsCounter">счетчик сравнений</param>
	/// <param name="swapsCounter">счетчик перестановок</param>
	void QSort_Abs(int * a, int size, int & cmpsCounter, int & swapsCounter);
	/// <summary>
	/// наглядно тестирует 
	/// все сортировкив классе
	/// </summary>
	void Test();
	/// <summary>
	/// Печатает таблицу со 
	/// статистикой для сортировок
	/// </summary>
	/// <param name="results">результаты сортировок</param>
	/// <param name="message">подпись</param>
	void PrintTable(vector<Result> results, string message);
	/// <summary>
	/// Выводи количество 
	/// сравнений и перестановок
	/// </summary>
	/// <param name="cmps">количество сравнений</param>
	/// <param name="swaps">количество перестановок</param>
	void PrintStatistics(int cmps, int swaps);
};

