
#pragma once
#include "UnitTest.h"
#include "SField.h"
#pragma region Тесты

#pragma region Тест сериализации
///<summary>
/// Тест сериализации
///</summary>
class SerializationTest :public UnitTest<string> {
public:
	SerializationTest(vector<string>values) :UnitTest("Тест сериализации", values) {

	}
	void Test() override {
		SField<string> field("someName", "someValue");
		this->Add(field.ToString());
		UnitTest::Compare();
	}
};
#pragma endregion


#pragma region Тест десериализации
///<summary>
/// Тест десериализации
///</summary>
class DeserializationTest :public UnitTest<string> {
public:
	DeserializationTest(vector<string>values) :UnitTest("Тест десериализации", values) {

	}
	void Test() override {
		SField<string> field = SField<string>("someName:someValue;");
		this->Add(field.ToString());
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion


#pragma region Тест операторов
///<summary>
/// Тест операторов
///</summary>
class SFieldOperatorsTest :public UnitTest<bool> {
public:
	SFieldOperatorsTest(vector<bool>values) :UnitTest("Тест операторов", values) {

	}
	void Test() override {
		stringstream ss;
		SField<string> field = SField<string>("someName:someValue;");
		SField<string> fieldSame = SField<string>("someName:someValue;");
		SField<string> fieldAnother = SField<string>("anotherName:anotherValue;");
		this->Add(field == fieldSame);
		this->Add(field == fieldAnother);
		this->Add(field != fieldAnother);
		this->Add(field != fieldSame);
		ss << field;
		this->Add(ss.str() == "someName:someValue;");
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma endregion
#pragma region Тесты сериализуемого поля
///<summary>
/// Тесты сериализуемого поля
///</summary>
class SFieldTests :UnitTests {
public:
	SFieldTests() : UnitTests("Тесты сериализуемого поля") {}
	void Start()override {
		SerializationTest({ "someName:someValue;" }).Start();
		DeserializationTest({ "someName:someValue;" }).Start();
		SFieldOperatorsTest({ true,false,true,false,true }).Start();
	}
};
#pragma endregion
#pragma endregion
