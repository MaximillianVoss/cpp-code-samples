#pragma once
#include "pch.h"
#include "LLItem.h"
#include "Constants.h"
template <typename T>
class LL {
private:
#pragma region Поля
	/// <summary>
	/// Текущая длина списка
	/// </summary>
	int length;
#pragma endregion
public:
#pragma region Поля
	/// <summary>
	/// Начало списка
	/// </summary>
	LLItem<T>* head;
	/// <summary>
	/// Конец списка
	/// </summary>
	LLItem<T>* tail;
#pragma endregion
#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// Создает пустой список
	/// начала списка - пустой указатель
	/// конец списка - пустой указатель
	/// </summary>
	LL() {
		this->head = NULL;
		this->tail = NULL;
		this->length = 0;
	}
	/// <summary>
	/// Деструктор
	/// </summary>
	~LL() {
		try {
			LLItem<T>* current = this->head;
			while (current && this->length > 0)
			{
				LLItem<T>* toDel = current;
				current = current->next;
				if (toDel != nullptr) {
					delete(toDel);
					toDel = NULL;
					this->DecLength();
				}
				else
					break;
			}
		}
		catch (exception ex) {
			cout << ex.what();
		}
	}
#pragma endregion
#pragma region Методы
#pragma region Добавление/Удаление
	/// <summary>
	/// Добавляет элемент в конец списка
	/// </summary>
	void virtual Add(T data) { throw exception(Constants::Strings::Errors::notImplemented); };
	/// <summary>
	/// Добавляет элемент по указанному индексу
	/// </summary>
	void virtual Add(T data, size_t index) { throw exception(Constants::Strings::Errors::notImplemented); };
	/// <summary>
	/// Добавляет копию в конец списка
	/// </summary>
	void virtual Add(LLItem<T>* item) { throw exception(Constants::Strings::Errors::notImplemented); }
	/// <summary>
	/// Удаляет элемент в конце списка
	/// </summary>
	void virtual Delete() { throw exception(Constants::Strings::Errors::notImplemented); };
	/// <summary>
	/// Удаляет элемент по указанному индексу
	/// </summary>
	void virtual Delete(size_t index) { throw exception(Constants::Strings::Errors::notImplemented); };
	/// <summary>
	/// Удаляет элемент с указанным значением
	/// </summary>
	void virtual Delete(LLItem<T>* item) { throw exception(Constants::Strings::Errors::notImplemented); };
	/// <summary>
	/// Очистка списка
	/// </summary>
	void Clear() {
		while (this->head)
			this->Delete();
	}
#pragma endregion
#pragma region Поиск
	/// <summary>
	/// Поиск указанного элемента в списке (поле data)
	/// </summary>
	/// <param name="item">Указатель на элемент</param>
	/// <returns>NULL-если элемента не существует</returns>
	LLItem<T>* Find(LLItem<T>* item) {
		LLItem<T>* current = this->head;
		while (current)
		{
			if (item == current)
				return current;
			current = current->next;
		}
		return NULL;
	}
	/// <summary>
	/// Поиск указанного элемента в списке (поле data)
	/// </summary>
	/// <param name="data">Данные</param>
	/// <returns>NULL-если элемента не существует</returns>
	LLItem<T>* Find(T data) {
		LLItem<T>* current = this->head;
		while (current)
		{
			if (data == current->data)
				return current;
			current = current->next;
		}
		return NULL;
	}
	/// <summary>
	/// Поиск элемента по индексу
	/// </summary>
	/// <param name="index"></param>
	///<returns>NULL-если элемента не существует</returns>
	LLItem<T>* Find(size_t index) {
		if (this->length < index)
			return NULL;
		size_t i = 0;
		LLItem<T>* current = this->head;
		while (current && i <= index)
		{
			if (i == index)
				return current;
			current = current->next;
			i++;
		}
		return NULL;
	}
	/// <summary>
	/// Получает последний элемент в списке
	/// </summary>
	/// <returns></returns>
	LLItem<T>* GetLast() {
		return this->Find(size_t(this->GetLength() - 1));
	}
#pragma endregion
#pragma region Длина
	/// <summary>
	/// Увеличивает длину списка
	/// </summary>
	void IncLength() {
		this->length++;
	}
	/// <summary>
	/// Уменьшает длину списка
	/// </summary>
	void DecLength() {
		this->length--;
	}
	/// <summary>
	/// Получает длину списка
	/// </summary>
	/// <returns></returns>
	int GetLength() {
		return this->length;
	}
#pragma endregion
#pragma region Вывод
	/// <summary>
	/// Преобразует список в строку
	/// </summary>
	/// <param name="showDetails">показывать каждый элемент подробно</param>
	/// <returns></returns>
	string ToString(bool showDetails = false) {
		LLItem<T>* current = this->head;
		if (current) {
			stringstream ss;
			while (current)
			{
				ss << current->ToString(showDetails);
				if (current->next)
					ss << Constants::Strings::Separators::arrow;
				current = current->next;
			}
			return ss.str();
		}
		else
			return Constants::Strings::Errors::Lists::empty;
	}
	/// <summary>
	/// Экспортирует данные из списка в массив
	/// </summary>
	/// <returns>vector с данными</returns>
	vector<T> ToList() {
		vector<T> items;
		LLItem<T>* current = this->head;
		while (current) {
			items.push_back(current->data);
			current = current->next;
		}
		return items;
	}
#pragma endregion
#pragma endregion
};
#pragma region Операторы
template<typename T>
ostream& operator<<(ostream& os, LL<T>& list)
{
	os << list.ToString() << endl;
	return os;
}
#pragma endregion