#include <iostream>
class Set
{ 
private:
	enum {N=32};
	char S;
	struct spiski
	{
		int value;
		spiski * next;   // сделующий по списку
		spiski (int a){next=NULL; value=a;}; // конструктор элемента
		~spiski() { if(next) delete next; }		
	};
	spiski *symtab[N];   // хеш-таблица
public:
	Set();              // конструктор по умолчанию
	Set (char);         // конструктор множества
	Set (const Set &);  // конструктор копии
	Set operator &(const Set&) const; 
	Set operator |(const Set&) const;
	Set operator -(const Set&) const;
	Set operator =(const Set&);
	int f(int); // хеш-функция 
	spiski *lookup(int k)// поиск элемента по ключу в хеш-таблице
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
	void add(int); // поиск места и добавление элемента в Set 
	void Show();
	int power();
};

