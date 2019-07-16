#include "stdafx.h"
#include "ChessFigure.h"

int ChessFigure::GetRow()
{
	return row;
}

int ChessFigure::GetColumn()
{
	return column;
}

void ChessFigure::SetRow(int _row)
{
	row = _row;
}

void ChessFigure::SetColumn(int _col)
{
	column = _col;
}

void ChessFigure::Init(int _row, int _col)
{
	SetRow(_row);
	SetColumn(_col);
}

bool ChessFigure::Attack(Cell cell)
{
	return false;
}

ChessFigure::ChessFigure()
{
	name = "F";
	Init(-1, -1);
}

ChessFigure::ChessFigure(string _name, Cell cell, Field _moves)
{
	name = _name;
	Init(cell.row, cell.column);
	moves = _moves;
}

ChessFigure::ChessFigure(ChessFigure * figure)
{
	//Init(figure.GetRow(), figure.GetCol());
}

ChessFigure::~ChessFigure()
{
}
