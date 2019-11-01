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
	uint32_t memoryLength;
	uint16_t memoryStart;
	uint32_t memoryEnd;

	void initializeSection(uint16_t start, uint32_t length);
	void deleteSection();
public:
	uint8_t * memory;
	bool isValid = true;
	MemorySection(uint16_t start, uint32_t length);
	virtual ~MemorySection();

	virtual bool containsAddress(uint16_t addr);
	virtual bool writeAddress(uint16_t addr, uint8_t value);
	virtual uint8_t readAddress(uint16_t addr);
};

} /* namespace memory */

#endif /* MEMORYSECTION_H_ */
