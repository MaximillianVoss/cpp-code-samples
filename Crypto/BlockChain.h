#pragma once
#include "TWLL.h"
#include "Block.h"
#include "Client.h"
#include "SHA1.h"
//перенести Log.h LogItem.h в проект Log
#include "Log.h"
/// <summary>
/// Блокчейн
/// </summary>
class BlockChain
{
private:

#pragma region Поля
	/// <summary>
	/// 
	/// </summary>
	TWLList<Block> blocks;
	/// <summary>
	/// Список клиентов
	/// </summary>
	TWLList<Client> clients;
	/// <summary>
	/// Минимальный порог для победы
	/// </summary>
	size_t voteMin = 60;
	/// <summary>
	/// Максимальное значение для голосования
	/// </summary>
	size_t voteMax = 100;
	/// <summary>
	/// Лог событий
	/// </summary>
	Log log;
#pragma endregion

#pragma region Методы



#pragma endregion
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
	Block Add(Block block) {
		LLItem<Block>* found = this->blocks.Find(block);
		if (!found) {
			size_t clientIndex = this->Voting(this->GetOnlineCount(), voteMin, voteMax);
			if (clientIndex != -1) {
				block.ownerId = this->clients.Find(clientIndex)->data.GetKey();
				this->blocks.Add(block);
				log.Add(Constants::Strings::BlockChain::blockAdded);
			}
			else {
				log.Add((Constants::Strings::BlockChain::voitingRestarted));
				return this->Add(block);
			}
			return block;
		}
		return block;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="client"></param>
	Client Add(Client client) {
		SHA1 sha;
		//если нет ключа, но есть фраза, то регистрируем как нового
		if (client.GetKey() == "") {
			if (client.GetPhrase() != "") {
				client.SetKey(sha.GetHash(this->GetRandStr(10) + client.GetPhrase()));
				log.Add((Constants::Strings::BlockChain::clientAdded));
				this->clients.Add(client);
				return client;
			}
		}
		return Client();
	}
#pragma endregion
#pragma region Соединение
	bool Connect(Client client) {
		if (!client.isOnline) {
			LLItem<Client>* found = this->clients.Find(client);
			if (found) {
				found->data.isOnline = true;
				return true;
			}
		}
		return false;
	}
	bool Disconnect(Client client) {
		if (client.isOnline) {
			LLItem<Client>* found = this->clients.Find(client);
			if (found) {
				found->data.isOnline = false;
				return true;
			}
		}
		return false;
	}
	vector<Client> GetClientList() {
		//return this->clients.ToList();
		//return this->clients;
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
		//return this->clients;
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
		//block->ownerId = StageB(StageA(clients)).id;
		//block->ownerId = 
	}
	/// <summary>
	/// Верификация
	/// </summary>
	/// <param name="client"></param>
	/// <returns></returns>
	bool Verification(Client client) {

	}
	/// <summary>
	/// Голосование освнованное на случайной величине
	/// </summary>
	/// <param name="N"></param>
	/// <returns></returns>
	int Voting(int N, int limit, int maxValue) {
		log.Add((Constants::Strings::BlockChain::votingStarted));
		vector<vector<int>> items;
		for (int i = 0; i < N; i++) {
			items.push_back(vector<int>());
			for (int j = 0; j < N; j++)
				items[i].push_back(rand() % maxValue);
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
		log.Add((Constants::Strings::BlockChain::voitingEnded));
		if (max > limit * N)
			return index;
		return -1;
	}
#pragma endregion

#pragma region Прочее
	string GetRandStr(int length) {
		string eng = Constants::Strings::Alphabets::eng;
		stringstream ss;
		for (size_t i = 0; i < length; i++)
			ss << rand() % eng.size();
		return ss.str();
	}
	int  GetClientsCount() {
		return this->clients.GetLength();
	}
	int GetOnlineCount() {
		LLItem<Client>* current = this->clients.head;
		int onlineCounter = 0;
		while (current) {
			if (current->data.isOnline)
				onlineCounter++;
			current = current->next;
		}
		return onlineCounter;
	}
	int GetBlocksCount() {
		return this->blocks.GetLength();
	}
	string GetLogStr() {
		return this->log.ToString();
	}
#pragma endregion
#pragma endregion
};