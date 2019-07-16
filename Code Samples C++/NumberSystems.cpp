#include "stdafx.h"
#include "NumberSystems.h"

NumberSystems::NumberSystems()
{
}

NumberSystems::~NumberSystems()
{
}

char NumberSystems::GetChar(int a)
{
	if (a >= 10)
		return (char)('A' + (a - 10));
	else if (a < 0)
		return '-';
	else
		return (char)('0' + a);
}

int NumberSystems::GetNum(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (int)(c - 'A' + 10);
	else if (c >= '0' && c <= '9')
		return (int)(c - '0');
	else
		return -1;
}

char* NumberSystems::Convert(int a, int b)
{
	if (b > 1)
	{
		int *temp = (int*)malloc(sizeof(int));
		int i = 0;
		while (a > 0)
		{
			temp[i] = a % b;
			a /= b;
			if (a > 0)
			{
				i++;
				temp = (int*)realloc(temp, sizeof(int)*(i + 1));
			}
		}
		char * result = (char*)malloc(sizeof(char)*i + 1);
		int length = i;
		for (i; i >= 0; i--)
			result[length - i] = GetChar(temp[i]);
		result[length + 1] = '\0';
		return result;
	}
	else
	{
		throw exception("Основание должно быть больше 1\n");
	}
}

int NumberSystems::ConvertToDecimal(char * value, int base)
{
	int result = 0;
	for (size_t i = 0; i < strlen(value); i++)
	{
		int item = GetNum(value[strlen(value) - i - 1]);
		if (item >= 0)
			result += item * pow(base, i);
		else
			throw exception("Обнаружены недопустимые символы!");
	}
	return result;
}

char* NumberSystems::ConvertIntToString(int value)
{
	char * result = (char*)malloc(sizeof(char));
	int i = 0;
	while (value > 0)
	{
		int r = value % 10;
		result[i] = (char)(r + '0');
		result = (char*)realloc(result, sizeof(char)*(strlen(result) + 1));
		value /= 10;
		i++;
	}
	result = (char*)realloc(result, sizeof(char)*(strlen(result) + 1));
	result[strlen(result)] = '\0';
	return result;
}
