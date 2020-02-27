#include "pch.h"
#pragma once
/// <summary>
/// Класс для работы со строками
/// </summary>
class StrHelper
{
private:
	/// <summary>
	/// Ищет вхождение указанноу подстроки в коллекции
	/// </summary>
	/// <param name="items">коллекция строк</param>
	/// <param name="str">подстрока</param>
	/// <returns></returns>
	bool Find(vector<string> items, string str) {
		for (string item : items)
			if (str == item)
				return true;
		return false;
	}
public:
#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// Конструктор
	/// </summary>
	StrHelper() {}
	/// <summary>
	/// Деструктор
	/// </summary>
	~StrHelper() {}
#pragma endregion
#pragma region Методы
	/// <summary>
	/// Объединяет строки с списке в одну строку
	/// </summary>
	/// <param name="lines">список</param>
	/// <param name="spacer">разделитель</param>
	/// <returns></returns>
	string Join(vector<string> lines, string spacer = "") {
		stringstream ss;
		for (int i = 0; i < lines.size(); i++)
		{
			ss << lines[i];
			if (i < lines.size() - 1)
				ss << spacer;
		}
		return ss.str();
	}
	/// <summary>
	/// Заменяет все вхождения 
	/// указанной подстроки в строке
	/// </summary>
	/// <param name="str">исходная строка</param>
	/// <param name="what">что заменять</param>
	/// <param name="replace">на что заменять</param>
	/// <returns></returns>
	string Replace(string str, string what, string replace) {
		while (str.find(what) != -1)
			str = str.replace(str.find(what), what.size(), replace);
		return str;
	}
	/// <summary>
	/// Удаляет вхождения данного символа в строке
	/// </summary>
	/// <param name="str">строка</param>
	/// <param name="subStr">подстрока для удаления</param>
	/// <returns>строка с удаленными символами</returns>
	string Remove(string str, string subStr) {
		size_t pos = string::npos;
		while ((pos = str.find(subStr)) != std::string::npos)
			str.erase(pos, subStr.length());
		return str;
	}
	/// <summary>
	/// Проверяет содержит ли строка указанную коллекцию строк
	/// </summary>
	/// <param name="str">строка для проверки</param>
	/// <param name="collection">коллекция строк</param>
	/// <returns>true - если содержит все символы</returns>
	bool Contains(string str, vector<string> collection) {
		for (int i = 0; i < collection.size(); i++)
			if (!this->Contains(str, collection[i]))
				return false;
		return true;
	}
	/// <summary>
	/// Проверяет содержит ли строка указанную подстроку
	/// </summary>
	/// <param name="str">строка для проверки</param>
	/// <param name="strFind">подстрока</param>
	/// <returns>true - если содержит</returns>
	bool Contains(string str, string subStr) {
		return (str.find(subStr) != std::string::npos);
	}
	/// <summary>
	/// Поверяет, является ли строка числом
	/// </summary>
	/// <param name="s">строка</param>
	/// <returns>true - если является числом</returns>
	bool IsNumber(string str) {
		/*if (str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+')))
			return false;
		char* p;
		strtol(str.c_str(), &p, 10);
		return (*p == 0);*/
		return this->GetNumbers(str).size() == 1;
	}
	/// <summary>
	/// находит все числа в указанной строке
	/// </summary>
	/// <param name="str">строка с числами и другими литералами</param>
	/// <returns>список чисел</returns>
	vector<string> GetNumbers(string str) {
		vector<string>result;
		regex rx(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))");
		smatch m;
		while (regex_search(str, m, rx)) {
			result.push_back(m[1]);
			str = m.suffix().str();
		}
		return result;
	}
	/// <summary>
	/// разбивает строку по разделителям
	/// </summary>
	/// <param name="str">строка</param>
	/// <param name="delimiters">строка с разделителями</param>
	/// /// <param name="notDelete">строка с элементами, которые не нужно удалять</param>
	/// <returns>массив строк</returns>
	vector<string> Split(string str, string delimiters, string notDelete = "") {
		string buffer = "";
		vector<string> res;
		for (int i = 0; i < str.size(); i++)
		{
			char c = str[i];
			if (delimiters.find(c) == string::npos)
				buffer += c;
			else if (buffer.length() > 0) {
				res.push_back(buffer);
				buffer = "";
			}
			if (notDelete.find(c) != string::npos) {
				string temp;
				temp += c;
				res.push_back(temp);
			}
		}
		if (buffer.length() > 0) {
			res.push_back(buffer);
			buffer = "";
		}
		return res;
	}
	/// <summary>
/// 
/// </summary>
/// <param name="values"></param>
/// <returns></returns>
	vector<string> RemoveCopies(vector<string> values) {
		vector<string>result;
		for (string item : values)
			if (!this->Find(result, item))
				result.push_back(item);
		return result;
	}
#pragma endregion
};