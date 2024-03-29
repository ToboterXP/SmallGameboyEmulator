/*
 * MemoryManager.h
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#include "MemorySection.h"
#include "BasicROMSection.h"
#include <list>
#include <cstdint>

namespace memory {

class MemoryManager {
public:
	uint8_t * ram;
	BasicROMSection * romSection;
	MemorySection * ramSection;
	uint16_t lastAccess = 0;
	MemoryManager();
	virtual ~MemoryManager();

	uint8_t readMemory(uint16_t addr);
	void writeMemory(uint16_t addr, uint8_t val);
};

} /* namespace memory */

#endif /* MEMORYMANAGER_H_ */
