#pragma once
#include "pch.h"
#include "StrHelper.h"
#include "Constants.h"
template<typename T>
///<summary>
/// Сериализуемое поле
///</summary>
class SField
{
private:

#pragma region Поля
	/// <summary>
	/// Разделяет название поля и значение
	/// </summary>
	char separator = ':';
	/// <summary>
	/// </summary>
	char end = ';';
#pragma endregion

#pragma region Методы
	/// <summary>
	/// Десериализует строку с полем
	/// </summary>
	/// <param name="fieldStr">строка вида "имя поля":"значение поля"</param>
	/// <returns></returns>
	SField<string> Load(string fieldStr) {
		StrHelper sh = StrHelper();
		vector<string> lines = sh.Split(fieldStr, this->separator);
		if (lines.size() == 2)
			return SField<string>(sh.Remove(lines[0], this->end), sh.Remove(lines[1], this->end));
		else
			throw exception(Constants::Strings::Errors::Lists::incorrectSize);
	}
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
	/// <summary>
	/// Возвращает поле в виде строки
	/// </summary>
	/// <returns></returns>
	string ToString() {
		stringstream ss;
		ss << this->name << this->separator << this->value << this->end;
		return ss.str();
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// Создает поле с указанным именем и знечанием
	/// </summary>
	/// <param name="name">имя поля</param>
	/// <param name="value">значение</param>
	SField(string name, T value) {
		this->name = name;
		this->value = value;
	}
	/// <summary>
	/// Создает поле с именем "undefined" и пустым значением
	/// </summary>
	SField() :SField(Constants::Strings::undefined, "") {};
	/// <summary>
	/// Создает поле из указанной сериализованной строки
	/// </summary>
	/// <param name="fieldStr">строка вида "имя поля":"значение поля"</param>
	SField(string fieldStr) {
		SField<string> loadedObj = this->Load(fieldStr);
		this->name = loadedObj.name;
		this->value = loadedObj.value;
	}
	/// <summary>
	/// Создает копию указанного поля
	/// </summary>
	/// <param name="field">поле для копирования</param>
	SField(SField<T>* field) {
		this->name = field->name;
		this->value = field->value;
	}
	/// <summary>
	/// Деструктор
	/// </summary>
	~SField() {};
#pragma endregion

#pragma region Операторы
	bool operator==(SField<T> field) {
		return this->name == field.name && this->value == field.value;
	}
	bool operator!=(SField<T> field) {
		return !(this->name == field.name && this->value == field.value);
	}
#pragma endregion

#pragma region Обработчики событий

#pragma endregion

};
#pragma region Операторы
template<typename T>
ostream& operator<<(ostream& os, SField<T>& field)
{
	os << field.ToString();
	return os;
}
#pragma endregion