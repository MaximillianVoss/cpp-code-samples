#include "stdafx.h"
#include "Cell.h"

Cell::Cell()
{
	type = CellTypes::empty;
	value = 0;
}

Cell::Cell(string str)
{
	StrHelper strHelper;
	str = strHelper.Remove(str, '{');
	str = strHelper.Remove(str, '}');
	vector<string>values = strHelper.Split(str, ';');
	if (values.size() > 1) {
		row = -1;
		column = -1;
		type = (CellTypes)atoi(values[0].c_str());
		value = atoi(values[1].c_str());
	}
	else {
		row = -1;
		column = -1;
		//type = -1;
		//value = -1;
	}
}

Cell::Cell(int _row, int _col)
{
	row = _row;
	column = _col;
	type = CellTypes::empty;
	value = 0;
}

Cell::Cell(int _row, int _col, CellTypes _type)
{
	row = _row;
	column = _col;
	type = _type;
	value = 0;
}

Cell::Cell(int _row, int _col, CellTypes _type, int _value)
{
	row = _row;
	column = _col;
	type = _type;
	value = _value;
}

Cell::~Cell()
{
}

void Cell::Print()
{
	cout << (int)type;
}

string Cell::GetStr()
{
	return "{" + to_string(type) + ";" + to_string(value) + "}";
}

bool Cell::SameCoods(Cell cell)
{
	if (row == cell.row && column == cell.column)
		return true;
	return false;
}

void Cell::Add(int _row, int _col)
{
	row += _row;
	column += _col;
}

bool Cell::Check(int row, int column, int size)
{
	if (row > -1 && row < size && column > -1 && column < size)
		return true;
	return false;
}

bool Cell::Check(int size)
{
	return Check(row, column, size);
}
