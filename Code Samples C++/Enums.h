#pragma once
#pragma region Перечисления
#pragma region Menu
/// <summary>
/// действия в главном меню
/// </summary>
enum ActionsMain {
	/// <summary>
	/// новая игра
	/// </summary>
	newgame = 1,
	/// <summary>
	/// загрузить
	/// </summary>
	load,
	/// <summary>
	/// насройки
	/// </summary>
	settings,
	/// <summary>
	/// закрытие меню
	/// </summary>
	close
};
/// <summary>
/// действия в игровом меню
/// </summary>
enum ActionsInGame {
	/// <summary>
	/// выстрелить
	/// </summary>
	shoot = 1,
	/// <summary>
	/// сохранить игру
	/// </summary>
	save,
	/// <summary>
	/// назад
	/// </summary>
	goBack
};
/// <summary>
/// действия в меню настроек
/// </summary>
enum ActionsSettings {
	/// <summary>
	/// отлкадка(настройки)
	/// </summary>
	debug = 1,
	/// <summary>
	/// размер поля(настройки)
	/// </summary>
	fieldSize,
	setAI,
	goBackToMain
};
/// <summary>
/// 
/// </summary>
enum ActionsCommon {
	/// <summary>
	/// назад
	/// </summary>
	back
};
#pragma endregion

#pragma region Other
/// <summary>
/// типы клеток
/// </summary>
enum CellTypes {
	empty,
	hit,
	miss,
	ship,
	default,
	notFound
};
/// <summary>
/// типы кораблей
/// </summary>
enum ShipTypes {

};
/// <summary>
/// счет игроков
/// </summary>
enum Players {
	first,
	second
};
/// <summary>
/// Цвета в консоли
/// </summary>
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
/// <summary>
/// список полей игры Морской бой
/// </summary>
enum FieldsBS {
	/// <summary>
	/// размер поля
	/// </summary>
	size,
	/// <summary>
	/// игрок который ходит
	/// </summary>
	player,
	shipsRemain,
	fields,
	gameStarted,
	debugMode,
	maxShips
};
#pragma endregion
#pragma endregion