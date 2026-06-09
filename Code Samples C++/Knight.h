#include "pch.h"
#include "ChessFigure.h"
#pragma once
class Knight : public ChessFigure
{
public:
	bool Attack(Cell cell);	
	Knight(string _name, Cell cell, GameField _moves);
	Knight();
	~Knight();
};

