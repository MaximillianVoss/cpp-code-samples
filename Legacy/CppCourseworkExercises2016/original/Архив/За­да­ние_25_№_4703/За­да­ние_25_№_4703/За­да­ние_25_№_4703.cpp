#include <stdio.h>
#include "stdafx.h"
#include <stdlib.h>
#include <Windows.h>
#include <utility>
#include <time.h>
#include <string>
#define N 10
#pragma warning(disable:4996)
using namespace std;

struct student {
	char sur[20], name[15];
	int marks[3];
	int twos = 0;
	float ave = 0;
	void Print()
	{
		printf("%s %s\n", sur, name);
	}
	void GetTwos()
	{
		for (int i = 0;i < 3;i++)
			if (marks[i] == 2)twos++;
	}
	void CountAverage(float a, float b, float c) {
		ave = (a + b + c) / 3;
	}
	student()
	{

	}
	student(string _name, string lastname, int a, int b, int c)
	{
		strcpy(sur, lastname.c_str());
		strcpy(name, _name.c_str());
		marks[0] = a;
		marks[1] = b;
		marks[2] = c;
	}
};
void Task4703()
{
	int a[N];
	int i, m;
	for (i = 0; i < N; i++)
		scanf_s("%d", &a[i]);

	m = (2 ^ 16) - 1;

	for (i = 0; i < N; i++) {
		if ((a[i] > 0) && ((a[i] % 2) == 1) && (a[i] < m)) m = a[i];
	}

	printf("\n\n\n\n\n%i\n\n\n\n", m);

	system("pause");
}
int Task3628() {
	int m1 = 0, m2 = 0, increase = 0, incmax = 0, count = 1, x = 1;
	scanf_s("%i", &m2);
	if (!m2) { count = 0; x = 0; };
	while (x) {
		scanf_s("%i", &m1);
		if (!m1) break;
		if (m2 < m1)  increase += m1 - m2;
		else
			increase = 0;

		if (increase > incmax) incmax = increase;

		m2 = m1;
		count++;
	}

	printf("Got %i numbers\n", count);
	printf("Biggest difference is %i\n", incmax);

	system("pause");
	return 0;
}
int Task3130() {
	int m = 0;
	scanf_s("%i", &m);
	int *n = new int[m];
	for (int i = 0;i < m;i++) {
		scanf_s("%i", &n[i]);
	}
	for (int i = 0;i < m;i++) {
		if (n[i] < 0) printf("%i ", n[i]);
	}
	printf("\n");
	for (int i = 0;i < m;i++) {
		if (n[i] >= 0) printf("%i ", n[i]);
	}

	system("pause");
	return 0;
}
int Task3104() {
	int count;
	scanf_s("%i", &count);
	student *s = new student[count];

	for (int i = 0; i < count; i++) {
		int a, b, c;
		scanf("%s %s %i %i %i", &s[i].sur, &s[i].name, &s[i].marks[0], &s[i].marks[1], &s[i].marks[2]);
		s[i].GetTwos();
	}

	for (int i = 0; i < count; i++)
		if (s[i].twos == 3) s[i].Print();

	for (int i = 0; i < count; i++)
		if (s[i].twos == 2) s[i].Print();

	for (int i = 0; i < count; i++)
		if (s[i].twos == 1) s[i].Print();


	system("pause");
	return 0;
}


student *GetStudents(int count)
{
	student *s = new student[count];
	string names[10] = { "Pete","Ivan","Alex","Franz","Max","Anna","Paul","Alfred","Garry","Fred" };
	string lastNames[10] = { "Ivanov","Petrov","Sidorov","Surname1","Surname2","Surname3","Surname4","Surname5","Surname6","Surname7" };
	char temp[15] = "fsdf";
	srand(time(NULL));
	for (int i = 0; i < count; i++) {
		float a, b, c;
		s[i] = student(names[rand() % 10], lastNames[rand() % 10], rand() % 6, rand() % 6, rand() % 6);
		
		//scanf("%s %s %f %f %f", &s[i].sur, &s[i].name, &a, &b, &c);
		//s[i].CountAverage(a, b, c);
	}
	return s;
}

int Task3109() {
	int count;
	scanf_s("%i", &count);
	student *s = GetStudents(count);

	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1 - i; j++) {
			if (s[j].ave < s[j + 1].ave)
			{
				swap(s[j], s[j + 1]);
			}
		}
	}


	for (int i = 0; i < count; i++)
		if (s[i].ave==s[count-3].ave || s[i].ave == s[count-1].ave || s[i].ave == s[count-2].ave) s[i].Print();

	system("pause");
	return 0;
}

void main() {
	Task3109();
}