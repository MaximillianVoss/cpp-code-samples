#pragma once
#include "pch.h"
/// <summary>
/// Клиент блокчейна
/// </summary>
class Client
{
private:
public:
	/// <summary>
	/// ИД
	/// </summary>
	string id;
	/// <summary>
	/// Статус в сети:да/нет
	/// </summary>
	bool isOnline;
	/// <summary>
	/// 
	/// </summary>
	Client() {}
	/// <summary>
	/// Создает клиента с указанным ID
	/// </summary>
	/// <param name="id">ИД</param>
	Client(string id) {
		this->id = id;
	}
	/// <summary>
	/// 
	/// </summary>
	~Client() {}
};

