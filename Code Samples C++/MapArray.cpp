#include "stdafx.h"
#include "MapArray.h"


MapArray::MapArray()
{
}


MapArray::~MapArray()
{
}

bool MapArray::Add(string key, string value)
{
	if (Find(key)) {
		values.push_back(Pair(key, value));
		return true;
	}
	return false;
}

bool MapArray::Add(Pair pair)
{
	return Add(pair.key, pair.value);
}

bool MapArray::Remove(string key)
{
	if (Find(key))
	{
		for (int i = 0; i < values.size(); i++)
			if (values[i].key == key)
				values.erase(values.begin() + i);
		return true;
	}
	return false;
}

bool MapArray::Find(string key)
{
	return GetItem(key) == NULL;
}

size_t MapArray::GetSize()
{
	return values.size();
}

void MapArray::SetItem(size_t index, Pair item)
{
	if (index > -1 && index < values.size())
		values[index] = item;
}

Pair* MapArray::GetItem(string key)
{
	for (int i = 0; i < values.size(); i++)
		if (values[i].key == key)
			return &values[i];
	return NULL;
}

Pair* MapArray::GetItem(size_t index)
{
	if (index >= 0 && index < values.size())
		return &values[index];
	else
		return NULL;
}

string MapArray::GetStr()
{
	string str = "";
	for (int i = 0; i < values.size(); i++)
		str += values[i].GetStr() + '\n';
	return str;
}
