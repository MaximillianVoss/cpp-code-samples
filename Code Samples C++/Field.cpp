#include "stdafx.h"
#include "Field.h"

bool Field::Check(int coord)
{
	return coord > -1 && coord < size;
}

bool Field::Check(Cell cell)
{
	return Check(cell.column) && Check(cell.row);
}

Field::Field(Field *field) {
	a = field->a;
	size = field->size;
}

Field::Field()
{
}

Field::Field(vector<vector<Cell>> _a)
{
	a = _a;
}

Field::Field(vector<vector<int>> _a)
{
	size = _a.size();
	a.resize(size);
	for (int i = 0; i < size; i++) {
		a[i].resize(size);
		for (int j = 0; j < size; j++)
			a[i][j] = Cell(i, j, CellTypes::empty, _a[i][j]);
	}
}

Field::Field(size_t _size)
{
	size = _size;
	a.resize(size);
	for (int i = 0; i < size; i++) {
		a[i].resize(size);
		for (int j = 0; j < size; j++)
			a[i][j] = Cell(i, j);
	}
}

Field::Field(string str)
{
	StrHelper strHelper;
	vector<string>lines = strHelper.Split(str, string("| \n"), string(""));
	size = lines.size();
	for (int i = 0; i < lines.size(); i++)
	{
		vector<string>cellsStr = strHelper.Split(lines[i], ",", "");
		vector<Cell> row;
		for (int j = 0; j < cellsStr.size(); j++)
			row.push_back(Cell(cellsStr[j]));
		a.push_back(row);
	}
}

Field::~Field()
{
}

Cell Field::GetItem(size_t row, size_t column) {
	if (Check(row) && Check(column))
		return a[row][column];
	else
		return Cell(-1, -1, CellTypes::notFound);
}

bool Field::SetItem(Cell cell, int value)
{
	return SetItem(cell.row, cell.column, value);
}

bool Field::SetItem(Cell cell, CellTypes type, int value)
{
	return SetItem(cell.row, cell.column, type, value);
}

bool Field::SetItem(size_t row, size_t column, int value) {
	bool success = Check(row) && Check(column);
	if (success)
		a[row][column].value = value;
	return success;
}

bool Field::SetItem(size_t row, size_t column, CellTypes type, int value) {
	bool success = Check(row) && Check(column);
	if (success) {
		a[row][column].type = type;
		a[row][column].value = value;
	}
	return success;
}

Cell Field::GetItem(Cell cell)
{
	return GetItem(cell.row, cell.column);
}

Field Field::operator+(Field & b)
{
	for (int i = 0; i < min(size, b.size); i++) {
		for (int j = 0; j < min(size, b.size); j++)
			if (a[i][j].value == 0 && b.a[i][j].value != 0)
				a[i][j] = b.a[i][j];
	}
	this->a = a;
	return *this;
}

string Field::GetStr() {
	string str = "";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			if (j != size - 1)
				str += a[i][j].GetStr() + ',';
			else
				str += a[i][j].GetStr();
		str += "| \n";
	}
	return str;
}

Field Field::Shift(Directions direction)
{
	switch (direction) {
	case Directions::up:
		for (int i = 0; i < a.size() - 1; i++)
			a[i] = a[i + 1];
		//fill(a[a.size() - 1].begin(), a[a.size() - 1].end(), Cell(-1, -1, CellTypes::empty, 0));
		break;
	case Directions::down:
		for (int i = a.size() - 1; i > 0; i--)
			a[i] = a[i - 1];
		//fill(a[0].begin(), a[0].end(), Cell(-1, -1, CellTypes::empty, 0));
		break;
	case Directions::left:
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - 1; j++)
				a[i][j] = a[i][j + 1];
			a[i][size - 1].value = 0;
		}
		break;
	case Directions::right:
		for (int i = 0; i < size; i++) {
			for (int j = size - 1; j > 0; j--)
				a[i][j] = a[i][j - 1];
			a[i][0].value = 0;
		}
		break;
	}
	return Field(a);
}
