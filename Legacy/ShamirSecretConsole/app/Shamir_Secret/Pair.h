#pragma once
#include "pch.h"
template<class T1, class T2>
class Pair
{
private:
	T1 key;
	T2 value;
public:
	Pair() {

	}
	Pair(T1 key, T2 value) {
		this->key = key;
		this->value = value;
	}
	T2 GetValue() const {
		return this->value;
	}
	T1 GetKey() const {
		return this->key;
	}
};
