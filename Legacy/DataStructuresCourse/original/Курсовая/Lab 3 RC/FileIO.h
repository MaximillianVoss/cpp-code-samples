#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

#pragma once
class FileIO
{
public:
	///<summary></summary>
	vector<string> split(string str, char delimiter);
	///<summary>Получение всех строк текста из файла</summary>
	///<param name="fileName">имя файла</param>
	vector<string> GetLines(string fileName);
	///<summary>Вывод значений словаря в файл</summary>
	///<param name="fileName">имя файла</param>
	///<param name="values">словарь со значениями</param>
	void Save(string fileName, map<int, float> values);

	FileIO();
	~FileIO();
};

