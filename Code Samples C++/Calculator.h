#pragma once
#include "Stack.h"
#include "StrHelper.h"
#include "PolandStr.h"
#include <vector>
#include <string>
/// <summary>
/// —троковый калькул€тор
/// </summary>
class Calculator
{
private:
	/// <summary>
	/// флаг переполнени€
	/// </summary>
	bool overflow;
	/// <summary>
	/// поддерживаемые команды
	/// например:"+-*/^()"
	/// </summary>
	string commands = "";
	/// <summary>
	/// дл€ работы со строками
	/// </summary>
	StrHelper strWizard = StrHelper();
	/// <summary>
	/// дл€ составлени€ польской записи
	/// </summary>
	PolandStr polandStr = PolandStr(commands);
	/// <summary>
	/// вычисл€ет результат операции
	/// </summary>
	/// <param name="sa">первый операнд</param>
	/// <param name="sb">второй операнд</param>
	/// <param name="op">знак операции</param>
	/// <returns>результат операции в строковом виде, если ошибка вернет 0</returns>
	string MakeOpeartion(string sa, string sb, string op);
	/// <summary>
	/// ¬ыполнить целочисленную операцию
	/// </summary>
	/// <param name="sa">операнд 1</param>
	/// <param name="sb">операнд 2</param>
	/// <param name="op">знак операции</param>
	/// <returns></returns>
	string MakeOpeartionInt(string sa, string sb, string op);
public:
	/// <summary>
	/// »нициализирует калькул€тор
	/// </summary>
	/// <param name="_commands">ѕоддерживаемые команды, например:"+-*/^()"</param>
	Calculator(string _commands);
	/// <summary>
	/// деструктор
	/// </summary>
	~Calculator();
	/// <summary>
	/// ¬ычисл€ет  выражение 
	/// </summary>
	/// <param name="str">выражение, записанное в обратной польской записи</param>
	/// <param name="result">переменна€ дл€ хранени€ результата</param>
	/// <returns>true - если вычислени€ прошли успешно(нет переполнени€)</returns>
	bool Calculator::Calc(string str, double *result);
};

