#include "stdafx.h"
#include "ArrayHelper.h"

#pragma region Конструкторы
ArrayHelper::ArrayHelper()
{
}

ArrayHelper::~ArrayHelper()
{
}
#pragma endregion

#pragma region Методы
template <typename T>
T ArrayHelper::Sum(const T * a, int count)
{
	T sum = 0;
	for (size_t i = 0; i < count; i++)
		sum += a[i];
	return sum;
}

template <typename T>
T ArrayHelper::Sum(vector<T> a)
{
	T sum = 0;
	for (size_t i = 0; i < a.size(); i++)
		sum += a[i];
	return sum;
}

template <typename T>
float ArrayHelper::Avg(const T * a, int count)
{
	T sum = 0;
	for (size_t i = 0; i < count; i++)
		sum += a[i];
	return sum / count;
}

template <typename T>
float ArrayHelper::Avg(vector<T>a)
{
	T sum = 0;
	for (size_t i = 0; i < a.size(); i++)
		sum += a[i];
	return sum / count;
}

template <typename T>
T ArrayHelper::GetMax(const T * a, int count)
{
	T max = -MAXINT;
	for (size_t i = 0; i < count; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}

template <typename T>
T ArrayHelper::GetMax(vector<T>a)
{
	T max = -MAXINT;
	for (size_t i = 0; i < a.size(); i++)
		if (a[i] > max)
			max = a[i];
	return max;
}

template <typename T>
T ArrayHelper::GetMin(const T * a, int count)
{
	T min = MAXINT;
	for (size_t i = 0; i < count; i++)
		if (a[i] < min)
			min = a[i];
	return min;
}

template <typename T>
T ArrayHelper::GetMin(vector<T>a)
{
	T min = MAXINT;
	for (size_t i = 0; i < a.size(); i++)
		if (a[i] < min)
			min = a[i];
	return min;
}

#pragma endregion