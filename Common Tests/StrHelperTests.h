#pragma once
#include "StrHelper.h"
#include "UnitTest.h"

class SHJoinTest :public UnitTest<string> {
public:
	StrHelper sh = StrHelper();
	SHJoinTest(string title, vector<string>values) :UnitTest(title, values) {

	}
	void Test() override {
		this->actual.push_back(sh.Join({ "lol","kek","cheburek" }, "-,-"));
		this->actual.push_back(sh.Join({ "1","2","3","4","5","6","7","8","9" }, ","));
		UnitTest::Compare();
	}
};
class SHReplaceTest :public UnitTest<string> {
public:
	StrHelper sh = StrHelper();
	SHReplaceTest(string title, vector<string>values) :UnitTest(title, values) {

	}
	void Test() override {
		this->actual.push_back(sh.Replace("lolololo", "lo", "ke"));
		this->actual.push_back(sh.Replace("1234567890", "567", "111"));
		UnitTest::Compare();
	}
};
class SHRemoveTest :public UnitTest<string> {
public:
	StrHelper sh = StrHelper();
	SHRemoveTest(string title, vector<string>values) :UnitTest(title, values) {

	}
	void Test() override {
		this->actual.push_back(sh.Remove("1 2 3 4 5", " "));
		this->actual.push_back(sh.Remove(" lo loll", " lol"));
		this->actual.push_back(sh.Remove("one two three four", "three"));
		UnitTest::Compare();
	}
};
class SHContainsTest :public UnitTest<bool> {
public:
	StrHelper sh = StrHelper();
	SHContainsTest(string title, vector<bool>values) :UnitTest(title, values) {

	}
	void Test() override {
		this->actual.push_back(sh.Contains("12345", "123"));
		this->actual.push_back(sh.Contains("12 345", "123"));
		this->actual.push_back(sh.Contains("12345", { "1","2","3","4","5" }));
		this->actual.push_back(sh.Contains("123456", { "1","2","3","4","5","7" }));
		UnitTest::Compare();
	}
};
class SHIsNumberTest :public UnitTest<bool> {
public:
	StrHelper sh = StrHelper();
	SHIsNumberTest(string title, vector<bool>values) :UnitTest(title, values) {

	}
	void Test() override {
		this->actual.push_back(sh.IsNumber("12345"));
		this->actual.push_back(sh.IsNumber("ф12345"));
		this->actual.push_back(sh.IsNumber("-1.2345"));
		this->actual.push_back(sh.IsNumber("+1__2345"));
		this->actual.push_back(sh.IsNumber("+1.34456779"));
		this->actual.push_back(sh.IsNumber("-44444.55555"));
		this->actual.push_back(sh.IsNumber("1A"));
		this->actual.push_back(sh.IsNumber("ABCDEF"));
		UnitTest::Compare();
	}
};
class SHGetNumbersTest :public UnitTest<string> {
public:
	StrHelper sh = StrHelper();
	SHGetNumbersTest(string title, vector<string>values) :UnitTest(title, values) {

	}
	void Test() override {
		this->Add(sh.GetNumbers("123 asdas 456 asdasdasfds 12,3 asdasd 4.5"));
		UnitTest::Compare();
	}
};
class SHSplitTest :public UnitTest<string> {
public:
	StrHelper sh = StrHelper();
	SHSplitTest(string title, vector<string>values) :UnitTest(title, values) {

	}
	void Test() override {
		this->Add(sh.Split("one two three 1 2 3 4 5", " ", ""));
		this->Add(sh.Split("one.,two.,", ".,", "."));
		UnitTest::Compare();
	}
};
class SHRemoveCopiesTest :public UnitTest<string> {
public:
	StrHelper sh = StrHelper();
	SHRemoveCopiesTest(string title, vector<string>values) :UnitTest(title, values) {

	}
	void Test() override {
		this->Add(sh.RemoveCopies({ "1","2","3","4","5","6","3","4" }));
		this->Add(sh.RemoveCopies({ "lol","kek","kek","lol","some text" }));
		UnitTest::Compare();
	}
};
class StrHelperTests :UnitTests {
public:
	StrHelperTests() : UnitTests("Тесты класса для строк") {}
	void Start()override {
		SHJoinTest("Join", { "lol-,-kek-,-cheburek","1,2,3,4,5,6,7,8,9" }).Start();
		SHReplaceTest("Replace", { "kekekeke","1234111890" }).Start();
		SHRemoveTest("Remove", { "12345","","one two  four" }).Start();
		SHContainsTest("Contains", { true,false,true,false }).Start();
		SHGetNumbersTest("GetNumbers", { "123","456","4.5" }).Start();
		SHIsNumberTest("IsNumber", { true,false,true,false,true,true,false,false }).Start();
		SHSplitTest("Split", { "one","two","three","1","2","3","4","5","one",".","two","." }).Start();
		SHRemoveCopiesTest("RemoveCopies", { "1","2","3","4","5","6","lol","kek","some text" }).Start();
	}
};