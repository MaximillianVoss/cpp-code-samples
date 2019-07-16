#include "Enums.h"
#pragma once
class MenuItem
{
private:
public:
	int action;
	string title;
	MenuItem(int _action, string _title) {
		action = _action;
		title = _title;
	}
	~MenuItem() {
	}
};