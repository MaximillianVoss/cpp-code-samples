#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
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
	FileIO();
	~FileIO();
};

