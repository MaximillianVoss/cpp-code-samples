// Пересечение прямых.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void function(double a, double b, double c, double a1, double b1, double c1)
{
	if (a1 * b != a * b1)
	{
		double y = (a1*c - a*c1) / (a1 * b - a * b1);
		double x = ((c - b*y) / a);		
		cout <<"x=" <<  x << "\n";
		cout <<"y=" << y << "\n";
	}
	else if (a==a1 && b==b1&& c==c1)
	{
		cout << "прямые совпадают\n";
	}
	else
	{
		cout << "прямые параллельны\n";
	}
}

string GetSymbol(int i)
{
	switch (i)
	{
	case 0:
		return "a";
		break;
	case 1:
		return "b";
		break;
	case 2:
		return "c";
		break;
	case 3:
		return "a1";
		break;
	case 4:
		return "b1";
		break;
	case 5:
		return "c1";
		break;
	default:
		break;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	double args[6];
	for (int i = 0;i < 6;i++)
	{
		cout << "Введите " + GetSymbol(i) + "\n";
		cin >> args[i];
	}
	function(args[0],args[1],args[2],args[3],args[4],args[5]);
	system("pause");
	return 0;
}

