#include "Menu.h"
#pragma once
class BSInGameMenu : public Menu
{
private:
	/// <summary>
	/// корректный высстрел или нет
	/// </summary>
	bool correctShoot;
	/// <summary>
	/// завершать игру или нет
	/// true - да
	/// false - нет
	/// </summary>
	bool close;
public:
	BSInGameMenu(BSGame *_game);
	BSInGameMenu();
	~BSInGameMenu();
#pragma region Методы
	virtual bool Action(int action);
	/// <summary>
	/// получить координату у пользователя
	/// </summary>
	/// <returns></returns>
	Cell GetCoords();
#pragma endregion
};

