
#pragma once
#include "UnitTest.h"
#include "Sorts.h"
#pragma region Тесты

#pragma region Быстрая сортировка
///<summary>
/// Быстрая сортировка
///</summary>
class QuickSortTest :public UnitTest<int> {
public:
	QuickSortTest(vector<int>values) :UnitTest("Быстрая сортировка", values) {

	}
	void Test() override {
		Sorts<int> sorts;
		vector<int>items = { 4,2,1,3,0,5 };
		this->Add(sorts.QuickSort(items, Direction::ascending));
		this->Add(sorts.QuickSort(items, Direction::descending));
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
class QuickSortEdgeTest :public UnitTest<bool> {
public:
	QuickSortEdgeTest(vector<bool>values) :UnitTest("Быстрая сортировка: граничные случаи", values) {

	}
	void Test() override {
		Sorts<int> sorts;
		vector<int> empty;
		vector<int> single = { 42 };
		vector<int> duplicates = { 2,1,2,1 };
		this->Add(sorts.QuickSort(empty).empty());
		this->Add(sorts.QuickSort(single) == vector<int>({ 42 }));
		this->Add(sorts.QuickSort(duplicates, Direction::ascending) == vector<int>({ 1,1,2,2 }));
		this->Add(sorts.QuickSort(duplicates, Direction::descending) == vector<int>({ 2,2,1,1 }));
		UnitTest::Compare();
	}
};
#pragma endregion
#pragma endregion
#pragma region Тесты сортировок
///<summary>
/// Тесты сортировок
///</summary>
class SortsTests :UnitTests {
public:
	SortsTests() : UnitTests("Тесты сортировок") {}
	void Start()override {
		//Запуск одного теста: TestsClassName(vector<type>items).Start();
		QuickSortTest({ 0,1,2,3,4,5,5,4,3,2,1,0 }).Start();
		QuickSortEdgeTest({ true,true,true,true }).Start();
	}
};
#pragma endregion
#pragma endregion


