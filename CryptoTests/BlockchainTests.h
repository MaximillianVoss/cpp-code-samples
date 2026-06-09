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
	BlockChainVotingPlotTest(vector<bool>values) :UnitTest("Голосование графики", values, true) {

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
	/// <summary>
	/// Графики голосований и распределениея токенов
	/// </summary>
	/// <param name="initialClients">начальное число клиентов</param>
	/// <param name="initialCoins">начальное число монет</param>
	/// <param name="step">шаг с которым будет изменяться число проходов</param>
	/// <param name="setpsCount">количество шагов</param>
	/// <param name="testsCount">число шагов</param>
	/// <param name="plotGoup">группа графиков, по умолчанию 1</param>
	/// <param name="votesPercent">порог голосования</param>
	/// <returns></returns>
	Plotter<int> TestVoting1(
		size_t initialClients,
		size_t initialCoins,
		size_t step,
		size_t testsCount,
		size_t plotGoup = 1,
		float votesPercent = 0.51) {
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
		this->SetTickerMax(testsCount);
		for (int i = 0; i < testsCount; i++) {
			this->IncTicker();
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
			IO().Append("commonPlotLog.txt", { bc->GetLogStr() });
		}
		plotData.Add(votingDP1);
		plotData.Add(votingDP2);
		return plotData;
	}
	/// <summary>
	/// Графики голосований при изменении количества клиентов
	/// </summary>
	/// <param name="initialClients">начальное число клиентов</param>
	/// <param name="initialCoins">начальное число монет</param>
	/// <param name="step">шаг с которым будет изменяться число клиентов</param>
	/// <param name="setpsCount">число шагов</param>
	/// <param name="testsCount">число тестов</param>
	/// <param name="plotGoup">группа графиков, по умолчанию 1</param>
	/// <param name="votesPercent">порог голосования</param>
	/// <returns></returns>
	Plotter<int> TestVoting2(
		size_t initialClients,
		size_t initialCoins,
		size_t step,
		size_t setpsCount,
		size_t testsCount = 10,
		size_t plotGoup = 1,
		float votesPercent = 0.51) {
		Plotter<int> plotData("Графики голосований", { });
		stringstream ss;
		ss << "Случаи проваленных голосований(клиентов-" << initialClients << " " << "токенов-" << initialCoins << ")";
		string votingTitle1 = ss.str();
		ss.str(std::string());
		DataPack<int> votingDP1 = DataPack<int>(
			votingTitle1,
			"Количество клиентов",
			"Количество случаев",
			plotGoup
			);
		ss << "Случаи, когда в голосовании победило больше двух клиентов";
		string votingTitle2 = ss.str();
		ss.str(std::string());
		DataPack<int> votingDP2 = DataPack<int>(
			votingTitle2,
			"Количество клиентов",
			"Количество случаев",
			plotGoup
			);
		for (int i = 0; i < setpsCount; i++, initialClients += step) {
			BlockChain* bc = GenerateBlockchain(initialClients, initialCoins);
			bc->SetVotesPercent(votesPercent);
			for (int j = 0; j < testsCount; j++)
				bc->GenerateBlock(true);
			votingDP1.AddPoint(initialClients, bc->GetCounterVotingFailed());
			votingDP2.AddPoint(initialClients, bc->GetCounterVotingMultWinners());
			IO().Append("commonPlot2Log.txt", { bc->GetLogStr() });
		}
		plotData.Add(votingDP1);
		plotData.Add(votingDP2);

		return plotData;
	}
	/// <summary>
	/// Графики голосований при изменении порога голосования
	/// </summary>
	/// <param name="initialClients">начальное число клиентов</param>
	/// <param name="initialCoins">начальное число монет</param>
	/// <param name="step">шаг с которым будет изменяться порог голосования</param>
	/// <param name="setpsCount">число шагов</param>
	/// <param name="testsCount">число тестов</param>
	/// <param name="plotGoup">группа графиков, по умолчанию 1</param>
	/// <param name="votesPercent">порог голосования</param>
	/// <returns></returns>
	Plotter<float> TestVoting3(
		size_t initialClients,
		size_t initialCoins,
		float step,
		size_t setpsCount,
		size_t testsCount,
		size_t plotGoup = 1,
		float votesPercent = 0.51) {
		Plotter<float> plotData("Графики голосований", { });
		stringstream ss;
		ss << "Случаи проваленных голосований(клиентов-" << initialClients << " " << "токенов-" << initialCoins << ")";
		string votingTitle1 = ss.str();
		ss.str(std::string());
		DataPack<float> votingDP1 = DataPack<float>(
			votingTitle1,
			"Порог голосования",
			"Количество случаев",
			plotGoup
			);
		ss << "Случаи, когда в голосовании победило больше двух кандидатов";
		string votingTitle2 = ss.str();
		ss.str(std::string());
		DataPack<float> votingDP2 = DataPack<float>(
			votingTitle2,
			"Порог голосования",
			"Количество случаев",
			plotGoup
			);
		for (int i = 0; i < setpsCount; i++, votesPercent += step) {
			BlockChain* bc = GenerateBlockchain(initialClients, initialCoins);
			bc->SetVotesPercent(votesPercent >= 1.0 ? 1.0 : votesPercent);
			for (int j = 0; j < testsCount; j++) {
				for (int j = 0; j < (i + 1) * step; j++)
					bc->GenerateBlock(true);
			}
			votingDP1.AddPoint(votesPercent, bc->GetCounterVotingFailed());
			votingDP2.AddPoint(votesPercent, bc->GetCounterVotingMultWinners());
			IO().Append("commonPlot3Log.txt", { bc->GetLogStr() });
		}
		plotData.Add(votingDP1);
		plotData.Add(votingDP2);

		return plotData;
	}
	void VoteTest() {
		IO().WriteLines("C:\\commonPlot.txt", { TestVoting1(
			10,//число клиентов
			100,//число монет
			10,//шаг числа экспериментов
			5,//чило экспериментов(шагов)
			1,//группа графиков
			0.55//порог голосования
		).ToString() });
		IO().WriteLines("C:\\commonPlot2.txt", { TestVoting2(
			10,//число клиентов
			200,//число монет
			10,//шаг - прирост числа клиентов
			5,//число шагов
			10,//число экспериментов
			1,//группа графиков
			0.55//порог голосования
		).ToString() });
		IO().WriteLines("C:\\commonPlot3.txt", { TestVoting3(
			10,//число клиентов
			100,//число монет
			0.1,//шаг - прирост порога голосования
			5,//число шагов
			10,//число экспериментов
			1,//группа графиков
			0.55//порог голосования
		).ToString() });
	}
	void Test() override {

		VoteTest();
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