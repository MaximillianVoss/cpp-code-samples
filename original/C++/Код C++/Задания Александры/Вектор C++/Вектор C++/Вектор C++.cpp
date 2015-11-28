// ¬ектор C++.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;
int * resize(int *block ,int* array,int count)
{
	array = (int*)realloc(block, count * sizeof(int));
	return array;
}

//—труктура, описываща€ наш вектор
struct Vector {
	//здесь будут хранитьс€ элементы
	int *elements = new int[0];
	//текущий размер вектора
	int size =0 ;
	//метод, добавл€ющий элементы в вектор
	void add(int item)
	{
		//увеличиваем размер вектора на единицу
		size++;
		//перераспредел€ем пам€ть с учетом изменившегос€ размера
		elements = (int*)realloc(elements, size*sizeof(int));
		//добавл€ем элемент в массив
		//size -1 указывает на последний индекс
		elements[size - 1] = item;
	}
	
	void addAtIndex(int index,int value)
	{	
		//провер€ем меньше ли указанный индекс размера вектора
		if (index < size)
		{
			//если да
			//до увеличивае размер вектора 
			// и перераспредел€ем пам€ть с учетом изменившегос€ размера
			size++;
			elements = (int*)realloc(elements, size*sizeof(int));

			//начинаем копировать элементы с конца массива
			// по указанный индекс
			for (int i = size - 1;i >=index;i--)
			{
				elements[i] = elements[i-1];
			}
			//по указанному индексу вставл€ем элемент
			elements[index] = value;
		}
	}
	//извлечение элемента из конца вектора
	int pop()
	{
		
		int result = elements[size - 1];
		size--;
		elements = (int*)realloc(elements, size*sizeof(int));
		return result;
	}
	//удаление элемента сконца, без получени€ его значени€
	void remove()
	{
		size--;
		elements = (int*)realloc(elements, size*sizeof(int));
	}
	void removeAtIndex(int index)
	{
		if (index < size)
		{
			for (int i = index;i < size - 1;i++)
			{
				elements[i] = elements[i + 1];
			}
			size--;
			elements = (int*)realloc(elements, size*sizeof(int));
		}
	}
	//вывести вектор на экран
	void Print()
	{
		for (int i = 0;i < size;i++)
		{
			printf("%d\n", elements[i]);
		}
	}
};

void Print(string * array,int count)
{
	for (int i = 0;i < count;i++)
	{
		cout <<i+1<<")"<< array[i]<<"\n";
		//printf("%s\n", array[i]);
	}
}

Vector vect;
// меню дл€ вектора
void Menu()
{	
	int answer = 0, index = 0;;
	string menuItems[7] = { "»нициализировать вектор","ƒобавить в вектор","ƒобавить в вектор по индексу",
		"”далить из вектора","”далить из вектора по индексу","–аспечатать ветор","¬ыход" };
	Print(menuItems, 7);
	printf("¬ыберите пункт меню\n");

	cin >> answer;
	switch (answer)
	{
	case 1:
		for (int i = 0;i < 5;i++)
		{
			vect.add(i);
		}
		Menu();
		break;
	case 2:
		printf("¬ведите значение\n");
		cin >> answer;
		vect.add(answer);
		Menu();
		break;
	case 3:
		printf("¬ведите значение\n");
		cin >> answer;
		printf("¬ведите индекс\n");
		cin >> index;
		vect.addAtIndex(index, answer);
		Menu();
		break;
	case 4:
		vect.remove();
		Menu();
		break;
	case 5:
		printf("¬ведите индекс\n");
		cin >> index;
		vect.removeAtIndex(index);
		Menu();
		break;
	case 6:
		vect.Print();
		Menu();
		break;
	default:
		break;
	}
}

int main()
{
	setlocale(LC_CTYPE, "rus");
	Menu();
	system("pause");
}

