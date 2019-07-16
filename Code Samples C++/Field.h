#include "Cell.h"
#include "ChessEnums.h"
#include "StrHelper.h"
#pragma once
/// <summary>
/// класс игрового поля
/// </summary>
class Field
{
private:
	/// <summary>
	/// проверяет координату на корректность
	/// </summary>
	/// <param name="coord">координата</param>
	/// <returns>true- если в пределах поля</returns>
	bool Check(int coord);
public:
	/// <summary>
	/// Квадратная матрица содержит все клетки поля
	/// </summary>
	vector<vector<Cell>> a;
	/// <summary>
	/// текущий размер поля
	/// </summary>
	size_t size;
	/// <summary>
	/// 
	/// </summary>
	Field();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="_a"></param>
	Field(vector<vector<Cell>> _a);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	Field(vector<vector<int>> _a);
	/// <summary>
	/// Создает поле указанного размера
	/// </summary>
	/// <param name="_size">размер поля</param>
	Field(size_t _size);
	/// <summary>
	/// генерирует поле из строки вида:
	/// {0,0},{1,1},
	/// {1,1),{2,2}
	/// </summary>
	/// <param name="str">строка с данными</param>
	Field(string str);
	/// <summary>
	/// Деструктор
	/// </summary>
	~Field();
	/// <summary>
	/// Устанвлиает значение в указной строке и столбце
	/// </summary>
	/// <param name="row">строка</param>
	/// <param name="column">столбец</param>
	/// <param name="value">значение</param>
	bool SetItem(size_t row, size_t column, int value);
	bool SetItem(size_t row, size_t column, CellTypes type, int value);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="row"></param>
	/// <param name="columns"></param>
	/// <returns></returns>
	Cell GetItem(size_t row, size_t columns);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="cell"></param>
	/// <param name="value"></param>
	bool SetItem(Cell cell, int value);
	bool SetItem(Cell cell, CellTypes type, int value);
	/// <summary>
	/// s
	/// </summary>
	/// <param name="cell"></param>
	/// <returns></returns>
	Cell GetItem(Cell cell);
	/// <summary>
	/// оператор сложения
	/// </summary>
	Field operator+(Field & a);
	/// <summary>
	/// преобразует в строку
	/// </summary>
	/// <returns></returns>
	string GetStr();
	/// <summary>
	/// смещает матрицу
	/// </summary>
	Field Shift(Directions direction);
	/// <summary>
	/// проверяет клетку на принадлежность полю
	/// </summary>
	/// <param name="cell"></param>
	/// <returns></returns>
	bool Check(Cell cell);
	Field(Field * field);
};

