#pragma once
#include "Enums.h"
#include "Constants.h"
#include "pchUnit.h"
/// <summary>
/// Генерирует входные данные
/// </summary>
class Generator
{
private:
#pragma region Методы
	/// <summary>
	/// Генерирует строку укаазной длины
	/// </summary>
	/// <param name="length">длина</param>
	/// <param name="str">набор символов для генереации</param>
	/// <returns></returns>
	string GetStr(int length, const char* str) {
		int len = strlen(str);
		string result = "";
		for (int i = 0; i < length; i++)
			result += str[this->GetInt(0, len - 1)];
		return result;
	}
#pragma endregion
public:
#pragma region Поля
#pragma endregion
#pragma region Конструкторы
	Generator() {};
	~Generator() {};
#pragma endregion
#pragma region Методы
	/// <summary>
	/// Генерирует случайное целое число в указанных промежутках
	/// </summary>
	/// <param name="min">минимум (ВКЛЮЧИТЕЛЬНО)</param>
	/// <param name="max">максимум (ВКЛЮЧИТЕЛЬНО)</param>
	/// <returns></returns>
	int GetInt(int min, int max)
	{
		return  min + (rand() % static_cast<int>(max - min + 1));
	}
	/// <summary>
	/// Генерирует массив случайных целых чисел
	/// </summary>
	/// <param name="min">минимум (ВКЛЮЧИТЕЛЬНО)</param>
	/// <param name="max">максимум (ВКЛЮЧИТЕЛЬНО)</param>
	/// <param name="count">количество</param>
	/// <returns></returns>
	vector<int> GetIntArray(int min, int max, size_t count)
	{
		vector<int> items;
		for (int i = 0; i < count; i++)
			items.push_back(GetInt(min, max));
		return items;
	}
	/// <summary>
	/// Генерирует случайное вещественное число в указанных промежутках
	/// </summary>
	/// <param name="min">минимум (ВКЛЮЧИТЕЛЬНО)</param>
	/// <param name="max">максимум (ВКЛЮЧИТЕЛЬНО)</param>
	/// <returns></returns>
	double GetDouble(double min, double max) {
		double value = (double)rand() / RAND_MAX;
		return min + value * (max - min);
	}
	/// <summary>
	/// Генерирует массив случайных вещественных чисел
	/// </summary>
	/// <param name="min">минимум (ВКЛЮЧИТЕЛЬНО)</param>
	/// <param name="max">максимум (ВКЛЮЧИТЕЛЬНО)</param>
	/// <param name="count">количество</param>
	/// <returns></returns>
	vector<double> GetDoubleArray(double min, double max, size_t count) {
		vector<double> items;
		for (int i = 0; i < count; i++)
			items.push_back(GetDouble(min, max));
		return items;
	}
	/// <summary>
	/// Создает случайную строку указанной длинны
	/// </summary>
	/// <param name="length">длина</param>
	/// <param name="lang">язык</param>
	/// <returns></returns>
	string GetStr(int length, Language lang = byDefault) {
		if (lang == ENG || lang == byDefault)
			return GetStr(length, Constants::Strings::Alphabets::eng);
		if (lang == RUS)
			return GetStr(length, Constants::Strings::Alphabets::rus);
		return "";
	}
	/// <summary>
	/// Создает массив случайных строк указанной длины
	/// </summary>
	/// <param name="minlength">минимальная длина</param>
	/// <param name="maxlength">максимальная длина</param>
	/// <param name="count">количество</param>
	/// <param name="lang">язык</param>
	/// <returns></returns>
	vector<string> GetStrArray(size_t minlength, size_t maxlength, size_t count, Language lang = byDefault) {
		vector<string> items;
		for (int i = 0; i < count; i++)
			items.push_back(GetStr(GetInt(minlength, maxlength), lang));
		return items;
	}
#pragma endregion
};