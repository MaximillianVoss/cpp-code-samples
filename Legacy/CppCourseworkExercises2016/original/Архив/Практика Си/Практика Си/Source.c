#include <math.h>
#include <stdio.h>
#include <iostream>
#pragma warning(disable : 4996)

void Meth(int *a)
{
	int item = 0;
}

void arrprint(int* arr, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << *(arr + i*n + j) << ' ';
		}
		cout << endl;
	}
}


void GetItem(int i)
{

	//printf("%i", a*b);
}

void main()
{
	//int a, b;
	//scanf("%i %i", &a,&b);
	//ggg(a,b);
	//scanf("%i %i", &a,&b);
	//printf("%i", a*b);
	int m[10][10];
	m[0][0] = 80;
	m[0][1] = 100;
	m[10][10] = 110;
	Meth(&m[0][0]);
	getchar();
	getchar();
}