#include"IO.h"
#include "OWLL.h"
#include "IOtests.h"
#include "LLTests.h"
int main() {
	IO io = IO();
	io.SetRusIO();

	//IOTests().Start();
	LLTests().Start();

	io.Pause();
	return 0;
}