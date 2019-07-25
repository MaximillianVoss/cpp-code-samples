#pragma once
#include "Blockchain.h"
#include "UnitTest.h"

class BCAddBLockTest1 :public UnitTest<string> {
public:

	BCAddBLockTest1(string title, vector<string>values) :UnitTest(title, values) {

	}
	void Test() override {
		BlockChain blockChain;
		Client client1 = Client();
		Client client2 = Client();
		blockChain.Connect(&client1);
		blockChain.Connect(&client2);
		for (int i = 0; i <= 5; i++)
			blockChain.Add(new Block(to_string(i)));
		this->Add(blockChain.ToString());
		UnitTest::Compare();
	}
};

class BCConnectTest1 :public UnitTest<string> {
public:

	BCConnectTest1(string title, vector<string>values) :UnitTest(title, values) {

	}
	void Test() override {
		BlockChain blockChain;
		for (int i = 0; i <= 5; i++)
			blockChain.Connect(new Client());
		for (Client client : blockChain.GetClientList())
			this->Add(client.id);
		UnitTest::Compare();
	}
};

class BCVotingAlpha :public UnitTest<string> {
public:

	BCVotingAlpha(string title, vector<string>values) :UnitTest(title, values) {

	}
	void Test() override {
		BlockChain blockChain;
		int n = 15;
		cout << "Номер победителя голосования:" << blockChain.VotingAlpha(n) << " из " << n << endl;
		UnitTest::Compare();
	}
};

class BlockchainTests :UnitTests {
public:
	BlockchainTests() : UnitTests("Тесты блок чейна") {}
	void Start()override {
		//BCAddBLockTest1("Добавление блоков", { "0 1->1 1->2 1->3 1->4 1->5 1" }).Start();
		//BCConnectTest1("Соединение клиента", { "1","2","3","4","5","6" }).Start();
		BCVotingAlpha("Тестирование голосования", {}).Start();
	}
};