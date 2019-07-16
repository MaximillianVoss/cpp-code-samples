#include "stdafx.h"
#include "Converter.h"

#pragma region Конструктор/Деструктор

Converter::Converter()
{
}

Converter::~Converter()
{
}

#pragma endregion

#pragma region Методы

int Converter::Convert(char c)
{
	return ns.GetNum(c);
}

char Converter::Convert(int a)
{
	return ns.GetChar(a);
}

vector<int> Converter::Convert(const char * str)
{
	vector<int> res;
	for (int i = 0; i < strlen(str); i++)
		res.push_back(Convert(str[i]));
	return res;
}

vector<int> Converter::Convert(vector<char> str)
{
	string temp = "";
	for (char c : str)
		temp += c;
	return Convert(temp.c_str());

}

char * Converter::Convert(int value, int base)
{
	return ns.Convert(value, base);
}

int Converter::Convert(char * value, int base)
{
	return ns.ConvertToDecimal(value, base);
}

#pragma endregion
