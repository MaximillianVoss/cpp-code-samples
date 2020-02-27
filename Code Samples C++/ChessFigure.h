#include "stdafx.h"
#include "Field.h"
#pragma once
class ChessFigure
{
protected:
	/// <summary>
	/// получить строку
	/// </summary>
	int GetRow();
	/// <summary>
	/// получить столбец
	/// </summary>
	int GetColumn();
	/// <summary>
	/// задать строку
	/// </summary>
	/// <param name="_row">строка</param>
	void SetRow(int _row);
	/// <summary>
	/// задать столбец
	/// </summary>
	/// <param name="_col">столбец</param>
	void SetColumn(int _col);
	/// <summary>
	/// инциализирует позицию фигуры
	/// </summary>
	/// <param name="_row">строка</param>
	/// <param name="_col">столбец</param>
	void Init(int _row, int _col);
	/// <summary>
	/// имя или символ отображаемы на доске
	/// </summary>
	string name;
private:
	/// <summary>
	/// строка
	/// </summary>
	int row;
	/// <summary>
	/// столбец
	/// </summary>
	int column;
	/// <summary>
	/// строка в матрице ходов по умолчанию
	/// </summary>
	int rowMatrix = 3;
	/// <summary>
	/// столбец в матрице ходов по умолчанию
	/// </summary>
	int colMatrix = 3;
public:
	/// <summary>
	/// доступные ходы для фигуры
	/// </summary>
	Field moves;
	/// <summary>
	/// атака по указанной клетке
	/// </summary>
	/// <param name="cell">клетка</param>
	virtual bool Attack(Cell cell);
	/// <summary>
	/// получает доступные ходы дл фигуры
	/// </summary>
	/// <returns></returns>
	Field GetPossibleMoves(Cell cell) {
		Field res = Field(moves);
		while (cell.row > rowMatrix) {
			res = res.Shift(Directions::down);
			cell.row--;
		}
		while (cell.row < rowMatrix) {
			res = res.Shift(Directions::up);
			cell.row++;
		}
		while (cell.column > colMatrix) {
			res = res.Shift(Directions::right);
			cell.column--;
		}
		while (cell.column < colMatrix) {
			res = res.Shift(Directions::left);
			cell.column++;
		}
		return res;
	}
	/// <summary>
	/// оператор суммирования
	/// </summary>
	/// <param name="f">вторая фигура для сложения</param>
	/// <returns></returns>
	ChessFigure operator+(ChessFigure f) {
		ChessFigure res = ChessFigure(*this);
		res.moves = res.moves + f.moves;
		return res;
	}
	/// <summary>
	/// конструктор по умолчанию
	/// </summary>
	ChessFigure();
	/// <summary>
	/// создает фигуру с указанными координатами
	/// </summary>
	ChessFigure(string _name, Cell cell, Field _moves);
	/// <summary>
	/// делает копию фигуры
	/// </summary>
	/// <param name="figure">образец</param>
	ChessFigure(ChessFigure *figure);
	/// <summary>
	/// деструктор
	/// </summary>
	~ChessFigure();

};