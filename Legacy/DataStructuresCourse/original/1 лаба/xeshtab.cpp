#include "stdafx.h"
#include "XESH.h"
#include <string.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Set :: Set() // конструктор по умолчанию
{
	for (int i=0; i< N; i++)
		symtab[i]=NULL;
	
}

Set :: Set(char s) : S(s)// конструктор с генерированием
{ 
	int k;  // число, которое сгенерируется
	int h;  // хеш-код
	for(int i=0; i<N; i++)
		symtab[i]=NULL;
	for(int i = 0; i<N; i++)
	{
		k = rand();
		h = f(k);
		spiski * p = new spiski(k);
		if(symtab[h]==NULL)
			symtab[h]=p;
		else
		{
			spiski *t=symtab[h];
			//TODO:check fill
			while(t->next)
				t=t->next;
			t->next=p;
		}		
	}
	Show();
}

Set :: Set(const Set &B) // конструктор копирования
{
	S=B.S;
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
							
							C.add(q->value);
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
					C.add(r->value);
				r=r->next;
			}
		}
	}
	return C;
}

void Set :: add(int F)
{
	int h;
	spiski *q;
	spiski *p = new spiski(F);

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
	  for(int i=0; i<N; i++)
	  {
		  if(B.symtab[i])
		  {
			  r=B.symtab[i];
			  while(r)
			  {
				  add(r->value);
				  r=r->next;
			  }
		  }
		  else
			  symtab[i]=NULL;
	  }
  
	S='E';
  }
  return *this;
}

void Set :: Show()
{
	spiski *r;
	//cout << "\n" << S << "=[";
	printf("Множество %c:\n",S);
	for(int i=0; i<N;i++)
	{
		if(symtab[i])
		{
			r=symtab[i];
			printf("%i. %i ",i,r->value);
			if(r->next)
				while(r->next)
				{
					//cout << "("<<r->next->value<< ") ";
					printf(",%i", r->next->value);
					r=r->next;
				}
			printf("\n");
		}
		else
		{
			//printf("%i. empty list\n",i);
		}
	}
	//cout << "]";
}


int Set :: f(int h)
{
	int a=29, b=3;
	return (a*h+b)%N;
}