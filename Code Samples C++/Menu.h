#include "stdafx.h"
#include "InfoIO.h"
#include "FileIO.h"
#include "BSGame.h"
#include "Enums.h"
#include "MenuItem.h"
#include "Cell.h"
#pragma once
/// <summary>
/// Базоввый класс меню
/// </summary>
class Menu
{
private:
public:
	/// <summary>
	/// закрывать данное меню или нет
	/// </summary>
	bool closeMenu;
	/// <summary>
	/// завершать игру или нет
	/// true - да
	/// false - нет
	/// </summary>
	bool closeGame;
	/// <summary>
	/// ядро игры
	/// </summary>
	BSGame *game;
	/// <summary>
	/// пункты меню
	/// </summary>
	vector<MenuItem> menuItems;
	/// <summary>
	/// ввод вывод
	/// </summary>
	IO io = IO();
	/// <summary>
	/// файловый ввод вывод
	/// </summary>
	FileIO fileIO = FileIO();
	/// <summary>
	/// показывает меню
	/// </summary>
	/// <param name="items">элементы меню</param>
	/// <param name="clear">true-очистить экран</param>
	void ShowMenu(vector<MenuItem> items, bool clear);
	/// <summary>
	/// показывает меню не очищая экран
	/// </summary>
	/// <param name="items"></param>
	void ShowMenu(vector<MenuItem> items);
	/// <summary>
	/// запускает меню
	/// </summary>
	bool Start();
	/// <summary>
	/// запускает меню
	/// </summary>
	/// <param name="showField">показывать ли игровые поля</param>
	/// <returns></returns>
	bool Start(bool showField);
	/// <summary>
	/// задает действия для каждого пункта меню
	/// </summary>
	/// <param name="action">код действия</param>
	/// <returns></returns>
	virtual bool Action(int action);
	/// <summary>
	/// получает номер пункта меню от пользователя
	/// </summary>
	/// <returns>true - надо закрывать меню</returns>
	bool GetAction();
	/// <summary>
	/// 
	/// </summary>
	Menu();
	/// <summary>
	/// создает меню/подменю игры
	/// </summary>
	/// <param name="game">ссылка на игру</param>
	Menu(BSGame *_game);
	/// <summary>
	/// деструктор
	/// </summary>
	~Menu();
	/// <summary>
	/// печатает поле
	/// </summary>
	/// <param name="player">номер игрока</param>
	/// <param name="colorsMap">цветовая схема</param>
	void PrintField(int player, map<CellTypes, ConsoleColor> colorsMap);
	/// <summary>
	/// печатает поле
	/// </summary>
	/// <param name="player">номер игрока</param>
	void PrintField(int player);
	/// <summary>
	/// выводит на экран номер текущего игрока
	/// </summary>
	/// <param name="player">номер</param>
	void PrintPlayer(int player);
};

