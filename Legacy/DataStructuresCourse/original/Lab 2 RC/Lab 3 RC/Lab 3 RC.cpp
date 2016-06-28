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
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	AVL A(15);
	AVL B(15);
	AVL C(15);
	AVL D(15);
	A.OutTree("A");
	B.OutTree("B");
	C.OutTree("C");
	D.OutTree("D");
	(A - (B | C | D)).OutTree("A - B - C - D:");
	system("pause");
	return 0;
}

