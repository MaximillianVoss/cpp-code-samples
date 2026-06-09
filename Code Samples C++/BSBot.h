#include "Player.h"
#pragma once
/// <summary>
/// бот морского боя
/// </summary>
class BSBot : public Player
{
private:
public:
	/// <summary>
	/// 
	/// </summary>
	BSBot();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="_field"></param>
	BSBot(GameField * _field);
	/// <summary>
	/// Создает бота с указанными параметрами
	/// </summary>
	/// <param name="_startShips">начальное число кораблей</param>
	/// <param name="_field">ссылка поле</param>
	BSBot(int _ships, GameField * _field);
	/// <summary>
	///  получает клетку с координатами для стрельбы
	/// </summary>
	Cell BSBot::GetCoords();
	/// <summary>
	/// 
	/// </summary>
	~BSBot();
};