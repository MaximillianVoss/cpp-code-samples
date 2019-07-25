#pragma once
#include "ShamirsSecretSharing.h"
#include "UnitTest.h"

class SSSTest1 :public UnitTest<string> {
public:
	//BlockChain blockChain;
	SSSTest1(string title, vector<string>values) :UnitTest(title, values) {

	}
	void Test() override {
		//blockChain.Add(Block("1"));
		UnitTest::Compare();
	}
};

class SSSTests :UnitTests {
public:
	SSSTests() : UnitTests("Тест Разделения секрета Шамира") {}
	void Start()override {
	}
};