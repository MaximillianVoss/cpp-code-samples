#include "pch.h"
#pragma once
/// <summary>
/// Строки для сообщений
/// </summary>
class Messages {

};
/// <summary>
/// Строки для исключений
/// </summary>
class Exceptions {
public:
	static constexpr const char* notImplemented = "метод не раелизован";
	static constexpr const char* incorrectIndex = "некоррекнтый индекс";
	static constexpr const char* incorrectSize = "некорректный размер";
	static constexpr const char* incorrectValue = "некорректное значение";
};