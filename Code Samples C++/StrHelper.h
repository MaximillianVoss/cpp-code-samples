#pragma once
/// <summary>
/// класс дл€ работы со строками
/// </summary>
class StrHelper
{
private:
public:
#pragma region  онструкторы
	StrHelper();
	~StrHelper();
#pragma endregion
#pragma region ћетоды
	/// <summary>
	/// ќбъедин€ет строки с списке в одну строку
	/// </summary>
	/// <param name="lines">список</param>
	/// <returns></returns>
	string Join(vector<string> lines);
	/// <summary>
	/// ќбъедин€ет строки с списке в одну строку
	/// </summary>
	/// <param name="lines">список</param>
	/// <param name="spacer">разделитель</param>
	/// <returns></returns>
	string Join(vector<string> lines, string spacer);
	/// <summary>
	/// «амен€ет все вхождени€ 
	/// указанной подстроки в строке
	/// </summary>
	/// <param name="s">исходна€ строка</param>
	/// <param name="search">искома€ подстрока</param>
	/// <param name="replace">замена дл€ подстроки</param>
	void ReplaceAll(string & s, const string & search, const string & replace);
	/// <summary>
	/// «амен€ет все вхождени€ 
	/// указанной подстроки в строке
	/// </summary>
	/// <param name="str">исходна€ строка</param>
	/// <param name="what">что замен€ть</param>
	/// <param name="replace">на что замен€ть</param>
	/// <returns></returns>
	string Replace(string str, string what, string replace);
	/// <summary>
	/// разбивает строку по разделител€м
	/// </summary>
	/// <param name="str">строка</param>
	/// <param name="delimiters">строка с разделител€ми</param>
	/// /// <param name="notDelete">строка с элементами, которые не нужно удал€ть</param>
	/// <returns>массив строк</returns>
	vector<string> Split(string str, string delimiters, string notDelete);
	/// <summary>
	/// разбивает строку по разделител€м
	/// </summary>
	/// <param name="str">строка</param>
	/// <param name="delimiters">строка с разделител€ми</param>
	/// /// <param name="notDelete">строка с элементами, которые не нужно удал€ть</param>
	/// <returns></returns>
	//vector<string> Split(string str, const string delimiters, const string notDelete);
	/// <summary>
	/// разбивает строку по разделител€м
	/// </summary>
	/// <param name="str">строка</param>
	/// <param name="delimiter">разделитель</param>
	vector<string> Split(string str, char delimiter);
	/// <summary>
	/// ѕровер€ет содержит ли строка указанные символы
	/// </summary>
	/// <param name="str">строка дл€ проверки</param>
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
	/// ѕовер€ет, €вл€етс€ ли строка числом
	/// </summary>
	/// <param name="s">строка</param>
	/// <returns>true - если €вл€етс€ числом</returns>
	bool IsNumber(const std::string & s);
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
	/// удал€ет вхождени€ данного символа в строке
	/// </summary>
	/// <param name="str">строка</param>
	/// <param name="c">символ дл€ удалени€</param>
	/// <returns>строка с удаленными символами</returns>
	string Remove(string str, char c);
#pragma endregion
};

