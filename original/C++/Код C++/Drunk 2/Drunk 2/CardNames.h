#pragma once
#include <string.h>
#include <vector>
using namespace std;
class CardNames
{
public:
	enum  names { six=1,seven=2,eight=3,nine=4,ten=5,jack=6,queen=7,king=8,ace=9 };
	vector<string> strNames = { "six","seven","eight","nine","ten","jack","queen","king","ace" };
	CardNames()
	{
	}
	string GetName(int name)
	{
		if (name > 0 && name <= strNames.size())
			return strNames[name-1];
	}
};

