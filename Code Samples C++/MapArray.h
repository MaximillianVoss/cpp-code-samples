#include "stdafx.h"
#include "Pair.h"
#pragma once
class MapArray
{
private:

#pragma region Поля
	/// <summary>
	/// массив элементов типа ( ключ , значение )
	/// </summary>
	vector<Pair> values;
#pragma endregion

public:

#pragma region Методы
	/// <summary>
	/// добавляет элемент
	/// </summary>
	/// <param name="key">ключ</param>
	/// <param name="value">значение</param>
	/// <returns></returns>
	bool Add(string key, string value);
	/// <summary>
	/// добавляет элемент
	/// </summary>
	/// <param name="pair">пара типа ( ключ , значение )</param>
	/// <returns></returns>
	bool Add(Pair pair);
	/// <summary>
	/// удаляет значение по ключу
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	bool Remove(string key);
	/// <summary>
	/// ищет значение по ключу
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	bool Find(string key);
	/// <summary>
	/// получает размер
	/// </summary>
	/// <returns></returns>
	size_t GetSize();
	/// <summary>
	/// задает значение элемента по индексу
	/// </summary>
	/// <param name="index"></param>
	/// <param name="item"></param>
	void SetItem(size_t index, Pair item);
	/// <summary>
	/// получает элемент по ключу
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	Pair* GetItem(string key);
	/// <summary>
	/// олучает элемент по индексу
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	Pair* GetItem(size_t index);
	/// <summary>
	/// преобразует в строку
	/// </summary>
	/// <returns></returns>
	string GetStr();
#pragma endregion

#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// конструктор
	/// </summary>
	MapArray();
	/// <summary>
	/// деструктор
	/// </summary>
	~MapArray();
#pragma endregion

};