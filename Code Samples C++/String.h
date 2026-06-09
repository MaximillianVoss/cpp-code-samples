#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#pragma region Type String

class String
{

private:

#pragma region Поля

#pragma endregion

#pragma region Методы
	int GetCharIndex(char* str, char c)
	{
		if (str != NULL)
		{
			for (size_t i = 0; i < strlen(str); i++)
				if (str[i] == c)
					return i;
		}
		return -1;
	}
	bool IsStringSimpleContains(char* str, char c)
	{
		if (str == NULL)
			return false;
		for (size_t i = 0; i < strlen(str); i++)
		{
			if (str[i] == c)
				return true;
		}
		return false;
	}
	bool IsStringContains(String* str, char c)
	{
		if (str == NULL)
			return false;
		return IsStringSimpleContains(str->symbols, c);
	}
#pragma endregion

public:

#pragma region Поля
	char* symbols;
	size_t length;
#pragma endregion

#pragma region Методы

	int GetLength()
	{
		if (this == NULL)
			return 0;
		int length = 0;
		for (int i = 0;; i++)
		{
			if (this->symbols[i] == '\0')
				break;
			length++;
		}
		return length;
	}

	String Copy(String str)
	{
		String result;
		result.length = str.GetLength();
		result.symbols = (char*)calloc(result.length + 1, sizeof(char));
		for (int i = 0; i < result.length; i++)
		{
			result.symbols[i] = str.symbols[i];
		}
		return result;
	}

	int Compare(String str1, String str2)
	{
		if (str1.length > str2.length)
		{
			return 1;
		}
		else if (str1.length < str2.length)
		{
			return -1;
		}
		else
		{
			for (int i = 0; i < str1.length; i++)
			{
				if (str1.symbols[i] > str2.symbols[i])
				{
					return 1;
				}
				else if (str1.symbols[i] < str2.symbols[i])
				{
					return -1;
				}
			}
			return 0;
		}
	}

	void Add(char c)
	{
		if (this->length == 0)
		{
			this->~String();
			this->symbols = (char*)calloc(2, sizeof(char));
			this->length += 2;
		}
		else
		{
			this->symbols = (char*)realloc(this->symbols, (++(this->length)) * sizeof(char));
		}
		this->symbols[this->length - 2] = c;
		this->symbols[this->length - 1] = '\0';
	}

	bool IsNumber()
	{
		if (this == NULL)
			return false;
		String signs = String("+-");
		String digits = String("1234567890");
		String delimiters = String(".,");
		String alphabet = String("+-.,1234567890");
		int delimitersCount = 0;
		int signsCount = 0;
		int digitCount = 0;
		for (size_t i = 0; i < this->GetLength(); i++)
		{
			char currentChar = this->symbols[i];
#pragma region Знаки
			if (IsStringSimpleContains(signs.symbols, currentChar))
			{
				signsCount++;
				if (i != 0)
					return false;
				if (digitCount > 0)
					return false;
				if (signsCount > 1)
					return false;
			}
#pragma endregion

#pragma region Разделители
			if (IsStringSimpleContains(delimiters.symbols, currentChar))
			{
				delimitersCount++;
				if (delimitersCount > 1)
					return false;
				if (i == 0)
					return false;
				if (digitCount < 1)
					return false;
				if (i == (this->GetLength() - 1))
					return false;
			}
#pragma endregion

#pragma region Цифры
			if (currentChar == '0' && digitCount == 0)
				return false;
			if (IsStringSimpleContains(digits.symbols, this->symbols[i]))
			{
				digitCount++;
			}
#pragma endregion

			if (!IsStringSimpleContains(alphabet.symbols, this->symbols[i]))
				return false;
		}
		if ((signsCount > 0 || delimitersCount > 0) && digitCount == 0)
			return false;
		return true;
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	String(size_t length = 0)
	{
		this->symbols = (char*)calloc(length, sizeof(char));
		this->length = length;
	}
	String(bool b)
	{
		b == true ? this->Copy("true") : Copy("false");
	}
	~String()
	{
		free(this->symbols);
	}
#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion




};

#pragma endregion