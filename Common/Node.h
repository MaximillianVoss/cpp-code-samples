#pragma once
#include "pch.h"
#include "GraphItem.h"
#include "Enums.h"
#include "Constants.h"
#include "StrHelper.h"
template<typename T>
///<summary>
/// Вершина графа
///</summary>
class Node : public GraphItem
{
private:

#pragma region Поля
	/// <summary>
	/// Данные вершины
	/// </summary>
	T data;
#pragma endregion

#pragma region Методы

#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	/// <summary>
	/// Устанавливает данные в вершине
	/// </summary>
	/// <param name="data">данные</param>
	void SetData(T data) {
		this->data = data;
	}
	/// <summary>
	/// Получает данные из вершины
	/// </summary>
	/// <returns></returns>
	T GetData() {
		return this->data;
	}
	/// <summary>
	/// Получает указатель на данные в веришне
	/// </summary>
	/// <returns></returns>
	T* GetDataP() {
		return &this->data;
	}
	/// <summary>
	/// Преборазует объект в строку
	/// Для просмотра визуально:https://graphonline.ru/
	/// </summary>
	/// </summary>
	/// <param name="format">формат вывода</param>
	/// <param name="x">X координата для визуального отображения</param>
	/// <param name="y">Y координата для визуального отображения</param>
	/// <returns></returns>
	string ToString(OutputFormat format = OutputFormat::fields, int x = 0, int y = 0) {
		stringstream ss;
		if (format == OutputFormat::fields) {
			ss << "id:" << this->GetId() << endl;
			ss << "data:" << this->GetData() << endl;
		}
		else if (format == OutputFormat::xml) {
			StrHelper sh = StrHelper();
			ss << "<node positionX=" + sh.AddQoute(to_string(x)) +
				" positionY=" + sh.AddQoute(to_string(y)) +
				" id=" + sh.AddQoute(this->GetId()) +
				" mainText=" << '"' << this->GetData() << '"' <<
				" upText=\"\"></node>";
		}
		else
			ss << Constants::Strings::undefined;
		return ss.str();
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// Конструктор по умолчанию
	/// </summary>
	Node() {
		this->SetId(Constants::Strings::undefined);
		this->SetDeleted(false);
	};
	/// <summary>
	/// Создает вершину с указанными ID и данными
	/// </summary>
	/// <param name="id">ID</param>
	/// <param name="data">данные</param>
	/// <param name="longFormat">Длиный формат, true - ID будут в 32 разрядном представлении</param>
	Node(string id, T data, bool longFormat = true) {
		this->SetId(id, longFormat);
		this->SetData(data);
		this->SetDeleted(false);
	}
	/// <summary>
	/// Создает вершину с указанными ID и данными
	/// </summary>
	/// <param name="id">ID</param>
	/// <param name="longFormat">Длиный формат, true - ID будут в 32 разрядном представлении</param>
	Node(string id, bool longFormat = true) {
		this->SetId(id, longFormat);
		this->SetDeleted(false);
	}
	~Node() {};
#pragma endregion

#pragma region Операторы
	bool operator > (Node n) {
		return this->GetId() > n.GetId();
	}
	bool operator < (Node n) {
		return this->GetId() < n.GetId();
	}
	bool operator == (Node n) {
		return this->GetId() == n.GetId();
	}
#pragma endregion

#pragma region Обработчики событий

#pragma endregion

};
