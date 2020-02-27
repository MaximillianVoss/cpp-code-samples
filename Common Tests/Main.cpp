#include"IO.h"
#include "OWLL.h"
#include "IOtests.h"
#include "LLTests.h"
#include "StrHelperTests.h"
#include "SortsTests.h"
#include "GraphTests.h"
#include "SearchTests.h"
int main() {
	srand(time(NULL));
	IO io = IO();
	io.SetRusIO();

	//IOTests().Start();
	//LLTests().Start();
	//StrHelperTests().Start();
	SortsTests().Start();
	SearchTests().Start();
	GraphTests().Start();

	io.Pause();
	return 0;
}