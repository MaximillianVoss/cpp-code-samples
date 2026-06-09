#pragma once

#pragma once
#include "UnitTest.h"
#include "AVLTree.h"
#pragma region Тесты

#pragma region Добавление
///<summary>
/// Добавление
///</summary>
class AVLTreeAddTest :public UnitTest<string> {
public:
	AVLTreeAddTest(vector<string>values) :UnitTest("Добавление", values) {

	}
	void Test() override {
		AVLTree<string> tree = AVLTree<string>();
		vector<string> items = { "0","1","5","/","/" };
		for (int i = 0; i < items.size(); i++)
			tree.Add(items[i]);
		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion
#pragma endregion
#pragma region Тесты АВЛ дерева
///<summary>
/// Тесты АВЛ дерева
///</summary>
class AVLTreeTests :UnitTests {
public:
	AVLTreeTests() : UnitTests("Тесты АВЛ дерева") {}
	void Start()override {
		//Запуск одного теста: TestsClassName(vector<type>items).Start();
	}
};
#pragma endregion
#pragma endregion
