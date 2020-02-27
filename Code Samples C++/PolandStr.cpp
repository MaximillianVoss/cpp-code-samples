#include "stdafx.h"
#include "PolandStr.h"


PolandStr::PolandStr(string _commands) {
	commands = _commands;
}

PolandStr::~PolandStr()
{
}

int PolandStr::GetPriority(string command) {
	vector<string>commands;
	commands.push_back("(");
	commands.push_back("+-");
	commands.push_back("*/");
	commands.push_back("^");
	for (size_t i = 0; i < commands.size(); i++)
		if (commands[i].find(command) != string::npos)
			return i;
	return -1;
}

vector<string> PolandStr::Insert(vector<string> lexems, int idx, string value) {
	vector<string> result;
	for (size_t i = 0; i < lexems.size(); i++)
	{
		if (i == idx)
			result.push_back(value);
		result.push_back(lexems[i]);
	}
	if (idx > lexems.size() - 1)
		result.push_back(value);
	return result;
}

vector<string> PolandStr::LexemReplace(vector<string> lexems) {
	string strs[3] = { "(",")","+" };
	for (size_t i = 0; i < lexems.size() - 1; i++)
	{
		if (lexems[i] == "-") {
			if (i > 0) {
				lexems[i + 1] = "-" + lexems[i + 1];
				lexems.erase(lexems.begin() + i);
				lexems = Insert(lexems, i, strs[0]);
				if (commands.find(lexems[i - 1]) == -1) {
					lexems = Insert(lexems, i, strs[2]);
					lexems = Insert(lexems, i + 3, strs[1]);
				}
				else
					lexems = Insert(lexems, i + 2, strs[1]);


			}
			else {
				lexems[i + 1] = "-" + lexems[i + 1];
				lexems.erase(lexems.begin() + i);
				lexems = Insert(lexems, i, strs[0]);
				lexems = Insert(lexems, i + 2, strs[1]);
			}
		}
	}
	return lexems;
}

vector<string> PolandStr::GetPolandStr(string str) {
	Stack stack;
	str = strWizard.Replace(str, "--", "+");
	vector<string> lexems = strWizard.Split(str, commands + " ", commands);
	lexems = LexemReplace(lexems);

	vector<string>res;
	for each (string lexem in lexems)
	{
		if (commands.find(lexem) == string::npos)
			res.push_back(lexem);
		else if (lexem != " ") {
			if (lexem == ")") {
				while (!stack.isEmpty() && stack.Peek() != "(")
					res.push_back(stack.Pop());
				stack.Pop();
			}
			if (stack.isEmpty() || lexem == "(")
				stack.Push(lexem);
			else if (lexem != ")") {
				if (GetPriority(stack.Peek()) >= GetPriority(lexem))
					res.push_back(stack.Pop());
				stack.Push(lexem);

				//if (GetPriority(lexem) != -1)
				//	stack.Push(lexem);
			}
		}
	}
	while (!stack.isEmpty()) {
		string command = stack.Pop();
		if (command != ")")
			res.push_back(command);
	}
	return res;
}