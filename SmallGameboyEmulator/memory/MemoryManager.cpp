/*
 * MemoryManager.cpp
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#include "MemoryManager.h"

namespace memory {

MemoryManager::MemoryManager() {
	this-> sections = new std::list<MemorySection>();
}

MemoryManager::~MemoryManager() {
	delete this->sections;
}

void MemoryManager::addSection(MemorySection sec) {
	this->sections->push_back(sec);
}

uint8_t MemoryManager::readMemory(uint16_t addr) {
	for (std::list<MemorySection>::iterator it = this->sections->begin();
			it != this->sections->end(); ++it) {
		if ((*it).containsAddress(addr)) return (*it).readAddress(addr);
	}
	return 0xFF;
}

void MemoryManager::writeMemory(uint16_t addr, uint8_t val) {
	for (std::list<MemorySection>::iterator it = this->sections->begin();
				it != this->sections->end(); ++it) {
			if ((*it).writeAddress(addr,val)) return;
		}
}


} /* namespace memory */
