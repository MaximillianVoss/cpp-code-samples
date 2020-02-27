#include "stdafx.h"
#include "Stack.h"

#pragma region Конструктор/Деструктор
Stack::Stack()
{
}
Stack::~Stack()
{
}
#pragma endregion
#pragma region Методы

string Stack::Pop() {
	if (!isEmpty()) {
		string res = items.at(items.size() - 1);
		items.erase(items.begin() + items.size() - 1);
		return res;
	}
	return "";
}

string Stack::Peek() {
	if (!isEmpty())
		return  items.at(items.size() - 1);
	return "";
}

void Stack::Push(string  str) {
	items.push_back(str);
}

bool Stack::isEmpty() {
	return !(items.size() > 0);
}
#pragma endregion



