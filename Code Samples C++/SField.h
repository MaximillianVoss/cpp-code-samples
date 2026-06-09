#pragma once
#include "pch.h"
template<typename T>
///<summary>
/// Описание_класса
///</summary>
class SField
{
private:

#pragma region Поля

#pragma endregion

#pragma region Методы

#pragma endregion

public:

#pragma region Поля
	/// <summary>
	/// Название поля
	/// </summary>
	string name;
	/// <summary>
	/// Значение поля
	/// </summary>
	T value;
#pragma endregion

#pragma region Методы
	string ToString() {
		sstream 
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы

#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion
	SField(string name, T value) {
		this->name = name;
		this->value = value;
	}
	SField() :SField(Constants::Strings::undefined, "") {};
	~SField() {};

};
