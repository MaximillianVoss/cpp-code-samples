#include"IO.h"
#include "OWLL.h"
#include "IOtests.h"
int main() {
	IO io = IO();
	io.SetRusIO();

	IOTests ioTests = IOTests();
	ioTests.Start();

	io.Pause();
	return 0;
}