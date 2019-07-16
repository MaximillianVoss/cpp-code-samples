#include "stdafx.h"
#include "Zebra.h"

bool Zebra::Attack(Cell cell)
{
	Field posMoves = GetPossibleMoves(cell);
	return (moves.Check(cell) && posMoves.a[cell.row][cell.column].value != 0);
}

Zebra::Zebra(string _name, Cell cell, Field _moves)
{
	name = _name;
	Init(cell.row, cell.column);
	moves = Field(_moves);
}

Zebra::Zebra()
{
}


Zebra::~Zebra()
{
}
