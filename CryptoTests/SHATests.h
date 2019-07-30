#pragma once
#include "SHA1.h"
#include "UnitTest.h"
#pragma region Тесты

#pragma region Хэш строки
///<summary>
/// Хэш строки
///</summary>
class SHAStringTest :public UnitTest<string> {
public:
	SHAStringTest(vector<string>values) :UnitTest("Хэш строки", values) {

	}
	void Test() override {
		SHA1 sha;
		this->Add(sha.GetHash("1234567890"));
		this->Add(sha.GetHash("qwerty"));
		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Хэш файла
///<summary>
/// Хэш файла
///</summary>
class SHAFileTest :public UnitTest<string> {
public:
	SHAFileTest(vector<string>values) :UnitTest("Хэш файла", values) {
		SHA1 sha;
		this->Add(sha.GetHash(sha.GetFileStream("SHA input.txt")));
	}
	void Test() override {

		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion
#pragma endregion
#pragma region Тесты SHA1
///<summary>
/// Тесты SHA1
///</summary>
class SHA1Tests :UnitTests {
public:
	SHA1Tests() : UnitTests("Тесты SHA1") {}
	void Start()override {
		//Запуск одного теста: TestsClassName(vector<type>items).Start();
		SHAStringTest({ "01b307acba4f54f55aafc33bb06bbbf6ca803e9a","b1b3773a05c0ed0176787a4f1574ff0075f7521e" }).Start();
		SHAFileTest({ "b48d77d4c0501df93b80d9a160e3457a18be579c" }).Start();
	}
};
#pragma endregion
