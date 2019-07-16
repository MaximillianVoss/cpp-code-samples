#include "pch.h"
#include "StrHelper.h"
#pragma once
class FileIO
{
public:
	/// <summary>
	/// Записывает строки в файл
	/// </summary>
	///<param name="fileName">имя файла</param>
	/// <param name="lines">строки для записи</param>
	void WriteLines(string fileName, vector<string> lines);
	/// <summary>
	/// Записывает строки в файл
	/// добавляет к каждой строке перенос на новую строку
	/// </summary>
	///<param name="fileName">имя файла</param>
	/// <param name="lines">строки для записи</param>
	void WriteLinesLn(string fileName, vector<string> lines);
	///<summary>Получение всех строк текста из файла</summary>
	///<param name="fileName">имя файла</param>
	vector<string> ReadLines(string fileName);
	/// <summary>
	/// Читает матрицу из файла
	/// вид записи матрицы:
	/// 0 1 2
	/// 3 4 5
	/// 7 8 9
	/// размерность любая
	/// </summary>
	vector<vector<string>> ReadMatrix(string fileName);
	/// <summary>
	/// Добавляет указанные строки в конец файла
	/// </summary>
	void FileIO::Append(string filename, vector<string>lines);
	/// <summary>
	/// Открыть файл на чтение
	/// </summary>
	/// <param name="fileName">имя файла</param>
	/// <returns>файловый поток</returns>
	FILE* OpenRead(string fileName);
	/// <summary>
	/// Считывает содержимое файла в одну строку
	/// </summary>
	/// <param name="fileName">имя файла</param>
	/// <returns>строка с содержимым файла</returns>
	string ReadAllText(string fileName);
	/// <summary>
	/// Открыть файл на запись
	/// </summary>
	/// <param name="fileName">имя файла</param>
	/// <returns>файловый поток</returns>
	FILE* OpenWrite(string fileName);
	/// <summary>
	/// Закрыть файл
	/// </summary>
	/// <param name="file"></param>
	void Close(FILE* file);
	/// <summary>
	/// Удаляет комментарии из первого файла
	/// и сохраняет результат во второрм файле
	/// </summary>
	/// <param name="inFile">входной файл</param>
	/// <param name="outFile">вызодной файл</param>
	void RemoveComments(string inFile, string outFile);
	/// <summary>
	/// Удаляет комментарии из первого файла
	/// и сохраняет результат во второрм файле
	/// </summary>
	/// <param name="in">входной файл</param>
	/// <param name="out">выходной файл</param>
	void RemoveComments(FILE* in, FILE* out);
	FileIO();
	~FileIO();
};

