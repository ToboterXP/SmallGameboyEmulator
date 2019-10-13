/*
 * MemorySection.h
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#ifndef MEMORYSECTION_H_
#define MEMORYSECTION_H_

#include <cstdint>
#include <new>

namespace memory {

class MemorySection {
protected:
	uint8_t * memory;
	uint16_t memoryLength;
	uint16_t memoryStart;
	uint16_t memoryEnd;
public:
	bool isValid = true;
	MemorySection(uint16_t start, uint16_t length);
	virtual ~MemorySection();

	bool containsAddress(uint16_t addr);
	bool writeAddress(uint16_t addr, uint8_t value);
	uint8_t readAddress(uint16_t addr);
};

} /* namespace memory */

#endif /* MEMORYSECTION_H_ */
