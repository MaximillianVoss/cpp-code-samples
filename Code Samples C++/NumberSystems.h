#pragma once
/// <summary>
/// Для перевода в разные системы счисления
/// </summary>
class NumberSystems
{
private:
	/// <summary>
	/// конвертирует число в строку
	/// </summary>
	/// <param name="value">число для конвертации</param>
	/// <returns></returns>
	char * ConvertIntToString(int value);
public:
	/// <summary>
	/// Получает символ по коду
	/// </summary>
	/// <param name="a">код символа</param>
	/// <returns></returns>
	char GetChar(int a);
	/// <summary>
	/// Получает код символа
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	int GetNum(char c);
	/// <summary>
	/// 
	/// </summary>
	NumberSystems();
	/// <summary>
	/// 
	/// </summary>
	~NumberSystems();
	/// <summary>
	/// Конвертирует число из десятичной 
	/// системы счисления в указанную систему счисления
	/// </summary>
	/// <param name="a">число</param>
	/// <param name="b">основание</param>
	/// <returns></returns>
	char * Convert(int a, int b);
	/// <summary>
	/// Конвертирует число из указанной системы счисления в 10ую
	/// </summary>
	/// <param name="value">значение</param>
	/// <param name="base">исходное основание</param>
	/// <returns></returns>
	int ConvertToDecimal(char * value, int base);
};

