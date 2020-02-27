#include "stdafx.h"
#include "PairStr.h"

#pragma region Конструкторы/Деструкторы
PairStr::PairStr()
{
}

PairStr::PairStr(string _key, string _value)
{
	key = _key;
	value = _value;
}

PairStr::~PairStr()
{
}
string PairStr::GetStr()
{
	return "key:" + key + ' ' + "value:" + value;
}
#pragma endregion