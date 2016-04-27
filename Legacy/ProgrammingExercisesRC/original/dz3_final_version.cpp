/* Задача: Реализовать функции проверки правильности расстановки скобок. Выводить ошибку
и номер неправильного элемента*/

#define L 6	//длина стека
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack{
	char S[L];
	int up;
};щпиуи

void push(stack *stk, char ch);	//поместить значение на вершину стека
char pop(stack *stk);	//снять значение с вершины стека
char top(stack *stk);	//копировать значение с вершины стека
int full(stack *stk);	//проверяет есть ли место в стеке
int empty(stack *stk);	//пустой стек или нет
void reset(stack *stk);	//привести стек в действие

int checkBr(char *str, stack *stk, int *res);	//проверка расстановки скобок
int isOpenBr(char br);	//определяет открытая ли скобка
int isCloseBr(char br);	//определяет закрытая ли скобка
char companBr(char br);	//сравнение скобок
void printError(int num, int *res);	//печать ошибки по значению, передаем номер ошибки и индекс неправильного элемента



int main(){
	int res=0;
	stack my_stk;	//объявляем наш стек
	reset(&my_stk);	//Инициализируем стек, делаем готовым к работе
	char str[]="({)";	//инициализируем символьную строку
	printError(checkBr(str, &my_stk, &res), &res);
	reset(&my_stk);	//Инициализируем стек, делаем готовым к работе
	res=0;
	char str2[]="";	//инициализируем символьную строку
	printError(checkBr(str2, &my_stk, &res), &res);
	reset(&my_stk);	//Инициализируем стек, делаем готовым к работе
	res=0;
	char str3[]="(gvgvgv[)])";	//инициализируем символьную строку
	printError(checkBr(str3, &my_stk, &res), &res);
	reset(&my_stk);	//Инициализируем стек, делаем готовым к работе
	res=0;
	char str4[]="()()])";	//инициализируем символьную строку
	printError(checkBr(str4, &my_stk, &res), &res);
	reset(&my_stk);	//Инициализируем стек, делаем готовым к работе
	res=0;
	char str5[]="]([)])";	//инициализируем символьную строку
	printError(checkBr(str5, &my_stk, &res), &res);
	reset(&my_stk);	//Инициализируем стек, делаем готовым к работе
	res=0;
	char str6[]="[]([])";	//инициализируем символьную строку
	printError(checkBr(str6, &my_stk, &res), &res);
	reset(&my_stk);	//Инициализируем стек, делаем готовым к работе
	res=0;
	char str7[]="[[[[[[[[[[[[]([])";	//инициализируем символьную строку
	printError(checkBr(str7, &my_stk, &res), &res);
	reset(&my_stk);	//Инициализируем стек, делаем готовым к работе
	res=0;
	char str8[]="[jhvjjvjhv]([])";	//инициализируем символьную строку
	printError(checkBr(str8, &my_stk, &res), &res);
	reset(&my_stk);	//Инициализируем стек, делаем готовым к работе
	res=0;
	char str9[]="[jhvjv](jh[]";	//инициализируем символьную строку
	printError(checkBr(str9, &my_stk, &res), &res);
}

int checkBr(char *str, stack *stk, int *res){
	int i;
	for(i=0;str[i]!=0;i++){
		if(isOpenBr(str[i]))	//Если текущий символ — открытая скобка, то
			if (!full(stk)){ //Если стек не заполнен, то
				push(stk, str[i]); //Помещаем текущий элемент в стек
			}
			else{
				*res= i;
				return 4; // переполнение стека
			}
		else if(isCloseBr(str[i])){ //Иначе если текущий символ — закрытая скобка, то (иначе переходим к следущему символу)
			if(empty(stk)){
				*res= i;
				return 2; //Если стек пуст, лишняя закрывающаяся скобка
			}
			if(companBr(str[i])==top(stk)) //Если закрытая скобка является парной к вершине стека, то
				pop(stk); //удаляем вершину стека
			else{
				*res= i;
				return 1; //присваиваем статус "неправильная закрывающаяся скобка"
			}
		}
	}
	if(!empty(stk)){
		*res= i;
		return 3; // Не хватает закрывающейся скобки
	}
	return 0;
}

char companBr(char ch){
	switch (ch){
		case ']': return '['; 
		case ')': return '(';
		case '}': return '{';
	}
}

int isCloseBr(char ch){ 
	return (ch==']'||ch=='}'||ch==')');
}

int isOpenBr(char ch){
	return (ch=='{'||ch=='['||ch=='(');
}

void printError(int num, int *res){
	switch (num){
		case 1: printf("Неправильная закрывающаяся скобка с индексом %i\n", *res); break;
		case 2: printf("Лишняя закрывающаяся скобка с индексом %i\n", *res); break;
		case 3: printf("Не хватает закрывающейся скобки после элемента с индексом %i\n", *res); break;
		case 4: printf("Переполнение стека после элемента с индексом %i\n", *res); break;
		case 0: printf("Все верно\n");
	}
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
