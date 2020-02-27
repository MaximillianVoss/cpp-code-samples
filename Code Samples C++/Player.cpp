#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	field = NULL;
	isAI = false;
}

Player::Player(int _ships, Field * _field)
{
	ships = _ships;
	field = _field;
	isAI = false;
}

Player::~Player()
{

}

bool Player::GetIsAI()
{
	return isAI;
}

void Player::EnableAI()
{
	isAI = true;
}

void Player::DisableAI()
{
	isAI = false;
}

Cell Player::GetCoords()
{
	if (!isAI) {
		int row = -1, col = -1;
		io.Get(row, "Введите строку:");
		io.Get(col, "Введите столбец:");
		return Cell(row - 1, col - 1);
	}
	return Cell(rand() % (field->size), rand() % (field->size));
}