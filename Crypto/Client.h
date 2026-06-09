#pragma once
#include "pch.h"
/// <summary>
/// Клиент блокчейна
/// </summary>
class Client
{
private:

#pragma region Поля
	/// <summary>
	/// ID в виде хэш SHA-1
	/// </summary>
	string id;
	/// <summary>
	/// Пароль в виде хэш SHA-1
	/// </summary>
	string hash;
	/// <summary>
	/// количество токенов на счету
	/// </summary>
	int tokensCount;
	/// <summary>
	/// Статус в сети:да/нет
	/// </summary>
	bool isOnline;
	/// <summary>
	/// Количество голосов за данного клиента (используется в голосовании)
	/// </summary>
	size_t votesCount;
	/// <summary>
	/// Процент голосов, 
	/// который набрал клиент в голосовании
	/// </summary>
	float votesPercent;
	/// <summary>
	/// Вероятность получения токена (используется в голосовании)
	/// Например: от 0.2
	/// </summary>
	float probability;
	/// <summary>
	/// Начало промежутка в цепочке вероятностей (используется в голосовании)
	/// Например: от 0.1
	/// </summary>
	float probabilityFrom;
	/// <summary>
	/// Конец промежутка в цепочке вероятностей (используется в голосовании)
	/// Например: до 0.3
	/// </summary>
	float probabilityTo;
#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Конструкторы
	/// <summary>
	/// Конструктор по умолчанию
	/// </summary>
	Client() :Client("", "") {
	}
	/// <summary>
	/// Создает клиента с указанным ID
	/// </summary>
	/// <param name="id">ID в виде хэш SHA-1</param>
	/// /// <param name="hash">Пароль в виде хэш SHA-1</param>
	Client(string id, string hash) {
		this->isOnline = false;
		this->id = id;
		this->hash = hash;
		this->tokensCount = 0;
		this->votesCount = 0;
		this->probability = 0;
		this->probabilityFrom = 0;
		this->probabilityTo = 0;
		this->votesPercent = 0;
	}
	/// <summary>
	/// Деструктор
	/// </summary>
	~Client() {}
#pragma endregion

#pragma region Методы

#pragma region Set
	/// <summary>
	/// Задает хэш ID
	/// </summary>
	/// <param name="id"></param>
	void SetId(string id) {
		this->id = id;
	}
	/// <summary>
	/// Задает хэш пароля
	/// </summary>
	/// <param name="key"></param>
	void SetHash(string hash) {
		this->hash = hash;
	}
	/// <summary>
	/// Задает количество токенов в кошельке
	/// </summary>
	/// <param name="tokensCount"></param>
	void SetTokensCount(int tokensCount) {
		this->tokensCount = tokensCount;
	}
	/// <summary>
	/// Устанавливает статус "в сети"
	/// </summary>
	/// <param name="isOnline">true - онлайн</param>
	void SetOnline(bool isOnline) {
		this->isOnline = isOnline;
	}
	/// <summary>
	/// Устанавливает указанное количество голосов
	/// </summary>
	/// <param name="votesCount">количество голосов</param>
	void SetVotes(size_t votesCount) {
		this->votesCount = votesCount;
	}
	/// <summary>
	/// Задает вероятность получения токена (используется в голосовании)
	/// </summary>
	/// <param name="probability">вероятность</param>
	void SetProbability(float probability) {
		this->probability = probability;
	}
	/// <summary>
	/// Задает начало промежутка в цепочке вероятностей (используется в голосовании)
	/// </summary>
	/// <param name="probability">вероятность</param>
	void SetProbabilityFrom(float probability) {
		this->probabilityFrom = probability;
	}
	/// <summary>
	/// Задает конец промежутка в цепочке вероятностей (используется в голосовании)
	/// </summary>
	/// <param name="probability">вероятность</param>
	void SetProbabilityTo(float probability) {
		this->probabilityTo = probability;
	}
	/// <summary>
	/// Задает процент голосов, 
	/// который набрал клиент в голосовании
	/// </summary>
	/// <param name="votesPercent">процент голосов</param>
	void SetVotesPercent(float votesPercent) {
		this->votesPercent = votesPercent;
	}
#pragma endregion

#pragma region Get
	/// <summary>
	/// Возвращает хэш ID
	/// </summary>
	/// <returns></returns>
	string GetId() const {
		return this->id;
	}
	/// <summary>
	/// Получает хэш пароля
	/// </summary>
	/// <returns></returns>
	string GetHash() {
		return this->hash;
	}
	/// <summary>
	/// Получает количество токенов в кошельке
	/// </summary>
	/// <returns></returns>
	int GetTokensCount() {
		return this->tokensCount;
	}
	/// <summary>
	/// Возвращает статус "в сети"
	/// </summary>
	/// <returns></returns>
	bool GetOnline() {
		return this->isOnline;
	}
	/// <summary>
	/// Возвращает количество голосов
	/// </summary>
	/// <returns></returns>
	size_t GetVotes() {
		return this->votesCount;
	}
	/// <summary>
	/// Получает вероятность получения токена (используется в голосовании)
	/// </summary>
	/// <returns></returns>
	float GetProbability() {
		return this->probability;
	}
	/// <summary>
	/// Получает начало промежутка в цепочке вероятностей (используется в голосовании)
	/// </summary>
	/// <returns></returns>
	float GetProbabilityFrom() {
		return this->probabilityFrom;
	}
	/// <summary>
	/// Получает конец промежутка в цепочке вероятностей (используется в голосовании)
	/// </summary>
	/// <returns></returns>
	float GetProbabilityTo() {
		return this->probabilityTo;
	}
	/// <summary>
	/// Задает процент голосов, 
	/// который набрал клиент в голосовании
	/// </summary>
	float GetVotesPercent() {
		return this->votesPercent;
	}
#pragma endregion

#pragma region Add
	/// <summary>
	/// Добавляет указанное количество токенов в кошелек
	/// </summary>
	/// <param name="tokensCount"></param>
	void AddTokens(int tokensCount) {
		this->tokensCount += tokensCount;
	}
	/// <summary>
	/// Добавляет один голос
	/// </summary>
	void AddVote() {
		this->votesCount++;
	}
#pragma endregion

#pragma endregion















#pragma region Other
	string ToString() {
		stringstream ss;
		ss << "id:" << this->id << endl << "hash:" << this->hash << endl << "tokens:" << this->tokensCount;
		return ss.str();
	}
#pragma endregion
};



#pragma region Операторы
bool operator==(const Client& c1, const Client& c2) {
	return c1.GetId() == c2.GetId();
}
ostream& operator<<(ostream& os, Client c) {
	os << c.ToString();
	return os;
}
#pragma endregion

