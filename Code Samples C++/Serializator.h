#include "FileIO.h"
#include "Pair.h"
#include "StrHelper.h"
#pragma once
class Serializator
{
private:
#pragma region Поля
	/// <summary>
	/// разделитель
	/// </summary>
	string delimiter = ":";
	/// <summary>
	/// для работы с файлами
	/// </summary>
	FileIO fileIO = FileIO();
	/// <summary>
	/// для работы со строками
	/// </summary>
	StrHelper strHelper = StrHelper();
#pragma endregion

public:
#pragma region Методы
	/// <summary>
	/// сериализует поля объекта
	/// </summary>
	/// <param name="fileName">файл для сохранения</param>
	/// <param name="fieldsValues">поля и значения</param>
	void Serialize(string fileName, vector<Pair> fieldsValues);
	/// <summary>
	/// десериализует поля объекта
	/// </summary>
	/// <param name="fileName">файл для загрузки</param>
	/// <returns></returns>
	vector<Pair>Deserialize(string fileName);
#pragma endregion

#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// конструктор
	/// </summary>
	Serializator();
	/// <summary>
	/// деструктор
	/// </summary>
	~Serializator();
#pragma endregion
};

