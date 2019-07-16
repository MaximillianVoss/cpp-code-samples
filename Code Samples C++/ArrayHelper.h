#pragma once
class ArrayHelper
{
public:
	ArrayHelper();
	~ArrayHelper();

	template<typename T>
	/// <summary>
	/// Суммирует все элементы в массиве
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="count">число элементов</param>
	/// <returns></returns>
	T Sum(const T * a, int count);

	template <typename T>
	/// <summary>
	/// Суммирует все элементы в массиве
	/// </summary>
	/// <param name="a">массив</param>
	/// <returns></returns>
	T Sum(vector<T> a);

	template<typename T>
	/// <summary>
	/// Находит среднее 
	/// арифметическое элементов
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="count">число элементов</param>
	/// <returns></returns>
	float Avg(const T * a, int count);

	template <typename T>
	/// <summary>
	/// Находит среднее 
	/// арифметическое элементов
	/// </summary>
	/// <param name="a">массив</param>
	/// <returns></returns>
	float Avg(vector<T>a);

	template<typename T>
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <param name="count"></param>
	/// <returns></returns>
	T GetMax(const T * a, int count);

	template<typename T>
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	T GetMax(vector<T> a);

	template<typename T>
	/// <summary>
	/// Находит минимум в массиве
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="count">число элементов</param>
	/// <returns></returns>
	T GetMin(const T * a, int count);

	template<typename T>
	/// <summary>
	/// Находит минимум в массиве
	/// </summary>
	/// <param name="a">массив</param>
	/// <returns></returns>
	T GetMin(vector<T> a);
};

