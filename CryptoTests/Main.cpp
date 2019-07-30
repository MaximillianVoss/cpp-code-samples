#include"IO.h"
#include"ShamirSecretTests.h"
#include"BlockchainTests.h"
#include"SHATests.h"
int main() {
	IO io = IO();
	io.SetRusIO();
	srand(time(NULL));
	//SSSTests().Start();
	SHA1Tests().Start();
	BlockChainTests().Start();
	
	io.Pause();
}