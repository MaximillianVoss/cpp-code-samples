#include "stdafx.h"
#include "Menu.h"

void Menu::ShowMenu(vector<MenuItem> items, bool clear)
{
	if (clear)
		io.Clear();
	for (MenuItem item : items) {
		cout << item.action << '.' << item.title << endl;
	}
}

void Menu::ShowMenu(vector<MenuItem> items)
{
	ShowMenu(items, false);
}

bool Menu::Start()
{
	io.Clear();
	ShowMenu(menuItems);
	if (GetAction())
		Start();
	return true;
}

bool Menu::Start(bool showField)
{
	io.Clear();
	if (showField) {
		PrintField(game->GetPlayer(), game->colorsMap);
		PrintField(game->GetNextPLayer());
		PrintPlayer(game->GetPlayer());
	}
	ShowMenu(menuItems);
	if (GetAction())
		return Start(true);
	return true;
}

bool Menu::Action(int action)
{
	return false;
}

bool Menu::GetAction()
{
	int action = -1;
	if (game->GetPlayer(game->GetPlayer())->GetIsAI())
		action = ActionsInGame::shoot;
	else
		io.Get(action, "Выберите действие");
	return Action(action);
}

Menu::Menu()
{
}

Menu::Menu(BSGame * _game)
{
	game = _game;
}

Menu::~Menu()
{
}

void Menu::PrintField(int player, map<CellTypes, ConsoleColor> colorsMap)
{
	io.Print("Поле игрока " + to_string(player + 1));
	io.Print(game->GetField(player), colorsMap);
}

void Menu::PrintField(int player)
{
	io.Print("Поле игрока " + to_string(player + 1));
	if (game->isInDebugMode())
		io.Print(game->GetField(player), game->colorsMap);
	else
		io.Print(game->GetField(player), game->colorMapHidden);
}

void Menu::PrintPlayer(int player)
{
	io.PrintSeparator(22);
	io.Print("Ход игрока: " + to_string(game->GetPlayer() + 1));
	io.PrintSeparator(22);
}
