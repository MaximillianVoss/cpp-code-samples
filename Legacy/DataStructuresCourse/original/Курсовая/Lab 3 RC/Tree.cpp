#include "stdafx.h"
#include "Tree.h"
#include <set>
#include <time.h>
using namespace std;
Tree::Tree()
{
}

Tree::~Tree()
{
}
Tree::Tree(int size)
{
	//srand(time(NULL));
	for (int i = 0;i < size;i++)
		data.insert(rand() % 100);
}
int Tree::GetSize()
{
	return this->data.size();
}
int Tree::GetItemByIndex(int index)
{
	int i = 0;
	multiset<int>::iterator it = data.begin();
	while (it != data.end())
	{
		if (i == index)
			return  *it;
		i++;
		it++;
	}
	return -1;
}
bool Tree::FindItem(int value)
{
	multiset<int>::iterator it = data.begin();
	while (it != data.end())
	{
		if (*it == value)
			return  true;
		it++;
	}
	return false;
}

///<summary>исключение</summary>
Tree Tree :: operator - (Tree&tree) {
	Tree result;
	for (int i = 0;i < this->data.size();i++)
	{
		int value = this->GetItemByIndex(i);
		if (!tree.FindItem(value))
			result.data.insert(value);
	}
	return result;
}
///<summary>объединение</summary>
Tree Tree :: operator | (Tree&tree) {
	Tree result;
	for (int i = 0;i < this->data.size();i++)
		result.data.insert(this->GetItemByIndex(i));
	for (int i = 0;i < tree.data.size();i++)
		result.data.insert(tree.GetItemByIndex(i));
	return result;
}
///<summary>Замена элементов последовательности</summary>
///<param name="tree">дерево-источник</param>
///<param name="index">индекс откуда будет начинаться замена</param>
Tree Tree::Change(Tree tree, int index)
{
	Tree result;
	for (int i = 0;i < index;i++)
		result.data.insert(this->GetItemByIndex(i));
	for (int i = 0;i < tree.data.size();i++)
		result.data.insert(tree.GetItemByIndex(i));
		for (int i = index + tree.data.size();i < (int)this->data.size() - (int)(index + tree.data.size());i++)
			result.data.insert(this->GetItemByIndex(i));	
	return result;
}
