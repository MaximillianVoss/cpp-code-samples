// Объединение статических массивов.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;
///<summary>Заполняет массив с консоли</summary>
///<param name="a">указатель на массив для заполнения</param>
///<param name="length">длина массива</param>
///<param name="message">сообщение пере вводом массива</param>
void GetArrayFromUser(int *a, int length, string message)
{
	printf("%s\n", message.c_str());
	for (int i = 0;i < length;i++)
	{
		printf("Введите %i элемент массива:", i + 1);
		scanf("%i", &a[i]);
	}
}
///<summary>Коипует два массива в третий массив</summary>
///<param name="source1">указатель на первый массив</param>
///<param name="source2">указатель на второй массив</param>
///<param name="length1">длина первого массива</param>
///<param name="length2">длина второго массива</param>
int* Copy(int *source1, int *source2, int length1, int length2)
{
	int *result = new int[length1 + length2];
	int counter = 0;
	for (int i = 0;i < length1;i++)
	{
		result[i] = source1[i];
		counter++;
	}
	for (int i=0;i < length2;i++)
	{
		result[i+counter] = source2[i];
	}
	return result;
}
///<summary>Сортировка вставками</summary>
///<param name="values">массив для сортировки</param>
///<param name="size">размер массива</param>
void Sort(int *values,int size)
{
	int n = size, step = 0;
	if (n % 2 == 1)
		step = n / 2 + 1;
	else
		step = n / 2;
	while (step > 0)
	{
		for (int k = 0; k + step < n; k++)
		{
			if (abs(values[k]) > abs(values[k + step]))
			{
				swap(values[k], values[k + step]);
			}
		}
		step--;
	}
}
///<summary>Вывод массива на экран</summary>
///<param name="a">массив для вывода</param>
///<param name="size">размре массива</param>
void Print(int *a, int size)
{
	for (int i = 0;i < size;i++) printf("%4i ", a[i]);
	printf("\n");
}

int main()
{
	//локализация ввода с консоли
	SetConsoleCP(1251);
	//локализация вывода  консоли (поддержка кириллицы)
	SetConsoleOutputCP(1251);
	//размеры первого и второго массивов
	int size1, size2;
	printf("Введите количество элементов первого массива:");
	scanf("%i", &size1);
	printf("Введите количество элементов второго массива:");
	scanf("%i", &size2);
	//динамически выделяем память под первый массив
	int *a = new int[size1];
	//вводим первый массив с клавиатуры
	GetArrayFromUser(a, size1, "Введите массив");
	int *b = new int[size2];
	GetArrayFromUser(b, size2, "Введите массив");
	//копируем массивы в третий массив
	int *result = Copy(a, b, size1, size2);

	Sort(result, size1 + size2);
	Print(result, size1 + size2);



	system("pause");
	return 0;
}

