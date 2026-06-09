#pragma once
#include "UnitTest.h"
#include "DataPack.h"
#pragma region Тесты


#pragma region Тест создания и сериализации
///<summary>
/// Тест создания и сериализации
///</summary>
class CreateSerialisationTest :public UnitTest<bool> {
public:
	CreateSerialisationTest(vector<bool>values) :UnitTest("Тест создания и сериализации", values) {

	}
	void Test() override {
		DataPack<int> dataPack = DataPack<int>("DataPack1", "Y", "X", true, { 1,2,3,4,5,6 }, { 7,8,9,10,11,12 });
		string str = dataPack.ToString();
		DataPack<int> dataPackLoaded = DataPack<int>(str);
		string str1 = dataPack.ToString();
		string str2 = dataPackLoaded.ToString();
		//для добавления результатов
		this->Add(dataPack.ToString() == dataPackLoaded.ToString());
		IO().WriteLines("C:\\TestDataPack.txt", { dataPack.ToString() });
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma endregion
#pragma region Тесты набора данных
///<summary>
/// Тесты набора данных
///</summary>
class DataPackTests :UnitTests {
public:
	DataPackTests() : UnitTests("Тесты набора данных") {}
	void Start()override {
		//Запуск одного теста: TestsClassName(vector<type>items).Start();
		CreateSerialisationTest({ true }).Start();
	}
};
#pragma endregion
#pragma endregion
