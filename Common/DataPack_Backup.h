#pragma once
#include "pch.h"
template<typename T>
///<summary>
/// Набор данных
///</summary>
class DataPack
{
private:

#pragma region Поля
	/// <summary>
	/// Название набора данных
	/// </summary>
	string titleFieldName;
	/// <summary>
	/// Подпись оси X
	/// </summary>
	string xTitleFieldName;
	/// <summary>
	/// Подпись оси Y
	/// </summary>
	string yTitleFieldName;
	/// <summary>
	/// Данные по X
	/// </summary>
	vector<T>xValues;
	/// <summary>
	/// Данные по Y
	/// </summary>
	vector<T>yValues;
#pragma endregion

#pragma region Методы

#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы

#pragma region Get
	string GetTitle() {
		return this->titleFieldName;
	}
	string GetXTitle() {
		return this->xTitleFieldName;
	}
	string GetYTitle() {
		return this->yTitleFieldName;
	}
	vector<T>GetXValues() {
		return this->xValues;
	}
	vector<T>GetYValues() {
		return this->yValues;
	}
#pragma endregion

#pragma region Set
	void SetTitle(string title) {
		this->titleFieldName = title;
	}
	void SetXTitle(string title) {
		this->xTitleFieldName = title;
	}
	void SetYTitle(string title) {
		this->yTitleFieldName = title;
	}
	void SetXValues(vector<T> data) {
		this->xValues = data;
	}
	void SetYValues(vector<T> data) {
		this->yValues = data;
	}
#pragma endregion

#pragma region Add
	void AddXValue(T value) {
		this->xValues.push_back(value);
	}
	void AddYValue(T value)
	{
		this->yValues.push_back(value);
	}
	void AddPoint(T x, T y) {
		this->AddXValue(x);
		this->AddYValue(y);
	}
	void AddPoint(vector<T> values) {
		if (values.size() == 2)
			this->AddPoint(values[0], values[1]);
		else {
			char message[80];
			sprintf(message, Constants::Strings::Errors::Lists::incorrectSize, 2, values.size());
			throw exception(message);
		}
	}
#pragma endregion
	string ToString() {
		stringstream ss;
		ss << this->titleFieldName << endl;
		ss << this->xTitleFieldName << endl;
		ss << this->yTitleFieldName << endl;
		for (T value : this->xValues)
			ss << value << " ";
		ss << endl;
		for (T value : this->yValues)
			ss << value << " ";
		ss << endl;
		return ss.str();
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы

#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion
	/// <summary>
	/// Создает набор данных с указанными значениями
	/// </summary>
	/// <param name="title">Название набора данных</param>
	/// <param name="xTitle">Подпись оси X</param>
	/// <param name="yTitle">Подпись оси Y</param>
	/// <param name="xValues">Данные по X</param>
	/// <param name="yValues">Данные по Y</param>
	DataPack(string title, string xTitle, string yTitle, vector<T>xValues = {}, vector<T>yValues = {}) {
		this->titleFieldName = title;
		this->xTitleFieldName = xTitle;
		this->yTitleFieldName = yTitle;
		this->xValues = xValues;
		this->yValues = yValues;
	};
	/// <summary>
	/// Создает набор данных по умолчанию
	/// </summary>
	DataPack() :DataPack(Constants::Strings::undefined, Constants::Strings::undefined, Constants::Strings::undefined, {}, {}) {};
	/// <summary>
	/// Деструктор
	/// </summary>
	~DataPack() {};

};
