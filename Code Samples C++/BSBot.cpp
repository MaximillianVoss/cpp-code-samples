#include "stdafx.h"
#include "BSBot.h"

BSBot::BSBot()
{
	field = NULL;
	isAI = true;
}

BSBot::BSBot(Field * _field)
{
	field = _field;
	isAI = true;
}

Cell BSBot::GetCoords()
{
	return Cell(rand() % (field->size), rand() % (field->size));
}

BSBot::BSBot(int _ships, Field * _field)
{
	ships = _ships;
	field = _field;
	isAI = true;
}

BSBot::~BSBot()
{
}
