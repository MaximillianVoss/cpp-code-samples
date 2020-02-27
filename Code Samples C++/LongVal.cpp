#include "stdafx.h"
#include "LongVal.h"
#pragma region Конструкторы/Деструкторы
LongVal::LongVal()
{
	Init("0");
}

LongVal::LongVal(string str)
{
	Init(str);
}

LongVal::LongVal(vector<int> items)
{
	negative = false;
	Init(items);
}

LongVal::LongVal(vector<int> items, bool _negative)
{
	Init(items);
	negative = _negative;
}

LongVal::LongVal(int _length) {
	values = vector<int>(_length);
	length = _length;
}

LongVal::~LongVal()
{
}
#pragma endregion

#pragma region Методы
string LongVal::ToStr()
{
	string str = "";
	if (negative)
		str += '-';
	for (int i = 0; i < length; i++)
		str += to_string(values[i]);
	return str;
}

void LongVal::Init(int _length)
{
	values = vector<int>(_length);
	length = _length;
	//negative = false;
}

void LongVal::Init(string str)
{
	if (str.length() > 0) {
		if (str[0] == '-')
		{
			negative = true;
			str.erase(0, 1);
		}
		else
			negative = false;
		Init(str.length());
		for (size_t i = 0; i < str.length(); i++)
			values[i] = int(str[i]) - int('0');
	}
}

void LongVal::Init(vector<int> items)
{
	string str = "";
	for (int item : items)
		str += to_string(item);
	Init(str);
}

void LongVal::Init(vector<int> items, bool _negative)
{
	Init(items);
	negative = _negative;
}

void LongVal::PushBack(int value)
{
	values.push_back(value);
	length = values.size();
}

void LongVal::PushFront(int value)
{
	values.insert(values.begin(), value);
	length = values.size();
}

void LongVal::SetLength(int newLength)
{
	if (values.size() < newLength)
	{
		int oldLength = values.size();
		for (int i = 0; i < newLength - oldLength; i++)
			PushFront(0);
	}

}

int LongVal::GetLength()
{
	return length;
}
#pragma endregion