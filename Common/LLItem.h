#pragma once
#include "pch.h"
template <typename T>
/// <summary>
/// Элемент связного списка
/// </summary>
class LLItem {
public:
#pragma region Поля
	/// <summary>
	/// Данные
	/// </summary>
	T data;
	/// <summary>
	/// Следующий элемент
	/// </summary>
	LLItem* next;
	/// <summary>
	/// Предыдущий элемент
	/// </summary>
	LLItem* prev;
#pragma endregion
#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// Создает элемент списка с указанными динными и соседями
	/// </summary>
	/// <param name="data">данные</param>
	/// <param name="next">следующий элемент</param>
	/// <param name="prev">предыдущий элемент</param>
	LLItem(T data, LLItem * next = NULL, LLItem * prev = NULL) {
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
	/// <summary>
	/// Копирует указанный элемент
	/// </summary>
	/// <param name="item">элемент для копирования</param>
	LLItem(LLItem<T>* item) {
		this->data = item->data;
		this->next = item->next;
		this->prev = item->prev;
	}
	/// <summary>
	/// Создает элемент списка, 
	/// для данных вызывается конструктор по умолчанию
	/// </summary>
	LLItem() :LLItem(T()) {

	}
	/// <summary>
	/// Деструктор
	/// </summary>
	~LLItem() {
		this->next = NULL;
		this->prev = NULL;
	}
#pragma endregion
#pragma region Методы	
	/// <summary>
	/// Соединяет два элемента
	/// </summary>
	/// <param name="item">указатель на элемент(добавляется следом)</param>
	void Add(LLItem* item) {
		this->next = item;
		if (item)
			item->prev = this;
	}
	/// <summary>
	/// Преобразует элемент в строку
	/// </summary>
	/// <param name="showDetails">true - отображать всю информацию:данные + соседи</param>
	/// <returns></returns>
	string ToString(bool showDetails = false) {
		stringstream ss;
		if (showDetails) {
			if (this->next)
				ss << this->next->ToString(false);
			if (this->prev)
				ss << this->prev->ToString(false);
		}
		ss << this->data;
		return ss.str();
	}
#pragma endregion
#pragma region Операторы
	//friend ostream& operator<< <>(ostream& os, LLItem<T>& item)
	//{
	//	//os << item.data;
	//	return os;
	//}
	bool operator== (LLItem<T>& item) {
		return this->data == item.data;
	}
	/*LLItem<T>& operator+= (LLItem<T>& item) {
		this->next = item;
		item.prev = this;
		return *this;
	}*/
	//LLItem<T>* operator+=(LLItem<T>* item) {
	//	this->next = item;
	//	item->prev = this;
	//	return this;
	//}
#pragma endregion
};