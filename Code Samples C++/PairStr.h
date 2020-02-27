#include "stdafx.h"
#pragma once
class PairStr
{
private:
public:

#pragma region Поля
	/// <summary>
	/// ключ
	/// </summary>
	string key;
	/// <summary>
	/// значение
	/// </summary>
	string value;
#pragma endregion

#pragma region Конструкторы/Деструкторы
	PairStr();
	/// <summary>
	/// создает пару с указанным ключом и значением
	/// </summary>
	/// <param name="_key">ключ</param>
	/// <param name="_value">значение</param>
	PairStr(string _key, string _value);
	~PairStr();
#pragma endregion

#pragma region Методы
	/// <summary>
	/// преобразует в строку
	/// </summary>
	/// <returns></returns>
	string GetStr();
#pragma endregion

};