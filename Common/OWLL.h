#pragma once
#include "pch.h"
#include "LLItem.h"
#include "LL.h"
template <typename T>
/// <summary>
/// ����������� ������
/// </summary>
class OWLList :public LL<T> {
public:
#pragma region ������������/�����������
	/// <summary>
	/// ������� ������ ������
	/// ������ ������ - ������ ���������
	/// </summary>
	OWLList() :LL<T>() {
	}
	/// <summary>
	/// ����������
	/// </summary>
	~OWLList() {
	}
#pragma endregion
#pragma region ������
#pragma region ����������
	/// <summary>
	/// 
	/// </summary>
	/// <param name="data"></param>
	void Add(T data) override {
		if (!head)
			this->head = new  LLItem<T>(data);
		else
			this->GetLast()->next = new LLItem<T>(data);
		this->IncLength();
	};
	/// <summary>
	/// 
	/// </summary>
	/// <param name="data"></param>
	/// <param name="index"></param>
	void Add(T data, size_t index)override {
		LLItem<T>* found = this->Find(index);
		if (found) {
			LLItem<T>* foundPrev = this->Find(index - 1);
			if (foundPrev) {
				foundPrev->next = new LLItem<T>(data);
				foundPrev->next->next = found;
			}
			else {
				this->head = new LLItem<T>(data);
				this->head->next = found;
			}
			this->IncLength();
		}

	};
	/// <summary>
	/// 
	/// </summary>
	/// <param name="item"></param>
	void Add(LLItem<T>* item)override {
		if (!head)
			this->head = item;
		else
			this->GetLast()->next = item;
		if (item)
			this->IncLength();
	};
#pragma endregion
#pragma region ��������
	/// <summary>
	/// 
	/// </summary>
	void Delete()override {
		throw exception(Constants::Strings::Errors::notImplemented);
		//LLItem<T> *preLast = this->Find(size_t(this->GetLength() - 2));
		//LLItem<T> *last = this->Find(size_t(this->GetLength() - 1));
		//if(preLast)

	};
	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	void Delete(size_t index) override { throw exception(Constants::Strings::Errors::notImplemented); };
	/// <summary>
	/// 
	/// </summary>
	/// <param name="item"></param>
	void Delete(LLItem<T>* item) override { throw exception(Constants::Strings::Errors::notImplemented); };
#pragma endregion
#pragma endregion
};