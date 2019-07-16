#pragma once
class BinarySearch
{
public:
	BinarySearch();
	~BinarySearch();
	/// <summary>
	/// ищет указанное число 
	/// в массиве
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="value">искомое значение</param>
	/// <param name="start">начало отрезка</param>
	/// <param name="end">конец отрезка</param>
	/// <returns></returns>
	bool Search(int *a, int value, int start, int end);
};

