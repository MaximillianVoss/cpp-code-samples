
#pragma once
#include "pch.h"
#include "StrHelper.h"
#include "Constants.h"
template<typename T>
///<summary>
/// Описание_класса
///</summary>
class Converter
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


	T ConvertTo(string str)
	{
		istringstream ss(str);
		T num;
		ss >> num;
		return num;
	}
	vector<T> ConvertToVector(string str, string separator = " ", string notDelete = "", string prefix = "[", string postfix = "]") {
		if (str.length() > 2) {
			StrHelper sh;
			vector<string> items = sh.Split(str, separator, notDelete);
			vector<T> result;
			for (string item : items)
				result.push_back(this->ConvertTo(item));
			return result;
		}
		throw exception(Constants::Strings::Errors::Lists::incorrectSize);
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы

#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion

	template<typename T>
	class Lists {
	public:
		void Convert1() {

		}
	};

	Converter() {};
	~Converter() {};

};
