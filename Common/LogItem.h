
#pragma once
#include "pch.h"
using namespace chrono;
///<summary>
/// Залогированное сообщение
///</summary>
class LogItem
{
private:

#pragma region Поля
	/// <summary>
	/// ИД
	/// </summary>
	int id;
	/// <summary>
	/// время записи
	/// </summary>
	string time;
	/// <summary>
	/// строки сообщения
	/// </summary>
	vector<string>lines;
#pragma endregion

#pragma region Методы
	string GetTime() {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
		high_resolution_clock::time_point p = high_resolution_clock::now();
		milliseconds ms = duration_cast<milliseconds>(p.time_since_epoch());
		size_t fractional_seconds = ms.count() % 1000;
		oss << ":" << fractional_seconds;
		return oss.str();
	}
#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	string ToString() {
		stringstream ss;
		ss << this->time << endl;
		for (string line : this->lines)
			ss << line << endl;
		return ss.str();
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	LogItem() {
		this->id = -1;
		this->lines = {};
		this->time = this->GetTime();
	};
	LogItem(int id = -1, vector<string>lines = {}) {
		this->id = id;
		this->lines = lines;
		this->time = this->GetTime();
	};
	LogItem(int id, string message) {
		this->id = id;
		this->lines = { message };
		this->time = this->GetTime();
	}
	~LogItem() {
	};
#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion



};

#pragma region Операторы
ostream& operator<<(ostream& os, LogItem item)
{
	os << item.ToString();
	return os;
}
#pragma endregion

