/// <summary>
/// любой заголовок с нужным CellTypes
/// </summary>
#include "Enums.h"
#include "StrHelper.h"
#pragma once
class Cell
{
private:
public:
#pragma region Поля
	/// <summary>
	/// строка
	/// </summary>
	int row;
	/// <summary>
	/// столбец
	/// </summary>
	int column;
	/// <summary>
	/// тип
	/// </summary>
	CellTypes type;
	/// <summary>
	/// значение в клетке
	/// </summary>
	int value;
#pragma endregion
#pragma region Конструкторы/Деструкторы
	Cell();
	/// <summary>
	/// создает клетку из строки вида { тип ; значение }
	/// </summary>
	/// <param name="str">строка</param>
	Cell(string str);
	Cell(int _row, int _col);
	Cell(int _row, int _col, CellTypes _type);
	Cell(int _row, int _col, CellTypes _type, int _value);
	~Cell();
#pragma endregion
#pragma region Методы
	/// <summary>
	/// выводит клетку в консоль
	/// </summary>
	void Print();
	/// <summary>
	/// Преобразует в строку: { тип ; значение }
	/// </summary>
	string GetStr();
	/// <summary>
	/// проверка совпадают 
	/// у клеток координаты
	/// </summary>
	/// <param name="cell">клетка для проверки</param>
	/// <returns></returns>
	bool SameCoods(Cell cell);
	/// <summary>
	/// добавляет координаты
	/// к текущим
	/// </summary>
	/// <param name="_row"></param>
	/// <param name="_col"></param>
	void Add(int _row, int _col);
	/// <summary>
	/// возвращает число от 0 до 63
	/// в зависимости от своей позиции
	/// </summary>
	/// <returns></returns>
	int GetNum() {
		return row * 8 + column;
	}
	/// <summary>
	/// проверяет координаты 
	/// клетки на корректность
	/// </summary>
	/// <param name="row">строка</param>
	/// <param name="column">столбец</param>
	/// <param name="size">размер поля</param>
	/// <returns></returns>
	bool Check(int row, int column, int size);
	/// <summary>
	/// проверяет координаты 
	/// клетки на корректность
	/// </summary>
	/// <param name="size">размер поля</param>
	/// <returns>true если координаты клетки в пределах поля</returns>
	bool Check(int size);
#pragma endregion
};

