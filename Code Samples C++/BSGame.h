#include "stdafx.h"
#include "BShip.h"
#include "Field.h"
#include "Enums.h"
#include "Pair.h"
#include "Serializator.h"
#include "Player.h"
#include  "ArrayHelper.h"
#pragma once
/// <summary>
/// ядро игры
/// </summary>
class BSGame {
public:
#pragma region Поля
	/// <summary>
	/// карта соответствия цветов типу клеток
	/// корабли подсвечены
	/// </summary>
	map<CellTypes, ConsoleColor> colorsMap;
	/// <summary>
	/// карта соответствия цветов типу клеток
	/// корабли скрыты
	/// </summary>
	map<CellTypes, ConsoleColor>colorMapHidden;
#pragma endregion

#pragma region Конструкторы
	/// <summary>
		/// 
		/// </summary>
	BSGame();
	/// <summary>
	/// создает игру с параметрами
	/// </summary>
	/// <param name="_size">размер полей</param>
	BSGame(int _size);
	/// <summary>
	/// создает игру с параметрами
	/// </summary>
	/// <param name="_ships">начальное число кораблей</param>
	/// <param name="_size">размер полей</param>
	BSGame(int _ships, int _size);
	/// <summary>
	/// деструктор
	/// </summary>
	~BSGame();
#pragma endregion 

#pragma region Методы

#pragma region Start
	/// <summary>
	/// 
	/// </summary>
	void Start();
	/// <summary>
	///  Запускает игру
	/// </summary>
	/// <param name="_debugMode">режим отладки, true - включить</param>
	void Start(bool _debugMode);
	/// <summary>
	/// 
	/// </summary>
	void Finish();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool IsStarted();
#pragma endregion

#pragma region Players
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int GetPlayer();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int GetNextPLayer();
	/// <summary>
	/// Получет игрока по индексу
	/// </summary>
	/// <param name="i">номер игрока</param>
	/// <returns></returns>
	Player* GetPlayer(int i);
#pragma endregion

#pragma region Gameplay
	/// <summary>
	/// 
	/// </summary>
	/// <param name="player"></param>
	/// <returns></returns>
	Field GetField(int player);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="player"></param>
	void SetShips(int player);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="cell"></param>
	/// <returns></returns>
	bool Shoot(Cell cell);
	/// <summary>
	/// проверяет условие победы
	/// </summary>
	/// <returns></returns>
	bool CheckWin();
	/// <summary>
	/// находит победителя
	/// </summary>
	/// <returns></returns>
	int GetWinner();
#pragma endregion

#pragma region Save/Load
	/// <summary>
	/// сохранияет иргу
	/// </summary>
	void Save();
	/// <summary>
	/// загружает игру
	/// </summary>
	void Load();
#pragma endregion

#pragma region Settings
	/// <summary>
	/// возвращает состояние режима отладки
	/// </summary>
	/// <returns>true - если в режиме отладки</returns>
	bool isInDebugMode();
	/// <summary>
	/// установить режим отладки
	/// </summary>
	/// <param name="value">true- режим отладки,false - без отладки</param>
	void SetDebugMode(bool value);
	/// <summary>
	/// включает бота в игру
	/// игра становится PvAI
	/// </summary>
	/// <param name="_player">номер игрока</param>
	void EnableBot(int _player);
	/// <summary>
	/// удаляет бота из игры
	/// игра становится PvP
	/// </summary>
	/// <param name="_player">номер игрока</param>
	void DisableBot(int _player);
	/// <summary>
	/// показывает включен бот или нет
	/// </summary>
	/// <param name="_player">номер игрока</param>
	bool IsBotEnabled(int _player);
	/// <summary>
	/// устанавливает режим отладки
	/// </summary>
	void SetDebugMode();
#pragma endregion

#pragma endregion

private:
#pragma region Поля
	/// <summary>
	/// количество кораблей по умолчанию
	/// посчитывается именно чило 
	/// клеток занимается кораблями
	/// </summary>
	int defaultShips = 10;
	/// <summary>
	/// размер поля по умолчанию
	/// </summary>
	int defaultSize = 10;
	/// <summary>
	/// размер полей игроков
	/// </summary>
	int size;
	/// <summary>
	/// указывает на номер 
	/// активного игрока в данный момент:
	/// 0 - первый
	/// 1- второй 
	/// и т.д.
	/// </summary>
	int player;
	/// <summary>
	/// игроки
	/// </summary>
	vector<Player> players;
	/// <summary>
	/// 
	/// </summary>
	vector<Field> fields;
	/// <summary>
	/// true -если игра началась
	/// </summary>
	bool gameStarted;
	/// <summary>
	/// режим отладки 
	/// в нем показываются корабли противника
	/// </summary>
	bool debugMode;
	/// <summary>
	/// начальное число кораблей
	/// </summary>
	int startShips;
	/// <summary>
	/// содержит имена основных полей
	/// </summary>
	vector<string> fieldNames = {
		"size",
		"player",
		"shipsRemain",
		"fields",
		"gameStarted",
		"debugMode",
		"startShips"
	};
	/// <summary>
	/// размеры кораблей
	/// </summary>
	vector<int>sizes = { 4,3,3,2,2,2,1,1,1,1 };
	/// <summary>
	/// имя сохранения
	/// </summary>
	string savegameFile = "savegame.txt";
#pragma endregion

#pragma region Методы
	/// <summary>
	/// Инициализирует игру
	/// </summary>
	/// <param name="size">размер полей</param>
	void Init(int _size);
	/// <summary>
	/// Инициализирует игру
	/// </summary>
	/// <param name="_ships">начальное число кораблей</param>
	/// <param name="_size">размер полей</param>
	void Init(int _ships, int _size);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	bool CheckCoord(int value);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="cell"></param>
	/// <returns></returns>
	bool Check(Cell cell);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="types"></param>
	/// <param name="type"></param>
	/// <returns></returns>
	bool InRange(vector<CellTypes> types, CellTypes type);
#pragma endregion

};