#include "pch.h"
#include "GameField.h"

bool GameField::Check(int coord)
{
	return coord > -1 && coord < size;
}

bool GameField::Check(Cell cell)
{
	return Check(cell.column) && Check(cell.row);
}

GameField::GameField(GameField *field) {
	a = field->a;
	size = field->size;
}

GameField::GameField()
{
}

GameField::GameField(vector<vector<Cell>> _a)
{
	a = _a;
}

GameField::GameField(vector<vector<int>> _a)
{
	size = _a.size();
	a.resize(size);
	for (int i = 0; i < size; i++) {
		a[i].resize(size);
		for (int j = 0; j < size; j++)
			a[i][j] = Cell(i, j, CellTypes::empty, _a[i][j]);
	}
}

GameField::GameField(size_t _size)
{
	size = _size;
	a.resize(size);
	for (int i = 0; i < size; i++) {
		a[i].resize(size);
		for (int j = 0; j < size; j++)
			a[i][j] = Cell(i, j);
	}
}

GameField::GameField(string str)
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

GameField::~GameField()
{
}

Cell GameField::GetItem(size_t row, size_t column) {
	if (Check(row) && Check(column))
		return a[row][column];
	else
		return Cell(-1, -1, CellTypes::notFound);
}

bool GameField::SetItem(Cell cell, int value)
{
	return SetItem(cell.row, cell.column, value);
}

bool GameField::SetItem(Cell cell, CellTypes type, int value)
{
	return SetItem(cell.row, cell.column, type, value);
}

bool GameField::SetItem(size_t row, size_t column, int value) {
	bool success = Check(row) && Check(column);
	if (success)
		a[row][column].value = value;
	return success;
}

bool GameField::SetItem(size_t row, size_t column, CellTypes type, int value) {
	bool success = Check(row) && Check(column);
	if (success) {
		a[row][column].type = type;
		a[row][column].value = value;
	}
	return success;
}

Cell GameField::GetItem(Cell cell)
{
	return GetItem(cell.row, cell.column);
}

GameField GameField::operator+(GameField & b)
{
	for (int i = 0; i < min(size, b.size); i++) {
		for (int j = 0; j < min(size, b.size); j++)
			if (a[i][j].value == 0 && b.a[i][j].value != 0)
				a[i][j] = b.a[i][j];
	}
	this->a = a;
	return *this;
}

string GameField::GetStr() {
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

GameField GameField::Shift(Directions direction)
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
	return GameField(a);
}
