#include "Stack.h"
#include "StrHelper.h"
#include <vector>
#include <string>
#pragma once
/// <summary>
/// Составляет обратную польскую запись выражения
/// </summary>
class PolandStr
{
private:
	/// <summary>
	/// поддерживаемые команды
	/// </summary>
	string commands = "";
	StrHelper strWizard = StrHelper();
public:
	/// <summary>
	/// Инициализирует генератор
	/// </summary>
	/// <param name="_commands">поддерживаемые команды, например "+-*/^()"</param>
	PolandStr(string _commands);
	/// <summary>
	/// Деструктор
	/// </summary>
	~PolandStr();
	/// <summary>
	/// получает приоритет команды
	/// </summary>
	/// <param name="command">команда</param>
	/// <returns>приоритет команды</returns>
	int GetPriority(string command);
	/// <summary>
	/// Вставляет строку в указанное место
	/// </summary>
	/// <param name="lexems">список лексем</param>
	/// <param name="idx">индекс</param>
	/// <param name="value">строка</param>
	/// <returns></returns>
	vector<string> Insert(vector<string> lexems, int idx, string value);
	/// <summary>
	/// Заменят лексемы
	/// -5 -> (-5)
	/// 5-6 -> 5+(-6)
	/// </summary>
	/// <param name="lexems"></param>
	/// <returns></returns>
	vector<string> LexemReplace(vector<string> lexems);
	/// <summary>
	/// составляет польскую запись для выражения
	/// https://goo.gl/eaph5V
	/// </summary>
	/// <param name="str">строка с выражением</param>
	/// <returns>обратная польская запись выражения</returns>
	vector<string> GetPolandStr(string str);
};

