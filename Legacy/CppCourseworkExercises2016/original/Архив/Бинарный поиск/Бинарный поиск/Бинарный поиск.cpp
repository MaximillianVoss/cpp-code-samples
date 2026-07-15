#include "stdafx.h"
#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

#pragma region  Считывание значений
bool spaceChar(char ch)
{
	return (ch == ' ') || (ch == '\n') || (ch == '\t');
}

int readInt(int &ans, int l, int r)
{

	char ch;
	bool negative = false;
	int ok = 0;

	do
	{
		cin.get(ch);
	} while (spaceChar(ch));


	ans = 0;
	if (ch == '-')
	{
		//Отмечаем, что число отрицательное.
		negative = true;
		cin.get(ch);
	}
	else if (ch == '+')
		cin.get(ch);

	//Если считанный символ это не цифра, то...
	if ((ch<'0') || (ch>'9'))
		//Код ошибки - 1.
		ok = 1;
	while (!spaceChar(ch))
	{
		//Если при считывании еще не было ошибок, то...
		if (ok == 0)
		{
			//Если текущий символ это цифра, то...
			if ((ch >= '0') && (ch <= '9'))
			{
				ans = ans * 10 + ch - '0';

				if ((ans > 0) && (negative))
					//Меняем у него знак.
					ans = -ans;
			}
			//Иначе...
			else
				//Код ошибки -1.
				ok = 1;
		}
		//Если число не лежит в отрезке [l,r], то...
		if ((ans != 0) && ((ans<l) || (ans>r)))
			//Код ошибки - 2.
			ok = 2;
		//Считываем следующий символ.
		cin.get(ch);
	}

	//Если число не лежит в отрезке [l,r], то...
	if ((ok == 0) && ((ans<l) || (ans>r)))
		//Код ошибки - 2.
		ok = 2;
	while (ch != '\n')
	{
		cin.get(ch);
		if (!spaceChar(ch))
			ok = 1;
	}

	//Возвращаем код ошибки.
	return ok;
}

/*
Функция для считывания число до тех пор, пока оно не будет введено корректно.
Аргументы:
[l,r] - отрезок в котором должно лежать считываемое число.

Возвращаемое значение:
Считанное число.
*/

int readCorrectInt(int l, int r)
{
	/*
	ok - переменная для хранения результата работы функции readInt.
	ans - переменная в которую считывается число.
	*/
	int ok, ans;
	do
	{
		//Считываем число.
		ok = readInt(ans, l, r);
		//Если была какая-то ошибка при считывании, то выводим соответствующие сообщение.
		if (ok == 1)
			cout << "Ошибка. В записи числа присутствуют некорректные символы." << endl;
		else if (ok == 2)
			cout << "Ошибка. Число должно лежать в отрезке [" << l << ',' << r << "]" << endl;
		//Цикл выполняется, пока ok не равно нулю.
	} while (ok != 0);

	return ans;
}

#pragma endregion

#pragma region Вспомогательные методы
vector<vector<int>> CreateMatrix(int rowsCount, int columnCount)
{
	srand(time(NULL));
	vector<vector<int>> matrix;
	for (int i = 0;i < rowsCount;i++)
	{
		matrix.push_back(vector<int>());
		for (int j = 0; j < columnCount; j++)
		{
			matrix[i].push_back(1/*rand()%10*/);
		}
	}
	return matrix;
}
void PrintArray(int *a, int size)
{
	for (int i = 0;i < size;i++) printf("%4i ", a[i]);
	printf("\n");
}
void PrintArray(vector<int> a)
{
	for (int i = 0;i < a.size();i++) printf("%4i ", a[i]);
	printf("\n");
}
void PrintMessage(string message)
{
	printf("%s\n", message.c_str());
}
void PrintMatrix(vector<vector<int>> matrix)
{
	for (int i = 0; i < matrix.size();i++)
		PrintArray(matrix[i]);
}
void PrintMatrix(vector<vector<int>> matrix, string message)
{
	printf("%s\n", message.c_str());
	for (int i = 0; i < matrix.size();i++)
		PrintArray(matrix[i]);
}
void RotateMatrix(vector<vector<int>> &matrix)
{
	if (matrix.size() > 0)
	{
		int rows = matrix.size(), columns = matrix[0].size();
		int n = max(rows, columns);
		vector<vector<int>> result = CreateMatrix(n, n);
		for (int i = 0;i < rows;i++)
		{
			for (int j = 0;j < columns;j++)
			{
				result[j][i] = matrix[i][j];
			}
		}
		matrix.clear();
		matrix = CreateMatrix(columns, rows);
		for (int i = 0;i < matrix.size();i++)
		{
			for (int j = 0;j < matrix[i].size();j++)
			{
				matrix[i][j] = result[i][j];
			}
		}
	}
}
#pragma endregion

#pragma region Поиск
int BinarySearch(int value, vector<int> values)
{
	int left = 0, right = values.size(), mid;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (value<values[mid]) right = mid - 1;
		else if (value>values[mid]) left = mid + 1;
		else return mid;
	}
	return -1;
}
void binarySearch(vector<int>a, int value, int &entryCounter)
{
	/*
	[L,R] - границы отрезка поиска.
	X - середина отрезка [L,R]
	ps - вспомогательная перменная.
	*/
	int L=0, R=a.size()-1, X, ps;
	while (L <= R)
	{
		X = (L + R) / 2;
		if (a[X] < value) L = X + 1;
		else R = X - 1;
	}
	if ((L < a.size()) && (a[L] == value))
	{
		ps = L;
		L = 0;
		R = a.size() - 1;
		while (L <= R)
		{
			X = (L + R) / 2;
			if (a[X] <= value) L = X + 1;
			else R = X - 1;
		}
		entryCounter += (R - ps + 1);
	}
}
void LinearSearch(int value, vector<int> values, int &entryCounter)
{
	for each (int item in values)
	{
		if (value == item) entryCounter++;
	}
}
#pragma endregion
int main()
{

	setlocale(LC_ALL, "Russian");

	/*

	l - количество элементов для поиска.
	seq[] - элементы для поиска.
	L - левая граница бинарного поиска.
	R - правая граница бинарного поиска.
	X - середина отрезка [L,R].
	ps - вспомогательная переменная.
	pr - вспомогательная переменная.

	*/
	int i, j, N = 100, count, numberBin, L, R, X, ps, pr;

	PrintMessage("Введите количество строк матрицы:");
	int rows = readCorrectInt(1, N);
	PrintMessage("Введите количество столбцов матрицы:");
	int columns = readCorrectInt(1, N);

	vector<vector<int>> matrix = CreateMatrix(rows, columns);
	PrintMatrix(matrix, "Сгенерированная матрица:");

	do {
		PrintMessage("Введите корректное количество элементов для поиска :");
		count = readCorrectInt(1, N);
	} while (count > rows && count > columns);
	PrintMessage("Введите элементы для поиска:");
	vector <int> items;
	for (i = 0; i < count; i++)
	{
		cout << "Введите " << i + 1 << "-й элемент для поиска:" << endl;
		items.push_back(readCorrectInt(INT32_MIN, INT32_MAX));
	}
	PrintMessage("Введенные элементы для поиска:");
	PrintArray(items);
	PrintMessage("Последовательный поиск:");

	int entryCounter = 0;
	for each (int item in items)
	{
		for (int i = 0;i < rows; i += 2)
			LinearSearch(item, matrix[i], entryCounter);
	}
	RotateMatrix(matrix);
	for each (int item in items)
	{
		for (int i = 0;i < rows; i+=2)
			LinearSearch(item, matrix[i], entryCounter);
	}
	RotateMatrix(matrix);

	if (entryCounter == 0)
		PrintMessage("Вхождений нет");
	else
		cout << "Число вхождений:" << entryCounter << endl;

	//for (int i = 0;i < rows;i++)
	//	sort(matrix[i].begin(), matrix[i].end());
	//PrintMatrix(matrix, "Отсортированная матрица:");


	PrintMessage("Бинарный поиск:");
	entryCounter = 0;
	for each (int item in items)
	{
		for (int i = 0;i < rows; i += 2)
		{
			vector<int> temp = matrix[i];
			sort(temp.begin(), temp.end());
			binarySearch(temp, item, entryCounter);
		}
	}
	RotateMatrix(matrix);
	for each (int item in items)
	{
		for (int i = 0;i < rows; i += 2)
		{
			vector<int> temp = matrix[i];
			sort(temp.begin(), temp.end());
			binarySearch(temp, item, entryCounter);
		}
	}
	if (entryCounter == 0)
		PrintMessage("Вхождений нет");
	else
		cout << "Число вхождений:" << entryCounter << endl;

	system("pause");
	return 0;
}
