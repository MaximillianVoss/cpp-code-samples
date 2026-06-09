#pragma once
#include "pch.h"
template<typename TData, typename TValue>
///<summary>
/// Контейнер для элементов коллекций
///</summary>
class Container
{
private:

#pragma region Поля
	/// <summary>
	/// Хранимый объект
	/// </summary>
	TData data;
	/// <summary>
	/// Поля объекта для сравнения/поиска
	/// </summary>
	TValue value;
#pragma endregion

#pragma region Методы

#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы

#pragma endregion

#pragma region Конструкторы/Деструкторы
	Container(TData data, TValue value) {
		this->data = data;
		this->value = value;
	};
	Container() {};
	~Container() {};
#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion

};
