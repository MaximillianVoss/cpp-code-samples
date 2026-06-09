
#pragma once
#include "pch.h"
///<summary>
/// Базовый класс элемента графа
///</summary>
class GraphItem
{
private:

#pragma region Поля
	/// <summary>
	/// ID
	/// </summary>
	string id;
	/// <summary>
	/// Длина ID для длинного формата
	/// </summary>
	size_t idLength = 32;
	/// <summary>
	/// Задан ли ID в длинном формате
	/// </summary>
	bool longFormat;
	/// <summary>
	/// является ли элемент удаленным из графа
	/// </summary>
	bool isDeleted;
#pragma endregion

#pragma region Методы
	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	string CreateId(int value) {
		return this->CreateId(to_string(value));
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	string CreateId(string value) {
		//char id[33];
		//sprintf(id, "%032s", value.c_str());
		//return string(id);
		if (value.length() <= this->idLength)
		{
			while (value.length() < this->idLength)
				value = "0" + value;
			return value;
		}
		else
			throw exception(("Строка больше " + to_string(this->idLength) + " символов!").c_str());
	}
	/// <summary>
	/// Проверяет является ли строка числом
	/// </summary>
	/// <param name="s">строка</param>
	/// <returns></returns>
	bool IsNumber(const std::string& s)
	{
		return(strspn(s.c_str(), "-.0123456789") == s.size());
	}
#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	/// <summary>
	/// Получает ID вершины
	/// </summary>
	/// <param name="id">ID</param>
	/// <param name="longFormat">Длиный формат, true - ID будут в 32 разрядном представлении</param>
	void SetId(string id, bool longFormat) {
		this->longFormat = longFormat;
		if (longFormat)
		{
			if (this->IsNumber(id))
				this->id = this->CreateId(id);
			else
				this->id = id;
		}
		else
			this->id = id;
	}
	/// <summary>
	/// Устанавливает ID вершины
	/// </summary>
	/// <returns></returns>
	string GetId() {
		return this->id;
	}
	/// <summary>
	/// Получает формат id - true длинный формат
	/// </summary>
	/// <returns></returns>
	bool GetIdFormat() {
		return this->longFormat;
	}
	/// <summary>
	/// Помечает элемент как удаленный
	/// </summary>
	/// <param name="isDeleted">true - элемент считается удаленным</param>
	void SetDeleted(bool isDeleted) {
		this->isDeleted = isDeleted;
	}
	/// <summary>
	/// Возвращает значение поля "удалено"
	/// </summary>
	bool GetDeleted()
	{
		return this->isDeleted;
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	GraphItem(string id, bool longFromat = true, bool isDeleted = false) {
		this->SetId(id, longFromat);
		this->SetDeleted(isDeleted);
	}
#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion

	GraphItem() {};
	~GraphItem() {};

};
