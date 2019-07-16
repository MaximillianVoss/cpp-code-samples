#pragma once
#include "pch.h"
#include "ListItem.h"
template <typename T>
class OWLList {
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
	ListItem<T>* Get(int index) {
		ListItem<T>* current = head;
		if (current) {
			int i = 0;
			while (current->next && i < index)
				current = current->next;
			if (i < index)
				current = NULL;
		}
		return current;
	}
	/// <summary>
	/// Получает последний элемент списка
	/// </summary>
	/// <returns>NULL-если список пустой или указатель на элемент</returns>
	ListItem<T>* GetLast() {
		if (this->head) {
			ListItem<T>* current = head;
			while (current->next)
				current = current->next;
			return current;
		}
		return this->head;
	}
#pragma endregion
public:
#pragma region Поля
	/// <summary>
	/// Начало списка
	/// </summary>
	ListItem<T>* head;
#pragma endregion
#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// Создает пустой список
	/// начала списка - пустой указатель
	/// </summary>
	OWLList() {
		head = NULL;
	}
	/// <summary>
	/// Деструктор
	/// </summary>
	~OWLList() {
		ListItem<T>* current = head;
		while (current)
		{
			ListItem<T>* toDel = current;
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
		if (!head)
			this->head = new  ListItem<T>(data);
		else {
			ListItem<T>* newHead = new  ListItem<T>(data);
			newHead->next = head;
			this->head = newHead;
		}
	}
	/// <summary>
	/// Добавление в конец списка
	/// </summary>
	/// <param name="data">данные</param>
	void Add(T data) {
		if (!head)
			this->AddBegin(data);
		else
			this->GetLast()->next = new  ListItem<T>(data);
	}
	/// <summary>
	/// Добавление в список по указанному индексу
	/// </summary>
	/// <param name="data">данные</param>
	/// <param name="index">индекс</param>
	void Add(T data, int index) {
		ListItem<T>* prev = Get(index - 1);
		if (!prev)
			this->AddBegin(data);
		else {
			ListItem<T>* next = Get(index);
			if (!next)
				this->Add(data);
			else {
				prev->next = new ListItem<T>(data);
				prev->next->next = next;
			}
		}

	}
	/// <summary>
	/// Удаление элемента в начале списка
	/// </summary>
	void DeleteBegin() {
		if (head) {
			ListItem<T>* newHead = head->next;
			delete(this->head);
			this->head = newHead;
		}
	}
	/// <summary>
	/// Удаление элемента в конце списка
	/// </summary>
	void Delete() {
		ListItem<T>* last = this->GetLast();
		if (last) {
			ListItem<T>* toDel = last;
			free(toDel);
			toDel = NULL;
			last = NULL;
		}
	}
	/// <summary>
	/// Удаление элемента по индексу
	/// </summary>
	/// <param name="index"></param>
	void Delete(int index) {
		ListItem<T>* prev = Get(index - 1);
		if (!prev)
			this->DeleteBegin();
		else {
			ListItem<T>* current = Get(index);
			if (current) {
				prev->next = current->next;
				delete(current);
				current = NULL;
			}
		}
	}
	/// <summary>
	/// Получает длину списка
	/// </summary>
	/// <returns></returns>
	int GetLength() {
		int i = 0;
		ListItem<T>* current = head;
		while (current) {
			current = current->next;
			i++;
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
			ListItem<T>* current = head;
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