#pragma once
#include "pch.h"
#include "DataPack.h"
template<typename T>
///<summary>
/// Строит график по точкам
///</summary>
class Plotter
{
private:

#pragma region Поля
	/// <summary>
	/// Префикс для вызова компилятора питона
	/// </summary>
	string prefixPython = "python";
	/// <summary>
	/// Путь до файла python, который построит графики
	/// </summary>
	string pathToPyton = "C:\\Users\\Александр\\PycharmProjects\\GraphicsPlotter\\main.py";
#pragma endregion

#pragma region Методы

#pragma endregion

public:

#pragma region Поля
	/// <summary>
	/// имя
	/// </summary>
	string title;
	/// <summary>
	/// данные
	/// </summary>
	vector<DataPack<T>>data;
#pragma endregion

#pragma region Методы
	string ToString() {
		stringstream ss;
		ss << this->title << endl;
		for (DataPack<T> pack : this->data)
			ss << pack.ToString();
		return ss.str();
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы

#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion
	/// <summary>
	/// Создает график с  именем и данными
	/// </summary>
	/// <param name="name">имя</param>
	/// <param name="data">данные</param>
	Plotter(string title, vector<DataPack<T>>data) {
		this->title = title;
		this->data = data;
	}
	/// <summary>
	/// Создает пустой график без данных
	/// </summary>
	Plotter() :Plotter(Constants::Strings::undefined, {}) {};
	/// <summary>
	/// Деструктор
	/// </summary>
	~Plotter() {};
	/// <summary>
	/// Строит график по указанному .txt файлу
	/// </summary>
	/// <param name="filename">путь до .txt файла</param>
	void Plot(string filename) {
		stringstream ss;
		ss << this->prefixPython << " " << this->pathToPyton << " " << filename;
		system(ss.str().c_str());
	}
};
