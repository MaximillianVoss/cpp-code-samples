// Lab 3 RC.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Tree.h"
#include "FileIO.h"
#include "Node.h"
#include <string.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <set>
#include <map>
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
	printf("%s\n", message.c_str());
	PrintTree(tree);
}
void PrintVector(vector<string> values, string message)
{
	printf("%s\n", message.c_str());
	for each (string  item in values)
		printf("%s\n", item.c_str());
}

#pragma endregion

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	map<int, float> results;
	vector<string>errors;
	int total = 100;
	for (int i = 1;i <= total;i++)
	{
		printf(" %i проверок из %i завершено\n", i, total);
		if (errors.size() > 0)
			PrintVector(errors, "Следующие итерации завершились с ошибкой:");
		try
		{
			Tree tree(i * 10);
			Tree tree2(i * 10);
			int start = clock();
			tree - tree2;
			tree | tree2;
			tree.Change(tree2, 3);
			results.insert(pair<int, float> {i * 10, (float)(clock() - start) / CLOCKS_PER_SEC});
		}
		catch (exception ex)
		{
			errors.push_back(to_string(i)+ ' ' + ex.what());
		}
		if (i != total)
			system("cls");
	}
	try
	{
		FileIO io;
		io.Save("out.txt", results);
	}
	catch (exception ex)
	{
		printf(ex.what());
	}
	system("pause");
	return 0;
}

