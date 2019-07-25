#pragma once
#include "LL.h"
#include "OWLL.h"
#include "TWLL.h"
#include "Enums.h"
#include "UnitTest.h"
class LLCreateTest :public UnitTest<int> {
public:
	IO io = IO();
	LL<int> list = LL<int>();
	LLCreateTest(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		list.head = new LLItem<int>(1);
		list.head->next = new LLItem<int>(2);
		list.head->next->next = new LLItem<int>(3);
		this->actual.push_back(list.head->data);
		this->actual.push_back(list.head->next->data);
		this->actual.push_back(list.head->next->next->data);
		UnitTest::Compare();
	}
};
class LLFindTest :public UnitTest<int> {
public:
	IO io = IO();
	LL<int> list = LL<int>();
	LLFindTest(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		list.IncLength();
		list.IncLength();
		list.IncLength();
		list.head = new LLItem<int>(1);
		list.head->next = new LLItem<int>(2);
		list.head->next->next = new LLItem<int>(3);
		this->actual.push_back(list.Find(1)->data);
		this->actual.push_back(list.Find(2)->data);
		this->actual.push_back((int)list.Find(999));
		this->actual.push_back(list.Find((size_t)0)->data);
		this->actual.push_back((int)list.Find((size_t)3));
		UnitTest::Compare();
	}
};
class OWLLAddTest1 :public UnitTest<int> {
public:
	IO io = IO();
	OWLList<int> list = OWLList<int>();
	OWLLAddTest1(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		for (int i = 0; i < 10; i++)
			list.Add(i + 1);

		list.Add(999, (size_t)5);
		list.Add(997, (size_t)0);
		list.Add(998, (size_t)list.GetLength() - 1);
		list.Add(new LLItem<int>(996));
		this->actual = list.ToList();
		UnitTest::Compare();
	}
};
class OWLLAddTest2 :public UnitTest<int> {
public:
	IO io = IO();
	OWLList<int> list = OWLList<int>();
	OWLLAddTest2(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		for (int i = 0; i < 10000; i++)
			list.Add(i + 1);
		this->actual.push_back(list.GetLength());
		UnitTest::Compare();
	}
};
class TWLLAddTest1 :public UnitTest<int> {
public:
	IO io = IO();
	TWLList<int> list = TWLList<int>();
	TWLLAddTest1(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		for (int i = 0; i < 10000; i++)
			list.Add(i + 1);
		this->actual.push_back(list.GetLength());
		UnitTest::Compare();
	}
};
class TWLLAddTest2 :public UnitTest<int> {
public:
	IO io = IO();
	TWLList<int> list = TWLList<int>();
	TWLLAddTest2(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		list.Add(1);
		this->actual.push_back(list.GetLast()->data);
		list.Add(8);
		this->actual.push_back(list.GetLast()->data);
		list.Add(14);
		this->actual.push_back(list.GetLast()->data);
		UnitTest::Compare();
	}
};
class TWLLAddTest3 :public UnitTest<int> {
public:
	IO io = IO();
	TWLLAddTest3(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		TWLList<int> list = TWLList<int>();
		for (int i = 0; i < 3; i++)
			list.Add(i + 1);
		list.Add(list);
		this->Add(list.ToList());
		UnitTest::Compare();
	}
};
class TWLLAddTest4 :public UnitTest<int> {
public:
	IO io = IO();
	TWLList<int> list = TWLList<int>();
	TWLLAddTest4(string title, vector<int> values) :UnitTest(title, values) {

	}
	void Test() override {
		TWLList<int> list1 = TWLList<int>();
		TWLList<int> list2 = TWLList<int>();
		vector<int> items;
		for (int i = 0; i < 5; i++)
			items.push_back(i + 1);
		list1.Add(items);
		list2.Add(list1);
		list2.Add(&list1);
		this->Add(list2.ToList());
		UnitTest::Compare();
	}
};
class TWLLOperatorsTest :public UnitTest<int> {
public:
	IO io = IO();
	TWLList<int> list = TWLList<int>();
	TWLLOperatorsTest(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		TWLList<int>* list1 = new TWLList<int>();
		TWLList<int>* list2 = new TWLList<int>();
		for (int i = 0; i < 3; i++)
		{
			list1->Add(i + 1);
			list2->Add(i);
		}
		TWLList<int> list3 = *list1 + *list2;
		this->Add(list3.ToList());
		UnitTest::Compare();
	}
};
class TWLLDeleteTest1 :public UnitTest<int> {
public:
	IO io = IO();
	TWLList<int> list = TWLList<int>();
	TWLLDeleteTest1(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		for (int i = 0; i < 10000; i++)
			list.Add(i + 1);
		list.Clear();
		this->actual.push_back(list.GetLength());
		UnitTest::Compare();
	}
};
class TWLLDeleteTest2 :public UnitTest<int> {
public:
	IO io = IO();
	TWLList<int> list = TWLList<int>();
	TWLLDeleteTest2(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		for (int i = 0; i < 10; i++)
			list.Add(i);
		for (int i = 0; i < 7; i++)
			list.Delete();
		this->Add(list.ToList());
		UnitTest::Compare();
	}
};
class LLTests : UnitTests {
public:
	LLTests() :UnitTests("Тесты связных списков") {
	}
	void Start() override {
		LLCreateTest("Создание базового класса односвязного списка", { 1,2,3 }).Start();
		LLFindTest("Поиск в базовом односвязном списке", { 1,2,NULL,1,NULL }).Start();
		//OWLLAddTest1("Односвязный список: добавление тест 1", { 997,1,2,3,4,5,999,6,7,8,9,998,10,996 }).Start();
		//OWLLAddTest2("Односвязный список: добавление тест 2", { 10000 }).Start();
		TWLLAddTest1("Двусвязный список: добавление тест 1", { 10000 }).Start();
		TWLLAddTest2("Двусвязный список: добавление тест 2", { 1,8,14 }).Start();
		TWLLAddTest3("Двусвязный список: добавление тест 3", { 1,2,3,1,2,3 }).Start();
		TWLLAddTest4("Двусвязный список: добавление тест 4", { 1,2,3,4,5,1,2,3,4,5 }).Start();
		TWLLDeleteTest1("Двусвязный список: удаление тест 1", { 0 }).Start();
		TWLLDeleteTest2("Двусвязный список: удаление тест 2", { 0, 1, 2 }).Start();
	}
};