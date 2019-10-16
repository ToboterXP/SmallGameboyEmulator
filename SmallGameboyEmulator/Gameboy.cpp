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
	this->memory->addSection(BasicROMSection("./marioLand.gb"));

	this->processor = new Processor(this->memory);

	int i=0;
	while (i<10000 && !(processor->frozen)) {
		processor->clock();
		i++;
	}
	printf("%i",i);
}

Gameboy::~Gameboy() {
	delete this->memory;
}

void Gameboy::test() {
	this->processor->clock();
}

