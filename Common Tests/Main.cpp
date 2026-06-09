#include"IO.h"
#include "OWLL.h"
#include "IOtests.h"
#include "LLTests.h"
#include "StrHelperTests.h"
#include "SortsTests.h"
#include "GraphTests.h"
#include "SearchTests.h"
#include "SFieldTests.h"
#include "SObjectTests.h"
#include "DataPackTest.h"
#include "AVLTreeTest.h"
int main()
{
	srand(time(NULL));
	IO io = IO();
	io.SetRusIO();

	//IOTests().Start();
	//LLTests().Start();
	//StrHelperTests().Start();
	//SortsTests().Start();
	//SearchTests().Start();
	//GraphTests().Start();
	//SFieldTests().Start();
	//SObjectsTests().Start();
	//DataPackTests().Start();
	//AVLTreeTests().Start();

	io.Pause();
	return 0;
}