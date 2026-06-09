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

bool RunCoreUnitTests()
{
	bool passed = true;

	passed &= SHJoinTest("Join", { "lol-,-kek-,-cheburek","1,2,3,4,5,6,7,8,9" }).Start();
	passed &= SHReplaceTest("Replace", { "kekekeke","1234111890" }).Start();
	passed &= SHRemoveTest("Remove", { "12345","","one two  four" }).Start();
	passed &= SHContainsTest("Contains", { true,false,true,false }).Start();
	passed &= SHGetNumbersTest("GetNumbers", { "123","456","4.5" }).Start();
	passed &= SHIsNumberTest("IsNumber", { true,false,true,false,true,true,false,false }).Start();
	passed &= SHSplitTest("Split", { "one","two","three","1","2","3","4","5","one",".","two","." }).Start();
	passed &= SHSplitCharTest("Split by char", { "alpha","beta","gamma" }).Start();
	passed &= SHRemoveCopiesTest("RemoveCopies", { "1","2","3","4","5","6","lol","kek","some text" }).Start();
	passed &= SHFormatTest("Format helpers", { "\"text\"","true","false" }).Start();
	passed &= QuickSortTest({ 0,1,2,3,4,5,5,4,3,2,1,0 }).Start();
	passed &= BinarySearchTest1({ 0,1,-1,5,2,2,-1 }).Start();
	passed &= BinarySearchTest2({ true,true,false,true,false,true,false }).Start();

	return passed;
}

int main()
{
	srand(1);
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

	const bool passed = RunCoreUnitTests();
	cout << (passed ? "Common unit tests passed" : "Common unit tests failed") << endl;
	return passed ? 0 : 1;
}
