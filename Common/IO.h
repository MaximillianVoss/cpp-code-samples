#pragma once
#include "Constants.h"
#include "pch.h"
#pragma once
/// <summary>
/// Ввод/вывод информации в консоль и файлы
/// </summary>
class IO
{
private:
#pragma region Поля
#pragma endregion
#pragma region Методы
#pragma region Ввод
	/// <summary>
	/// Считывает значение указанного типа из консоли
	/// </summary>
	///<param name="value">значение</param>
	///<param name="message">сообщение</param>
	template<typename T>
	bool Get(T& value, string message = "") {
		this->Print(message, true);
		cin >> value;
		if (!cin.good()) {
			cin.clear();
			cin.ignore();
			return false;
		}
		return true;
	}
	bool Get(string& value, string message = "") {
		this->Print(message, true);
		cin.clear();
		cin.ignore();
		char buffer[Constants::Ints::strMaxLength];
		cin.getline(buffer, sizeof(buffer));
		value = buffer;
		if (!cin.good()) {
			cin.clear();
			cin.ignore();
			return false;
		}
		return true;
	}
#pragma endregion 
#pragma region Вывод
	char PutGetNext(char c, FILE* input, FILE* output) {
		fputc(c, output);
		return fgetc(input);
	}
#pragma endregion
#pragma endregion
public:
#pragma region Поля
	string txtExtension = ".txt";
	string endInstruction = ":";
#pragma endregion
#pragma region Конструктор/Деструктор
	/// <summary>
	/// 
	/// </summary>
	IO() {

	}
	/// <summary>
	/// 
	/// </summary>
	~IO() {

	}
#pragma endregion
#pragma region Методы
#pragma region Ввод
#pragma region Консоль
	template<typename T>
	/// <summary>
	/// Считывает значение указанного типа из консоли
	/// </summary>
	///<param name="message">сообщение</param>
	T Get(string message = "") {
		T value;
		if (this->Get<T>(value, message))
			return value;
		else {
			this->Print(Constants::Strings::Errors::IO::input);
			return Get<T>(message);
		}
	}
	string GetLine(string message = "") {
		string value;
		if (this->Get(value, message))
			return value;
		else {
			this->Print(Constants::Strings::Errors::IO::input);
			return this->GetLine(message);
		}
	}
#pragma endregion
#pragma region Файл
	FILE* OpenRead(string fileName) {
		FILE* file = NULL;
		fopen_s(&file, fileName.c_str(), "r");
		return file;
	}
	FILE* OpenWrite(string fileName) {
		FILE* file = NULL;
		fopen_s(&file, fileName.c_str(), "w");
		return file;
	}
	void  Close(FILE* file) {
		if (file != NULL)
			fclose(file);
	}
	vector<string> ReadLines(string fileName)
	{
		fstream stream(&fileName[0]);
		string line;
		vector<string> result;
		while (getline(stream, line))
			result.push_back(line);
		stream.close();
		return result;
	}
	string ReadString(string fileName) {
		string res = "";
		vector<string> lines = ReadLines(fileName);
		for (int i = 0; i < lines.size(); i++)
			res += lines[i];
		return res;
	}
#pragma endregion
#pragma endregion
#pragma region Вывод
#pragma region Консоль
	/// <summary>
	/// Устанавлвает цвет в консоли
	/// </summary>
	/// <param name="text">цвет текста</param>
	/// <param name="background">цвет фона</param>
	void SetColor(int text, int background)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	}
	/// <summary>
	/// Устанавливает одинаковый цвет для 
	/// фона и текста
	/// </summary>
	/// <param name="color">цвет и текста и заднего фона</param>
	void SetColor(int color) {
		SetColor(color, color);
	}
	/// <summary>
	/// печатает разделитель в консоли 
	/// </summary>
	/// <param name="separator">символ разделителя</param>
	/// <param name="length">число разделителей</param>
	void PrintSeparator(char separator = '_', int length = Constants::Ints::strMaxLength) {
		for (int i = 0; i < length; i++)
			cout << separator;
		cout << endl;
	}
	/// <summary>
	/// Выводит указанную строку в консоль
	/// </summary>
	/// <param name="message">сообщение для вывода</param>
	void Print(string message, bool newLine = false)
	{
		this->Print(message.c_str(), newLine);
	}
	/// <summary>
	/// Выводит указанную строку в консоль
	/// </summary>
	/// <param name="message">сообщение для вывода</param>
	void Print(const char* message, bool newLine = false)
	{
		if (strlen(message) > 0) {
			if (newLine)
				cout << endl;
			printf("%s", message);
		}
	}
	/// <summary>
	/// вывести значение целого типа в консоль
	/// </summary>
	/// <param name="value">значение</param>
	/// <param name="newLine">true - добавить перенос на новую строку</param>
	void Print(int value, bool newLine = false) {
		if (newLine)
			cout << endl;
		cout << value;
	}
	/// <summary>
	/// вывести значение вещественного типа в консоль
	/// </summary>
	/// <param name="value">значение</param>
	/// <param name="newLine">true - добавить перенос на новую строку</param>
	void Print(float value, bool newLine = false) {
		if (newLine)
			cout << endl;
		cout << value;
	}
	/// <summary>
	/// вывести значение вещественного типа в консоль
	/// </summary>
	/// <param name="value">значение</param>
	/// <param name="newLine">true - добавить перенос на новую строку</param>
	void Print(double value, bool newLine = false) {
		if (newLine)
			cout << endl;
		cout << value;
	}
	template <typename T>
	/// <summary>
	/// выводит массив на экан 
	/// в строку(4 пробела на элемент)
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="size">размер</param>	
	void Print(T* a, int size, string message = "", bool newLine = false, bool numerate = false, string separator = "")
	{
		this->Print(message, true);
		for (size_t i = 0; i < size; i++) {
			if (numerate) {
				this->Print(to_string(i + 1) + '.', newLine);
				this->Print(a[i], !newLine);
			}
			else {
				this->Print(a[i], newLine);
			}
			if (i < size - 1)
				this->Print(separator);
		}
		cout << endl;
	}
	template <typename T>
	/// <summary>
	/// Выводит матрицу в консоль
	/// </summary>
	/// <param name="a">матрица</param>
	/// <param name="row">строки</param>
	/// <param name="cols">столбцы</param>
	void Print(T** a, size_t rows, size_t cols, string message = "", string separator = "") {
		this->Print(message, true);
		throw exception(Constants::Strings::Errors::notImplemented);
		//for (size_t i = 0; i < rows; i++)
		//	this->Print(a[i], cols, "", true, separator);
	}
	template <typename T>
	/// <summary>
	/// выводим вектор на экран в строку
	/// </summary>
	/// <param name="a">вектор для вывода</param>
	/// <param name="message">сообщение</param>
	void Print(vector<T> a, string message = "", bool newLine = false, bool numerate = false, string separator = "")
	{
		this->Print(&a[0], a.size(), message, newLine, numerate, separator);
	}
	template <typename T>
	/// <summary>
	/// выводим матрицу на экран в квадратном виде
	/// </summary>
	/// <param name="matrix">матрица для вывода</param>
	void Print(vector<vector<T>> matrix, string message = "", string separator = "")
	{
		this->Print(message, true);
		throw exception(Constants::Strings::Errors::notImplemented);
		//if (matrix.size() > 0)
		//	this->Print(&matrix[0], (size_t)matrix.size(),(size_t) matrix[0].size(), message, separator);
		//this->Print(message, true);
		//cout << endl;
		//for (size_t i = 0; i < matrix.size(); i++) {
		//	this->Print(matrix[i], "", false, false, separator);
		//}
	}
#pragma endregion
#pragma region Файлы
	/// <summary>
	/// Создает файл с указанным именем
	/// </summary>
	/// <param name="fileName">имя файла</param>
	void AddFile(string fileName) {
		this->WriteLines(fileName, {});
	}
	/// <summary>
	/// Удаляет файл
	/// </summary>
	/// <param name="fileName">имя файла</param>
	bool RemoveFile(string fileName) {
		if (remove(fileName.c_str()) != 0)
			return false;
		return true;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="fileName"></param>
	void ClearLines(string fileName) {
		this->AddFile(fileName);
	}
	/// <summary>
	/// Проверяет существует файл или нет
	/// </summary>
	/// <param name="fileName">Имя файла</param>
	/// <returns></returns>
	bool IsExists(string fileName) {
		ifstream f(fileName.c_str());
		return f.good();
	}
	/// <summary>
	/// Записывает строки в файл
	/// </summary>
	///<param name="fileName">имя файла</param>
	/// <param name="lines">строки для записи</param>
	/// <param name="addNewline">true-добавить перенос строки</param>
	void WriteLines(string fileName, vector<string>lines, bool addNewline = false) {
		ofstream stream(&fileName[0]);
		for (string line : lines) {
			if (addNewline)
				line += '\n';
			stream.write(line.c_str(), line.size());
		}
		stream.close();
	}
	/// <summary>
	/// Добавляет указанные строки в конец файла
	/// </summary>
	void Append(string filename, vector<string>lines, bool addNewline = false) {
		vector<string>currentLines = ReadLines(filename);
		currentLines.insert(currentLines.end(), lines.begin(), lines.end());
		WriteLines(filename, currentLines, addNewline);
	}
	/// <summary>
	/// Удаляет комментарии из первого файла и сохраняет результат во втором файле
	/// </summary>
	/// <param name="inFile">входной файл</param>
	/// <param name="outFile">выходной файл</param>
	void RemoveComments(string inFile, string outFile) {
		FILE* input = OpenRead(inFile);
		FILE* output = OpenWrite(outFile);
		if (!input)
		{
			printf("\nНе удалось открыть файл %s для чтения", inFile.c_str());
			fclose(output);
		}
		char cur = fgetc(input);

		if (output)
		{
			if (cur != EOF)
			{
				while (cur != EOF)
				{
					if ((cur != '/') && (cur != '\"') && (cur != '\''))
						cur = PutGetNext(cur, input, output);
					else
					{
						if ((cur != '\"') && (cur != '\''))
						{
							cur = fgetc(input);
							if (cur == '/' || cur == '*')
							{
								if (cur == EOF)
									break;
								if (cur == '/')
								{
									cur = fgetc(input);
									while (cur != '\n')
									{
										if (cur == EOF)
											break;
										if (cur == '\\')
										{
											cur = fgetc(input);
											cur = fgetc(input);
										}
										else
											cur = fgetc(input);
									}
								}
								else
								{
									cur = fgetc(input);
									while (cur)
									{
										if (cur == EOF)
											break;
										if (cur == '*')
										{
											cur = fgetc(input);
											if (cur == '/')
											{
												cur = fgetc(input);
												break;
											}
										}
										else
											cur = fgetc(input);
									}
								}
							}
							else
								fputc('/', output);
						}
						else
						{
							if (cur == '\"')
							{
								cur = PutGetNext(cur, input, output);
								while (cur != '\"')
								{
									if (cur == EOF)
										break;
									if (cur == '\\')
									{
										cur = PutGetNext(cur, input, output);
										cur = PutGetNext(cur, input, output);
										if (cur == '\"')
											break;
									}
									else
									{
										if (cur != '\n')
											cur = PutGetNext(cur, input, output);
										else
											break;
									}
								}
								cur = PutGetNext(cur, input, output);
							}
							else
							{
								cur = PutGetNext(cur, input, output);
								while (cur != '\'')
								{
									if (cur == EOF || cur == '\'')
										break;
									if (cur == '\\')
										cur = PutGetNext(cur, input, output);
									if (cur != '\n')
										cur = PutGetNext(cur, input, output);
									else
										break;
								}
								cur = PutGetNext(cur, input, output);
							}
						}
					}
				}
			}
		}
		else
			printf("\nНе удалось открыть файл %s для чтения", outFile.c_str());
		printf("\nКомментарии из фалйа %s удалены, выходной файл: %s.\n", inFile.c_str(), outFile.c_str());
		Close(input);
		Close(output);
	}
#pragma endregion
#pragma endregion
#pragma region Другое
	/// <summary>
	/// Устанавливает русский ввод/вывод в консоли
	/// </summary>
	void SetRusIO() {
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
	}
	/// <summary>
	/// Ставит программу на паузу, 
	/// пока не будет нажата любая клавиша
	/// </summary>
	void Pause() {
		system("pause");
	}
	/// <summary>
	/// очищает консоль
	/// </summary>
	void Clear()
	{
		system("cls");
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="milliSeconds"></param>
	void Wait(int milliSeconds) {
		Sleep(milliSeconds);
	}
#pragma endregion
#pragma endregion


};