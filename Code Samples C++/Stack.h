#pragma once
#include<string>
#include<vector>
using namespace std;
/// <summary>
/// Стандартный стек
/// со стандартными функциями
/// </summary>
class Stack
{
private:
	/// <summary>
	/// содержимое стека
	/// </summary>
	vector<string> items;
public:
	Stack();
	~Stack();
	/// <summary>
	/// извлечение из стека
	/// </summary>
	/// <returns>элемент из верхушки стека</returns>
	string Pop();
	/// <summary>
	/// возвращает элемент 
	/// из стека без извлечения
	/// </summary>
	/// <returns>элемент из верхушки стека</returns>
	string Peek();
	/// <summary>
	/// добалвение в стек
	/// </summary>
	/// <param name="str">элемент для добавления</param>
	void Push(string  str);
	/// <summary>
	/// проверят стек на пустоту
	/// </summary>
	/// <returns>true - если стек пуст</returns>
	bool isEmpty();
};