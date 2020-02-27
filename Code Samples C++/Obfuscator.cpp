#include "stdafx.h"
#include "Obfuscator.h"
#include "StrHelper.h"
#include "FileIO.h"
#include "Pair.h"

#pragma region Конструктор/Деструктор 
Obfuscator::Obfuscator(string _configFileName)
{
	configFileName = _configFileName;
	FileIO fileIO = FileIO();
	StrHelper strHelper = StrHelper();
	vector<string> lines = fileIO.ReadLines(_configFileName);
	for (int i = 0; i < lines.size(); i++) {
		vector<string> words = strHelper.Split(lines[i], ": ", "");
		if (words.size() > 1) {
			if (words[0] == input)
				inputFileName = words[1];
			if (words[0] == output)
				outputFileName = words[1];
			if (words[0] == keywords)
				keyWordsFileName = words[1];
			if (words[0] == dummy)
				dummyFileName = words[1];
		}
	}
}

Obfuscator::~Obfuscator()
{
}
#pragma endregion

#pragma region Методы
/// <summary>
/// удаление табуляции
/// </summary>
/// <param name="a">список строк</param>
/// <returns></returns>
vector<string> Obfuscator::RemoveTabs(vector<string> a) {
	StrHelper strHelper;
	for (size_t i = 0; i < a.size(); i++)
		strHelper.ReplaceAll(a[i], "\t", "");
	return a;
}
/// <summary>
/// переименование переменных
/// </summary>
/// <param name="a">список строк</param>
/// <returns></returns>
vector<string>Obfuscator::RenameVariables(vector<string> a) {
	FileIO fileIO = FileIO();
	StrHelper strHelper = StrHelper();
	vector<string> res = RemoveTabs(a);
	vector<string> variables;
	string keyChars = "!?&=<'>(){}[]#\":;,.";
	string replaceChars = "(())[]{}-+=;";
	string keyWords = fileIO.ReadAllText(keyWordsFileName);
	for (int i = 0; i < res.size(); i++)
	{
		if (res[i].size() > 0)
		{
			for (int k = 0; k < replaceChars.length(); k++) {
				string toReplace = "";
				toReplace += replaceChars[k];
				string newStr = " ";
				newStr += replaceChars[k];
				newStr += " ";
				strHelper.ReplaceAll(res[i], toReplace, newStr);
			}
			vector<string> items = strHelper.Split(res[i], ' ');
			for (int j = 0; j < items.size(); j++) {
				if (keyWords.find(items[j].c_str()) == std::string::npos) {
					if (!strHelper.Contains(items[j], keyChars) && !strHelper.IsNumber(items[j]))
						variables.push_back(items[j]);
				}
			}
		}
	}
	variables = strHelper.RemoveCopies(variables);
	vector<Pair> pairs;
	for (int i = 0; i < variables.size(); i++)
		pairs.push_back(Pair("v" + to_string(i), variables[i]));
	for (int j = 0; j < res.size(); j++) {
		for (int i = 0; i < pairs.size(); i++)
			strHelper.ReplaceAll(res[j], pairs[i].value, pairs[i].key);
	}
	return res;
}
/// <summary>
/// Добавляет подставные функции и переменные
/// </summary>
/// <param name="a">список строк</param>
/// <returns></returns>
vector<string> Obfuscator::AddDummyVariables(vector<string> a)
{
	FileIO fileIO = FileIO();
	vector<string> dummy = fileIO.ReadLines(dummyFileName);
	for (int i = 0; i < dummy.size(); i++)
		a.push_back(dummy[i]);
	return a;
}
/// <summary>
/// Обфусцирует код
/// </summary>
/// <param name="a">список строк</param>
/// <returns></returns>
vector<string> Obfuscator::Obfuscate(vector<string> a)
{
	vector<string> res = a;
	res = RenameVariables(res);
	res = AddDummyVariables(res);
	res = RemoveTabs(res);
	return res;
}
/// <summary>
/// Обфусцирует указанный файл с кодом
/// </summary>
/// <param name="inFileName">имя входного файла</param>
/// <param name="outFileName">имя выходного файла</param>
void Obfuscator::Obfuscate()
{
	FileIO fileIO = FileIO();
	fileIO.RemoveComments(inputFileName, outputFileName);
	fileIO.WriteLinesLn(outputFileName.c_str(), Obfuscate(fileIO.ReadLines(outputFileName.c_str())));
}
#pragma endregion
