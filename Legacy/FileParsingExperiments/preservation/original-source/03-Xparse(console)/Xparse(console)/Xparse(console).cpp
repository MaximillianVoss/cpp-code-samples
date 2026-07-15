// Xparse(console).cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

int _tmain(int argc, _TCHAR* argv[])
{
	/*std::cout << "ffff" << std::endl;
	std::string name;
	std::cin >> name;
	std::cout << "Helo, " << name << std::endl;*/
	std::fstream fs;
	std::cout << "Enter path to file";
	std::string name;
	std::cin >> name;
	fs.open(name, std::fstream::in | std::fstream::out | std::fstream::app);
	if (fs.is_open())
	{
		while (!fs.eof())
		{
			//std::count  fs;
		}
	}
	fs << "ff";
	fs.close();
	
	return 0;
}

