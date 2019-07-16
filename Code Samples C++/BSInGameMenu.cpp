#include "stdafx.h"
#include "BSInGameMenu.h"


BSInGameMenu::BSInGameMenu(BSGame * _game)
{
	game = _game;
	menuItems =
	{
		{ ActionsInGame::shoot,"Выстрелить" },
		{ ActionsInGame::save,"Сохранить" },
		{ ActionsInGame::goBack,"Назад" }
	};
}

BSInGameMenu::BSInGameMenu()
{

}

BSInGameMenu::~BSInGameMenu()
{
}

bool BSInGameMenu::Action(int action)
{
	bool ans = false;
	switch (action)
	{
	case ActionsInGame::save:
		game->Save();
		return game->IsStarted();
	case ActionsInGame::shoot:
		game->Shoot(game->GetPlayer(game->GetPlayer())->GetCoords());
		if (game->CheckWin()) {
			game->Finish();
			cout << "Победил игрок:" << game->GetWinner() + 1 << endl;
			system("pause");
		}
		return game->IsStarted();
	case ActionsInGame::goBack:
		io.Print("Вы точно хотите выйти?");
		io.Get(&ans);
		if (ans) {
			game->Finish();
			return false;
		}
		else
			return true;
	default:
		return true;
	}
}

Cell  BSInGameMenu::GetCoords() {

	int row = -1, col = -1;
	io.Get(row, "Введите строку:");
	io.Get(col, "Введите столбец:");
	return Cell(row - 1, col - 1);
}
