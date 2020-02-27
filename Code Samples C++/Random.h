#include "stdafx.h"
#pragma once
class Random
{
public:
	Random();
	~Random();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	vector<int> GetArrayInt(int min, int max, int count, bool onlyPositive);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="count"></param>
	/// <returns></returns>
	vector<int> GetArrayInt(int min, int max, int count);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	int GetInt(int min, int max, bool onlyPositive);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	int GetInt(int min, int max);
};

