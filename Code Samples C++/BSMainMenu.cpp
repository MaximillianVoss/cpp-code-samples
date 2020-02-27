#include "stdafx.h"
#include "BSMainMenu.h"

#pragma region Конструкторы
BSMainMenu::BSMainMenu(BSGame *_game)
{
	game = _game;
	Init();
}

BSMainMenu::BSMainMenu()
{
	game = NULL;
	Init();
}

BSMainMenu::~BSMainMenu()
{

}
#pragma endregion

#pragma region Методы

bool  BSMainMenu::Action(int action) {
	BSInGameMenu inMenu = BSInGameMenu(game);
	BSSettingMenu settingsMenu = BSSettingMenu(game);
	closeGame = false;
	bool closeSettings = false;
	switch (action)
	{
		return game->IsStarted();
	case ActionsMain::newgame:
		if (!game)
			game = new BSGame();
		game->Start();
		while (!closeGame) {
			if (!game->IsStarted())
				ShowMenu(menuItems, true);
			else
				closeGame = inMenu.Start(true);
		}
		return true;
	case ActionsMain::load:
		game->Load();
		closeGame = inMenu.Start(true);
		return true;
	case ActionsMain::settings:
		settingsMenu.Start();
		game = settingsMenu.game;
		return true;
	case ActionsMain::close:
		io.Print("До свидания!");
		return false;
	default:
		io.Print("Некорректный пукт меню!");
		return true;
	}
}

void BSMainMenu::Init()
{
	menuItems =
	{
	{ ActionsMain::newgame,"Новая игра" },
	{ ActionsMain::load,"Загрузить игру" },
	{ ActionsMain::settings,"Настройки" },
	{ ActionsMain::close,"Выход" }
	};
}

#pragma endregion