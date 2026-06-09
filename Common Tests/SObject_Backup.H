#pragma once
#include "pch.h"
#include "SField.h"
#include "StrHelper.h"
template<typename T>
///<summary>
/// Сериализуемый объект
///</summary>
class SObject
{
private:

#pragma region Поля
	char open = '{';
	char close = '}';
	/// <summary>
	/// Разделяет название поля и значение
	/// </summary>
	char fieldSeparator = ':';
	/// <summary>
	/// </summary>
	char fieldEnd = ';';
#pragma endregion

#pragma region Методы
	bool IsFieldExist(string name) {
		for (size_t i = 0; i < fields.size(); i++)
			if (name == fields[i].name)
				return true;
		return false;
	}
	bool IsFieldExist(size_t index) {
		if (index >= 0 && index < fields.size())
			return true;
		return false;
	}
	size_t Find(string name) {
		for (size_t i = 0; i < fields.size(); i++)
			if (name == fields[i].name)
				return i;
		throw exception(Constants::Strings::Errors::Lists::notFound);
	}
	SField<T> Find(size_t index) {
		if (index >= 0 && index < fields.size())
			return this->fields[index];
		else
			throw exception(Constants::Strings::Errors::Lists::incorrectIndex);
	}
	void Add(SField<T> field) {
		if (IsFieldExist(field.name))
			throw exception(Constants::Strings::Errors::Lists::elementAlreadyExists);
		else
			this->fields.push_back(field);
	}
#pragma endregion

public:

#pragma region Поля
	vector<SField<T>> fields;
#pragma endregion

#pragma region Методы
	void Add(string name, T value) {
		this->Add(SField<T>(name, value));
	}
	void Delete(string name) {
		this->Delete(this->Find(name));
	}
	void Delete(size_t index) {
		if (IsFieldExist(index))
			this->fields.erase(this->fields.begin() + index);
		else
			throw exception(Constants::Strings::Errors::Lists::notFound);
	}
	SField<T>Get(string name) {
		return this->Find(name);
	}
	SField<T>Get(int index) {
		return this->Find(index);
	}
	void Set(string name, T value) {
		size_t index = this->Find(name);
		this->fields[index].value = value;
	}
	void Set(size_t index, T value) {
		size_t index = this->Find(index);
		this->fields[index].value = value;
	}
	size_t GetFieldsCount() {
		return this->fields.size();
	}
	void Load(string str) {
		//Десереализация - см. Lab 13
		if (str.length() > 1) {
			StrHelper sh;
			if (str[0] == open && str[str.length() - 1] == close) {
				str = str.substr(1);
				str = str.substr(0, str.length() - 1);
				vector<string> fieldsStrs = sh.Split(str, fieldEnd);
				for (int i = 0; i < fieldsStrs.size(); i++)
				{
					vector<string> items = sh.Split(fieldsStrs[i], fieldSeparator);
					if (items.size() > 1)
						fields.push_back(SField<string>(items[0], items[1]));
					else
						fields.push_back(SField<string>("error", "error"));
				}
			}
		}
	}
	string ToString() {
		stringstream ss;
		ss << open;
		for (int i = 0; i < this->fields.size(); i++)
			ss << fields[i].ToString();
		//str = str.substr(0, str.length() - 1);
		ss << close;
		return ss.str();
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	SObject() {};
	SObject(string str) { this->Load(str); }
	SObject(vector<SField<T>> fields) {
		for (SField<T> field : fields)
			this->Add(field);
	}
	~SObject() {};
#pragma endregion

#pragma region Операторы
	//см.  Lab 13
	SField<T>* operator[](string name) {
		for (size_t i = 0; i < fields.size(); i++)
			if (name == fields[i].name)
				return &this->fields[i];
		return NULL;
	}
	SField<T>* operator[](size_t index) {
		if (index >= 0 && index < fields.size())
			return &this->fields[index];
		return NULL;
	}
	bool operator==(SObject<T> obj) {
		/*for (SField<T> field : this->fields)
			if (obj.Get(field).value != field.value)
				return false;*/
		return true;
	}
	bool operator!=(SObject<T> obj) {
		/*for (SField<T> field : this->fields)
			if (obj.Get(field).value != field.value)
				return true;*/
		return false;
	}
#pragma endregion

#pragma region Обработчики событий

#pragma endregion

};
#pragma region Операторы
template<typename T>
ostream& operator<<(ostream& os, SObject<T>& obj)
{
	os << obj.ToString();
	return os;
}
#pragma endregion