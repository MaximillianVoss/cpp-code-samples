
#pragma once
#include "UnitTest.h"
#include "BinarySearch.h"
#pragma region Тесты

#pragma region 
///<summary>
/// Тест двоичного поиска
///</summary>
class BinarySearchTest1 :public UnitTest<int> {
public:
	BinarySearchTest1(vector<int>values) :UnitTest("Тест двоичного поиска 1", values) {

	}
	void Test() override {
		BinarySearch<int> bs;
		this->Add({
			bs.Find({0},0),
			bs.Find({0,1},1),
			bs.Find({0,1},99),
			bs.Find({0,1,2,3,4,5,6},5),
			bs.Find({0,1,2,3,4,5,6},2),
			bs.Find({3,1,2},3),
			bs.Find({3,1,2},0)
			});
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};

#pragma region Тест двоичного поиска
///<summary>
/// Тест двоичного поиска
///</summary>
class BinarySearchTest2 :public UnitTest<bool> {
public:
	BinarySearchTest2(vector<bool>values) :UnitTest("Тест двоичного поиска 2", values) {

	}
	void Test() override {
		BinarySearch<int> bs;
		this->Add({
			bs.IsExist({0},0),
			bs.IsExist({0,1},1),
			bs.IsExist({0,1},99),
			bs.IsExist({0,1,2,3,4,5,6},5),
			bs.IsExist({0,1,2,3,4,5,6},99),
			bs.IsExist({3,1,2},1),
			bs.IsExist({3,1,2},0)
			});
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion
#pragma endregion
#pragma endregion
#pragma region Тест поиска
///<summary>
/// Тест поиска
///</summary>
class SearchTests :UnitTests {
public:
	SearchTests() : UnitTests("Тест поиска") {}
	void Start()override {
		//Запуск одного теста: TestsClassName(vector<type>items).Start();
		BinarySearchTest1({ 0,1,-1,5,2,2,-1 }).Start();
		BinarySearchTest2({ true,true,false,true,false,true,false }).Start();
	}
};
#pragma endregion
#pragma endregion
