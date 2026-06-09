
#pragma once
#include "pch.h"
#include "IO.h"
#include "SObject.h"
#include "StrHelper.h"
template<typename T>
///<summary>
/// Загружает и сохраняет сериализуемые объекты
///</summary>
class SLoader
{
private:

#pragma region Поля
	string separator = ",";
#pragma endregion

#pragma region Методы

#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	/*void Save(string filename, SObject<T>obj) {
		this->Save(filename, { obj });
	}*/
	void Save(string filename, vector<SObject<T>>objects) {
		stringstream ss;
		for (int i = 0; i < objects.size(); i++)
			if (i != objects.size() - 1)
				ss << objects[i].ToString() << this->separator;
			else
				ss << objects[i].ToString();
		IO().WriteLines(filename, { ss.str() });
	}
	vector<SObject<string>> Load(string filename) {
		vector<string> lines = IO().ReadLines(filename);
		string objStr = StrHelper().Join(lines);
		vector<SObject<string>> result;
		lines = StrHelper().Split(objStr, this->separator);
		for (string line : lines)
			result.push_back(SObject<string>(line));
		return result;
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы

#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion

	SLoader() {};
	~SLoader() {};

};
