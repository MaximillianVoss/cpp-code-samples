// Пересечение отрезков.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;
// в зависимости от i возвращается строка требуемой координаты точки
string GetSymbol(int i)
{
	switch (i)
	{
	case 0:
		return "x1";
		break;
	case 1:
		return "y1";
		break;
	case 2:
		return "x2";
		break;
	case 3:
		return "y2";
		break;
	case 4:
		return "x3";
		break;
	case 5:
		return "y3";
		break;
	case 6:
		return "x4";
		break;
	case 7:
		return "y4";
		break;
	default:
		break;
	}
}
//получение коэффициентов прямой a,b,c
void GetLine(int *array,int x1,int y1,int x2,int y2)
{
	 array[0] = y2 -y1;//a
	 array[1] = x1 -x2;//b
	 array[2] = array[0] *x1 + array[1] *y1;//c
}
//метод проверяет пересекаются ли линии
void IsLinesCrossed(double* pointCoord,double a, double b, double c, double a1, double b1, double c1)
{
	if (a1 != 0 && a1 * b != a * b1)
	{
		pointCoord[0] = (a1*c - a*c1) / (a1 * b - a * b1); // y
		pointCoord[1] = ((c - b*pointCoord[0]) / a); //x
		pointCoord[2] = 1; // если точка пересечения найдена ставим контрольный флаг
						   //, чтобы вывести ее координаты в дальнейшем
	}
	else
	{
		cout << "Нет точки пересения \n";
		pointCoord[2]= 0;
	}
}
//метод проверяет точку на принадлежность отрезкам
bool check(int x11,int y11,int x12,int y12,int x21,int y21,int x22,int y22,int xPoint,int yPoint)
{
	// находим границы по х и у для каждого отрезка
	int minX1 = min(x11,x12);
	int maxX1 = max(x11, x12);
	int minY1 = min(y11, y12);
	int maxY1 = max(y11, y12);

	int minX2 = min(x21, x22);
	int maxX2 = max(x21, x22);
	int minY2 = min(y21, y22);
	int maxY2 = max(y21, y22);

	//проверяем точку на принадлежность отрезкам 
	if (xPoint>=minX1 && xPoint >= minX2 && xPoint <= maxX2 &&xPoint <= maxX1
		&&
		xPoint >= minY2 && xPoint >= minY2 && xPoint <= maxY2 &&xPoint <= maxY1)
	{
		return true;
	}
	else
	{
		return false;
	}

}
//вывод массива на экран
void PrintArray(double *a,int count)
{
	printf("\n");
	for (int i = 0; i< 2;i++)
	{
		// .2f  - 2 это количество цифр после запятой
		printf("%.2f \n",a[i]);
	}
}
//вывод массива на экран
void PrintArray(int *a, int count)
{
	printf("\n");
	for (int i = 0; i< 2;i++)
	{
		printf("%i \n", a[i]);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	// поддержка русского
	setlocale(LC_CTYPE, "rus");
	int params[8]; //точки отрезков
	int array1[3]; //коэффициенты a,b,c  для первого отрезка
	int array2[3]; //коэффициенты a,b,c  для второго отрезка
	double pointCood[3]; // координаты точки пересечения (x и y) и контрольный флаг
	//ввод координат отрезков
	for (int i = 0;i < 8;i++)
	{
		cout << "Введите " + GetSymbol(i) + "\n";
		cin >> params[i];
	}

	//получение коэффициентов линий: коэффиенты сохраниятся в array1
	GetLine(array1, params[0], params[1], params[2], params[3]);
	GetLine(array2, params[4], params[5], params[6], params[7]);
	//проверяем пересекаются ли линии
	IsLinesCrossed(pointCood,array1[0], array1[1], array1[2], array2[0], array2[1], array2[2]);
	//если точка пересечения найдена и принадлежит отрезкам
	if (pointCood[2] != 0)
	{
		PrintArray(pointCood, 2);
		if (check(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], pointCood[0], pointCood[1]))
		{
			printf("точка принадлежит отрезкам");
		}
	}
	
	system("pause");
	return 0;
}

