#pragma once
#include "Stack.h"
#include "StrHelper.h"
#include "PolandStr.h"
#include <vector>
#include <string>
/// <summary>
/// Строковый калькулятор
/// </summary>
class Calculator
{
private:
	/// <summary>
	/// флаг переполнения
	/// </summary>
	bool overflow;
	/// <summary>
	/// поддерживаемые команды
	/// например:"+-*/^()"
	/// </summary>
	string commands = "";
	/// <summary>
	/// для работы со строками
	/// </summary>
	StrHelper strWizard = StrHelper();
	/// <summary>
	/// для составления польской записи
	/// </summary>
	PolandStr polandStr = PolandStr(commands);
	/// <summary>
	/// вычисляет результат операции
	/// </summary>
	/// <param name="sa">первый операнд</param>
	/// <param name="sb">второй операнд</param>
	/// <param name="op">знак операции</param>
	/// <returns>результат операции в строковом виде, если ошибка вернет 0</returns>
	string MakeOpeartion(string sa, string sb, string op);
	/// <summary>
	/// Выполнить целочисленную операцию
	/// </summary>
	/// <param name="sa">операнд 1</param>
	/// <param name="sb">операнд 2</param>
	/// <param name="op">знак операции</param>
	/// <returns></returns>
	string MakeOpeartionInt(string sa, string sb, string op);
public:
	/// <summary>
	/// Инициализирует калькулятор
	/// </summary>
	/// <param name="_commands">Поддерживаемые команды, например:"+-*/^()"</param>
	Calculator(string _commands);
	/// <summary>
	/// деструктор
	/// </summary>
	~Calculator();
	/// <summary>
	/// Вычисляет  выражение 
	/// </summary>
	/// <param name="str">выражение, записанное в обратной польской записи</param>
	/// <param name="result">переменная для хранения результата</param>
	/// <returns>true - если вычисления прошли успешно(нет переполнения)</returns>
	bool Calculator::Calc(string str, double *result);
};

