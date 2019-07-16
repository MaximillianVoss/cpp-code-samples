#include "Menu.h"
#include "BSInGameMenu.h"
#include "BSSettingMenu.h"
#pragma once
/// <summary>
/// меню игры
/// </summary>
class BSMainMenu : public Menu
{
public:

#pragma region Конструкторы
	BSMainMenu(BSGame *_game);
	BSMainMenu();
	~BSMainMenu();
#pragma endregion

#pragma region Методы

#pragma endregion
private:
#pragma region Поля

#pragma endregion

#pragma region Методы
	virtual bool Action(int action);

	void Init();
#pragma endregion
};