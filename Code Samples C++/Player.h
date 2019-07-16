#include "stdafx.h"
#include "Field.h"
#include "InfoIO.h"
#pragma once
/// <summary>
/// игрок
/// </summary>
class Player
{
protected:
	/// <summary>
	/// поле противника
	/// </summary>
	Field * field;
	/// <summary>
	/// для ввода/вывода информации
	/// </summary>
	IO io = IO();
	/// <summary>
	/// является ли ИИ:
	/// true - если да
	/// </summary>
	bool isAI;
public:
	/// <summary>
	/// число оставшихся кораблей
	/// </summary>
	int ships;
	/// <summary>
	/// конструктор по умолчанию
	/// </summary>
	Player();
	/// <summary>
	/// создает игрока с парметрами
	/// </summary>
	/// <param name="_ships">начальное число кораблей</param>
	/// <param name="_field">поле противника</param>
	Player(int _ships, Field * _field);
	/// <summary>
	/// деструктор
	/// </summary>
	~Player();
	/// <summary>
	///  получает клетку с координатами для стрельбы
	/// </summary>
	Cell GetCoords();
	/// <summary>
	/// возвращает значение isAI
	/// </summary>
	/// <returns>true - если ИИ</returns>
	bool GetIsAI();
	/// <summary>
	/// отдает угрока под управление ИИ
	/// </summary>
	void EnableAI();
	/// <summary>
	/// возвращает игрока под управление человека
	/// </summary>
	void DisableAI();
};

