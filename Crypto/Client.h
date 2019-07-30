#pragma once
#include "pch.h"
/// <summary>
/// Клиент блокчейна
/// </summary>
class Client
{
private:
	/// <summary>
	/// секретная фраза для генерации ключа
	/// </summary>
	string phrase;
	/// <summary>
	/// секретный ключ
	/// </summary>
	string key;
public:
	/// <summary>
	/// Статус в сети:да/нет
	/// </summary>
	bool isOnline;
	/// <summary>
	/// Создает клиента с указанным ID
	/// </summary>
	/// <param name="id">ИД</param>
	Client(string key = "", string phrase = "") {
		this->isOnline = false;
		this->key = key;
		this->phrase = phrase;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	string GetKey() {
		return this->key;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	void SetKey(string key) {
		this->key = key;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	string GetPhrase() {
		return this->phrase;
	}
	/// <summary>
	/// 
	/// </summary>
	~Client() {}
};

#pragma region Операторы
bool operator==(Client& c1, Client& c2) {
	return c1.GetKey() == c2.GetKey();
}
#pragma endregion

