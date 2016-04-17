// C++ taine.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h" 
#include <string.h> 
#include <iostream> 
#include <stdio.h> 
#include <Windows.h> 
#include <time.h> 
#include <vector>
#pragma warning(disable : 4996) 
using namespace std;
class student
{
public:
	string name;
	string lastname;
	int age;

	student()
	{

	}
	student(string _name, string _lastname, int _age)
	{
		name = _name;
		lastname = _lastname;
		age = _age;
	}
	~student()
	{

	}


};

class queue
{
private:
	vector<student> students;
public:
	void add(student stew)
	{
		students.push_back(stew);
	}
	student pop()
	{
		if (students.size() > 0)
		{
			student first = students[0];
			students.erase(students.begin(), students.begin() + 1);
			return first;
		}
		return student();
	}
	void sort()
	{
		for (int i = 0; i < students.size() - 1;i++)
		{
			for (int j = 0; j < students.size() - 1 - i;j++)
			{
				if (students[j].lastname > students[j + 1].lastname)
				{
					swap(students[j], students[j + 1]);
				}
			}
		}
	} 
	void print() 
	{
		for (int i = 0;i < students.size();i++)
			printf("%s\n", students[i].lastname.c_str());
		
	}
};



int * FillArray(int size)
{
	srand(time(NULL));
	int *a = new int[size];
	for (int i = 0;i < size;i++)
	{
		a[i] = rand() % 100;
	}
	return a;
}

void PrintArray(int *a, int size)
{

	for (int i = 0; i < size; i++)
	{
		printf("%4i", a[i]);
	}
	printf("\n");
}

void quicksort(int *a, int size)
{
	int x = a[size / 2];
	int i = 0;
	int j = size - 1;
	while (i <= j)
	{
		while (a[i] < x) i++;
		while (a[j] > x) j--;
		if (i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	if (j > 0)quicksort(a, j + 1);
	if (i < size)quicksort(a + i, size - i);

}

void BubleSort(int *mas, int size)
{

	for (int i = 0;i < size - 1;i++)
	{
		for (int j = 0;j < size - 1 - i;j++)
		{
			if (mas[j] > mas[j + 1])
			{
				int a = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = a;
			}
		}
	}

}

void SortPractice()
{
	int size;
	printf("Enter size:\n");
	scanf_s("%i", &size);
	int *a = FillArray(size);
	//PrintArray(a,size);

	double start = clock();
	quicksort(a, size);
	//BubleSort(a, size);
	double end = clock();
	//PrintArray(a,size);



	printf("seconds:%f", (end - start) / 1000);
	//BubleSort(a,size);
	//PrintArray(a);
}

void ClassPractice()
{
	student stew =  student("ivan", "ivanov", 29);
	student stew2 = student("ivan", "petrov", 29);
	student stew3 = student("ivan", "aidorov", 29);
	queue *q = new queue();

	q->add(stew3);
	q->add(stew2);
	q->add(stew);
	q->print();
	q->sort();
	q->print();
	/*student *stew = new student();
	char buffer[20];
	printf("Enter student's name: ");
	scanf("%s", &buffer);
	stew->name = buffer;
	printf("Enter student's lastname: ");
	scanf("%s", &buffer);
	stew->lastname = buffer;
	printf("Enter student's age: ");
	scanf("%i", &stew->age);*/
}


int main()
{
	ClassPractice();
	system("pause");
	return 0;
}

