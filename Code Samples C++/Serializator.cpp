#include "pch.h"
#include "Serializator.h"

#pragma region Методы
void Serializator::Serialize(string fileName, vector<Pair>fieldsValues)
{
	vector<string> values;
	for (int i = 0; i < fieldsValues.size(); i++)
		values.push_back(fieldsValues[i].key + delimiter + fieldsValues[i].value);
	fileIO.WriteLinesLn(fileName, values);
}

vector<Pair> Serializator::Deserialize(string fileName)
{
	vector<Pair> values;
	vector<string> lines = fileIO.ReadLines(fileName);
	for (string line : lines)
	{
		vector<string> items = strHelper.Split(line, delimiter, "");
		if (items.size() > 1)
			values.push_back(Pair(items[0], items[1]));
		else
			values[values.size() - 1].value += line;
	}
	return values;
}
#pragma endregion

#pragma region Конструкторы/Деструкторы
Serializator::Serializator()
{
}

Serializator::~Serializator()
{
}
#pragma endregion