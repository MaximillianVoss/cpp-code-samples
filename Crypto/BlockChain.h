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
	/// счетчик клиентов
	/// </summary>
	size_t clientsCounter;
	/// <summary>
	/// счетчик блоков
	/// </summary>
	size_t blocksCounter;
	/// <summary>
	/// счетчик клиентов онлайн
	/// </summary>
	size_t onlineCounter;
	/// <summary>
	/// 
	/// </summary>
	TWLList<Block> blocks;
	/// <summary>
	/// Граф клиентов
	/// </summary>
	Graph<Client> clients;
	/// <summary>
	/// Минимальный порог для победы
	/// </summary>
	size_t voteMin = 60;
	/// <summary>
	/// Максимальное значение для голосования
	/// </summary>
	size_t voteMax = 100;
	/// <summary>
	///Количество первых этапов голосования
	/// </summary>
	size_t votingFirstCounter = 0;
	/// <summary>
	/// Общее количество голосований
	/// </summary>
	size_t votingTotalCounter = 0;
	/// <summary>
	/// счетчик успешных голосований
	/// </summary>
	size_t votingSuccessCounter = 0;
	/// <summary>
	/// счетчик неудачных голосаний
	/// </summary>
	size_t votingFailCounter = 0;
	/// <summary>
	///Процент голосов для победы
	/// </summary>
	float votesPercent = 0.51;
	/// <summary>
	/// Лог событий
	/// </summary>
	Log log;
#pragma endregion

#pragma region Методы

#pragma region GET
	/// <summary>
	/// Получает блок с указанными ИД
	/// </summary>
	/// <param name="id">ИД</param>
	/// <returns></returns>
	Block* GetBlock(string id) {
		return &this->blocks.Find(Block(id, ""))->data;
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
		SHA1 sha;
		if (block != NULL && !this->GetBlock(block->GetId()) && block->GetOwnerId() != "")
		{
			this->blocks.Add(*block);
			this->blocksCounter++;
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
			this->clientsCounter = this->clients.GetNodesCount();
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
		LLItem<Block>* currentBlock = this->blocks.head;
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
		//for (int i = 0; i < this->clients.GetNodesCount(); i++)
		parallel_for(size_t(0), this->clients.GetNodesCount(), [&](size_t i) {
			this->Ledger(this->clients.GetNode(i)->GetDataP());
			});
	}
	/// <summary>
	/// Голосование по распределению блоков
	/// </summary>
	/// <returns></returns>
	void Voting(Block* block, vector<Client>clientsForVoting = {}) {
		this->votingTotalCounter++;
		if (clientsForVoting.size() == 0)
		{
			//возможно неправильно возвращает голосующих!
			//проверить!
			clientsForVoting = this->GetClients(ClientsType::nonZeroOnline);
			/// проверка если не найдено ни одного клиента, то надо 
			/// сообщать о провале голосования и выходить
			this->Ledger();
		}
		int tokensCount = 0;
		parallel_for(size_t(0), clientsForVoting.size(), [&](size_t i) {
			tokensCount += clientsForVoting[i].GetTokensCount();
			});
		if (tokensCount == 0)
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
		size_t maxVotes = 0;
		//for (int i = 0; i < clientsForVoting.size(); i++) {
		parallel_for(size_t(0), clientsForVoting.size(), [&](size_t i) {
			float value = (float)(rand() % 100) / 100;
			for (int j = 0; j < clientsForVoting.size(); j++)
				if ((value >= clientsForVoting[j].GetProbabilityFrom()) && (clientsForVoting[j].GetProbabilityTo() >= value)) {
					clientsForVoting[j].AddVote();
					if (clientsForVoting[j].GetVotes() > maxVotes)
						maxVotes = clientsForVoting[j].GetVotes();
					break;
				}
			});
		//}
		for (int i = 0; i < clientsForVoting.size(); i++) {
			if (clientsForVoting[i].GetVotes() != maxVotes) {
				clientsForVoting.erase(clientsForVoting.begin() + i);
				i--;
			}
		}
		if (clientsForVoting.size() == 1) {
			block->SetOwnerId(clientsForVoting[0].GetId());
			this->GetClient(block->GetOwnerId())->AddTokens(1);
			this->log.Add("Голосование прошло успешно блок:" + block->GetId() + " владелец:" + block->GetOwnerId());
			this->votingSuccessCounter++;
		}
		else {

			if ((float)maxVotes / (float)clientsForVoting.size() < this->votesPercent) {
				this->log.Add("Следующий этап голосования");
				//for (int i = 0; i < clientsForVoting.size(); i++)
				parallel_for(size_t(0), clientsForVoting.size(), [&](size_t i) {
					clientsForVoting[i].SetVotes(0);
					});
				this->votingFailCounter++;
				Voting(block, clientsForVoting);
			}
			else {
				this->log.Add("Голосование провалено, блок не подписан!");
				this->log.Add("Всего голосовавших:" + to_string(clientsForVoting.size()));
				this->log.Add("Максимум голосов:" + to_string(maxVotes));
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
		this->blocksCounter = 0;
		this->clientsCounter = 0;
	}
	~BlockChain() {
	}
#pragma endregion

#pragma region Методы
#pragma region Добавление
	Block* Add(string blockId, string blockOwnerId) {
		Block* block = new Block(blockId, blockOwnerId);
		if (this->Add(block))
			return block;
		return NULL;
	}
	Client* Add(string password) {
		SHA1 sha;
		Client* client = new Client(sha.GetHash(to_string(++this->clientsCounter)), sha.GetHash(password));
		if (this->Add(client))
			return client;
		return NULL;
	}
#pragma endregion

#pragma region Генерация блока
	Block* GenerateBlock() {
		Block* block = new Block(SHA1().GetHash(to_string(this->blocksCounter + 1)), "");
		this->votingFirstCounter++;
		Voting(block);
		if (this->Add(block))
			return block;
		else
			return NULL;
		return NULL;
	}
	Block* GenerateBlock(string blockOwnerId) {
		return this->Add(SHA1().GetHash(to_string(this->blocksCounter + 1)), blockOwnerId);
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
			this->onlineCounter++;
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
			this->onlineCounter--;
		}
		return client;
	}
#pragma endregion

#pragma region SET

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
			return this->clients.GetNodesCount() - this->onlineCounter;
		}
		if (type == ClientsType::online) {
			return this->onlineCounter;
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
		return this->blocks.GetLength();
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
	size_t GetVotingFirstCount() {
		return this->votingFirstCounter;
	}
	/// <summary>
	/// Получает общее число голосований
	/// </summary>
	/// <returns></returns>
	size_t GetVotingTotalCount() {
		return this->votingTotalCounter;
	}
	/// <summary>
	/// Получает значение успешных голосований
	/// </summary>
	/// <returns></returns>
	size_t GetVotingSuccessCount() {
		return this->votingSuccessCounter;
	}
	/// <summary>
	/// Получает значение проваленных голосований
	/// </summary>
	/// <returns></returns>
	size_t GetVotingFailCount() {
		return this->votingFailCounter;
	}
#pragma endregion

#pragma region Сериализация
	string ToString() {
		return this->blocks.ToString();
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