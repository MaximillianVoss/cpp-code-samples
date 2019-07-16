#include "stdafx.h"
#include "ChessFigure.h"
#pragma once
class Zebra : public ChessFigure
{
public:
	bool Attack(Cell cell);
	Zebra(string _name, Cell cell, Field _moves);
	Zebra();
	~Zebra();
};

