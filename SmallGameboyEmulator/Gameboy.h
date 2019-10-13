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
#include <iostream>
#include <cstdint>
#include <string>

using namespace memory;
using namespace proc;
using namespace std;

class Gameboy {
protected:
	MemoryManager * memory;
	Processor * processor;
public:
	Gameboy();
	virtual ~Gameboy();

	void test();
};

#endif /* GAMEBOY_H_ */