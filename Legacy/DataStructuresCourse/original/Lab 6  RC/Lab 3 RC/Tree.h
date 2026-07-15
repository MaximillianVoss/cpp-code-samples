#include <set>
#include <time.h>
using namespace std;
#pragma once
class Tree
{
private:
	multiset<int> data;
public:
	int GetItemByIndex(int index);
	bool FindItem(int value);
	Tree(int size);
	Tree();
	~Tree();
	Tree operator - (Tree&tree);
	Tree operator | (Tree&tree);
	Tree Change(Tree tree, int index);
	int GetSize();
};

