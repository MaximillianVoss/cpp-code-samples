//Задача: реализация очереди

#define L 10
#include <iostream>
#include <string.h>

using namespace std;


// Чтобы избежать неоднозначности полноты и пустоты массива, одна ячейка всегда остаётся пустой:
// в массив очереди из 10 ячеек будет помещено не больше 9-ти элементов

class queue{
	public:
	void enqueue(char ch); //Помещаем значение в "хвост" очереди
	char dequeue(); //Удаляем и возвращаем символ из "головы"
	char front()const; //Копирует символ из "головы"
	int full()const; //Проверка очереди на полноту
	int empty()const; //Проверка очереди на пустоту
	void reset(); //Сброс очереди
	private:
	int next(int pos)const;	//вычисление новой позиции
	char S[L]; //Объявляем массив очереди
	int rear, tail; //Объявляем индекс головы и индекс хвоста
};

int main(){
	char str[]="0123456789";	//Инициализируем строку, которую будем помещать в очередь
	queue queue_1; //Создаём экземпляр класса "Очередь"
	queue_1.reset(); //Очищаем очередь
	int i=0;
	while(!queue_1.full()) //Пока очередь не полна
		queue_1.enqueue(str[i++]);//Заполняем очередь элементом
	while(!queue_1.empty()){ //Пока очередь не пуста
		cout<<queue_1.dequeue()<<endl; //выводим головной элемент из очереди
	}
}

int queue::next(int pos)const{
	return (pos+1)%L;
}

void queue::enqueue(char ch){
	tail=next(tail);	//сдвигаем хвост
	S[tail]=ch;
}

char queue::dequeue(){
	int head = front();	//сохроняем голову
	rear=next(rear);	//сдвигаем голову
	return head;
}

char queue::front()const{
	return S[rear];	//Возвращаем копию значения головы
}

int queue::full()const{
	return rear==next(next(tail));
}

int queue::empty()const{
	return rear==next(tail);
}

void queue::reset(){
	tail=L-1;	//Выставляем указатель хвоста на последний элемент массива
	rear=0;	//Выставляем указатель головы на последний элемент массива
}
