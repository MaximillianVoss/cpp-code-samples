// Lab 3 RC.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "AVL.h"
#include <string.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "FileIO.h"
using namespace std;

vector<string> LoadSet(string filename)
{
	std::vector<string> result;
	FileIO io;
	std::vector<string> lines = io.GetLines(filename);
	for each(string line in lines)
	{
		std::vector<string> items = io.split(line, ',');
		result.insert(result.end(), items.begin(), items.end());
	}
	return result;
}
int main()
{
	setlocale(LC_ALL, "rus");
	AVL a(LoadSet("secondSet.txt")), b(LoadSet("secondSet.txt"));
	AVL c = a - b;
	c.OutTree();
	/*AVL first(15);
	AVL second(15);
	first.OutTree("дерево А:");
	second.OutTree("дерево B:");
	(first - second).OutTree("A - B:");
	(first | second).OutTree("A + B:");
	int n = 0;
	printf("Введите позицию замены:\n");
	scanf_s("%i", &n);
	first.Change(second, n);
	first.OutTree("дерево А после замены:");*/

	system("pause");
    return 0;
}

