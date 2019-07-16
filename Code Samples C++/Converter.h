#include "NumberSystems.h"
#pragma once
class Converter
{
private:
	NumberSystems ns;
public:
	Converter();
	~Converter();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	int Convert(char c);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	char Convert(int a);
	/// <summary>
	/// конвертирует указанную 
	/// строку с цифрами в массив цифр
	/// </summary>
	/// <param name="str">строка</param>
	/// <returns></returns>
	vector<int> Convert(const char * str);
	/// <summary>
	/// конвертирует указанный массив символами цифр 
	/// в массив цифр
	/// </summary>
	/// <param name="str">массив символов(цифы)</param>
	/// <returns></returns>
	vector<int> Convert(vector<char> str);
	/// <summary>
	/// Конвертирует число из десятичной 
	/// системы счисления в указанную систему счисления
	/// </summary>
	/// <param name="value">число</param>
	/// <param name="base">основание СС</param>
	/// <returns></returns>
	char* Convert(int value, int base);
	/// <summary>
	/// Конвертирует число из указанной системы счисления в десятичную
	/// </summary>
	/// <param name="value">строка, содержащая число</param>
	/// <param name="base">исходное основание</param>
	/// <returns></returns>
	int Convert(char *value, int base);
};

