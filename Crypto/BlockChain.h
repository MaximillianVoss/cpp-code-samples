#pragma once
#include "TWLL.h"
#include "Block.h"
#include "Client.h"
class BlockChain :TWLList<Block>
{
private:
	/// <summary>
	/// 
	/// </summary>
	int clientId = 0;
	/// <summary>
	/// 
	/// </summary>
	TWLList blocks;
	/// <summary>
	/// 
	/// </summary>
	//TWLList<Client> clients;
	vector<Client> clients;
public:
#pragma region Конструкторы
	BlockChain() {
	}

	~BlockChain() {
	}
#pragma endregion
#pragma region Методы
#pragma region Добавление
	/// <summary>
/// 
/// </summary>
/// <param name="block"></param>
	void Add(Block* block) {
		this->Voting(this->clients, block);
		this->blocks.Add(*block);
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="client"></param>
	void Add(Client client) {
		//this->clients.Add(client);
		this->clients.push_back(client);
	}

#pragma endregion
#pragma region Соединение
	void Connect(Client* client) {
		this->clientId++;
		client->id = to_string(this->clientId);
		client->isOnline = true;
		this->Add(*client);
		this->clients.push_back(*client);
	}
	void Disconnect(Client* client) {
		client->isOnline = true;
		//this->clients.Delete(*client);
	}
	vector<Client> GetClientList() {
		//return this->clients.ToList();
		return this->clients;
	}
#pragma endregion
#pragma region Сериализация
	string ToString() {
		return this->blocks.ToString();
	}
#pragma endregion
#pragma region Голосование
	/// <summary>
/// 
/// </summary>
/// <returns></returns>
	vector<Client> GetActive() {
		return this->clients;
	}
	/// <summary>
	/// Голосование по распределению блоков
	/// </summary>
	/// <param name="client"></param>
	/// <returns></returns>
	double LedgerCounting(Client client) {
		//vector<Block> items = this->blocks.
		return 1.0;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="clients"></param>
	/// <returns></returns>
	vector<Client> StageA(vector<Client> clients) {
		return clients;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="clients"></param>
	/// <returns></returns>
	Client StageB(vector<Client> clients) {
		//return clients.GetLast()->data;
		return clients[clients.size() - 1];

	}
	/// <summary>
	/// Голосование по распределению блоков
	/// </summary>
	/// <param name="clients"></param>
	/// <returns></returns>
	void Voting(vector<Client> clients, Block* block) {
		block->ownerId = StageB(StageA(clients)).id;
	}
	/// <summary>
	/// Верификация
	/// </summary>
	/// <param name="client"></param>
	/// <returns></returns>
	bool Verification(Client client) {

	}

	int VotingAlpha(int N) {
		vector<vector<int>> items;
		for (int i = 0; i < N; i++) {
			items.push_back(vector<int>());
			for (int j = 0; j < N; j++)
				items[i].push_back(rand() % 100);
		}
		int max = 0;
		int index = -1;
		for (int i = 0; i < N; i++) {
			int sum = 0;
			for (int j = 0; j < N; j++)
				sum += items[j][i];
			if (sum > max) {
				max = sum;
				index = i;
			}
		}
		return index;
	}
#pragma endregion
#pragma endregion
};