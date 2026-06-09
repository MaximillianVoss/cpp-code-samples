#pragma once
#include "pch.h"
class Pair
{
public:
	string key;
	string value;

	Pair() = default;

	Pair(string key, string value) {
		this->key = key;
		this->value = value;
	}

	string GetValue() const {
		return this->value;
	}

	string GetKey() const {
		return this->key;
	}

	string GetStr() const {
		return this->key + ":" + this->value;
	}
};

