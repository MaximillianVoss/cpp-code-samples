#pragma once
#include "pch.h"
template <typename T>
/// <summary>
/// Элемент связного списка
/// </summary>
class ListItem {
public:
	/// <summary>
	/// Данные
	/// </summary>
	T data;
	/// <summary>
	/// Следующий элемент
	/// </summary>
	ListItem* next;
	/// <summary>
	/// Предыдущий элемент
	/// </summary>
	ListItem* prev;
	/// <summary>
	/// Создаем элемент списка с указанными данными
	/// </summary>
	/// <param name="data">данные(любой тип)</param>
	ListItem(T data) {
		this->data = data;
		this->next = NULL;
		this->prev = NULL;
	}
	/// <summary>
	/// Создает элемент списка, 
	/// для данных вызывается конструктор по умолчанию
	/// </summary>
	ListItem() :ListItem(T()) {

	}
	/// <summary>
	/// Деструктор
	/// </summary>
	~ListItem() {
		this->next = NULL;
		this->prev = NULL;
	}
	/// <summary>
	/// Преобразует элемент в строку
	/// </summary>
	/// <param name="showDetails">true - отображать всю информацию:данные + соседи</param>
	/// <returns></returns>
	string ToString(bool showDetails) {
		string str = "";
		if (showDetails) {
			if (this->next)
				str += this->next->ToString(false);
			if (this->prev)
				str += this->prev->ToString(false);
		}
		return str + this->ToString();
	}
	/// <summary>
	/// Преобразует элемент в строку
	/// </summary>
	/// <returns></returns>
	string ToString() {
		return to_string(this->data);
	}
};