#include "Field.h"
#include "Enums.h"
#pragma once
/// <summary>
/// корабль на поле
/// </summary>
class BShip
{
private:
	/// <summary>
	/// размер корабля
	/// </summary>
	int size;
	/// <summary>
	/// указатель на гровое поле
	/// </summary>
	Field *field;
	/// <summary>
	/// проверяет окрестности клетки:
	/// 1.вокруг клетки не должно быть 
	/// других клеток, кроме пустых
	/// </summary>
	/// <param name="cell">клетка для проврки</param>
	bool Check(Cell cell);
public:
	/// <summary>
	/// создает корабль
	/// </summary>
	BShip();
	/// <summary>
	/// создает корабль с указанными параметрами
	/// </summary>
	/// <param name="_size">размер корабля</param>
	/// <param name="_field">указатель на поле</param>
	BShip(int _size, Field *_field);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="cell"></param>
	/// <returns></returns>
	bool SetShip(Cell cell);
	/// <summary>
	/// ставит каробль на первую подходящую клетку
	/// </summary>
	bool SetFirstEmpty();
	~BShip();
};

