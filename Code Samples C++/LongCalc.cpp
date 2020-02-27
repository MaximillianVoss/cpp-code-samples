#include "stdafx.h"
#include "LongCalc.h"

LongCalc::LongCalc()
{
}

LongCalc::~LongCalc()
{
}

LongVal LongCalc::Sum(LongVal a, LongVal b)
{
	return a + b;
}

LongVal LongCalc::Sum(string a, string b)
{
	return Sum(LongVal(a), LongVal(b));
}

LongVal LongCalc::Sub(LongVal a, LongVal b)
{
	return string();
}

LongVal LongCalc::Sub(string a, string b)
{
	return Sub(LongVal(a), LongVal(b));
}

LongVal LongCalc::Div(LongVal a, LongVal b)
{
	return string();
}

LongVal LongCalc::Div(string a, string b)
{
	return Div(LongVal(a), LongVal(b));
}

LongVal LongCalc::Mul(LongVal a, LongVal b)
{
	return string();
}

LongVal LongCalc::Mul(string a, string b)
{
	return Mul(LongVal(a), LongVal(b));
}

LongVal LongCalc::Mod(LongVal a, LongVal b)
{
	return string();
}

LongVal LongCalc::Mod(string a, string b)
{
	return Mod(LongVal(a), LongVal(b));
}
