#include "stdafx.h"
#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

#pragma region Струткура для стека
struct StackAdv
{
private:
	int size;
	int maxSize;
	char *data;
public:
	StackAdv()
	{
		maxSize = 10;
		size = 0;
		data = new char[maxSize];
	}
	///<summary>Добавление элемента в стек</summary>
	///<param name="c">Элемент для добавления</param>
	int push(char c)
	{
		if (size < maxSize)
		{
			data[size] = c;
			size++;
			return 1;
		}
		return 0;
	}
	///<summary>Извлечение элемента из стека</summary>
	char pop()
	{
		if (size > 0)
		{
			char temp = data[size - 1];
			size--;
			return temp;
		}
		else
			return '-';


	}
	///<summary>Проверка стека на заполненность</summary>
	int full()
	{
		if (size == maxSize)
			return 1;
		else
			return 0;
	}
	///<summary>Проверка стека на путоту</summary>
	int empty()
	{
		if (size > 0)
			return 0;
		else
			return 1;
	}
	///<summary>Считывание элемента из верхушки стека</summary>
	char top()
	{
		if (size > 0)
			return data[size - 1];
		else
			return '-';
	}
};
#pragma endregion

#pragma region система управления стеком
//структура для команд
struct Command
{
	int value;
	string command;
	Command(int _value, string _command)
	{
		value = _value;
		command = _command;
	}
};
///<summary>Преобразует текстовую команду в число</summary>
///<param name="commands">список команд</param>
///<param name="command">команда в текстовом виде</param>
int GetCommand(vector<Command> commands, char* command)
{
	for each (Command item in commands)
	{
		if (strcmp(item.command.c_str(), command) == 0)
			return item.value;
	}
	return 0;
}
///<summary>Вывод текстового сообщения в консоль</summary>
///<param name="message">сообщение для вывода</param>
void Message(string message)
{
	printf("%s\n", message.c_str());
}
///<summary>Вывод символа в консоль</summary>
///<param name="message">символ для вывода</param>
void Message(char message)
{
	printf("%c\n", message);
}
///<summary>Меню для работы со стеком</summary>
void Menu()
{
	vector<Command> commands = { Command(1,"push"), Command(2,"pop"), Command(3,"top"), Command(4,"empty"), Command(5,"full"), Command(6,"help") };
	StackAdv queue;
	char command[20];
	char value = ' ';
	scanf("%s", &command);
	while (strcmp(command, "exit") != 0)
	{
		switch (GetCommand(commands, command))
		{
		case 1:
			scanf("%s", &value);
			if (queue.push(value) == 1)
				Message("Добавлено в стек");
			else
				Message("Стек переполнен");
			break;
		case 2:

			value = queue.pop();
			if (value != '-')
			{
				Message("Извлечено из стека:");
				Message(value);
			}
			else
				Message("Стек пуст");
			break;
		case 3:
			value = queue.top();
			if (value != '-')
			{
				Message("Извлечено из стека:");
				Message(value);
			}
			else
				Message("Стек пуст");
			break;
		case 4:
			if (queue.empty() == 1)
				Message("Стек пуст");
			else
				Message("Стек не пуст");
			break;
		case 5:
			if (queue.full() == 1)
				Message("Стек переполнен");
			else
				Message("Стек не переполнен");
			break;
		case 6:
			Message("Список доступных команд:\n");
			for each(Command item in commands)
			{
				if (item.command != "help")
				{
					if (item.command == "push")
						printf("%s <символ для добавленя>\n", item.command.c_str());
					else
						printf("%s\n", item.command.c_str());
				}

			}
			Message("\n");
			break;
		default:
			Message("Неизвестная команда");
			break;
		}
		scanf("%s", command);
	}
}
#pragma endregion

#pragma region Точка входа(расскоменить для использования)
//int main()
//{
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//	Menu();
//	system("pause");
//	return 0;
//}
#pragma endregion