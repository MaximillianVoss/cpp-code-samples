#include "stdafx.h"
#include "AVL.h"
#include "time.h"
#include <Windows.h>
#include <string>

void Message(string message)
{
	printf("%s\n", message.c_str());
}
void Message(string message, bool center)
{
	if (center)
	{
		for (int i = 0;i < 40 - message.length() / 2;i++)
			printf("%c",' ');
	}	
	Message(message);
}
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	AVL a,b,c,d;
	Message("АВЛ дерево", true);
	Message("Вычисление (A-B-C-D)",true);
	a.OutTree("Дерево А:");
	b.OutTree("Дерево B:");
	c.OutTree("Дерево C:");
	d.OutTree("Дерево D:");
	AVL q(treeSize);
	q = a - b;
	q = a - c;
	q = a - d;
	q.OutTree("Результат");

	system("pause");
}






