#pragma once
#include "pch.h"
#include "ListItem.h"
template <typename T>
class TWLList {
private:
#pragma region Константы
	const string incorrectIndex = "Некорректный индекс - список слишком мал!";
	const string listIsEmpty = "Список пуст";
	const string separator = "->";
#pragma endregion
#pragma region Поля
#pragma endregion
#pragma region Методы
	/// <summary>
	/// Получение элемента по индексу
	/// </summary>
	/// <param name="index">индекс элемента списка</param>
	/// <returns>NULL-если элемента не существует</returns>
	ListItem* Get(int index) {
		ListItem* current = head;
		if (current) {
			int i = 0;
			while (current->next && i < index)
				current = current->next;
			if (i < index)
				current = NULL;
		}
		return current;
	}
#pragma endregion
public:
#pragma region Поля
	/// <summary>
	/// Начало списка
	/// </summary>
	ListItem* head;
#pragma endregion
#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// Создает пустой список
	/// начала списка - пустой указатель
	/// </summary>
	TWLList() {
		head = NULL;
	}
	/// <summary>
	/// Деструктор
	/// </summary>
	~TWLList() {
		ListItem* current = head;
		while (current)
		{
			ListItem* toDel = current;
			current = current->next;
			delete(toDel);
		}
	}
#pragma endregion
#pragma region Методы
	/// <summary>
	/// Добавление в начало списка
	/// </summary>
	/// <param name="data">данные</param>
	void AddBegin(T data) {
		if (!this->head)
			this->head = new  ListItem<T>(data);
		else {
			ListItem* newHead = new  ListItem<T>(data);
			newHead->next = this->head;
			this->head->prev = newHead;
			this->head = newHead;
		}
	}
	/// <summary>
	/// Добавление в конец списка
	/// </summary>
	/// <param name="data">данные</param>
	void Add(T data) {
		if (!head)
			this->head = new  ListItem<T>(data);
		else {
			ListItem* current = head;
			while (current->next)
				current = current->next;
			current->next = new  ListItem<T>(data);
			current->next->prev = current;
		}

	}
	/// <summary>
	/// Добавление в список по указанному индексу
	/// </summary>
	/// <param name="data">данные</param>
	/// <param name="index">индекс</param>
	void Add(T data, int index) {
		if (!head)
			this->head = new  ListItem<T>(data);
		else {
			ListItem* current = head;
			int i = 0;
			while (current->next && i < index) {
				current = current->next;
				i++;
			}
			if (i < index)
				throw exception(this->incorrectIndex);
			ListItem* next = NULL;
			if (current)
				next = current->next;
			current->next = new  ListItem<T>(data);
			current->next->prev = current;
			current->next->next = next;
			if (next)
				next->prev = current->next;
		}
	}
	/// <summary>
	/// Удаление элемента в начале списка
	/// </summary>
	void DeleteBegin() {
		if (head) {
			ListItem* newHead = head->next;
			delete(this->head);
			this->head = newHead;
			this->head->prev = NULL;
		}
	}
	/// <summary>
	/// Удаление элемента в конце списка
	/// </summary>
	void Delete() {
		if (head) {
			ListItem* current = head;
			while (current->next)
				current = current->next;
			ListItem* toDel = current;
			free(toDel);
			current = NULL;
		}
	}
	/// <summary>
	/// Удаление элемента по индексу
	/// </summary>
	/// <param name="index"></param>
	void Delete(int index) {
		if (head) {
			ListItem* prev = Get(index - 1);
			ListItem* current = Get(index);
			if (!prev || !current)
				throw exception(this->incorrectIndex);
			prev->next = current->next;
			delete(current);
		}
	}
	/// <summary>
	/// Получает длину списка
	/// </summary>
	/// <returns></returns>
	int GetLength() {
		int i = 0;
		if (head) {
			ListItem* current = head;
			while (current->next) {
				current = current->next;
				i++;
			}
		}
		return i;
	}
	/// <summary>
	/// Преобразует список в строку
	/// </summary>
	/// <param name="showDetails">показывать каждй элемент подробно</param>
	/// <returns></returns>
	string ToString(bool showDetails = false) {
		if (head) {
			string str = "";
			ListItem* current = head;
			while (current)
			{
				str += current->ToString(showDetails) + this->separator;
				current = current->next;
			}
			return str;
		}
		else
			return this->listIsEmpty;
	}
#pragma endregion
};