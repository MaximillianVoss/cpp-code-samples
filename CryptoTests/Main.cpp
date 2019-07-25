#include"IO.h"
#include "ShamirSecretSharingTests.h"
#include"BlockchainTests.h"
int main() {
	IO io = IO();
	io.SetRusIO();
	srand(time(NULL));
	//SSSTests().Start();
	BlockchainTests().Start();
	io.Pause();
}