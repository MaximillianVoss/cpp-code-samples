#pragma once
#include "DynamicArray.h"
template<typename T>
///<summary>
/// Стек-контейнер
///</summary>
class Stack :public DynamicArray<T>
{
private:

#pragma region Поля

#pragma endregion

#pragma region Методы

#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	/// <summary>
/// Добавляет элемент в верхушку стека
/// </summary>
/// <param name="item"></param>
	void Push(T item) {
		//this->Insert(item, this->GetCount() > 0 ? this->GetCount() - 1 : 0);
		this->Add(item);
	}
	/// <summary>
	/// Извлекает элемент из верхушки стека с удалением
	/// </summary>
	/// <returns></returns>
	T Pop() {
		if (!this->IsEmpty()) {
			T result = this->Get(this->GetCount() - 1);
			this->Delete(this->GetCount() - 1);
			return result;
		}
		throw exception(Constants::Strings::Errors::Lists::empty);
	}
	/// <summary>
	/// Просмотреть верхушку стека(без удаления)
	/// </summary>
	T Peek() {
		if (!this->IsEmpty())
			return this->Get(this->GetCount() - 1);
		throw exception(Constants::Strings::Errors::Lists::empty);
	}
	/// <summary>
	/// Проверяет, является ли список пустым
	/// </summary>
	/// <returns></returns>
	bool IsEmpty() {
		return this->GetCount() == 0;
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	Stack() :DynamicArray<T>() {

	};
	~Stack() {};
#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion

};
