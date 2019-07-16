#include "stdafx.h"
#include "BSGame.h"

#pragma region Списки
/// <summary>
/// типы клеток по которым можно стрелять
/// </summary>
vector<CellTypes> success = { CellTypes::empty,CellTypes::ship };
/// <summary>
/// типы клеток, по которым уже нельзя вытсрелить
/// </summary>
vector<CellTypes> fail = { CellTypes::miss,CellTypes::hit };
#pragma endregion

#pragma region Конструкторы

BSGame::BSGame()
{
	Init(defaultShips, defaultSize);
}

BSGame::BSGame(int _size)
{
	Init(defaultShips, _size);
}

BSGame::BSGame(int _ships, int _size)
{
	if (_ships <= 0)
		_ships = 10;
	Init(_ships % sizes.size(), _size);
}

BSGame::~BSGame()
{

}
#pragma endregion

#pragma region Методы
void BSGame::Start() {
	Init(size);
	gameStarted = true;
}

void BSGame::Start(bool _debugMode) {
	debugMode = _debugMode;
	Start();
}

void BSGame::Finish() {
	gameStarted = false;
}

void BSGame::Init(int _size) {
	startShips = 0;
	for (int i = 0; i < sizes.size(); i++)
		startShips += sizes[i];
	player = Players::first;
	gameStarted = true;
	size = _size;
	fields.clear();
	players.clear();
	//добавляет двух игроков
	for (int i = 0; i < 2; i++) {
		Field *field = new  Field(size);
		fields.push_back(*field);
		Player *player = new Player(startShips, field);
		players.push_back(*player);
		SetShips(i);
	}
	//Для теста
	//EnableBot(Players::first);
	//TODO: добавить в ноастройки
	EnableBot(Players::second);
	colorsMap =
	{
		{CellTypes::empty,ConsoleColor::Blue},
		{CellTypes::hit,ConsoleColor::Green},
		{CellTypes::miss,ConsoleColor::Red},
		{CellTypes::ship,ConsoleColor::LightGray },
		{CellTypes::default,ConsoleColor::Black }
	};
	colorMapHidden =
	{
		{ CellTypes::empty,ConsoleColor::Blue },
		{ CellTypes::hit,ConsoleColor::Green },
		{ CellTypes::miss,ConsoleColor::Red },
		{ CellTypes::ship,ConsoleColor::Blue },
		{ CellTypes::default,ConsoleColor::Black }
	};
}

void BSGame::Init(int _ships, int _size)
{
	for (int i = 0; i < sizes.size() - _ships; i++)
		sizes.erase(sizes.begin());
	Init(_size);
}

bool BSGame::IsStarted() {
	return gameStarted;
}

int BSGame::GetPlayer() {
	return player;
}

int BSGame::GetNextPLayer() {
	return (player + 1) % 2;
}

Player* BSGame::GetPlayer(int i)
{
	if (i > -1 && i < players.size())
		return &players[i];
	return NULL;
}

bool BSGame::isInDebugMode()
{
	return debugMode;
}

Field BSGame::GetField(int player)
{
	if (player > -1 && player < fields.size())
		return fields[player];
	else
		return Field();
}

int GetRadInt(int start, int end) {
	if (end != 0)
		return (rand() % end + start) % end;
	else
		return -1;
}

void BSGame::SetShips(int player) {
	vector<int> _sizes = sizes;
	while (_sizes.size() > 0) {
		BShip ship = BShip(_sizes[0], &fields[player]);
		int x = rand() % size;
		int	y = rand() % size;
		if (ship.SetShip(Cell(x, y)) || ship.SetFirstEmpty()) {
			_sizes.erase(_sizes.begin());
		}
	}
}

void BSGame::SetDebugMode(bool value)
{
	debugMode = value;
}

bool BSGame::CheckCoord(int value) {
	return value > -1 && value < size;
}

bool BSGame::Check(Cell cell) {
	bool inSuccess = false;
	for (int i = 0; i < success.size(); i++)
		if (fields[GetNextPLayer()].GetItem(cell.row, cell.column).type == success[i]) {
			inSuccess = true;
			break;
		}
	return CheckCoord(cell.row) && CheckCoord(cell.column) && inSuccess;
}

bool BSGame::InRange(vector<CellTypes>types, CellTypes type) {
	return find(types.begin(), types.end(), type) != types.end();
}

bool BSGame::Shoot(Cell cell) {
	if (Check(cell))
	{
		CellTypes curCellValue = (CellTypes)fields[GetNextPLayer()].GetItem(cell).type;
		if (InRange(success, curCellValue))
		{
			if (curCellValue == CellTypes::ship) {
				fields[GetNextPLayer()].SetItem(cell, CellTypes::hit, CellTypes::hit);
				players[GetNextPLayer()].ships--;

			}
			else
			{
				fields[GetNextPLayer()].SetItem(cell, CellTypes::miss, CellTypes::miss);
				player = GetNextPLayer();
			}
			return true;
		}
		else
			return false;
	}
	return false;
}

bool BSGame::CheckWin()
{
	return GetWinner() != -1;
}

int BSGame::GetWinner()
{
	bool zeroShips = false;
	int index = 0;
	for (int i = 0; i < players.size(); i++) {
		if (players[i].ships == 0)
			zeroShips = true;
		if (players[index].ships > players[i].ships)
			index == i;
	}
	if (zeroShips)
		return index;
	return -1;

}

void BSGame::Save() {
	Serializator s;
	vector<Pair> values;
	values.push_back(Pair(fieldNames[0], to_string(size)));
	values.push_back(Pair(fieldNames[1], to_string(player)));
	if (players.size() > 0)
	{
		values.push_back(Pair(fieldNames[2] + '0', to_string(players[0].ships)));
		values.push_back(Pair(fieldNames[2] + '1', to_string(players[1].ships)));
	}
	values.push_back(Pair(fieldNames[4], to_string(gameStarted)));
	values.push_back(Pair(fieldNames[5], to_string(debugMode)));
	values.push_back(Pair(fieldNames[6], to_string(maxShips)));
	values.push_back(Pair(fieldNames[3] + '0', fields[0].GetStr()));
	values.push_back(Pair(fieldNames[3] + '1', fields[1].GetStr()));
	s.Serialize(savegameFile, values);
}

void BSGame::Load() {
	Serializator s;

	vector<Pair> values = s.Deserialize(savegameFile);
	for (int i = 0; i < values.size(); i++) {
		if (values[i].key == fieldNames[0])
			size = atoi(values[i].value.c_str());
		if (values[i].key == fieldNames[1])
			player = atoi(values[i].value.c_str());
		if (values[i].key == fieldNames[2] + '0')
			players[0].ships = atoi(values[i].value.c_str());
		if (values[i].key == fieldNames[2] + '1')
			players[1].ships = atoi(values[i].value.c_str());
		if (values[i].key == fieldNames[4])
			gameStarted = atoi(values[i].value.c_str());
		if (values[i].key == fieldNames[5])
			debugMode = atoi(values[i].value.c_str());
		if (values[i].key == fieldNames[6])
			startShips = atoi(values[i].value.c_str());
		if (values[i].key == fieldNames[3] + '0')
			fields[0] = Field(values[i].value);
		if (values[i].key == fieldNames[3] + '1')
			fields[1] = Field(values[i].value);
	}
}

void BSGame::EnableBot(int _player)
{
	if (players.size() > _player)
		players[_player].EnableAI();
}

void BSGame::DisableBot(int _player)
{
	if (players.size() > _player)
		players[_player].DisableAI();
}

bool BSGame::IsBotEnabled(int _player)
{
	if (players.size() > _player)
		return players[_player].GetIsAI();
}

void BSGame::SetDebugMode()
{
	EnableBot(Players::first);
	EnableBot(Players::second);
}
#pragma endregion