/*Задача:  Функция инициализирует массив случайными значениями, она должна менять местами кол-во строк и 
столбцов, то есть транспонировать массив. Рассмотреть отдельно случай, когда размерности строк и столбцов 
равны*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create2(int sz1, int sz2);
void erase2(int** m, int sz1, int sz2);
void print2(int** m, int sz1, int sz2);
void init2(int** m, int sz1, int sz2);
int** change(int** m, int *sz1, int *sz2); //функция выбора способа транспонирования
int** transponir1(int** m, int** n, int *sz1, int *sz2);	//функция транспонирования двумерного неквадратного массива
int** transponir2(int** m, int *sz1, int *sz2);	//функция транспонирования двумерного квадратного массива

int main(){
	int** m, sz1, sz2;
	scanf("%i %i", &sz1, &sz2);
	if(sz1>0&&sz2>0){
		m=create2(sz1, sz2);
		init2(m, sz1, sz2);
		print2(m, sz1, sz2);
		m=change(m, &sz1, &sz2);
		print2(m, sz1, sz2);
		erase2(m, sz1, sz2);
	}else printf("Error!\n");
}

int** create2(int sz1, int sz2){
	int** m=(int**)malloc(sz1*sizeof(int*));
	int i;
	for(i=0; i<sz1; i++)
	m[i]=(int*)malloc(sz2*sizeof(int));
	return m;
}

void erase2(int** m, int sz1, int sz2){
	int i;
	for(i=0; i<sz1; i++) free(m[i]);
	free(m);
}

void print2(int** m, int sz1, int sz2){
	int i, j;
	for(i=0; i<sz1; i++){
		for(j=0; j<sz2; j++) printf("%i ", m[i][j]);
		printf("\n");
	}
}

void init2(int** m, int sz1, int sz2){
	int i, j;
	srand(time(0));
	for(i=0; i<sz1; i++)
		for(j=0; j<sz2; j++)
		m[i][j]=rand()%100;
}

int** change(int** m, int *sz1, int *sz2){
	if(*sz1!=*sz2){	//если массив не квадратный
		int** n;	//объявляем новый двумерный массив
		n=create2(*sz2, *sz1);	//выделяем память для нового массива
		n=transponir1(m, n, sz1, sz2);	//вызываем функцию транспонирования
		erase2(m, *sz1, *sz2);	//очищаем память из-под старого массива
		int temp=*sz1;
		*sz1=*sz2; //меняем местами размер строки и размер столбца, для последующего использования в главном модуле
		*sz2=temp;
		return n;	//возвращаем адрес нулевого элемента нового массива
	}else{
		m=transponir2(m, sz1, sz2);
		return m;	//возвращаем адрес нулевого элемента старого транспонированного массива
	} 
}

int** transponir1(int** m, int** n, int *sz1, int *sz2){	//транспонирование неквадратного массива
	int i, j;
	for(i=0; i<*sz2; i++)
			for(j=0; j<*sz1; j++)
				n[i][j]=m[j][i]; 	//транспонируем старый массив в новый массив
	return n;			
}

int** transponir2(int** m, int *sz1, int *sz2){	//транспонирование квадратного массива
	int temp, i, j;	//создаем временную переменную
	for(i=0; i<*sz1; i++){
		for(j=0; j<i; j++){
			temp=m[i][j];
			m[i][j]=m[j][i];
			m[j][i]=temp;
		}
	}
	return m;		
}
