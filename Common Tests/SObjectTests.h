
#pragma once
#include "UnitTest.h"
#include "SObject.h"
#include "SLoader.h"
#pragma region Тесты

#pragma region Добавление полей
///<summary>
/// Добавление полей
///</summary>
class AddFieldsTest :public UnitTest<int> {
public:
	AddFieldsTest(vector<int>values) :UnitTest("Добавление полей", values) {

	}
	void Test() override {
		SObject<string> obj;
		for (int i = 0; i < 100; i++)
			obj.Add("field" + to_string(i), to_string(i));
		this->Add({ (int)obj.GetFieldsCount() });
		try {
			obj.Add("field1", "alreadyExists");
		}
		catch (exception ex) {
			this->Add(1);
		}
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Удаление полей
///<summary>
/// Удаление полей
///</summary>
class DeleteFieldsTest :public UnitTest<int> {
public:
	DeleteFieldsTest(vector<int>values) :UnitTest("Удаление полей", values) {
		SObject<string> obj;
		for (int i = 0; i < 100; i++)
			obj.Add("field" + to_string(i), to_string(i));
		this->Add({ (int)obj.GetFieldsCount() });
		for (int i = 0; i < 10; i++)
			obj.Delete(i);
		for (int i = 90; i < 100; i++)
			obj.Delete("field" + to_string(i));
		this->Add({ (int)obj.GetFieldsCount() });
		try {
			obj.Delete("notExistingField");
		}
		catch (exception ex) {
			this->Add(1);
		}
		try {
			int notExistingIndex = 1024;
			obj.Delete(notExistingIndex);
		}
		catch (exception ex) {
			this->Add(1);
		}
	}
	void Test() override {

		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region SET полей
///<summary>
/// SET полей
///</summary>
class SetFieldsTest :public UnitTest<string> {
public:
	SetFieldsTest(vector<string>values) :UnitTest("SET полей", values) {

	}
	void Test() override {

		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region GET полей
///<summary>
/// GET полей
///</summary>
class GetFieldsTest :public UnitTest<string> {
public:
	GetFieldsTest(vector<string>values) :UnitTest("GET полей", values) {

	}
	void Test() override {

		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Сохранение
///<summary>
/// Сохранение
///</summary>
class SaveTest :public UnitTest<string> {
public:
	SaveTest(vector<string>values) :UnitTest("Сохранение", values) {

	}
	void Test() override {
		SObject<string> obj;
		obj.Add("name", "Alex");
		obj.Add("age", "123");
		obj.Add("details", "LOL");
		this->Add(obj.ToString());
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Загрузка
///<summary>
/// Загрузка
///</summary>
class LoadTest :public UnitTest<string> {
public:
	LoadTest(vector<string>values) :UnitTest("Загрузка", values) {

	}
	void Test() override {
		SObject<string> obj;
		obj.Add("name", "Alex");
		obj.Add("age", "123");
		obj.Add("details", "LOL");
		string objStr = obj.ToString();
		this->Add(SObject<string>(objStr).ToString());
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Тест операторов
///<summary>
/// Тест операторов
///</summary>
class SObjectOperatorsTest :public UnitTest<bool> {
public:
	SObjectOperatorsTest(vector<bool>values) :UnitTest("Тест операторов", values) {

	}
	void Test() override {
		SObject<string> obj, objSame, objAnother;
		obj.Add("name", "Alex");
		objSame.Add("name", "Alex");
		objAnother.Add("name", "Dmitry");
		this->Add(obj == objSame);
		this->Add(obj == objAnother);
		this->Add(obj != objAnother);
		this->Add(obj != objSame);
		//this->Add(vector<bool>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Тестирование загрузчика
///<summary>
/// Тестирование загрузчика
///</summary>
class SLoaderTest :public UnitTest<bool> {
public:
	SLoaderTest(vector<bool>values) :UnitTest("Тестирование загрузчика", values) {

	}
	void Test() override {
		SLoader<string> loader;
		vector<SObject<string>> expectedObjects = {
			SObject<string>({ SField<string>("name", "Alex"),SField<string>("age", "123 456"),SField<string>("details", "LOL") }),
			SObject<string>({ SField<string>("name", "Ivan"),SField<string>("age", "789 012"),SField<string>("details", "KEK") }),
			SObject<string>({ SField<string>("name", "Vladimir"),SField<string>("lastname", "Putin"),SField<string>("details", "Pecheneg") })
		};
		loader.Save("SLoaderTest.txt", expectedObjects);
		vector<SObject<string>> actualObjects = loader.Load("SLoaderTest.txt");
		bool result = true;
		for (int i=0;i< actualObjects.size();i++)
			if (expectedObjects[i] != actualObjects[i]) {
				result = false;
				break;
			}
		this->Add(result);
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma endregion
#pragma region Тесты сериализуемого объекта
///<summary>
/// Тесты сериализуемого объекта
///</summary>
class SObjectsTests :UnitTests {
public:
	SObjectsTests() : UnitTests("Тесты сериализуемого объекта") {}
	void Start()override {
		//Запуск одного теста: TestsClassName(vector<type>items).Start();
		AddFieldsTest({ 100,1 }).Start();
		DeleteFieldsTest({ 100,80,1,1 }).Start();
		SaveTest({ "{name:Alex;age:123;details:LOL;}" }).Start();
		LoadTest({ "{name:Alex;age:123;details:LOL;}" }).Start();
		SObjectOperatorsTest({ true,false,true,false }).Start();
		SLoaderTest({ true }).Start();
	}
};
#pragma endregion
#pragma endregion
