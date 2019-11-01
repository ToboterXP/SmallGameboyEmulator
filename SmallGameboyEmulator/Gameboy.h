/*
 * Gameboy.h
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#ifndef GAMEBOY_H_
#define GAMEBOY_H_

#include <memory/MemoryManager.h>
#include <processor/Processor.h>
#include <memory/BasicROMSection.h>
#include <video/PPU.h>
#include <misc/Joypad.h>
#include <misc/OAMDMA.h>
#include <iostream>
#include <cstdint>
#include <string>

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

using namespace memory;
using namespace proc;
using namespace ppu;
using namespace std;
using namespace misc;


class Gameboy {
protected:
	int procCD = 3;
	FILE * log;
public:
	MemoryManager * memory;
	Processor * processor;
	PPU * ppu;
	Joypad * joypad;
	OAMDMA * oam;
	Gameboy();
	virtual ~Gameboy();

	void test();
	void clock();

	void debugInstruction(uint8_t opcode);
};




#endif /* GAMEBOY_H_ */
