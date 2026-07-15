// Бинарное дерево C++.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	Item(int _value)
	{
		value = _value;
		left = NULL;
		right = NULL;
	}
};

class BinaryTree
{
private :
	
public:
	Item *root;
	BinaryTree(int itemsCount)
	{
		GenerateTree(itemsCount);
	}
	void GenerateTree(int itemsCount)
	{
		srand(time(NULL));
		for (int i = 0;i < itemsCount;i++)
		{
			Add(new Item(rand()%100));
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
	void Print(Item * root)
	{
		if (root)
		{
			printf("(%i)\n", root->value);
			Print(root->left);
			Print(root->right);
		}
	}
};

int main()
{
	BinaryTree *tree = new BinaryTree(20);
	tree->Print(tree->root);
	system("pause");
	return 0;
}

