/*
 * MemorySection.cpp
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#include "MemorySection.h"
#include <cstdio>

namespace memory {

MemorySection::MemorySection(uint16_t start, uint32_t length) {
	initializeSection(start,length);
	this->memory = new uint8_t[length];
}

MemorySection::~MemorySection() {
	deleteSection();
	delete this->memory;
}

void MemorySection::initializeSection(uint16_t start, uint32_t length) {
	this->memoryLength = length;
	this->memoryStart = start;
	this->memoryEnd = start+length;
}

void MemorySection::deleteSection() {
	this->isValid = false;
}

bool MemorySection::containsAddress(uint16_t addr) {
	return addr >= this->memoryStart && addr < this->memoryEnd;
}

bool MemorySection::writeAddress(uint16_t addr, uint8_t value) {
	if (this->containsAddress(addr)) {
		this->memory[addr - this->memoryStart] = value;
		return true;
	} else {
		return false;
	}
}

uint8_t MemorySection::readAddress(uint16_t addr) {
	if (this->containsAddress(addr)) {
			return this->memory[addr - this->memoryStart];
		} else {
			return 0xFF;
		}
}


} /* namespace memory */
