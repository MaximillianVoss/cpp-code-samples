#include "stdafx.h"
#include "Calculator.h"
#include "PolandStr.h"

Calculator::Calculator(string _commands)
{
	overflow = false;
	commands = _commands;
}

Calculator::~Calculator()
{
}
/// <summary>
/// проверка на переполнение
/// </summary>
/// <param name="a">операнд 1</param>
/// <param name="b">операнд 2</param>
/// <param name="operation">знак операции(1 символ)</param>
/// <returns>true - если есть переполнение</returns>
bool CheckOveflow(int a, int b, char operation) {
	switch (operation)
	{
	case '+':
		if (((b > 0) && (a > (INT_MAX - b))) ||
			((b < 0) && (a < (INT_MIN - b))))
			return true;
		break;
	case'-':
		if ((b > 0 && a < INT_MIN + b) ||
			(b < 0 && a > INT_MAX + b))
			return true;
		break;
	case'*':
		if (a > 0) {
			if (b > 0) {
				if (a > (INT_MAX / b))
					return true;
			}
			else {
				if (b < (INT_MIN / a))
					return true;
			}
		}
		else {
			if (b > 0) {
				if (a < (INT_MIN / b))
					return true;
			}
			else {
				if ((a != 0) && (b < (INT_MAX / a)))
					return true;
			}
		}
		break;
	case'/':
		if ((b == 0) || ((a == LONG_MIN) && (b == -1)))
			return true;
		break;
	default:
		return false;
	}
	return false;
}
/// <summary>
/// вычисляет результат операции
/// </summary>
/// <param name="sa">первый операнд</param>
/// <param name="sb">второй операнд</param>
/// <param name="op">знак операции</param>
/// <returns>результат операции в строковом виде, если ошибка вернет 0</returns>
string Calculator::MakeOpeartion(string sa, string sb, string op) {
	double result = 0;
	double a = stod(sa.c_str());
	double b = stod(sb.c_str());
	if (op == "+")
		result = a + b;
	if (op == "-")
		result = a - b;
	if (op == "*")
		result = a * b;
	if (op == "/")
		result = a / b;
	if (op == "^")
		result = pow(a, b);
	overflow = CheckOveflow(a, b, op.c_str()[0]);
	overflow = abs(result) > pow(2, 31);
	return std::to_string(result);
}
/// <summary>
/// вычисляет результат операции
/// </summary>
/// <param name="sa">первый операнд</param>
/// <param name="sb">второй операнд</param>
/// <param name="op">знак операции</param>
/// <returns>результат операции в строковом виде, если ошибка вернет 0</returns>
string Calculator::MakeOpeartionInt(string sa, string sb, string op) {
	double result = 0;
	double a = stod(sa.c_str());
	double b = stod(sb.c_str());
	if (op == "+")
		result = a + b;
	if (op == "-")
		result = a - b;
	if (op == "*")
		result = a * b;
	if (op == "/")
		result = a / b;
	if (op == "^")
		result = pow(a, b);
	overflow = CheckOveflow(a, b, op.c_str()[0]);
	overflow = abs(result) > pow(2, 31);
	return std::to_string((int)result);
}
/// <summary>
/// Вычисляет  выражение 
/// </summary>
/// <param name="str">выражение, записанное в обратной польской записи</param>
/// <param name="result">переменная для хранения результата</param>
/// <returns>true - если вычисления прошли успешно(нет переполнения)</returns>
bool Calculator::Calc(string str, double *result) {
	Stack stack;
	vector<string> lexems = polandStr.GetPolandStr(str);
	string commands = "+-*/^() ";
	for each (string lexem in lexems)
	{
		if (commands.find(lexem) == string::npos)
			stack.Push(lexem);
		else
			stack.Push(MakeOpeartionInt(stack.Pop(), stack.Pop(), lexem));
	}
	double res = stod(stack.Pop().c_str());
	if (res == -0)
		res = abs(res);

	*result = (int)res;
	return !overflow;
}
