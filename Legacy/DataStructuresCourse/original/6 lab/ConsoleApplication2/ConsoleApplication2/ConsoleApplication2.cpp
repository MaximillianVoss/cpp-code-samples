// Lab_3_fixed.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <vector>
using namespace std;


class Set
{ 
private:
	enum {N=32};
	char S;
	int len;
	struct spiski
	{
		int value;
		int num;
		spiski * next;    
		spiski (int a){next=NULL; value=a;}; 
		~spiski() { if(next) delete next; }		
	};
	spiski *symtab[N];  
public:
	Set();              
	Set (char);         
	Set (char, int );  
	Set (const Set &); 
	Set operator &(const Set&) const; 
	Set operator |(const Set&) const;
	Set operator -(const Set&) const;
	Set operator =(const Set&);
	spiski *del(spiski *r){return r->next;} 
	void concat(const Set&, const Set&); // сцепление
	void mul(const Set&A, int); // размножение
	void excl(const Set&, const Set&);// исключение
	int f(int); // хеш-функция 
	spiski *lookup(int k)// поиск элемента по ключю в хеш-таблице
	{
		int h;
		spiski *r;
		h=f(k);
		if(symtab[h])
		{
			r=symtab[h];
			while(r)
			{		
				if(r->value==k)
					return r;
				else 
				r=r->next;
			}
			return NULL;
		}
		else
			return NULL;

	};	
	void add(int, int); // поиск места и добавление элемента в Set 
	void Show();
	int power();
};

void Set :: concat(const Set &A, const Set &B)
{
	Set C(A); Set R(B);

	for(int i=0; i<N; i++){
		if(R.symtab[i]){
			if(C.symtab[i]){
				spiski* q=C.symtab[i];
				while(q->next)
					q=q->next;
				q->next=R.symtab[i];
				for(spiski* d=R.symtab[i]; d; d=d->next)
					d->num+=C.len; // новый порядковый номер
			}
			else {
				C.symtab[i]=R.symtab[i]; 
				for(spiski* d=R.symtab[i]; d; d=d->next)
					d->num+=C.len; // новый порядковый номер 
			}
		}
	}
	C.len=C.len+R.len;
	*this=C;
}

void Set :: mul(const Set &A,int n)
{
	Set B(A);
	for(int i=0; i<n; i++){	
		B.concat(B, A);
	}
	*this=B;
}

void Set :: excl(const Set&A, const Set&B) // из А исключается B
{
	// т.к. в качестве последовательности выбран порядок появление элементов,
	// то достаточно исключить из А все элементы, порядоковый номер которых меньше B.len
	Set C(A);
	spiski *r;
	if(C.len<=B.len){
		for (int i=0; i<N; i++)
			C.symtab[i]=NULL;
		C.len=0;
	}
	else{
		for(int i=0; i<N; i++){
			if(C.symtab[i]){
				r=C.symtab[i];
				while(r){
					if(r->num<B.len){
						if(r==C.symtab[i]){
							r=del(r); C.symtab[i]=r;
						}
						else r=del(r);
					}
					else{
						r->num=r->num-B.len;
						r=r->next;
					}
				}
			}
		}
		C.len=C.len-B.len;
	}
	*this=C;
}

Set :: Set() // конструктор по умолчанию
{
	for (int i=0; i< N; i++)
		symtab[i]=NULL;
	
}

Set :: Set(char s) : S(s)// конструктор с генерированием
{ 
	int k;  // число, которое сгенерируется
	int h;  // хеш-код
	int j=0;

	for(int i=0; i<N; i++)
		symtab[i]=NULL;
	for(j = 0; j<N; j++)
	{
		k = 0 + rand() % 100;
		h=f(k);
		spiski * p = new spiski(k);
		p->num=j;
		if(symtab[h]==NULL)
			symtab[h]=p;
		else
		{
			spiski *t=symtab[h];
			while(t->next)
				t=t->next;
			t->next=p;
		}
	}
	len=j;
	Show();
}

Set :: Set(char s, int n) : S(s)// конструктор с генерированием
{ 
	int k;  // число, которое сгенерируется
	int h;  // хеш-код
	int j=0;

	for(int i=0; i<N; i++)
		symtab[i]=NULL;
	for(j = 0; j<n && j<N; j++)
	{
		k = 0 + rand() % 100;
		h=f(k);
		spiski * p = new spiski(k);
		p->num=j;
		if(symtab[h]==NULL)
			symtab[h]=p;
		else
		{
			spiski *t=symtab[h];
			while(t->next)
				t=t->next;
			t->next=p;
		}
	}
	len=j;
	Show();
}

Set :: Set(const Set &B) // конструктор копирования
{
	S=B.S;
	len=B.len;
	spiski *t, *q=NULL;
	for (int i=0; i<N; i++)
	{		
		symtab[i]=NULL;
		if(B.symtab[i])
		{
			t=B.symtab[i];
			
			while(t)
			{
				spiski *p = new spiski(t->value);
				p->num=t->num;
				if(!symtab[i])
				{
					symtab[i]=p;
					q=symtab[i];
				}
				else
				{
					while(q->next)
						q=q->next;
					q->next=p;
					q=q->next;
				}
				t=t->next;
			}
		}
	}

}

Set Set :: operator & (const Set &B) const //пересечение 
{
	Set C;		 // результат пересечения
	spiski *r, *q;		 // вспомогательная переменная для указания на B.beg 
	
	for(int i=0; i<N; i++)
	{
		if(symtab[i] && B.symtab[i])
		{
			r=B.symtab[i];
			while(r)
			{
				q=symtab[i];
				while(q)
				{
					if(q->value==r->value)
						if(!C.lookup(q->value)) // если такого элемена еще нету в пересечении	
						{
							
							C.add(q->value, q->num);
						}
					q=q->next;
				}
				r=r->next;
			}
		}	
		else 
			C.symtab[i]=NULL;
	}
	return C;
}

Set Set :: operator | (const Set & B) const // объединение 
{
	Set C(*this);// копирование в C первого аргумента
	spiski *r;

	for(int i=0; i<N; i++)
	{
		if(B.symtab[i])
		{
			r=B.symtab[i];
			while(r)
			{
				if(!C.lookup(r->value))
					C.add(r->value, r->num);
				r=r->next;
			}
		}
	}
	return C;
}

void Set :: add(int F, int n)
{
	int h;
	spiski *q;
	spiski *p = new spiski(F);
	p->num=n;

	h=f(F);
	if(symtab[h])
	{
		q=symtab[h];
		while(q->next)
			q=q->next;
		q->next=p;
	}
	else
		symtab[h]=p;
}

Set Set :: operator -(const Set & B) const // вычитание множества из множества
{
	Set C(*this); 
	spiski *r, *q, *t;

	for(int i=0; i<N; i++)
	{
		q=B.symtab[i];
		while(q)
		{
			if(C.lookup(q->value))
			{
				r=C.symtab[i];
				if(r->value==q->value)
				{
					if(r->next)
					{
						C.symtab[i]->next=r->next->next;
						delete r;
					}
					else
					{
						delete r;
						C.symtab[i]=NULL;
					}
				}
				else
				{
					if(r->next)
						while(r->next)
						{
							if(r->next->value==q->value)
							{
								t=r;
								t->next=r->next->next;
								delete r->next;
							}
							r=r->next;
						}
				}
			}
			q=q->next;
		}
	}
			
	return C;
}


Set Set :: operator =(const Set &B)
{
	spiski *r;

  if(this !=&B)
  {
	  len=B.len;
	  for(int i=0; i<N; i++)
	  {
		  symtab[i]=NULL;
		  if(B.symtab[i])
		  {
			  r=B.symtab[i];
			  while(r)
			  {
				  add(r->value, r->num);
				  r=r->next;
			  }
		  }
	  }
  
	S='R';
  }
  return *this;
}

void Set :: Show()
{
	spiski *r;
	cout << "\n" << S << "=[";
	for(int i=0; i<N;i++)
	{
		if(symtab[i])
		{
			r=symtab[i];
			cout << r->value << "{" << r->num << "} ";
			while(r->next)
				{
					cout << "("<<r->next->value<< "{" << r->next->num << "}) ";
					r=r->next;
				}

		}
	}
	cout << "]\n";
}


int Set :: f(int h)
{
	int a=29, b=3;
	return (a*h+b)%N;
}


int _tmain()
{

	//multiset<int> test;
	//test.insert(1);
	//qso)

	srand(time(NULL));
	int t=0, p=0;

	do{		
		system("cls");
		Set A('A'), B('B', 10), E;
		cout << "Laboratornaya rabota 3" << endl;
		cout << "Tsarou Yauheni,4306" << endl;
		cout << "\nDeistviya nad posledovatelnistyami" << endl;
		cout << "1-Concat" << endl;
		cout << "2-Excl" << endl;
		cout << "3-Mul" << endl;
		cout << "0-Zavershit raboty" << endl;
		cout << "Viberite punkt" << endl;
		cin >> t;
		switch(t)
		{
		case 1:
			E.concat(A, B);
			E.Show();
			_getch();
			break;		case 2:
			E.excl(A, B);
			E.Show();
			_getch();
			break;
		case 3:
			cout << "\nSkolko raz proizvesti ramnojenie? ";
			cin >> p;
			E.mul(B, p);
			E.Show();
			_getch();
			break;
		case 0:
			cout << "\nPress any key!";
			_getch();
			break;
		default:
			cout << "\nOshibka!";
			_getch();
			break;
		}
		
	}
	while(t);	
	return 0;
}

