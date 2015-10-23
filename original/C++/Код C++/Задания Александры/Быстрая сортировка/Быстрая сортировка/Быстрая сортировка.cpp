// Быстрая сортировка.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>

#define a_size 10
#define range  1000
using namespace std;

void PrintArray(int* a, int count)
{
	printf("\n");
	for (int i = 0; i < count;i++)
	{
		printf("%i \n", a[i]);
	}
}

void Qsort(int *a, int currentSize)
{
	//currentSize - первый итератор
	int size = currentSize;
	//k - второй итератор
	int k = 0;
	//середина сортируемого куска массива
	int middle = a[(int)(currentSize / 2)];
	int tempValue = 0;
	do
	{
		//здесь сравниеваем все элементы,
		//начиная с первого со значением центрального
		while (a[k]<middle)
		{
			k++;
		}
		//второй итератор идет с конца массива
		while (a[currentSize]>middle)
		{
			currentSize--;
		}
		//проверка взаимного расположения итераторов
		if (k <= currentSize)
		{
			tempValue = a[k];
			a[k] = a[currentSize];
			a[currentSize] = tempValue;
			k++;
			currentSize--;
		}


	} 
	while (k <= currentSize);

	if (currentSize>0)
		Qsort(a,currentSize);
	if(size>k)
		Qsort(a+k,size - k);
}



int _tmain(int argc, _TCHAR* argv[])
{
	//int a[5] = {9,10,1,2,6};
	setlocale(LC_CTYPE, "rus");
	int n = 0;
	cout << "Введите число элементов\n";	
	cin >> n;
	int* a = new int[n]; //обявляем массив на n элементов
	for (int i = 0;i < n;i++)
	{
		cin >> a[i]; //в цикле заполняем массив
	}	
	Qsort(a, n-1); //cортируем массив
	PrintArray(a, n); // печатаем отсортированный массив
	system("pause");
	return 0;
}

