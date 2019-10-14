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

	processor->setAF(0xabcd);
	for (uint16_t i=0x100; i<0x120; i++) {
		this->memory->writeMemory(i,(uint8_t)i);
	}
	this->memory->writeMemory(0x100,0xab);
	this->memory->writeMemory(0x101,0xcd);
	this->memory->writeMemory(0x102,0xef);
	printf("%x\n",processor->getInstruction16());
	printf("%x\n",processor->getInstruction8());

	/*cout << "Writing memory from 0x1f0 to 0x210\n";
	for (uint16_t i=0x1f0; i<0x210; i++) {
		this->memory->writeMemory(i,(uint8_t)i);
	}
	cout << "Reading memory from 0x1f0 to 0x210\n";
	for (uint16_t i=0x1f0; i<0x210; i++) {
		cout << std::to_string( this->memory->readMemory(i) ) << "\n";
	}*/
}

