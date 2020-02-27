#include "stdafx.h"
#include "StrHelper.h"

#pragma region Конструкторы
StrHelper::StrHelper()
{
}

StrHelper::~StrHelper()
{
}
#pragma endregion

#pragma region Методы

string StrHelper::Join(vector<string> lines)
{
	return Join(lines, "");
}

string StrHelper::Join(vector<string> lines, string spacer)
{
	string res = "";
	for (int i = 0; i < lines.size(); i++)
		res += lines[i] + spacer;;
	return res;
}

void StrHelper::ReplaceAll(string &s, const string &search, const string &replace) {
	for (size_t pos = 0; ; pos += replace.length()) {
		// Locate the substring to replace
		pos = s.find(search, pos);
		if (pos == string::npos) break;
		// Replace by erasing and inserting
		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}

string StrHelper::Replace(string str, string what, string replace) {
	while (str.find(what) != -1)
		str = str.replace(str.find(what), what.size(), replace);
	return str;
}

vector<string> StrHelper::Split(string str, string delimiters, string notDelete) {
	string buffer = "";
	vector<string> res;
	for (int i = 0; i < str.size(); i++)
	{
		char c = str[i];
		if (delimiters.find(c) == string::npos)
			buffer += c;
		else if (buffer.length() > 0) {
			res.push_back(buffer);
			buffer = "";
		}
		if (notDelete.find(c) != string::npos) {
			string temp;
			temp += c;
			res.push_back(temp);
		}
	}
	if (buffer.length() > 0) {
		res.push_back(buffer);
		buffer = "";
	}
	return res;
}

vector<string> StrHelper::Split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string tok;
	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}
	return internal;
}

vector<string> Split(string str, const string delimiters, const string notDelete)
{
	return Split(str, string(delimiters), string(notDelete));
}

bool StrHelper::Contains(string str, string collection) {
	for (int i = 0; i < str.size(); i++)
		if (collection.find(str[i]) != std::string::npos)
			return true;
	return false;
}

bool StrHelper::IsNumber(const std::string& s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
		return false;
	char * p;
	strtol(s.c_str(), &p, 10);
	return (*p == 0);
}
string StrHelper::Remove(string str, char c)
{
	string temp = "";
	for (int i = 0; i < str.length(); i++)
		if (str[i] != c)
			temp += str[i];
	return temp;
}
#pragma endregion