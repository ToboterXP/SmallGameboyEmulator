
#include <iostream>

using namespace std;
#include "Gameboy.h"

int main( int argc, char *argv[] ) {
	cout << "\n";
	Gameboy * gb = new Gameboy();
	gb->test();
	delete gb;
	return 0;
}
