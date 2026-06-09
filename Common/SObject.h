#pragma once
#include "pch.h"
#include "SField.h"
#include "StrHelper.h"
#include "Constants.h"
template<typename T>
///<summary>
/// Сериализуемый объект
///</summary>
class SObject
{
private:

#pragma region Поля
	/// <summary>
	/// Служит символом начала объкта в строковом виде
	/// </summary>
	char open = Constants::Strings::Prefixes::brace[0];
	/// <summary>
	/// Служит символом конца объкта в строковом виде
	/// </summary>
	char close = Constants::Strings::Postfixes::brace[0];
	/// <summary>
	/// Разделяет название поля и значение в строковом виде
	/// </summary>
	char fieldSeparator = Constants::Strings::Separators::colon[0];
	/// <summary>
	/// Указывает на конец поля и разделяет поля между собой в строковом виде
	/// </summary>
	char fieldEnd = Constants::Strings::Separators::semicolon[0];
	/// <summary>
	/// Индекс для случая когда элемента не найден
	/// </summary>
	int notFoundIndex = Constants::Ints::Lists::notFoundIndex;
#pragma endregion

#pragma region Методы
	bool IsFieldExist(string name) {
		return this->Find(name) != NULL;
	}
	bool IsFieldExist(size_t index) {
		return this->Find(index) != NULL;
	}
	SField<T>* Find(string name) {
		for (size_t i = 0; i < fields.size(); i++)
			if (name == fields[i].name)
				return &this->fields[i];
		return NULL;
	}
	SField<T>* Find(size_t index) {
		if (index >= 0 && index < fields.size())
			return &this->fields[index];
		return NULL;
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
		int index = this->GetIndex(name);
		if (index != notFoundIndex)
			this->Delete(index);
		else
			throw exception(Constants::Strings::Errors::Lists::notFound);
	}
	void Delete(size_t index) {
		if (IsFieldExist(index))
			this->fields.erase(this->fields.begin() + index);
		else
			throw exception(Constants::Strings::Errors::Lists::notFound);
	}
	SField<T>* Get(string name) {
		SField<T>* field = this->Find(name);
		if (field)
			return field;
		throw exception(Constants::Strings::Errors::Lists::notFound);
	}
	SField<T>* Get(int index) {
		SField<T>* field = this->Find(index);
		if (field)
			return field;
		throw exception(Constants::Strings::Errors::Lists::incorrectIndex);
	}
	int GetInt(string fieldName) {
		return atoi(this->Get(fieldName)->value.c_str());
	}
	float GetFloat(string fieldName) {
		return atof(this->Get(fieldName)->value.c_str());
	}
	bool GetBool(string fieldName)
	{
		string fieldVal = this->Get(fieldName)->value;
		if (fieldVal == "true" || fieldVal == "TRUE" || fieldVal == "True" || fieldVal == "1")
			return true;
		else
			return false;
	}
	/// <summary>
	/// Получает индекс поля, если такого поля нет, возвращает единицу
	/// </summary>
	/// <param name="name">имя поля</param>
	/// <returns></returns>
	int GetIndex(string name) {
		for (int i = 0; i < this->fields.size(); i++)
			if (this->fields[i].name == name)
				return i;
		return this->notFoundIndex;
	}
	void Set(string name, T value) {
		SField<T>* field = this->Find(name);
		if (field)
			field->value = value;
		else {
			this->Add(name, value);
			this->Set(name, value);
		}
		//throw exception(Constants::Strings::Errors::Lists::notFound);
	}
	void Set(size_t index, T value) {
		SField<T>* field = this->Find(index);
		if (field)
			field->value = value;
		else {
			this->Add(field->name, value);
			this->Set(field->name, value);
		}
		//throw exception(Constants::Strings::Errors::Lists::incorrectIndex);
	}
	size_t GetFieldsCount() {
		return this->fields.size();
	}

#pragma region Сериализация
	void FromString(string str) {
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
	string ToString(bool newLine = false) {
		stringstream ss;
		ss << open;
		if (newLine)
			ss << endl;
		for (int i = 0; i < this->fields.size(); i++) {
			ss << "\t" << fields[i].ToString();
			if (newLine)
				ss << endl;
		}
		if (newLine)
			ss << endl;
		ss << close;
		return ss.str();
	}
#pragma endregion

#pragma endregion

#pragma region Конструкторы/Деструкторы
	SObject() {};
	SObject(string str) { this->FromString(str); }
	SObject(vector<SField<T>> fields) {
		for (SField<T> field : fields)
			this->Add(field);
	}
	~SObject() {};
#pragma endregion

#pragma region Операторы
	SField<T>* operator[](string name) {
		return this->Find(name);
	}
	SField<T>* operator[](size_t index) {
		return this->Find(index);
	}
	//template<typename T>
	bool operator==(SObject<T> obj) {
		for (SField<T> field : this->fields) {
			SField<T>* objField = obj[field.name];
			if (objField) {
				if (objField->value != field.value)
					return false;
			}
			else
				return false;
		}
		return true;
	}
	bool operator!=(SObject<T> obj)const {
		for (SField<T> field : this->fields) {
			SField<T>* objField = obj[field.name];
			if (objField) {
				if (objField->value != field.value)
					return true;
			}
			else
				return true;
		}
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
template<typename T>
bool operator!=(SObject<string>& a, SObject<string>& b) {
	/*for (SField<T> field : this->fields)
		if (obj.Get(field).value != field.value)
			return true;*/
	return false;
}
#pragma endregion