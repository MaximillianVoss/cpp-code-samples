// Lab 3 RC.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Tree.h"
#include "Node.h"
#include <string.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <set>
using namespace std;

#pragma region Print
void PrintTree(Tree tree)
{
	Node *node = new  Node();
	node = node->Build(tree);
	if (node)
		node->PrintTree();
	else
		printf("В дереве нет элементов");
}
void PrintTree(Tree tree, string message)
{
	printf("%s", message.c_str());
	printf("\n");
	PrintTree(tree);
}
#pragma endregion

int main()
{
	setlocale(LC_ALL, "rus");
	const int treeSize = 15;
	srand(time(NULL));

	Tree tree(treeSize);
	Tree tree2(treeSize);
	
	PrintTree(tree,"Дерево А:");
	PrintTree(tree2, "Дерево Б:");
	PrintTree(tree - tree2, "А-Б:");
	PrintTree(tree | tree2, "А+Б");
	PrintTree(tree.Change(tree2, 3), "Замена элементов дерева А:");
	system("pause");
    return 0;
}

