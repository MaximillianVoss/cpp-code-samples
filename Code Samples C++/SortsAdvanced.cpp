#include "stdafx.h"
#include "SortsAdvanced.h"

#pragma region Конструкторы
SortsAdvanced::SortsAdvanced()
{
}


SortsAdvanced::~SortsAdvanced()
{
}
#pragma endregion

#pragma region Вспомогательные методы
bool SortsAdvanced::cmp(int a, int b, int &cmpsCounter)
{
	cmpsCounter++;
	if (abs(a) > abs(b))
		return true;
	return false;
}
void SortsAdvanced::PrintTable(vector<Result>results, string message)
{
	printf("%s\n", string(78, '_').c_str());
	printf("%25s %25s %25s\n", "Название сортировки", "Количество сравнений", "Количество перестановок");
	printf("%s\n", string(78, '_').c_str());
	for (size_t i = 0; i < results.size(); i++)
	{
		printf("%25s %25i %25i\n", results[i].name.c_str(), results[i].cmpsValue, results[i].swapsValue);
	}
	printf("%s\n", string(78, '_').c_str());
}
void SortsAdvanced::PrintStatistics(int cmps, int swaps)
{
	printf("swaps:%i cmps:%i\n", swaps, cmps);
}
#pragma endregion

#pragma region Сортировки
void SortsAdvanced::BubbleSort_Abs(vector<int>&a, int &cmpsCounter, int &swapsCounter)
{
	bool flag = 1;
	int to = a.size();
	int temp;
	while (flag) {
		flag = 0;
		for (int j = 0; j < to - 1; j++) {
			cmpsCounter++;
			if (abs(a[j]) > abs(a[j + 1])) {
				swapsCounter++;
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag = 1;
			}
		}
		to--;
	}
}
void SortsAdvanced::SelectSort_Abs(vector<int>&a, int &cmpsCounter, int &swapsCounter)
{
	int m = a.size();
	vector<int> nw;
	for (int j = 0; j < m; j++) {
		int min = 0;
		while ((a[min] == INT_MAX) && (min < m)) {
			min++;
		}
		for (int l = 0; l < m; l++) {
			if ((a[l] != INT_MAX) && (l != min)) {
				if (!cmp(a[l], a[min], cmpsCounter))
				{
					min = l;
				}
			}
		}
		nw.push_back(a[min]);
		a[min] = INT_MAX;
		swapsCounter++;
	}
	for (int j = 0; j < m; j++) {
		a[j] = nw[j];
	}
}
void SortsAdvanced::Insertsort_Abs(vector<int>&a, int &cmpsCounter, int &swapsCounter)
{
	int m = a.size();
	for (int j = 0; j < m - 1; j++) {
		int min = j;
		for (int l = j + 1; l < m; l++) {
			cmpsCounter++;
			if (abs(a[min]) > abs(a[l])) {
				min = l;
			}
		}
		if (min != j) {
			swapsCounter++;
			int temp = a[j];
			a[j] = a[min];
			a[min] = temp;
		}
	}
}
void SortsAdvanced::ShellSort_Abs(vector<int> &a, int &cmpsCounter, int &swapsCounter)
{
	int n = a.size(), step = 0;
	if (n % 2 == 1)
		step = n / 2 + 1;
	else
		step = n / 2;
	while (step > 0)
	{
		for (int k = 0; k + step < n; cmpsCounter++, k++)
		{
			if (abs(a[k]) > abs(a[k + step]))
			{
				swap(a[k], a[k + step]);
				swapsCounter++;
			}
		}
		step--;
	}
}
void SortsAdvanced::QSort_Abs(int* a, int size, int &cmpsCounter, int &swapsCounter) {
	long i = 0, j = size - 1;
	int temp, p, mIndex = size >> 1;
	p = a[mIndex];
	if (size > 1)
	{
		do {
			while (i != mIndex && cmp(p, a[i], cmpsCounter))
			{
				if (i == j) { cmpsCounter--; }
				i++;
			}
			while (j != mIndex && cmp(a[j], p, cmpsCounter))
			{
				if (i == j) { cmpsCounter--; }
				j--;
			}

			if (i <= j) {
				if (i == mIndex)
				{
					mIndex = j;
				}
				if (j == mIndex)
				{
					mIndex = i;
				}

				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
				if (i == j || a[i] == a[j])
				{
					swapsCounter--;
				}
				i++;
				j--;
				swapsCounter++;
			}
		} while (i <= j);
		if (j > 0) QSort_Abs(a, j + 1, cmpsCounter, swapsCounter);
		if (size > i) QSort_Abs(a + i, size - i, cmpsCounter, swapsCounter);

	}
}
#pragma endregion

#pragma region Тестовые примеры
/*vector<int> sample0 = { 1,2,3,4,5,6,7,8,9,10 };
vector<int> sample1 = { 1,2,3,4,5,6,7,8,9,10 };
vector<int> sample2 = { 7,3,0,2,8,6,1,9 };
vector<int> sample3 = { 7,3,0,2,8,6,1,9 };
vector<int> sample4 = { 1,1,1,1,1,1,1,1 };*/
/*
HlopQSort(&sample2[0], sample2.size());
Print(sample2);
PrintStatistics(cs, cp);
QSort_Abs(&sample3[0], sample3.size(), cmpsCounter, swapsCounter);
Print(sample3);
PrintStatistics(cmpsCounter, swapsCounter);
*/
/*
//здесь можно сравнить сортировки  Шелла из примера
//и передаланные мной
//sample2 и sample3 - одинаковые массивы, сделано из -за тоого чтобы в ShellSort_Abs
//не попал отсортированный sample2 методом  ShellSortExample
ShellSortExample(sample2);
Print(sample2);
ShellSort_Abs(sample3, cmpsCounter, swapsCounter);
Print(sample3);
PrintStatistics(cmpsCounter, swapsCounter);
*/
/* Тут можно рассомментить и сравнить как работают сортировки и убедиться что все ок
HlopQSort - перенес сортировку из кода
QSort_Abs - передалана под абсолютное значение

HlopQSort(&sample0[0], 7);
PrintStatistics(cp, cs);
Print(sample2);
QSort_Abs(&sample0[0], 7, cmpsCounter, swapsCounter);
PrintStatistics(cp, cs);
Print(sample2);
*/
#pragma endregion

#pragma region Тесты сортировок
void SortsAdvanced::Test() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int cmpsCounter = 0, swapsCounter = 0;
	vector<int> Sizes = { 150,300,450,600,750,900,1050 };
	for each (int size in Sizes)
	{
#pragma region Настройка
		printf("Размер матрицы:%i\n", size);
		Matrix m(size, size, Matrix::MatrixType::zero);
		vector<vector<int>> matrix = m.matrix;
		vector<vector<int>> reserveCopy = matrix;
		vector<Result> results;
#pragma endregion

#pragma region Пузырек
		for (size_t i = 0; i < matrix.size(); i++)
			BubbleSort_Abs(matrix[i], cmpsCounter, swapsCounter);
		matrix = reserveCopy;
		results.push_back(Result("Сортировка Пузырьком", cmpsCounter, swapsCounter));
		cmpsCounter = 0, swapsCounter = 0;
#pragma endregion

#pragma region Сортировка отбором
		for (size_t i = 0; i < matrix.size(); i++)
			SelectSort_Abs(matrix[i], cmpsCounter, swapsCounter);
		matrix = reserveCopy;
		results.push_back(Result("Сортировка отбором", cmpsCounter, swapsCounter));
		cmpsCounter = 0, swapsCounter = 0;
#pragma endregion

#pragma region Сортировка вставками
		for (size_t i = 0; i < matrix.size(); i++)
			Insertsort_Abs(matrix[i], cmpsCounter, swapsCounter);
		matrix = reserveCopy;
		results.push_back(Result("Сортировка вставками", cmpsCounter, swapsCounter));
		cmpsCounter = 0, swapsCounter = 0;
#pragma endregion

#pragma region Сортировка Шелла
		for (size_t i = 0; i < matrix.size(); i++)
			ShellSort_Abs(matrix[i], cmpsCounter, swapsCounter);
		matrix = reserveCopy;
		results.push_back(Result("Сортировка Шелла", cmpsCounter, swapsCounter));
		cmpsCounter = 0, swapsCounter = 0;
#pragma endregion

#pragma region Быстрая сортировка
		for (size_t i = 0; i < matrix.size(); i++)
			QSort_Abs(&matrix[i][0], matrix[0].size(), cmpsCounter, swapsCounter);
		matrix = reserveCopy;
		results.push_back(Result("Быстрая сортировка", cmpsCounter, swapsCounter));
		cmpsCounter = 0, swapsCounter = 0;
#pragma endregion
		PrintTable(results, "Таблица сравнений:");
	}
}
#pragma endregion


