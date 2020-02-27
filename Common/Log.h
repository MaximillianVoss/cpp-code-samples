
#pragma once
#include "pch.h"
#include "LogItem.h"
///<summary>
/// Логирует сообщения
///</summary>
class Log
{
private:

#pragma region Поля
	/// <summary>
	/// Лимит сообшений лога
	/// </summary>
	size_t logLimit;
	/// <summary>
	/// записи
	/// </summary>
	vector<LogItem> items;
	/// <summary>
	/// текущий Id элемента
	/// </summary>
	int currentItemId;
	/// <summary>
	/// Разделитель сообщений лога
	/// </summary>
	string logSpacer = "__________________";
#pragma endregion

#pragma region Методы

#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	void Add(string message) {
		this->items.push_back(LogItem(this->currentItemId++, message));
	}
	void Add(vector<string> lines) {
		this->items.push_back(LogItem(this->currentItemId++, lines));
	}
	void Add(LogItem item) {
		if (this->GetCount() > this->logLimit)
			this->Clear();
		this->items.push_back(item);
	}
	int GetCount() {
		return this->items.size();
	}
	void Clear() {
		this->items.clear();
	}
	string ToString() {
		stringstream ss;
		for (LogItem item : this->items)
		{
			ss << this->logSpacer << endl;
			ss << item << endl;
			ss << this->logSpacer << endl;
		}
		return ss.str();
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	Log(int limit = 1000) {
		this->logLimit = limit;
		this->currentItemId = 1;
	};
	~Log() {};
#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion



};
#pragma region Операторы
ostream& operator<<(ostream& os, Log log)
{
	os << log.ToString();
	return os;
}
#pragma endregion