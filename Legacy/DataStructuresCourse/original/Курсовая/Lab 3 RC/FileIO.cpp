#include "stdafx.h"
#include "FileIO.h"
using namespace std;
FileIO::FileIO()
{
}

FileIO::~FileIO()
{
}

vector<string> FileIO::split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string tok;
	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}
	return internal;
}

vector<string> FileIO::GetLines(string fileName)
{
	fstream stream(&fileName[0]);
	string line;
	vector<string> result;
	while (getline(stream, line))	
		result.push_back(line);	
	return result;
}

void FileIO::Save(string fileName, map<int, float> values)
{
	ofstream out(fileName.c_str());
	if (out)
	{
		out << values.size() << endl;
		for (auto it = values.begin(); it != values.end(); ++it)
		{
			out << (*it).first << " : " << (*it).second << endl;
		}
	}
	else
	{
		throw exception("Не удалось открыть файл.");
	}
}