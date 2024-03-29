/*
 * MemoryManager.cpp
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#include "MemoryManager.h"
#include <cstdio>

namespace memory {

MemoryManager::MemoryManager() {
	romSection = NULL;
	ramSection = NULL;
	ram = NULL;
}

MemoryManager::~MemoryManager() {
}

uint8_t MemoryManager::readMemory(uint16_t addr) {
	if (ram==NULL) ram = ramSection->memory;
	if (romSection->containsAddress(addr)) return romSection->readAddress(addr);
	return ramSection->readAddress(addr);
}

void MemoryManager::writeMemory(uint16_t addr, uint8_t val) {
	if (ram==NULL) ram = ramSection->memory;
	lastAccess = addr;
	if (romSection->containsAddress(addr)) romSection->writeAddress(addr,val);
	ramSection->writeAddress(addr,val);
}

} /* namespace memory */
