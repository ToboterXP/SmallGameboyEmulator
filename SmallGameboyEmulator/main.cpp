
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
#include "Gameboy.h"

int main( int argc, char *argv[] ) {
	if (argc!=2 && argc!=3) {
		cout << "Small Gameboy Emulator" << endl
				<< "Usage: sgb <romFile> [pixelSize]" << endl
				<< "pixelSize: size of a single GB pixel" << endl;
		return 0;
	}
	string romFile = string(argv[1]);
	int screenSize = 3;
	if (argc==3) {
		try {
			screenSize = stoi(argv[2]);
		}  catch(std::invalid_argument * e) {
			cout << "Error converting pixel size. Using default." << endl;
			screenSize = 3;
		}
	}
	Gameboy * gb = new Gameboy(romFile,screenSize);
	gb->run();
	delete gb;
	return 0;
}
