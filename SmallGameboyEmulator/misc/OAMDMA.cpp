/*
 * OAMDMA.cpp
 *
 *  Created on: 30.10.2019
 *      Author: Tobias
 */

#include <misc/OAMDMA.h>
#include <cstdio>

namespace misc {

OAMDMA::OAMDMA(MemoryManager * memory) {
	this->memory = memory;
}

void OAMDMA::clock() {
	if (memory->lastAccess == 0xff46) {
		uint16_t base = memory->readMemory(0xff46)*0x100;
		for (int i=0;i<0xa0;i++) {
			memory->writeMemory(0xfe00+i,memory->readMemory(base+i));
		}
		memory->lastAccess = 0;
	}
}

OAMDMA::~OAMDMA() {
}

} /* namespace ppu */
