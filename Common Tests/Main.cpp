#include"IO.h"
#include "OWLL.h"
#include "IOtests.h"
#include "LLTests.h"
#include "StrHelperTests.h"
int main() {
	IO io = IO();
	io.SetRusIO();

	//IOTests().Start();
	LLTests().Start();
	StrHelperTests().Start();
	io.Pause();
	return 0;
}