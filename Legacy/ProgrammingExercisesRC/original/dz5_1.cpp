#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

class myString{
	public:
		myString(); //конструктор, передаватьс€ ничего не должно
		myString(const char *str); //конструктор преобразовывающий
		myString(const myString &str);	//копирующий конструктор
		~myString();	//деструктор	
		myString& myStrcpy(const myString &str2);	//функци€ копировани€ одной строки в другую
		myString& myStrcat(const myString &str2);	//сцепление строк
		myString& myStrstr(const myString &str1, const myString &str2);	//поиск строки, передаем две строки, а возвращаем объект
		int myStrcmp(const mроиироyString &str2)const;	//сравнение строк
		int myStrlen()const;		//получение длины строки
		void print()const{cout<<S<<endl;};	//функци€ печати
	private:
		char *S;
		int size;
};

myString::myString():size(0)	//конструктор 
{
	S=new char[size+1];
	assert(S!=0);
	S[0]='\0';
}

myString::~myString()		//деструктор
{
	delete []S;
}

myString::myString(const myString &str):size(str.size)	//копирующий конструктор
{
	S=new char[size+1];
	assert(S!=0);
	strcpy(S,str.S);
}

myString::myString(const char *str){		//преобразовывающий конструктор
	size=strlen(str);
	S=new char[size+1];
	assert(S!=0);
	strcpy(S, str);
}

myString& myString::myStrcpy(const myString &str2){		//копирование строки
	if(this!=&str2){
		char *x=new char[str2.size+1];
		assert(x!=0);
		strcpy(x, str2.S); //куда откуда
		delete[]S;
		S=x;
		size=str2.size;
	}
	return *this; 
}

int myString::myStrlen()const{	//нахождение длины
	return size;
}

int myString::myStrcmp(const myString &str2)const{	//сравнение строк
	return strcmp(S, str2.S); //что с чем
}

myString& myString::myStrcat(const myString &str2){	//сцепление строк
	char *x=new char[size+str2.size+1];
	assert(x!=0); 
	strcpy(x, S); //копирование, куда откуда
	strcat(x, str2.S); //сцепление
	delete[]S; //очищаем строку
	S=x;
	size+=str2.size; //измен€ем размер
	return *this;
}

myString& myString::myStrstr(const myString &str1, const myString &str2){	//поиск строки в строке
	char *x = strstr(str1.S, str2.S); //создаЄм строку, в которой будет хранитьс€ результат поиска
	if(x==0){ //если поиск результатов не дал
		size=0;
		S=new char[1];
		S[0]='\0'; //возвратим пустую строку
	}
	else{ //если поиск дал результаты
		size=strlen(x);
		char* y = new char[size+1];
		strcpy(y,x);
		delete []S; //очищаем строку
		S=y;
	}
	return *this;
}

int main(){
	myString str, str2("veritas");	//объ€вл€ем две строки
	str.myStrcat("lolo").print();	//сцепление строк
	cout<<str2.myStrlen()<<endl;	//печать длины строки
	str.myStrstr(str, "o").print();	//поиск строки в строке
	str.myStrcpy(str2).print();	//копирование строки в строку
	cout<<str.myStrcmp("veritas")<<endl;	//печать результата сравнени€
	return 0;
}
