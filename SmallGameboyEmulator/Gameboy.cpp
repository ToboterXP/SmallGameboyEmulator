/*
 * Gameboy.cpp
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#include "Gameboy.h"

#include <stdlib.h>

Gameboy::Gameboy() {
	this->memory = new MemoryManager();
	//catch-all ram
	this->memory->addSection(MemorySection(0x00,0x10000));

	this->processor = new Processor(this->memory);
}

Gameboy::~Gameboy() {
	delete this->memory;
}

void Gameboy::test() {
	this->processor->clock();
}

