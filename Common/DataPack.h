
#pragma once
#include "pch.h"
#include "SObject.h"
#include "Converter.h"
template<typename T>
///<summary>
/// Описание_класса
///</summary>
class DataPack : public  SObject<string>
{
private:

#pragma region Поля
	vector<string> fieldsName = {
		"title",
		"xTitle",
		"yTitle",
		"group",
		"xData",
		"yData"
	};
	string titleFieldName = this->fieldsName[0];
	string xTitleFieldName = this->fieldsName[1];
	string yTitleFieldName = this->fieldsName[2];
	string groupFieldName = this->fieldsName[3];
	string xDataFieldName = this->fieldsName[4];
	string yDataFieldName = this->fieldsName[5];
#pragma endregion

#pragma region Методы
	vector<T> ConvertVector(string vectorStr) {
		vector<T>result;
		vector<string> itemsStr = StrHelper().Split(vectorStr);
		for (string item : itemsStr)
			result.push_back(Convert(item));
		return result;
	}
	T Convert(string& str)
	{
		std::istringstream ss(str);
		T num;
		ss >> num;
		return num;
	}
	bool Find(string fieldName) {
		for (string name : this->fieldsName)
			if (name == fieldName)
				reuturn true;
		return false;
	}
	void Init(string title, string xTitle, string yTitle, int group, vector<T> xData, vector<T> yData) {
		SetTitle(title);
		SetXTitle(xTitle);
		SetYTitle(yTitle);
		SetGroup(group);
		SetXData(xData);
		SetYData(yData);
	}
	void Init(string title, string xTitle, string yTitle, int group, string xData, string yData) {
		SetTitle(title);
		SetXTitle(xTitle);
		SetYTitle(yTitle);
		SetGroup(group);
		SetXData(xData);
		SetYData(yData);
	}

#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы

#pragma region SET
	void SetTitle(string value) {
		this->Set(this->titleFieldName, value);
	}
	void SetXTitle(string value) {
		this->Set(this->xTitleFieldName, value);
	}
	void SetYTitle(string value) {
		this->Set(this->yTitleFieldName, value);
	}
	void SetGroup(int value) {
		this->Set(this->groupFieldName, to_string(value));
	}
	void SetXData(string value) {
		this->Set(this->xDataFieldName, value);
	}
	void SetXData(vector<T> values) {
		this->Set(this->xDataFieldName, Converter<T>::Lists().Convert(values));
	}
	void SetYData(string value) {
		this->Set(this->yDataFieldName, value);
	}
	void SetYData(vector<T> values) {
		this->Set(this->yDataFieldName, Converter<T>::Lists().Convert(values));
	}
#pragma endregion

#pragma region GET
	string GetXTitle() {
		return this->Get(this->xTitleFieldName)->value;
	}
	string GetYTitle() {
		return this->Get(this->yTitleFieldName)->value;
	}
#pragma endregion


#pragma region Add
	void AddPoint(T x, T y) {
		Converter<T> converter = Converter<T>();
		vector<T> xValues = Converter<T>::Lists().Convert(this->Get(this->xDataFieldName)->value);
		vector<T> yValues = Converter<T>::Lists().Convert(this->Get(this->yDataFieldName)->value);
		xValues.push_back(x);
		yValues.push_back(y);
		this->Set(this->xDataFieldName, Converter<T>::Lists().Convert(xValues));
		this->Set(this->yDataFieldName, Converter<T>::Lists().Convert(yValues));
	}
#pragma endregion



#pragma region Десериализация
	void FromString(string str) {
		SObject<string> obj = SObject<string>(str);
		string val = obj.Get(this->groupFieldName)->value;
		bool separate = (val == "1");
		Init(
			obj.Get(this->titleFieldName)->value,
			obj.Get(this->xTitleFieldName)->value,
			obj.Get(this->yTitleFieldName)->value,
			separate,
			obj.Get(this->xDataFieldName)->value,
			obj.Get(this->yDataFieldName)->value
		);
	}
#pragma endregion


#pragma endregion

#pragma region Конструкторы/Деструкторы

#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion

	DataPack() :DataPack("", "", "", true, {}, {}) {

	};
	DataPack(string title, string xTitle, string yTitle, int group = 1, vector<T> xData = {}, vector<T> yData = {}) {
		this->Init(title, xTitle, yTitle, group, xData, yData);
	}
	DataPack(string serializedStr) {
		this->FromString(serializedStr);
	}
	~DataPack() {};

};
