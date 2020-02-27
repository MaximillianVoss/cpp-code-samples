#include "stdafx.h"
#include "BShip.h"

bool BShip::Check(Cell cell)
{
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++) {
			Cell checkCell = field->GetItem(Cell(cell.row + i, cell.column + j));
			if (checkCell.type == CellTypes::notFound || checkCell.type == CellTypes::ship)
				return false;
		}
	return true;
}

BShip::BShip()
{
	size = 0;

}

BShip::BShip(int _size, Field * _field)
{
	size = _size;
	field = _field;
}

bool BShip::SetShip(Cell cell)
{
	for (int i = 0; i < size; i++)
		if (!Check(Cell(cell.row + i, cell.column)))
			return false;
	for (int i = 0; i < size; i++)
		field->SetItem(Cell(cell.row + i, cell.column), CellTypes::ship, CellTypes::ship);
}

bool BShip::SetFirstEmpty()
{
	for (int i = 0; i < field->size; i++)
		for (int j = 0; j < field->size; j++) {
			if (SetShip(Cell(i, j)))
				return true;
		}
	return false;
}

BShip::~BShip()
{
}