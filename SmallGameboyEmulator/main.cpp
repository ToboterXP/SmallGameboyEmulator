
#include <iostream>

using namespace std;
#include "Gameboy.h"

int main() {
	cout << "\n";
	Gameboy * gb = new Gameboy();
	gb->test();
	delete gb;
	return 0;
}
