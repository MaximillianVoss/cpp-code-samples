#include <iostream>
#include <time.h>
#include <stdlib.h>

class card;
class deck;
class players;

using namespace std;

class card{		//класс карта
	public:
		card(int i=0){val=i; next=0;}	//Конструктор карта
		int getNum(){return val%9;}		//Достаем номинал карты
		void setValue(int i){val=i;} //Задаём значение карты
		int getValue(){return val;} //Достаём значение карты
		void printCard()const; //Печать карты
		void setNext(card* n){next=n;} //Задатаём указатель на следующую карту
		card* getNext(){return next;}	//Достаём указатель на следующую карту
	private:
		int val; //Значение карты
		card *next; //Указатель на следующую карту
};

void card::printCard()const{
	switch(val%9){
		case 0: cout<<6;break; //Шестёрка
		case 1: cout<<7;break; //Семёрка
		case 2: cout<<8;break; //Восьмёрка
		case 3: cout<<9;break; //Девятка
		case 4: cout<<10;break; //Десятка
		case 5: cout<<'V';break; //Валет
		case 6: cout<<'D';break; //Дама
		case 7: cout<<'K';break; //Король
		case 8: cout<<'T';break; //Туз
	}	
	switch(val%4){
		case 3: cout<<char(3)<<" ";break; //Червы
		case 2: cout<<char(4)<<" ";break; //Бубны
		case 1: cout<<char(5)<<" ";break; //Трефи
		case 0: cout<<char(6)<<" ";break; //Пики
	}
}

class deck{		//Класс колода
	public:
		deck();	//Конструктор
		void printDeck()const; //Напечатать колоду
		void shuffle(); //Перемешать колоду
		void distrib(players &p1, players &p2);	//Каздача карт
	private:
		const static int size=36; //Размер колоды
		card x[size]; //Сама колода
};

deck::deck(){		//Конструткор 
	for(int i=0;i<size;i++)		
		x[i]=i;
}

void deck::printDeck()const{		//Напечатаем колоду
	for(int i=0; i<size; i++){
		x[i].printCard();
	} 
}

void deck::shuffle(){	//Перемешаем колоду
	int y, r;
	srand(time(0));
	for(int i=0; i<size; i++){
		r=rand()%size;
		y=x[r].getValue();
		x[r].setValue(x[i].getValue());
		x[i].setValue(y);
	}
}

class players{
	public:
		players(){tail=0;} //Конструктор очередь
		void reset(){tail=0;} //Сброс очереди
		void setTail(card* t){tail=t;} //Задаем указатель на хвост
		void enqueue(card* c); //Помещаем в хвост
		card* dequeue(); //Возвращаем символ из "головы"
		card* front()const{return tail->getNext();} //Копирует символ из "головы"
		int full()const{return 0;} //Проверка очереди на полноту
		int empty()const{return tail==0;} //Проверка очереди на пустоту	
		void printQueue()const; //Печать очереди
		void enqueueMore(players& c); //Помещение в хвост карт со "стола" выйгрывшиму игроку
	private:
		card *tail;
};

void players::enqueue(card* c){	//Помещаем в хвост одну карту
	if(empty()){	//Если очередь пустая
		tail=c;	//Помещаем в хвост карту
		tail->setNext(tail);	//Хвост ссылается сам на себя
	}
	else{
		c->setNext(tail->getNext());	//Вставляем карту перед головой
		tail->setNext(c);	//Задали голову
		tail=c;	//Переместили хвост
	}
}

void deck::distrib(players &p1, players &p2){		//Раздача карт игрокам
	for(int i=0; i<size; i+=2)
	{
		p1.enqueue(&x[i]);
		p2.enqueue(&x[i]+1);
	}
}

card* players::dequeue(){	//Возвращаем символ из "головы"
	card *h=tail->getNext();	//Находим голову очереди через хвост
	if (tail==h)	//Если в очереди одна карта и хвост ссылается сам на себя
		tail=0;
	else
		tail->setNext(h->getNext()); //Задаем в хвосте новую голову
 	return h; //Возвращаем карту из старой головы
}

void players::printQueue()const	//Печать очереди
{
	card *c=new card;
	if(tail==0)
		cout<<"Карты кончились";
	else{	
		(tail->getNext())->printCard();	//Переход к голове, вывод 1 карты
		c->setNext(tail->getNext());	//Вставляем карту перед головой
		c->setNext((tail->getNext())->getNext());	//Устанавливаем с на следующую карту
		while (c->getNext()!=(tail->getNext())){
			(c->getNext())->printCard();
			c->setNext((c->getNext())->getNext());
		}
	}	
}

void players::enqueueMore(players& c){	//Помещение в хвост карт со "стола" выйгрывшиму игроку
	if(tail==0){	//Если очередь пуста
		tail=c.tail;
		tail->setNext(c.tail->getNext());
	}
	else {
		card* h=tail->getNext();	//Находим голову очереди через хвост
		tail->setNext(c.tail->getNext());
		c.tail->setNext(h);
		tail=c.tail;
	}
	c.tail=0;
}

int compare(card *c1, card* c2){	//Сравнение двух карт
	int res=c1->getNum()-c2->getNum();
	return (res>0)?1:((res<0)?2:0);	//Вернем либо 0, либо 1, либо 2
}

int onTheTable(players &p1, players &p2, players &table){	//Печать стола, распределение карт на столе
	card* c1=new card;
	card* c2=new card;
	if (p1.empty() && p2.empty()) 
		return 0;
	else 
		if (p1.empty())  {	//Если у первого игрока кончились карты, то второй игрок выкладывает карты за него
			c1=p2.dequeue();
			c2=p2.dequeue();
		}
		else 
			if (p2.empty())  {	//Если у второго игрока кончились карты, то второй игрок выкладывает карты за него
				c1=p1.dequeue();
				c2=p1.dequeue();
			}	
			else {	
				c1=p1.dequeue();
				c2=p2.dequeue();
			}
	table.enqueue(c1);	//Выкладываем две карты на стол
	table.enqueue(c2);
	cout<<"На столе: ";
	table.printQueue();
	return compare(c1, c2);
}

int resDraw(int res, players &p1, players &p2, players &table){	//Присвоим выйгравшему игроку карты после ничьи
	switch(res){
		case 0: return 0;	//Все карты на столе
		case 1:	{
			p1.enqueueMore(table);
			return 1;
		}
		case 2: {
			p2.enqueueMore(table);
			return 2;	
		}
	}
}

int draw(players &p1, players &p2, players &table){	//Ничья
	int res=0;
	while (res==0&&(!p1.empty() || !p2.empty())){	//Пока очереди одного из игроков не пусты и номинал карт одинаковы
		onTheTable(p1,p2,table);	//Карты рубашкой вверх
		res=onTheTable(p1,p2,table);	//Еще один ход
	}
	return resDraw(res,p1,p2,table);	//Присвоим карты выйгравшему ход
}

void printWhoWin(int res){ //Напечатаем победителя
	switch(res){
		case 0: {
			cout<<"Ничья";
			break;
		}
		case 1: {
			cout<<"Первый игрок выйграл";
			break;
		}
		case 2:{
			cout<<"Второй игрок выйграл";
			break;
		}
	}
}

int go(players &p1, players &p2, players &table){
	int res=onTheTable(p1, p2, table);
	switch (res){
		case 0: {
			cout<<"\nЗначения карт равны, выкладываются две карты рубашками вверх, следом игроки ходят снова\n";
			return draw(p1, p2, table); 
		}
		case 1: {
			cout<<"\nПервый игрок забирает карту\n";	
			p1.enqueueMore(table);
			return 1;
		} 
		case 2: {
			cout<<"\nВторой игрок забирает карту\n";
			p2.enqueueMore(table);
			return 2;
		}
	}
}

void game(players &p1, players &p2){	//Игра
	int res=0;
	players table;
	while(!p1.empty()&&!p2.empty()){
		res=go(p1, p2, table);
		cout<<"Карты первого игрока: ";
		p1.printQueue();	//Печатаем карты первого игрока
		cout<<"\nКарты второго игрока: ";
		p2.printQueue();	//Печатаем карты второго игрока
		cout<<"\n";	
	}
	printWhoWin(res);
}

main(){
	deck myDeck;	//Объявляем колоду
	cout<<"Колода: ";
	myDeck.printDeck();	//Печатаем колоду
	myDeck.shuffle();	//Пеемешиваем колоду
	cout<<"\n";
	cout<<"Перемешанная колода: ";
	myDeck.printDeck();	//Печатаем колоду
	cout<<"\n";
	players p1, p2;	//Объявляем двух игроков
	myDeck.distrib(p1, p2);	//Раздаем карты игрокам
	cout<<"Карты первого игрока: ";
	p1.printQueue();	//Печатаем карты первого игрока
	cout<<"\nКарты второго игрока: ";
	p2.printQueue();	//Печатаем карты второго игрока
	cout<<"\n";
	game(p1, p2);	//Вызываем функцию игры
}
