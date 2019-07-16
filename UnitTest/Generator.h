#pragma once
#include "Enums.h"
#include "Constants.h"
#include "pchUnit.h"
/// <summary>
/// √енерирует входные данные
/// </summary>
class Generator
{
private:
#pragma region ћетоды
	/// <summary>
	/// √енерирует строку укаазной длины
	/// </summary>
	/// <param name="length">длина</param>
	/// <param name="str">набор символов дл€ генереации</param>
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
#pragma region ѕол€
#pragma endregion
#pragma region  онструкторы
	Generator() {};
	~Generator() {};
#pragma endregion
#pragma region ћетоды
	/// <summary>
	/// √енерирует случайное целое число в указанных промежутках
	/// </summary>
	/// <param name="min">минимум (¬ Ћё„»“≈Ћ№Ќќ)</param>
	/// <param name="max">максимум (¬ Ћё„»“≈Ћ№Ќќ)</param>
	/// <returns></returns>
	int GetInt(int min, int max)
	{
		return  min + (rand() % static_cast<int>(max - min + 1));
	}
	/// <summary>
	/// √енерирует массив случайных целых чисел
	/// </summary>
	/// <param name="min">минимум (¬ Ћё„»“≈Ћ№Ќќ)</param>
	/// <param name="max">максимум (¬ Ћё„»“≈Ћ№Ќќ)</param>
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
	/// √енерирует случайное вещественное число в указанных промежутках
	/// </summary>
	/// <param name="min">минимум (¬ Ћё„»“≈Ћ№Ќќ)</param>
	/// <param name="max">максимум (¬ Ћё„»“≈Ћ№Ќќ)</param>
	/// <returns></returns>
	double GetDouble(double min, double max) {
		double value = (double)rand() / RAND_MAX;
		return min + value * (max - min);
	}
	/// <summary>
	/// √енерирует массив случайных вещественных чисел
	/// </summary>
	/// <param name="min">минимум (¬ Ћё„»“≈Ћ№Ќќ)</param>
	/// <param name="max">максимум (¬ Ћё„»“≈Ћ№Ќќ)</param>
	/// <param name="count">количество</param>
	/// <returns></returns>
	vector<double> GetDoubleArray(double min, double max, size_t count) {
		vector<double> items;
		for (int i = 0; i < count; i++)
			items.push_back(GetDouble(min, max));
		return items;
	}
	/// <summary>
	/// —оздает случайную строку указанной длинны
	/// </summary>
	/// <param name="length">длина</param>
	/// <param name="lang">€зык</param>
	/// <returns></returns>
	string GetStr(int length, Language lang = byDefault) {
		if (lang == ENG || lang == byDefault)
			return GetStr(length, Constants::Strings::Alphabets::eng);
		if (lang == RUS)
			return GetStr(length, Constants::Strings::Alphabets::rus);
		return "";
	}
	/// <summary>
	/// —оздает массив случайных строк указанной длины
	/// </summary>
	/// <param name="minlength">минимальна€ длина</param>
	/// <param name="maxlength">максимальна€ длина</param>
	/// <param name="count">количество</param>
	/// <param name="lang">€зык</param>
	/// <returns></returns>
	vector<string> GetStrArray(size_t minlength, size_t maxlength, size_t count, Language lang = byDefault) {
		vector<string> items;
		for (int i = 0; i < count; i++)
			items.push_back(GetStr(GetInt(minlength, maxlength), lang));
		return items;
	}
#pragma endregion
};