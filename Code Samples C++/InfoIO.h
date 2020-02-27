#include "stdafx.h"
//#include "Field.h"
//#include "Enums.h"
#pragma once
/// <summary>
/// Содержит методы и обертки 
/// для вывода массивов, матриц и примитивов
/// </summary>
class IO
{
private:

public:
#pragma region Конструктор/Деструктор
	IO();
	~IO();
#pragma endregion

#pragma region Перечисления

#pragma endregion

#pragma region Методы

#pragma region Ввод
	/// <summary>
	/// проверяет вялется ли строка целым числом
	/// </summary>
	/// <param name="s">строка</param>
	/// <returns>true -если целое число</returns>
	bool isInt(string s);
	/// <summary>
	/// проверяет вялется ли строка целым числом 
	/// </summary>
	/// <param name="s">строка</param>
	/// <returns>true -если целое число</returns>
	bool isInt(char* s);
	/// <summary>
	/// получает целое число из консоли
	/// </summary>
	/// <param name="value">переменная для хранения</param>
	/// <param name="message">инструкия по вводу</param>
	/// <returns>false если ввели не число</returns>
	bool Get(int& value, string message);
	/// <summary>
	/// получает дробное число из консоли
	/// </summary>
	/// <param name="value">переменная для хранения</param>
	/// <param name="message">инструкия по вводу</param>
	/// <returns>false если ввели не число</returns>
	bool Get(double& value, string message);
	/// <summary>
	/// Получает целочисленный массив из консоли
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="n">размер</param>
	void Get(int* a, int n);
	/// <summary>
	/// Получает массив дробных чисел из консоли
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="n">размер</param>
	void Get(double* a, int n);
	/// <summary>
	/// Получает строку от пользователя
	/// </summary>
	/// <param name="str">ссылка на строку</param>
	/// <param name="message">сообщение</param>
	void Get(string* str, string message);
	/// <summary>
	/// Получает строку от пользователя
	/// </summary>
	/// <param name="str">ссылка на строку</param>
	void Get(string* str);
	/// <summary>
	/// получает блевое значение от пользователя
	/// </summary>
	/// <param name="b">булевое значение</param>
	void Get(bool* b);
	/// <summary>
	/// Получает целое число у пользователя
	/// </summary>
	/// <returns></returns>
	int GetInt();
	/// <summary>
	/// Получает целое число у пользователя
	/// </summary>
	/// <param name="message">сообщение</param>
	/// <returns></returns>
	int GetInt(string message);
	/// <summary>
	/// Получает вещественное число у пользователя
	/// </summary>
	/// <returns></returns>
	double GetDouble();
	/// <summary>
	/// Получает вещественное число у пользователя
	/// </summary>
	/// <param name="message">сообщение</param>
	/// <returns></returns>
	double GetDouble(string message);
	/// <summary>
	/// Получает строку у пользователя
	/// </summary>
	/// <returns></returns>
	string GetStr();
	/// <summary>
	/// Получает строку у пользователя
	/// </summary>
	/// <param name="message">сообщение</param>
	/// <returns></returns>
	string GetStr(string message);
#pragma endregion

#pragma region Вывод
	/// <summary>
	/// Устанавлвает цвет в консоли
	/// </summary>
	/// <param name="text">цвет текста</param>
	/// <param name="background">цвет фона</param>
	void SetColor(int text, int background);
	/// <summary>
	/// Устанавливает одинаковый цвет для 
	/// фона и текста
	/// </summary>
	/// <param name="commonColor">цвет</param>
	void SetColor(int color);
	/// <summary>
	/// Выводик указанную строку в консоль
	/// </summary>
	/// <param name="message">сообщение для вывода</param>
	void Print(string message);
	/// <summary>
	/// Выводик указанную строку в консоль
	/// </summary>
	/// <param name="message">сообщение для вывода</param>
	void Print(const char* message);
	template <typename T>
	/// <summary>
	/// выводит массив на экан 
	/// в строку(4 пробела на элемент)
	/// </summary>
	/// <param name="a">массив</param>
	/// <param name="size">размер</param>	
	void Print(T* a, int size)
	{
		for (size_t i = 0; i < size; i++)
			Print(a[i]);
		cout << endl;
	}
	template <typename T>
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <param name="row"></param>
	/// <param name="cols"></param>
	void Print(T * *a, int rows, int cols) {
		for (size_t i = 0; i < rows; i++)
			Print(a[i], cols);
	}
	template <typename T>
	/// <summary>
	/// выводим вектор на кэран в строку
	/// </summary>
	/// <param name="a">вектор для вывода</param>
	void Print(vector<T> a)
	{
		Print(&a[0], a.size());
	}
	template <typename T>
	/// <summary>
	/// выводим вектор на экран в строку
	/// </summary>
	/// <param name="a">вектор для вывода</param>
	/// <param name="message">сообщение</param>
	void Print(vector<T> a, string message)
	{
		this->Print(message);
		this->Print(&a[0], a.size());
	}
	template <typename T>
	/// <summary>
	/// выводим вектор на экран в строку
	/// каждая строка с выводится новой строки
	/// </summary>
	/// <param name="a">вектор для вывода</param>
	/// <param name="numerate">true- нумеровать строки</param>
	void PrintLn(T * a, int size, bool numerate)
	{
		for (int i = 0; i < size; i++)
			if (numerate)
				PrintLn(a[i], i + 1);
			else
				PrintLn(a[i]);
		cout << endl;
	}
	template <typename T>
	/// <summary>
	/// выводим вектор на экран в строку
	/// каждая строка с выводится новой строки
	/// </summary>
	/// <param name="a">вектор для вывода</param>
	/// <param name="numerate">true- нумеровать строки</param>
	void PrintLn(vector<T> a, bool numerate)
	{
		PrintArrayLn(&a[0], a.size(), numerate);
	}
	template<typename T>
	/// <summary>
	/// вывести значение 
	/// любого типа в консоль
	/// после перейти на новую строку
	/// </summary>
	/// <param name="value">значение</param>
	void PrintLn(T value) {
		cout << value << endl;
	}
	template<typename T>
	/// <summary>
	/// вывести значение 
	/// любого типа в консоль
	/// после перейти на новую строку
	/// </summary>
	/// <param name="i">номер элемента</param>
	/// <param name="value">значение</param>
	void PrintLn(T value, int i) {
		cout << i << '.' << value << endl;
	}
	template<typename T>
	/// <summary>
	/// вывести значение 
	/// любого типа в консоль
	/// </summary>
	/// <param name="value">значение</param>
	void Print(T value) {
		//cout << value;
	}
	/// <summary>
	/// выводим матрицу на экран в квадратном виде
	/// </summary>
	/// <param name="matrix">матрица для вывода</param>
	void Print(vector<vector<int>> matrix);
	/// <summary>
	/// выводит матрицу с подписью 
	/// </summary>
	/// <param name="matrix">матрица</param>
	/// <param name="message">подпись</param>
	void Print(vector<vector<int>> matrix, string message);
	/// <summary>
	/// Выводит игрововое поле 
	/// в  виде клеточек
	/// </summary>
	/// <param name="field">игровое поле</param>
	/// <param name="colorsMap">карта цветов</param>
	//void Print(Field field, map<CellTypes, ConsoleColors> colorsMap);
	/// <summary>
	/// печатает разделитель в консоли вида: "________"
	/// </summary>
	/// <param name="count">число разделителей</param>
	void PrintSeparator(int count);
#pragma endregion

#pragma endregion

#pragma region Другое
	/// <summary>
	/// Устанавливает русский ввод/вывод в консоли
	/// </summary>
	void SetRusIO();
	/// <summary>
	/// Ставит программу на паузу, 
	/// пока не будет нажата любая клавиша
	/// </summary>
	void Pause();
	/// <summary>
	/// очищает консоль
	/// </summary>
	void Clear();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="milliSeconds"></param>
	void Wait(int milliSeconds);
#pragma endregion

};