// Перестановка солбцов и строк в матрице.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <time.h>
#pragma warning(disable : 4996)
using namespace std;

void PrintArray(vector<int> a)
{
	for (int i = 0;i < a.size();i++) printf("%4i ", a[i]);
	printf("\n");
}
void PrintMatrix(vector<vector<int>> matrix)
{
	for (int i = 0; i < matrix.size();i++)
		PrintArray(matrix[i]);
	printf("\n");
}
void PrintfMessage(string message)
{
	printf("%s\n", message.c_str());
}
bool GetIntFromUser(int &value, string message)
{
	PrintfMessage(message);
	if (cin >> value) {
		return true;
	}
	else if (cin.bad()) {
		PrintfMessage("Ошибка ввода, повторите ввод");
		return false;
	}
	else {
		PrintfMessage("Ошибка форматирования, проверьте формат данных  повторите ввод");
		return false;
	}
}
vector<vector<int>> CreateMatrix(int rowsCount, int columnCount)
{
	srand(time(NULL));
	vector<vector<int>> matrix;
	for (int i = 0;i < rowsCount;i++)
	{
		matrix.push_back(vector<int>());
		for (int j = 0; j < columnCount; j++)
		{
			matrix[i].push_back((rand() % 100)*(pow(-1, rand() % 2)));
		}
	}
	return matrix;
}
vector<vector<int>> CreateMatrix(int rowsCount, int columnCount, int value)
{
	vector<vector<int>> matrix;
	for (int i = 0;i < rowsCount;i++)
	{
		matrix.push_back(vector<int>());
		for (int j = 0; j < columnCount; j++)
		{
			matrix[i].push_back(value);
		}
	}
	return matrix;
}
void RotateMatrix(vector<vector<int>> &matrix)
{
	if (matrix.size() > 0)
	{
		int rows = matrix.size(), columns = matrix[0].size();
		int n = max(rows, columns);
		vector<vector<int>> result = CreateMatrix(n, n, 0);
		for (int i = 0;i < rows;i++)
		{
			for (int j = 0;j < columns;j++)
			{
					result[j][i] = matrix[i][j];
			}
		}
		matrix.clear();
		matrix = CreateMatrix(columns, rows, 0);
		for (int i = 0;i < matrix.size();i++)
		{
			for (int j = 0;j < matrix[i].size();j++)
			{
				matrix[i][j] = result[i][j];				
			}
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int rowCount, columnCount;
	GetIntFromUser(rowCount, "Введите число строк:");
	GetIntFromUser(columnCount, "Введите число столбцов:");
	vector<vector<int>>matrix = CreateMatrix(rowCount, columnCount);
	PrintMatrix(matrix);
	RotateMatrix(matrix);
	PrintMatrix(matrix);

	system("pause");
	return 0;
}

