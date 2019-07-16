#pragma once
#include "Enums.h"
#include "IO.h"
#include "UnitTest.h"

//IO io = IO();
//string a = io.GetStr();
//io.WriteLines("lol.txt", { a });
class InIntTest :public UnitTest<int> {
public:
	IO io = IO();
	InIntTest(string title, vector<int> values) :UnitTest(title, values) {

	}

	void Test() override {
		string input = Constants::Strings::Messages::Inputs::inputValue;
		input += " ";
		this->actual.push_back(io.Get<int>(input + "1"));
		this->actual.push_back(io.Get<int>(input + "22"));
		this->actual.push_back(io.Get<int>(input + "333"));
		UnitTest::Compare();
	}
};
class InDoubleTest :public UnitTest<double> {
public:
	IO io = IO();
	InDoubleTest(string title, vector<double> values) :UnitTest(title, values) {

	}

	void Test() override {
		string input = Constants::Strings::Messages::Inputs::inputValue;
		input += " ";
		this->actual.push_back(io.Get<double>(input + "1.0"));
		this->actual.push_back(io.Get<double>(input + "2.3"));
		this->actual.push_back(io.Get<double>(input + "4.55"));
		UnitTest::Compare();
	}
};
class InStringTest :public UnitTest<string> {
public:
	IO io = IO();
	InStringTest(string title, vector<string> values) :UnitTest(title, values) {

	}

	void Test() override {
		string input = Constants::Strings::Messages::Inputs::inputValue;
		input += " ";
		this->actual.push_back(io.Get<string>(input + "hello"));
		this->actual.push_back(io.Get<string>(input + "lol"));
		this->actual.push_back(io.GetLine(input + "abc defgh"));
		UnitTest::Compare();
	}
};
class FileCreateRemoveTest :public UnitTest<bool> {
public:
	IO io = IO();
	FileCreateRemoveTest(string title, vector<bool> values) :UnitTest(title, values) {

	}

	void Test() override {
		string fileName = this->name + io.txtExtension;
		io.AddFile(fileName);
		this->actual.push_back(io.IsExists(fileName));
		this->actual.push_back(io.RemoveFile(fileName));
		this->actual.push_back(io.IsExists(fileName));
		UnitTest::Compare();
	}
};
class FileIOTest :public UnitTest<string> {
public:
	IO io = IO();
	FileIOTest(string title, vector<string> values) :UnitTest(title, values) {

	}

	void Test() override {
		string fileName = this->name + io.txtExtension;
		io.WriteLines(fileName, this->expected, true);
		this->actual = io.ReadLines(fileName);
		UnitTest::Compare();
	}
};
class FileAppendTest :public UnitTest<string> {
public:
	IO io = IO();
	FileAppendTest(string title, vector<string> values) :UnitTest(title, values) {

	}

	void Test() override {
		string fileName = this->name + io.txtExtension;
		if (io.IsExists(fileName))
			io.ClearLines(fileName);
		io.Append(fileName, this->expected, true);
		this->actual = io.ReadLines(fileName);
		UnitTest::Compare();
	}
};
class OutTest :public UnitTest<bool> {
public:
	IO io = IO();
	OutTest(string title, vector<bool> values) :UnitTest(title, values) {
	}

	void Test() override {
		io.SetColor(ConsoleColor::dark_red, ConsoleColor::black);
		io.Print("Красная строка на черном фоне");
		io.SetColor(ConsoleColor::dark_green, ConsoleColor::white);
		io.Print("Зеленая строка на белом фоне");
		io.SetColor(ConsoleColor::black, ConsoleColor::dark_red);
		io.Print("Черная строка на красном фоне");
		io.SetColor(ConsoleColor::white, ConsoleColor::black);
		io.Print("По умолчанию:белый текст на черном фоне");
		vector<int>items;
		for (int i = 0; i < 10; i++)
			items.push_back(i);
		//io.Print(items, "Вывод вектора 1-10:", true);
		io.Print(items);
		io.Print(items, "Вывод вектора 1-10:");
		UnitTest::Compare();
	}
};
class IOTests {
public:
	IOTests() {
	}
	void Start() {
		FileCreateRemoveTest("Создание и удаление файлов", { true,true,false }).Start();
		FileIOTest("Запись чтение файлов", { "hello","lol","abc defgh" }).Start();
		FileAppendTest("Добавление строк в файл", { "hello","lol","abc defgh" }).Start();
		OutTest("Вывод в консоль", {}).Start();
		//InIntTest intTest = InIntTest("Ввод целочисленных данных", { 1,22,333 });
		//intTest.Start();
		//InDoubleTest doubleTest = InDoubleTest("Ввод вещественных данных", { 1.0,2.3,4.55 });
		//doubleTest.Start();
		//InStringTest stringTest = InStringTest("Ввод строковых данных", { "hello","lol","abc defgh" });
		//stringTest.Start();
		//OutTest outTests = OutTest();
		//outTests.Start();
	}
};