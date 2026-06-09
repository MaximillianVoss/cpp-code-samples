#pragma once
#include "pch.h"
#include "Constants.h"
///<summary>
/// Динамический массив-контейнер
///</summary>
template<typename T>
class DynamicArray
{
private:

#pragma region Поля
	/// <summary>
	/// Количество элементов
	/// </summary>
	size_t count;
	/// <summary>
	/// Элементы массива
	/// </summary>
	T* items;
#pragma endregion

#pragma region Методы

#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	/// <summary>
	/// Добавляет элемент в список
	/// </summary>
	/// <param name="item">элемент для добавления</param>
	void Add(T item) {
		if (this->items) {
			T* copy = new T[this->count + 1];
			for (int i = 0; i < this->count; i++)
				copy[i] = this->items[i];
			copy[this->count] = item;
			this->items = copy;
			this->count++;
		}
		else {
			this->items = new T[++this->count];
			this->items[this->count - 1] = item;
		}
	}
	/// <summary>
	/// Втавляет элемент по указаному иднексу
	/// </summary>
	/// <param name="item">элемент для вставки</param>
	/// <param name="index">индекс где будет размещен элемент</param>
	void Insert(T item, size_t index) {
		if (items) {
			if (index < this->count) {
				T* copy = new T[this->count + 1];
				for (int i = 0; i < index; i++)
					copy[i] = this->items[i];
				copy[index] = item;
				for (int i = index; i < this->count; i++)
					copy[i + 1] = this->items[i];
				this->items = copy;
				this->count++;
			}
		}
		else
			this->Add(item);
	}
	/// <summary>
	/// Удаляет элемент списка по индексу
	/// </summary>
	/// <param name="index">индеск элемента</param>
	void Delete(size_t index) {
		if (index < this->count)
		{
			T* copy = new T[this->count - 1];
			for (int i = 0, ii = 0; i < this->count; i++)
				if (i != index)
					copy[ii++] = this->items[i];
			this->items = copy;
			this->count--;
			if (this->count == 0)
				this->items = NULL;
		}
	}
	/// <summary>
	/// Получает элемент списка  по индексу
	/// </summary>
	/// <param name="index">индекс элемента</param>
	/// <returns></returns>
	T Get(size_t index) {
		if (index < this->count)
			for (int i = index; i < this->count; i++)
				if (index == i)
					return this->items[i];
		throw exception(Constants::Strings::Errors::Lists::incorrectIndex);
	}
	/// <summary>
	/// Возвращает длину списка
	/// </summary>
	/// <returns></returns>
	size_t GetCount() {
		return this->count;
	}
	/// <summary>
	/// Сериализует список
	/// </summary>
	/// <returns></returns>
	string ToString(string separator = " ") {
		stringstream ss;
		for (int i = 0; i < this->count; i++)
			ss << this->items[i] << separator;
		return ss.str();
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	DynamicArray() {
		this->count = 0;
		this->items = NULL;
	};
	~DynamicArray() {};
#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion

};
