#include "Menu.h"
#pragma once
class BSSettingMenu :public Menu
{
public:
	BSSettingMenu(BSGame *_game);
	BSSettingMenu();
	~BSSettingMenu();
#pragma region Ìועמהû
	virtual bool Action(int action);
#pragma endregion
};

