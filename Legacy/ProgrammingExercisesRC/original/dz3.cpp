#define L 6	//длина стека
#include <stdio.h>
#include <stdlib.h>

struct stack{
	char S[L];
	int up;
};

void push(stack *stk, char ch);	//поместить значение на вершину стека
char pop(stack *stk);	//снять значение с вершины стека
char top(stack *stk);	//копировать значение с вершины стека
int full(stack *stk);	//проверяет есть ли место в стеке
int empty(stack *stk);	//пустой стек или нет
void reset(stack *stk);	//привести стек в действие

char isOpenBr(char br);	//определяет открытая скобка
char isCloseBr(char br);	//определяет закрытая скобка
void printError(int num);	//печать ошибки по значению


int main(){
	int i=0;
	stack my_stk;	//объявляем наш стек
	reset(&my_stk);	//Инициализируем стек, делаем готовым к работе
	char str[]="{}()";	//инициализируем символьную строку
	push(&my_stk, str[i++]);	//помещаем первое значение в стек
	while(!full(&my_stk) &&  i<L)	//пока есть место в стеке и счетчик меньше длины стека
	{
		if(((top(&my_stk)=='(') && (str[i]==')')) || ((top(&my_stk)=='[') && (str[i]==']')) || ((top(&my_stk)=='{') && (str[i]=='}'))){		
			if(pop(&my_stk))	//снимаем значение с вершины стека
				i++;
		}
		else
			push(&my_stk, str[i++]);	//помещаем значения в стек
	}
	if(empty(&my_stk))	//если стек пуст
		printf("Скобки верно расставлены");
	else
		printf("Скобки неверно расставлены");
}

void push(stack *stk, char ch){
	stk->S[++(stk->up)]=ch;
}

char pop(stack *stk){
	return stk->S[stk->up--];
}

char top(stack *stk){
	return stk->S[stk->up];
}

int full(stack *stk){
	return stk->up==L-1;
}

int empty(stack *stk){
	return stk->up==-1;
}

void reset(stack *stk){
	stk->up=-1;
}
