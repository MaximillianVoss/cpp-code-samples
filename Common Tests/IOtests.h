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
		this->actual.push_back(io.Get<int>(input + "1" + io.endInstruction));
		this->actual.push_back(io.Get<int>(input + "22" + io.endInstruction));
		this->actual.push_back(io.Get<int>(input + "333" + io.endInstruction));
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
		this->actual.push_back(io.Get<double>(input + "1.0" + io.endInstruction));
		this->actual.push_back(io.Get<double>(input + "2.3" + io.endInstruction));
		this->actual.push_back(io.Get<double>(input + "4.55" + io.endInstruction));
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
		this->actual.push_back(io.Get<string>(input + "hello" + io.endInstruction));
		this->actual.push_back(io.Get<string>(input + "lol" + io.endInstruction));
		this->actual.push_back(io.GetLine(input + "abc def" + io.endInstruction));
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
		io.Print("Красная строка на черном фоне", true);
		io.SetColor(ConsoleColor::dark_green, ConsoleColor::white);
		io.Print("Зеленая строка на белом фоне", true);
		io.SetColor(ConsoleColor::black, ConsoleColor::dark_red);
		io.Print("Черная строка на красном фоне", true);
		io.SetColor(ConsoleColor::white, ConsoleColor::black);
		io.Print("По умолчанию:белый текст на черном фоне", true);
		vector<int>items;
		for (int i = 0; i < 10; i++)
			items.push_back(i);
		io.Print(items, "Вывод вектора 1-10:", false, false, ",");
		io.Print(items, "Вывод вектора 1-10:", true, true);
		vector<vector<int>> matrix;
		for (int i = 0; i < 10; i++) {
			matrix.push_back(vector<int>());
			for (int j = 0; j < 10; j++)
				matrix[i].push_back(rand() % 100);
		}
		io.Print(matrix, "Вывод матрицы:");
		UnitTest::Compare();
	}
};
class IOTests {
public:
	IOTests() {
	}
	void Start() {
		//Тесты на вывод данных
		FileCreateRemoveTest("Создание и удаление файлов", { true,true,false }).Start();
		FileIOTest("Запись чтение файлов", { "hello","lol","abc defgh" }).Start();
		FileAppendTest("Добавление строк в файл", { "hello","lol","abc defgh" }).Start();
		OutTest("Вывод в консоль", {}).Start();
		//Тесты на ввод данных
		//InIntTest("Ввод целочисленных данных", { 1,22,333 }).Start();
		//InDoubleTest("Ввод вещественных данных", { 1.0,2.3,4.55 }).Start();
		//InStringTest("Ввод строковых данных", { "hello","lol","abc def" }).Start();

	}
};