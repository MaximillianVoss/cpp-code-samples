#pragma once
#include "Blockchain.h"
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
		BlockChain bc;
		this->Add(bc.GetClientsCount());
		bc.Add(Client("", "qwerty"));
		bc.Add(Client("", "12345678"));
		this->Add(bc.GetClientsCount());
		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Соединение клиентов
///<summary>
/// Соединение клиентов
///</summary>
class BlockChainConnectTest :public UnitTest<bool> {
public:
	BlockChainConnectTest(vector<bool>values) :UnitTest("Соединение клиентов", values) {

	}
	void Test() override {
		BlockChain bc;
		Client c1 = bc.Add(Client("", "qwerty"));
		Client c2 = Client("", "12345678");
		this->Add(bc.Connect(c1));
		this->Add(bc.Connect(c2));
		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Рассоединение клиентов
///<summary>
/// Рассоединение клиентов
///</summary>
class BlockChainDicsonnectTest :public UnitTest<bool> {
public:
	BlockChainDicsonnectTest(vector<bool>values) :UnitTest("Рассоединение клиентов", values) {

	}
	void Test() override {
		BlockChain bc;
		Client c1 = Client("", "qwerty");
		Client c2 = Client("", "12345678");
		c1 = bc.Add(c1);
		c1.isOnline = bc.Connect(c1);
		this->Add(bc.Disconnect(c1));
		c2 = bc.Add(c2);
		this->Add(bc.Disconnect(c2));
		c2.isOnline = bc.Connect(c2);
		this->Add(bc.Disconnect(c2));
		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Добавление Блока с ручной подписью
///<summary>
/// Добавление Блока с ручной подписью
///</summary>
class BlockChainAddTest1 :public UnitTest<int> {
public:
	BlockChainAddTest1(vector<int>values) :UnitTest("Добавление Блока с ручной подписью", values) {

	}
	string GetTime() {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
		return oss.str();
	}
	void Test() override {
		BlockChain bc;
		IO io = IO();
		string fileName = "BC add log.txt";
		for (size_t i = 0; i < 100; i++)
		{
			Client c = Client("", to_string(i));
			c = bc.Add(c);
			c.isOnline = bc.Connect(c);
		}
		this->Add(bc.GetBlocksCount());
		for (size_t i = 0; i < 100; i++)
		{
			Block b = Block(to_string(i), "");
			b = bc.Add(b);
			io.Append(fileName, { "_____________", GetTime(),"Добавление блока",b.ToString(true) }, true);
		}
		this->Add(bc.GetBlocksCount());
		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
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
		BlockChainAddWallet({ 0,2 }).Start();
		BlockChainConnectTest({ true,false }).Start();
		BlockChainDicsonnectTest({ true,false,true }).Start();
		BlockChainAddTest1({ 0,100 }).Start();
	}
};
#pragma endregion
#pragma endregion
