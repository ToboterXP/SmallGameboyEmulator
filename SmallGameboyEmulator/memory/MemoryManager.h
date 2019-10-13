/*
 * MemoryManager.h
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#include "MemorySection.h"
#include <list>
#include <cstdint>

namespace memory {

class MemoryManager {
protected:
	std::list<MemorySection> * sections;
public:
	MemoryManager();
	virtual ~MemoryManager();
	void addSection(MemorySection sec);

	uint8_t readMemory(uint16_t addr);
	void writeMemory(uint16_t addr, uint8_t val);
};

} /* namespace memory */

#endif /* MEMORYMANAGER_H_ */