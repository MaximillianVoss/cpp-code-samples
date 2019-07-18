#pragma once
#include "OWLL.h"
#include "TWLL.h"
#include "Enums.h"
#include "UnitTest.h"
class OWLLTest :public UnitTest<int> {
public:
	IO io = IO();
	OWLList<int> list = OWLList<int>();
	OWLLTest(string title, vector<int> values) :UnitTest(title, values) {
	}

	void Test() override {
		for (int i = 0; i < 10; i++)
			list.Add(i + 1);
		io.Print(list.ToString());
		UnitTest::Compare();
	}
};
class LLTests {
public:
	LLTests() {
	}
	void Start() {
		OWLLTest("Тест односвязного списка", { 1,2,3,4,5,6,7,8,9,10 }).Start();
	}
};