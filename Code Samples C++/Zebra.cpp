#include "pch.h"
#include "Zebra.h"

bool Zebra::Attack(Cell cell)
{
	GameField posMoves = GetPossibleMoves(cell);
	return (moves.Check(cell) && posMoves.a[cell.row][cell.column].value != 0);
}

Zebra::Zebra(string _name, Cell cell, GameField _moves)
{
	name = _name;
	Init(cell.row, cell.column);
	moves = GameField(_moves);
}

Zebra::Zebra()
{
}


Zebra::~Zebra()
{
}
