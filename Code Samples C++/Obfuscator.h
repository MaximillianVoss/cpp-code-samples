#include "stdafx.h"
#pragma once
class Obfuscator
{
private:
#pragma region Константы
	const string input = "input";
	const string output = "output";
	const string keywords = "keywords";
	const string dummy = "dummy";
#pragma endregion
#pragma region Поля
	string configFileName = "config.txt";
	string inputFileName = "";
	string outputFileName = "";
	string dummyFileName = "";
	string keyWordsFileName = "";
#pragma endregion
#pragma region Методы
	/// <summary>
	/// Удаление символов табуляции
	/// </summary>
	/// <param name="a">массив со строками</param>
	/// <returns>строки с удаленной табуляцией</returns>
	vector<string> RemoveTabs(vector<string> a);
	/// <summary>
	/// переименование переменных
	/// </summary>
	/// <param name="a">список строк</param>
	/// <returns></returns>
	vector<string> RenameVariables(vector<string> a);
	/// <summary>
	/// Добавляет подставные функции и переменные
	/// </summary>
	/// <param name="a">список строк</param>
	/// <returns></returns>
	vector<string> AddDummyVariables(vector<string> a);
	/// <summary>
	/// Обфусцирует код
	/// </summary>
	/// <returns>измененый список строк</returns>
	vector<string> Obfuscate(vector<string> a);
#pragma endregion
public:
#pragma region Поля

#pragma endregion
#pragma region Конструктор/Деструктор 
	/// <summary>
	/// Создает обфукатор
	/// </summary>
	/// <param name="_configFileName">путь до файла конфигурации</param>
	Obfuscator(string _configFileName);
	~Obfuscator();
#pragma endregion
#pragma region Методы

	/// <summary>
	/// Обфусцирует указанный файл с кодом
	/// </summary>
	/// <param name="inFileName">имя входного файла</param>
	/// <param name="outFileName">имя выходного файла</param>
	void Obfuscate();
#pragma endregion
};

