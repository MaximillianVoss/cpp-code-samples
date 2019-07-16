#include "stdafx.h"
#include "Knight.h"




bool Knight::Attack(Cell cell)
{
	return false;
}

Knight::Knight(string _name, Cell cell, Field _moves)
{
	name = _name;
	Init(cell.row, cell.column);
	moves = _moves;
}

Knight::Knight()
{

}


Knight::~Knight()
{
}
