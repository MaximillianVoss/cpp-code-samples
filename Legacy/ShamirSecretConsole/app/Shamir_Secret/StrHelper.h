#include "pch.h"
#pragma once
/// <summary>
/// класс для работы со строками
/// </summary>
class StrHelper
{
private:
public:
#pragma region Конструкторы
	StrHelper();
	~StrHelper();
#pragma endregion
#pragma region Методы
	/// <summary>
	/// Объединяет строки с списке в одну строку
	/// </summary>
	/// <param name="lines">список</param>
	/// <returns></returns>
	string Join(vector<string> lines);
	/// <summary>
	/// Объединяет строки с списке в одну строку
	/// </summary>
	/// <param name="lines">список</param>
	/// <param name="spacer">разделитель</param>
	/// <returns></returns>
	string Join(vector<string> lines, string spacer);
	/// <summary>
	/// Заменяет все вхождения
	/// указанной подстроки в строке
	/// </summary>
	/// <param name="s">исходная строка</param>
	/// <param name="search">искомая подстрока</param>
	/// <param name="replace">замена для подстроки</param>
	void ReplaceAll(string& s, const string& search, const string& replace);
	/// <summary>
	/// Заменяет все вхождения
	/// указанной подстроки в строке
	/// </summary>
	/// <param name="str">исходная строка</param>
	/// <param name="what">что заменять</param>
	/// <param name="replace">на что заменять</param>
	/// <returns></returns>
	string Replace(string str, string what, string replace);
	/// <summary>
	/// разбивает строку по разделителям
	/// </summary>
	/// <param name="str">строка</param>
	/// <param name="delimiters">строка с разделителями</param>
	/// /// <param name="notDelete">строка с элементами, которые не нужно удалять</param>
	/// <returns>массив строк</returns>
	vector<string> Split(string str, string delimiters, string notDelete);
	/// <summary>
	/// разбивает строку по разделителям
	/// </summary>
	/// <param name="str">строка</param>
	/// <param name="delimiters">строка с разделителями</param>
	/// /// <param name="notDelete">строка с элементами, которые не нужно удалять</param>
	/// <returns></returns>
	//vector<string> Split(string str, const string delimiters, const string notDelete);
	/// <summary>
	/// разбивает строку по разделителям
	/// </summary>
	/// <param name="str">строка</param>
	/// <param name="delimiter">разделитель</param>
	vector<string> Split(string str, char delimiter);
	/// <summary>
	/// Проверяет содержит ли строка указанные символы
	/// </summary>
	/// <param name="str">строка для проверки</param>
	/// <param name="collection">символы в одной строке</param>
	/// <returns></returns>
	bool Contains(string str, string collection);
	/// <summary>
	///
	/// </summary>
	/// <param name="str"></param>
	/// <param name="strFind"></param>
	/// <returns></returns>
	bool ContainsStr(string str, string strFind) {
		return (str.find(strFind) != std::string::npos);
	}
	/// <summary>
	/// Поверяет, является ли строка числом
	/// </summary>
	/// <param name="s">строка</param>
	/// <returns>true - если является числом</returns>
	bool IsNumber(string str);
	/// <summary>
	///
	/// </summary>
	/// <param name="values"></param>
	/// <returns></returns>
	vector<string> RemoveCopies(vector<string> values) {
		string valuesStr = "";
		for (int i = 0; i < values.size(); i++)
			if (!ContainsStr(valuesStr, values[i])) {
				valuesStr += values[i];
				valuesStr += " ";
			}
		values = Split(valuesStr, ' ');
		return values;
	}
	/// <summary>
	/// удаляет вхождения данного символа в строке
	/// </summary>
	/// <param name="str">строка</param>
	/// <param name="c">символ для удаления</param>
	/// <returns>строка с удаленными символами</returns>
	string Remove(string str, char c);
#pragma endregion
};
