/*
 * Gameboy.cpp
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#include "Gameboy.h"

Gameboy::Gameboy() {
	this->memory = new MemoryManager();
	this->memory->addSection(MemorySection(0x00,0x200));
}

Gameboy::~Gameboy() {
	delete this->memory;
}

void Gameboy::test() {
	cout << "Writing memory from 0x1f0 to 0x210\n";
	for (uint16_t i=0x1f0; i<0x210; i++) {
		this->memory->writeMemory(i,(uint8_t)i);
	}
	cout << "Reading memory from 0x1f0 to 0x210\n";
	for (uint16_t i=0x1f0; i<0x210; i++) {
		cout << std::to_string( this->memory->readMemory(i) ) << "\n";
	}
}

