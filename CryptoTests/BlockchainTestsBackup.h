#pragma once
#pragma once
#include "Blockchain.h"
#include "Plotter.h"
#include "UnitTest.h"
#include "IO.h"
#pragma region Тесты

#pragma region Добавление кошелька в блокчейн
///<summary>
/// Добавление кошелька в блокчейн
///</summary>
class BlockChainAddWallet :public UnitTest<int> {
public:
	BlockChainAddWallet(vector<int>values) :UnitTest("Добавление кошелька в блокчейн", values) {

	}
	void Test() override {
		/*BlockChain bc;
		string fileName = this->name + ".txt";
		this->Add(bc.GetClientsCount());
		bc.Add(Client("", "qwerty"));
		bc.Add(Client("", "12345678"));
		this->Add(bc.GetClientsCount());
		IO().Append(fileName, { bc.GetLogStr() });
		UnitTest::Compare();*/
		BlockChain bc;
		bc.Add("qwerty_lol_kek_cheburek");
		bc.Add("12345678");
		this->Add(bc.GetClientsCount(ClientsType::all));
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Соединение клиентов
///<summary>
/// Соединение клиентов
///</summary>
class BlockChainConnectTest :public UnitTest<size_t> {
public:
	BlockChainConnectTest(vector<size_t>values) :UnitTest("Соединение клиентов", values) {

	}
	void Test() override {
		BlockChain bc;
		vector<Client*> clients;
		for (int i = 0; i < 6; i++) {
			clients.push_back(bc.Add(to_string(1230 + i)));
			bc.Connect(clients[i]->GetId(), to_string(1230 + i));
		}
		bc.Connect(clients[0], clients[1]);
		bc.Connect(clients[0], clients[2]);
		bc.Connect(clients[0], clients[3]);
		bc.Connect(clients[3], clients[4]);
		bc.Connect(clients[3], clients[5]);
		IO().WriteLines("BlockChainConnectTest.graphml", { bc.ToString(OutputFormat::xml) });
		this->Add({ bc.GetClientsCount(ClientsType::online), bc.GetConnectionsCount() });
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Рассоединение клиентов
///<summary>
/// Рассоединение клиентов
///</summary>
class BlockChainDicsonnectTest :public UnitTest<size_t> {
public:
	BlockChainDicsonnectTest(vector<size_t>values) :UnitTest("Рассоединение клиентов", values) {

	}
	void Test() override {
		BlockChain bc;
		vector<Client*> clients;
		for (int i = 0; i < 6; i++) {
			clients.push_back(bc.Add(to_string(1230 + i)));
			bc.Connect(clients[i]->GetId(), to_string(1230 + i));
		}
		bc.Connect(clients[0], clients[1]);
		bc.Connect(clients[0], clients[2]);
		bc.Connect(clients[0], clients[3]);
		bc.Connect(clients[3], clients[4]);
		bc.Connect(clients[3], clients[5]);
		bc.Disconnect(clients[2]);
		bc.Disconnect(clients[5]);
		this->Add({ bc.GetClientsCount(ClientsType::online), bc.GetConnectionsCount() });
		IO().WriteLines("BlockChainDicsonnectTest.graphml", { bc.ToString(OutputFormat::xml) });
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Добавление Блока с ручной подписью
///<summary>
/// Добавление Блока с ручной подписью
///</summary>
class BlockChainAddBlocksTest :public UnitTest<int> {
public:
	BlockChainAddBlocksTest(vector<int>values) :UnitTest("Добавление Блока с ручной подписью", values) {

	}

	void Test() override {
		BlockChain bc;
		vector<Client*> clients;
		this->Add(bc.GetBlocksCount());
		for (int i = 0; i < 6; i++) {
			clients.push_back(bc.Add(to_string(1230 + i)));
			bc.Connect(clients[i]->GetId(), to_string(1230 + i));
			for (int j = 0; j < i + 1; j++)
				bc.GenerateBlock(clients[i]->GetId());

		}
		this->Add(bc.GetBlocksCount());
		bc.CalcLedger();
		vector<Client>clientsBC = bc.GetClients(ClientsType::all);
		for (int i = 0; i < clientsBC.size(); i++)
			this->Add(clientsBC[i].GetTokensCount());
		IO().WriteLines("BlockChainAddTestLog.txt", { bc.GetLogStr() });
		IO().WriteLines("BlockChainAddBlocksTest.graphml", { bc.ToString(OutputFormat::xml) });
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Подсчет леджинга
///<summary>
/// Подсчет леджинга
///</summary>
class BlockChainLedgingCountTest :public UnitTest<int> {
public:
	BlockChainLedgingCountTest(vector<int>values) :UnitTest("Подсчет леджинга", values) {

	}
	void Test() override {
		BlockChain bc;
		vector<Client*> clients;
		for (int i = 0; i < 6; i++) {
			clients.push_back(bc.Add(to_string(1230 + i)));
			bc.Connect(clients[i]->GetId(), to_string(1230 + i));
			if (i > 1)
				for (int j = 0; j < i + 1; j++)
					bc.GenerateBlock(clients[i]->GetId());
		}
		bc.CalcLedger();
		this->Add(bc.GetClientsCount(ClientsType::nonZero));
		this->Add(bc.GetClientsCount(ClientsType::zero));
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Голосование
///<summary>
/// Голосование
///</summary>
class BlockChainVotingTest :public UnitTest<bool> {
public:
	BlockChainVotingTest(vector<bool>values) :UnitTest("Голосование", values) {

	}
	void Test() override {
		//TODO:
		//информация для графиков по итогам раунда
		//логи с итогами раунда
		//ГОЛОСОВАНИЕ работает неправильно, поправить сравнения с вероятностями на A<x<B,где A,B границы промежутка
		//доделать проверку для теста голосования, пока там пустые ожидаемые значения!!!!!
		//подумать как равомерно распределять токены - когда у одного 1 у других 0, он накапливает токены
		//Добавить в русную несколько токенов всем участникам - у всех 0 , они не могут голосовать
		//собирать данные для графиков и выводить на экран питоном
		//передача данных графиков в Python файл
		BlockChain bc;
		vector<Client*> clients;
		int tokensCount = 100;
		int clientsCount = 10;
		this->Add(bc.GetBlocksCount() == 0);
		for (int i = 0; i < clientsCount; i++) {
			clients.push_back(bc.Add(to_string(i)));
			bc.Connect(clients[i]->GetId(), to_string(i));
			for (int j = 0; j < tokensCount / clientsCount; j++)
				bc.GenerateBlock(clients[i]->GetId());
		}
		bc.CalcLedger();
		this->Add(bc.GetCounterVotingTotal() < tokensCount);
		IO().WriteLines("BlockChainVotingTestLog.txt", { bc.GetLogStr() });
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Голосование графики
///<summary>
/// Голосование графики
///</summary>
class BlockChainVotingPlotTest :public UnitTest<bool> {
public:
	BlockChainVotingPlotTest(vector<bool>values) :UnitTest("Голосование графики", values) {

	}
	BlockChain* GenerateBlockchain(int clientsCount, int tokensCount) {
		BlockChain* bc = new BlockChain();
		vector<Client*> clients;
		for (int i = 0; i < clientsCount; i++) {
			clients.push_back(bc->Add(to_string(i)));
			bc->Connect(clients[i]->GetId(), to_string(i));
			for (int j = 0; j < tokensCount / clientsCount; j++)
				bc->GenerateBlock(clients[i]->GetId());
		}
		bc->CalcLedger();
		return bc;
	}
	Plotter<int> TestVoting(size_t initialClients, size_t initialCoins, size_t step, size_t testsCount, size_t plotGoup, float votesPercent) {
		Plotter<int> plotData("Графики голосований и распределениея токенов", { });
		stringstream ss;
		ss << "Случаи проваленных голосований(клиентов-" << initialClients << " " << "токенов-" << initialCoins << ")";
		string votingTitle1 = ss.str();
		ss.str(std::string());
		DataPack<int> votingDP1 = DataPack<int>(
			votingTitle1,
			"Количество экспериментов",
			"Количество случаев",
			plotGoup
			);
		ss << "Случаи, когда в голосовании победило больше двух кандидатов";
		string votingTitle2 = ss.str();
		ss.str(std::string());
		DataPack<int> votingDP2 = DataPack<int>(
			votingTitle2,
			"Количество экспериментов",
			"Количество случаев",
			plotGoup
			);

		for (int i = 0; i < testsCount; i++) {
			BlockChain* bc = GenerateBlockchain(initialClients, initialCoins);
			bc->SetVotesPercent(votesPercent);
			for (int j = 0; j < (i + 1) * step; j++) {
				bc->GenerateBlock(true);
			}
			bc->CalcLedger();
			votingDP1.AddPoint((i + 1) * step, bc->GetCounterVotingFailed());
			votingDP2.AddPoint((i + 1) * step, bc->GetCounterVotingMultWinners());
			ss << "Эксперимент №" << i + 1;
			string clientTitle = ss.str();
			ss.str(std::string());
			DataPack<int> clientsTokensDP = DataPack<int>(
				clientTitle,
				"№ клиента",
				"Количество токенов",
				plotGoup + 1
				);


			int c = 0;
			for (Client client : bc->GetClients())
				clientsTokensDP.AddPoint(c++, client.GetTokensCount());
			plotData.Add(clientsTokensDP);
		}
		plotData.Add(votingDP1);
		plotData.Add(votingDP2);
		return plotData;
	}
	void VoteTest1() {
		DataPack<int> votingDataPack("voting pack", "token", "failed votings", 1);
		DataPack<int> clinetsTokensPack("client tokens", "client N", "tokens", 2);
		int tokensCount = 100;
		int clientsCount = 10;
		BlockChain bc;
		vector<Client*> clients;
		for (int i = 0; i < clientsCount; i++) {
			clients.push_back(bc.Add(to_string(i)));
			bc.Connect(clients[i]->GetId(), to_string(i));
			for (int j = 0; j < 10; j++)
				bc.GenerateBlock(clients[i]->GetId());
		}
		for (int i = 0; i < clientsCount; i++)
			for (int j = 0; j < tokensCount / clientsCount; j++) {
				bc.GenerateBlock(true);
				votingDataPack.AddPoint(bc.GetBlocksCount(), bc.GetCounterVotingFailed());
			}
		bc.CalcLedger();
		int i = 0;
		for (Client client : bc.GetClients())
			clinetsTokensPack.AddPoint(i++, client.GetTokensCount());
		//TODO 20/04/2020: Доделать конвертер массива - ставится точка после последнего члена
		//доделать сейвы PLotter/DataPack  и в C++/Python
		Plotter<int> comonPlot("Common plot", { votingDataPack ,clinetsTokensPack });
		IO().WriteLines("C:\\commonPlot.txt", { comonPlot.ToString() });
	}
	void VoteTest2() {


		DataPack<int> votingDP1 = DataPack<int>("График проваленных голосований(100)", "№ эксперимента", "Количество проваленныйх голосований", 1);
		DataPack<int> votingDP2 = DataPack<int>("График проваленных голосований(1000)", "№ эксперимента", "Количество проваленныйх голосований", 1);
		int iterationsCount = 100;
		BlockChain* bc1 = GenerateBlockchain(10, 100);
		for (int i = 0; i < iterationsCount; i++) {
			//TODO:сделать удаление добавленного блока после голосования
			bc1->GenerateBlock(true);
			votingDP1.AddPoint(i + 1, bc1->GetCounterVotingFailed());
			bc1->Delete();
		}
		BlockChain* bc2 = GenerateBlockchain(10, 1000);
		for (int i = 0; i < iterationsCount; i++) {
			//TODO:сделать удаление добавленного блока после голосования
			bc2->GenerateBlock(true);
			votingDP2.AddPoint(i + 1, bc2->GetCounterVotingFailed());
			bc2->Delete();
		}

		Plotter<int> comonPlot("Графики голосований", { votingDP1 ,votingDP2 });
		IO().WriteLines("C:\\commonPlot.txt", { comonPlot.ToString() });
		//this->AddPlot()
	}
	void VoteTest3() {
		IO().WriteLines("C:\\commonPlot.txt", { TestVoting(10,100,10,5,1,0.7).ToString() });
	}
	void Test() override {

		VoteTest3();
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma endregion
#pragma region Тесты блокчейна
///<summary>
/// Тесты блокчейна
///</summary>
class BlockChainTests :UnitTests {
public:
	BlockChainTests() : UnitTests("Тесты блокчейна") {}
	void Start()override {
		//Запуск одного теста: TestsClassName(vector<type>items).Start();
		BlockChainAddWallet({ 2 }).Start();
		BlockChainConnectTest({ 6,5 }).Start();
		BlockChainDicsonnectTest({ 4,3 }).Start();
		BlockChainAddBlocksTest({ 0,21,1,2,3,4,5,6 }).Start();
		BlockChainLedgingCountTest({ 4,2 }).Start();
		BlockChainVotingTest({ true,true }).Start();
		BlockChainVotingPlotTest({}).Start();
	}
};
#pragma endregion
#pragma endregion