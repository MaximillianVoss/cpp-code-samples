#pragma once
#include "TWLL.h"
#include "Block.h"
#include "Client.h"
#include "Graph.h"
#include "SHA1.h"
#include "Log.h"
/// <summary>
/// Тип клиентов
/// </summary> 
enum ClientsType {
	/// <summary>
	/// всех
	/// </summary>
	all,
	/// <summary>
	/// онлайн
	/// </summary>
	online,
	/// <summary>
	/// офлайн
	/// </summary>
	ofline,
	/// <summary>
	/// с ненулевым балансом
	/// </summary>
	nonZero,
	/// <summary>
	/// с нулевым балансом
	/// </summary>
	zero,
	/// <summary>
	/// с ненулевым балансом и онлайн
	/// </summary>
	nonZeroOnline
};
/// <summary>
/// Голос участвующего в голосовании
/// </summary>
class Vote {
public:
	Client* client;
	size_t votesCount;
	Vote(Client* client = NULL, size_t votesCount = 0) {
		this->client = client;
		this->votesCount = votesCount;
	}
};

/// <summary>
/// Блокчейн
/// </summary>
class BlockChain
{
private:

#pragma region Поля
	/// <summary>
	/// разделитель ID и пароля
	/// </summary>
	string delimeter = ".";
	/// <summary>
	/// Лог событий
	/// </summary>
	Log log;
#pragma region Данные
	/// <summary>
	/// 
	/// </summary>
	TWLList<Block>* blocks;
	/// <summary>
	/// Граф клиентов
	/// </summary>
	Graph<Client> clients;
#pragma endregion

#pragma region Параметры для голосования
	/// <summary>
	///Процент голосов для победы
	/// </summary>
	float votesPercent = 0.51;
#pragma endregion

#pragma region Счетчики
	/// <summary>
	/// счетчик клиентов
	/// </summary>
	size_t counterClients;
	/// <summary>
	/// счетчик блоков
	/// </summary>
	size_t counterBlocks;
	/// <summary>
	/// счетчик клиентов онлайн
	/// </summary>
	size_t counterOnline;
	/// <summary>
	///Количество первых этапов голосования
	/// </summary>
	size_t counterVotingFirstStage;
	/// <summary>
	/// Общее количество голосований
	/// </summary>
	size_t counterVotingTotal;
	/// <summary>
	/// счетчик успешных голосований
	/// </summary>
	size_t counterVotingCompleted;
	/// <summary>
	/// счетчик неудачных голосаний
	/// </summary>
	size_t counterVotingFailed;
	/// <summary>
	/// счетчик для слуаев, когда набралось больше двух победителей
	/// </summary>
	size_t counterVotingMultWinners;
#pragma endregion

#pragma endregion

#pragma region Методы

#pragma region GET
	/// <summary>
	/// Получает блок с указанными ИД
	/// </summary>
	/// <param name="id">ИД</param>
	/// <returns></returns>
	Block* GetBlock(string id) {
		return &this->blocks->Find(Block(id, ""))->data;
	}
	/// <summary>
	/// Получает клиента с указанными ИД
	/// </summary>
	/// <param name="id">ИД</param>
	/// <returns></returns>
	Client* GetClient(string id) {
		Node<Client>* node = this->clients.Find(Client(id, ""));
		if (node)
			return node->GetDataP();
		else
			return NULL;
	}
#pragma endregion

#pragma region ADD
	/// <summary>
	/// Добавляет блок
	/// </summary>
	/// <param name="block">указатель на блок</param>
	bool Add(Block* block) {
		if (block != NULL && !this->GetBlock(block->GetId()) && block->GetOwnerId() != "")
		{
			this->blocks->Add(*block);
			this->counterBlocks++;
			return true;
		}
		return false;
	}
	/// <summary>
	/// Добавляет клиента в сеть
	/// </summary>
	/// <param name="client">указатель на клиента</param>
	bool Add(Client* client) {
		if (GetClient(client->GetId()) == NULL) {
			this->clients.Add(*client);
			this->counterClients = this->clients.GetNodesCount();
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Голосование
	/// <summary>
/// Пересчитывает количество монет для указанного клиента
/// </summary>
/// <param name="client">указатель на клиента</param>
	void Ledger(Client* client) {
		LLItem<Block>* currentBlock = this->blocks->head;
		client->SetTokensCount(0);
		while (currentBlock) {
			if (currentBlock->data.GetOwnerId() == client->GetId())
				client->AddTokens(1);
			currentBlock = currentBlock->next;
		}
	}
	/// <summary>
	/// Подсчет леджинга у всех клиентов
	/// </summary>
	void Ledger() {
		//for (int i = 0; i < this->clients.GetNodesCount(); i++) {
		parallel_for(size_t(0), this->clients.GetNodesCount(), [&](size_t i) {
			this->Ledger(this->clients.GetNode(i)->GetDataP());
			});
		//}
	}
	/// <summary>
	/// Голосование по распределению блоков
	/// </summary>
	/// <param name="block">блок для подписи</param>
	/// <param name="clientsForVoting">клиенты, учавствующие в голосовании</param>
	/// <param name="onlyOneRound">только одн раунд госования(да/нет)</param>
	void Voting(Block* block, vector<Client>clientsForVoting = {}, bool onlyOneRound = false) {
		this->counterVotingTotal++;
		if (clientsForVoting.size() == 0)
		{
			this->counterVotingFailed++;
			this->log.Add("Голосование провалено, блок не подписан!");
			this->log.Add("Всего голосовавших:" + to_string(clientsForVoting.size()));
			return;
		}

		float tokensCount = 0;
		parallel_for(size_t(0), clientsForVoting.size(), [&](size_t i) {
			tokensCount += clientsForVoting[i].GetTokensCount();
			});
		float tokensCountAvg = tokensCount / (float)clientsForVoting.size();
		if (tokensCountAvg <= 10.0)
			parallel_for(size_t(0), clientsForVoting.size(), [&](size_t i) {
			clientsForVoting[i].SetProbability(1.0 / clientsForVoting.size());
				});
		else
			parallel_for(size_t(0), clientsForVoting.size(), [&](size_t i) {
			clientsForVoting[i].SetProbability((float)clientsForVoting[i].GetTokensCount() / (float)tokensCount);
				});

		if (clientsForVoting.size() > 0)
		{
			clientsForVoting[0].SetProbabilityTo(clientsForVoting[0].GetProbability());
			for (int i = 1; i < clientsForVoting.size(); i++)
			{
				clientsForVoting[i].SetProbabilityFrom(clientsForVoting[i - 1].GetProbabilityTo());
				clientsForVoting[i].SetProbabilityTo(clientsForVoting[i - 1].GetProbabilityTo() + clientsForVoting[i].GetProbability());
			}
		}
		parallel_for(size_t(0), clientsForVoting.size(), [&](size_t i) {
			float value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			for (int j = 0; j < clientsForVoting.size(); j++)
				if ((value >= clientsForVoting[j].GetProbabilityFrom()) && (clientsForVoting[j].GetProbabilityTo() >= value)) {
					clientsForVoting[j].AddVote();
					break;
				}
			});
		//счетчик считает количество клиентов, 
		//набравших больше порогового значения
		for (int i = 0; i < clientsForVoting.size(); i++) {
			float percent = (float)clientsForVoting[i].GetVotes() / (float)clientsForVoting.size();
			clientsForVoting[i].SetVotesPercent(percent);
		}
		for (int i = 0; i < clientsForVoting.size(); i++) {
			if (clientsForVoting[i].GetVotesPercent() < this->votesPercent) {
				clientsForVoting.erase(clientsForVoting.begin() + i);
				i--;
			}
		}
		if (clientsForVoting.size() > 1)
			this->counterVotingMultWinners++;
		if (clientsForVoting.size() == 1) {
			block->SetOwnerId(clientsForVoting[0].GetId());
			this->GetClient(block->GetOwnerId())->AddTokens(1);
			this->log.Add("Голосование прошло успешно блок:" + block->GetId() + " владелец:" + block->GetOwnerId());
			this->counterVotingCompleted++;
		}
		else {


			if (onlyOneRound) {
				//Voting(block, {});
				return;
			}
			else {
				this->log.Add("Следующий этап голосования");
				parallel_for(size_t(0), clientsForVoting.size(), [&](size_t i) {
					clientsForVoting[i].SetVotes(0);
					});
				Voting(block, clientsForVoting);
			}


		}
	}

#pragma endregion

#pragma region Connect emulation
	void Connect(Client* c) {
		if (this->GetClientsCount() > 1) {

		}
	}
#pragma endregion


#pragma endregion
public:
#pragma region Конструкторы
	BlockChain() {
		this->counterBlocks = 0;
		this->counterClients = 0;
		this->counterVotingFirstStage = 0;
		this->counterVotingTotal = 0;
		this->counterVotingCompleted = 0;
		this->counterVotingFailed = 0;
		this->counterVotingMultWinners = 0;
		this->blocks = new TWLList<Block>();
	}
	~BlockChain() {
	}
#pragma endregion

#pragma region Методы

#pragma region Добавление
	Block* Add(string blockId, string blockOwnerId) {
		Block* block = new Block(blockId, blockOwnerId);
		if (this->Add(block)) {
			Client* client = this->GetClient(blockOwnerId);
			if (client)
				client->AddTokens(1);
			return block;
		}
		return NULL;
	}
	Client* Add(string password) {
		SHA1 sha;
		Client* client = new Client(sha.GetHash(to_string(++this->counterClients)), sha.GetHash(password));
		if (this->Add(client))
			return client;
		return NULL;
	}
#pragma endregion

#pragma region Удаление
	void Delete(Block* block) {
		//this->blocks->D
		throw exception(Constants::Strings::Errors::notImplemented);
	}
	void Delete(string blockId) {
		/*LLItem<Block>* current = this->blocks->head;
		if (current)
			while (current) {
				if(current->data.GetId()==blockId)
					this->blocks->Delete
			}*/
		throw exception(Constants::Strings::Errors::notImplemented);
	}
	void Delete() {
		this->blocks->Delete();
	}
#pragma endregion

#pragma region Генерация блока
	/// <summary>
	/// Генерирует блок и распределяет с помощью голосования
	/// </summary>
	/// <param name="onlyOneRound">только одн раунд госования(да/нет)</param>
	/// <returns></returns>
	Block* GenerateBlock(bool onlyOneRound = false) {
		Block* block = new Block(this->counterBlocks + 1);
		this->counterVotingFirstStage++;
		this->Ledger();
		vector<Client> nonZero = this->GetClients(ClientsType::nonZeroOnline);
		if ((float)nonZero.size() / (float)this->counterClients > 0.5)
			Voting(block, this->GetClients(ClientsType::nonZeroOnline), onlyOneRound);
		else
			Voting(block, this->GetClients(ClientsType::all), onlyOneRound);
		if (this->Add(block))
			return block;
		else
			return NULL;
		return NULL;
	}
	Block* GenerateBlock(string blockOwnerId) {
		return this->Add(SHA1().GetHash(to_string(this->counterBlocks + 1)), blockOwnerId);
	}
#pragma endregion

#pragma region Подключение	
	/// <summary>
	/// Подключает клиента к блокчейну
	/// </summary>
	/// <param name="id">ID клиента</param>
	/// <param name="password">пароль(исходный, не хеш значение)</param>
	/// <returns></returns>
	Client* Connect(string id, string password) {
		Client* client = this->GetClient(id);
		if (client && client->GetHash() == SHA1().GetHash(password)) {
			client->SetOnline(true);
			this->counterOnline++;
		}
		return client;
	}
	/// <summary>
	/// Соединяет двух клиентов между собой
	/// </summary>
	/// <param name="c1">клиент 1</param>
	/// <param name="c2">клиент 2</param>
	/// <param name="ping">условное знчение пинга между ними</param>
	void Connect(Client* c1, Client* c2, size_t ping = rand() % 1000) {
		Node<Client>* n1 = this->clients.Find(*c1);
		Node<Client>* n2 = this->clients.Find(*c2);
		if (n1 && n2)
			this->clients.Connect(n1->GetId(), n2->GetId(), ping);
	}
#pragma endregion

#pragma region Отключение
	/// <summary>
	/// Оотключение от  блокчейна
	/// </summary>
	/// <param name="client">Указатель на клиента</param>
	/// <returns></returns>
	Client* Disconnect(Client* client) {
		Client* clientPointer = this->GetClient(client->GetId());
		Node<Client>* node = this->clients.Find(*client);
		if (clientPointer) {
			this->clients.Disconnect(node->GetId());
			client->SetOnline(false);
			this->counterOnline--;
		}
		return client;
	}
#pragma endregion

#pragma region SET
	/// <summary>
	/// Устанавливает порог для голосования:
	/// процент голосов, который необходимо набрать, чтобы получить токен
	/// </summary>
	/// <param name="votesPercent"></param>
	void SetVotesPercent(float votesPercent) {
		this->votesPercent = votesPercent;
	}
	/// <summary>
	/// Задает значение проваленных голосований
	/// </summary>
	/// <returns></returns>
	void SetVotingFailCount(size_t votingFailCounter) {
		this->counterVotingFailed = votingFailCounter;
	}
#pragma endregion

#pragma region GET
	/// <summary>
	/// Получает список клиентов указанного типа
	/// </summary>
	/// <param name="type">Тип клиентов</param>
	/// <returns></returns>
	vector<Client> GetClients(ClientsType type = ClientsType::all) {
		vector<Client> list = this->clients.GetNodesValues();
		if (type == ClientsType::all)
			return list;
		if (type == ClientsType::ofline) {
			for (int i = 0; i < list.size(); i++)
				if (list[i].GetOnline())
					list.erase(list.begin() + i);
			return list;
		}
		if (type == ClientsType::online) {
			for (int i = 0; i < list.size(); i++)
				if (!list[i].GetOnline())
					list.erase(list.begin() + i);
			return list;
		}
		if (type == ClientsType::zero) {
			for (int i = 0; i < list.size(); i++)
				if (list[i].GetTokensCount() != 0) {
					list.erase(list.begin() + i);
					i--;
				}
			return list;
		}
		if (type == ClientsType::nonZero) {
			for (int i = 0; i < list.size(); i++)
				if (list[i].GetTokensCount() == 0) {
					list.erase(list.begin() + i);
					i--;
				}
			return list;
		}
		if (type == ClientsType::nonZeroOnline) {
			for (int i = 0; i < list.size(); i++)
				if (list[i].GetTokensCount() == 0 || list[i].GetOnline() == false) {
					list.erase(list.begin() + i);
					i--;
				}
			return list;
		}
		return vector<Client>();
	}
	/// <summary>
	/// Получает количество клиентов указанного типа
	/// </summary>
	/// <param name="type">Тип клиентов</param>
	/// <returns></returns>
	size_t GetClientsCount(ClientsType type = ClientsType::all) {
		if (type == ClientsType::all) {
			return this->clients.GetNodesCount();
		}
		if (type == ClientsType::ofline) {
			return this->clients.GetNodesCount() - this->counterOnline;
		}
		if (type == ClientsType::online) {
			return this->counterOnline;
		}
		else {
			return this->GetClients(type).size();
		}
	}
	/// <summary>
	/// Получает количество соединений(между клиентами)
	/// </summary>
	/// <returns></returns>
	size_t GetConnectionsCount() {
		return this->clients.GetEdgesCount();
	}
	/// <summary>
	/// Получает количество блоков
	/// </summary>
	/// <returns></returns>
	size_t GetBlocksCount() {
		return this->blocks->GetLength();
	}
	/// <summary>
	/// Получает лог в виде строки
	/// </summary>
	/// <returns></returns>
	string GetLogStr() {
		return this->log.ToString();
	}
	/// <summary>
	/// Получает количество голосовний в блокчейне(первичных этапов)
	/// </summary>
	/// <returns></returns>
	size_t GetCounterVotingFirstStage() {
		return this->counterVotingFirstStage;
	}
	/// <summary>
	/// Получает общее число голосований
	/// </summary>
	/// <returns></returns>
	size_t GetCounterVotingTotal() {
		return this->counterVotingTotal;
	}
	/// <summary>
	/// Получает значение успешных голосований
	/// </summary>
	/// <returns></returns>
	size_t GetCounterVotingCompleted() {
		return this->counterVotingCompleted;
	}
	/// <summary>
	/// Получает значение проваленных голосований
	/// </summary>
	/// <returns></returns>
	size_t GetCounterVotingFailed() {
		return this->counterVotingFailed;
	}
	/// <summary>
	/// Возвращает значение счетчика 
	/// для слуаев, когда набралось больше двух победителей
	/// </summary>
	size_t GetCounterVotingMultWinners() {
		return this->counterVotingMultWinners;
	}
	/// <summary>
	/// Получает порог для голосования:
	/// процент голосов, который необходимо набрать, чтобы получить токен
	/// </summary>
	/// <returns></returns>
	float GetVotesPercent() {
		return this->votesPercent;
	}
#pragma endregion

#pragma region Сериализация
	string ToString() {
		return this->blocks->ToString();
	}
	string ToString(OutputFormat format = OutputFormat::fields) {
		return this->clients.ToString(format);
	}
#pragma endregion

#pragma region Леджинг
	void CalcLedger() {
		this->Ledger();
	}
#pragma endregion

#pragma region Прочее


#pragma endregion
#pragma endregion
};