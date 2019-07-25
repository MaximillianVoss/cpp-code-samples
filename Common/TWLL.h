#pragma once
#include "pch.h"
#include "LLItem.h"
#include "LL.h"
template <typename T>
class TWLList : public LL<T> {
public:
#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// Создает пустой список
	/// начала списка - пустой указатель
	/// </summary>
	TWLList() :LL<T>() {
	}
	/// <summary>
	/// Деструктор
	/// </summary>
	~TWLList() {
	}
#pragma endregion
#pragma region Методы
#pragma region Добавление
	void Add(T data) override {
		if (!head)
			this->head = new  LLItem<T>(data);
		else
			this->GetLast()->Add(new LLItem<T>(data));
		this->IncLength();
	};
	void Add(T data, size_t index)override {

	};
	void Add(LLItem<T>* item)override {
		if (!head)
			this->head = item;
		else
			this->GetLast()->Add(item);
		this->IncLength();
	};
	void Add(vector<T> items) {
		for (T item : items)
			this->Add(item);
	}
	void Add(TWLList<T>& list) {
		this->Add(list.ToList());
	}
	void Add(TWLList<T>* list) {
		this->Add(*list);
	}
#pragma endregion
#pragma region Удаление
	void Delete()override {
		LLItem<T>* last = this->GetLast();
		if (last) {
			if (last->prev)
				last->prev->Add(NULL);
			delete(last);
			last = NULL;
			this->DecLength();
			if (this->GetLength() == 0)
				this->head = NULL;
		}
	};
	void Delete(size_t index) override { throw exception(Constants::Strings::Errors::notImplemented); };
	void Delete(LLItem<T>* item) override { throw exception(Constants::Strings::Errors::notImplemented); };
#pragma endregion
#pragma endregion
#pragma region Операторы
	TWLList<T>& operator+(TWLList<T>& list) {
		TWLList<T>* result = new TWLList<T>();
		*result += *this;
		*result += list;
		return *result;
	}
	TWLList<T>& operator-(TWLList<T>& list) {
		TWLList<T> result = *this;
		result -= list;
		return result;
	}
	TWLList<T>& operator+=(TWLList<T>& list) {
		LLItem<T>* current = list.head;
		while (current)
		{
			this->Add(current);
			current = current->next;
		}
		return *this;
	}
	TWLList<T>& operator-=(TWLList<T>& list) {
		LLItem<T>* current = list.head;
		while (current)
		{
			this->Delete(current);
			current = current->next;
		}
		return *this;
	}
#pragma endregion
};
