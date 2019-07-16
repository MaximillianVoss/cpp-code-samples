#pragma once
#include "Generator.h"
/// <summary>
/// Юнит тест
/// </summary>
template<typename T>
class UnitTest {
private:
	string prefixName = "Test:";
	void Print(vector<T> items) {
		for (T item : items)
			cout << item << endl;
	}
public:
	string name;
	vector<T> expected;
	vector<T> actual;
	UnitTest() {
		this->name = this->prefixName + Constants::Strings::undefined;
		this->expected = 0;
	}
	UnitTest(string name, vector<T> expected) {
		this->name = this->prefixName + name;
		this->expected = expected;
	}
	virtual void Test() = 0;
	virtual bool Compare(T actual) { return false; };
	virtual bool Compare(vector<T> actual) { return false; };
	bool Compare(vector<T> actual, vector<T> expected) {
		if (actual.size() != expected.size())
			return false;
		for (int i = 0; i < actual.size(); i++)
			if (actual[i] != expected[i])
				return false;
		return true;
	}
	bool Compare() {
		return this->Compare(this->actual, this->expected);
	}
	void Start() {
		cout << this->name << endl;
		try {
			Test();
			if (this->Compare())
				cout << Constants::Strings::Messages::UnitTest::passed << endl;
			else {
				cout << Constants::Strings::Messages::UnitTest::failed << endl;
				cout << Constants::Strings::Messages::UnitTest::expected << endl;
				this->Print(this->expected);
				cout << Constants::Strings::Messages::UnitTest::actual << endl;
				this->Print(this->actual);
			}
		}
		catch (exception ex) {
			cout << ex.what() << endl;
		}
	}
};
/// <summary>
/// Стек юнит тестов
/// </summary>
template<typename T>
class UnitTests {
private:
	vector<UnitTest<T>> tests;
public:
	void Add(UnitTest<T>test) {
		this->tests.push_back(test);
	}
	void Clear() {
		this->tests.clear();
	}
	void Start() {
		for (test : tests)
			test.Start();
	}
};