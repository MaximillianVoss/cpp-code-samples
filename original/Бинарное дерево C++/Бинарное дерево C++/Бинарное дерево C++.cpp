// Ѕинарное дерево C++.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;
struct Item
{
public:
	int value;
	bool visited;
	Item *left;
	Item *right;
	Item()
	{

	}
	Item(int _value, bool _visited)
	{
		value = _value;
		left = NULL;
		right = NULL;
		visited = _visited;
	}
	void Print()
	{
		printf("%i ", value);
	}
};
class BinaryTree
{
private:

public:
	Item * root;
	BinaryTree(int itemsCount)
	{
		GenerateTree(itemsCount);
	}
	void GenerateTree(int itemsCount)
	{
		srand(time(NULL));
		for (int i = 0; i < itemsCount; i++)
		{
			Add(new Item(rand() % 100, false));
		}
	}
	void Add(Item * pasteItem)
	{
		if (root == NULL)
		{
			root = pasteItem;
		}
		else
		{
			Item *current = root;
			while (current != NULL)
			{
				if (current->value == pasteItem->value)
					break;
				if (current->value > pasteItem->value)
				{
					if (current->left)
						current = current->left;
					else
					{
						current->left = pasteItem;
						break;
					}
				}
				else
				{
					if (current->right)
						current = current->right;
					else
					{
						current->right = pasteItem;
						break;
					}
				}
			}
		}
	}
};
int GetAvgHeight(Item * node)
{
	if (node == NULL)
		return 0;
	int left, right;
	if (node->left != NULL) {
		left = GetAvgHeight(node->left);
	}
	else
		left = 0;
	if (node->right != NULL) {
		right = GetAvgHeight(node->right);
	}
	else
		right = 0;
	int max = left > right ? left : right;
	return max + 1;
}

int main()
{
	setlocale(LC_ALL, "rus");
	BinaryTree *tree = new BinaryTree(15);
	int hLeft = GetAvgHeight(tree->root->left);
	int hRight = GetAvgHeight(tree->root->right);
	double result = (hLeft + hRight) / 2;
	printf("—редн€€ высота дерева:%.2lf\n", result);
	system("pause");
	return 0;
}

