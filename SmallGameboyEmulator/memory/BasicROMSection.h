/*
 * BasicROMSection.h
 *
 *  Created on: 16.10.2019
 *      Author: Tobias
 */

#ifndef BASICROMSECTION_H_
#define BASICROMSECTION_H_

#include "MemorySection.h"
#include <SDL2/sdl.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

namespace memory{

enum ROMMapperType {
	NONE,
	MBC1,
	MBC2,
	MMM01,
	MBC3,
	MBC5
};

class BasicROMSection : public MemorySection {
protected:
	uint8_t * rom;
	uint8_t * ram;
	uint8_t ramSizeID = 0;
	int ramSize = 0;
	uint64_t bankOffset;
	uint64_t ramOffset;
	uint8_t romMode;
	ROMMapperType romType;
public:
	uint8_t cartridgeType;
	uint8_t romBank=0;
	bool changed = false;
	bool sramLock = true;
	string romFilename;
	BasicROMSection(string filename);
	virtual ~BasicROMSection();
	bool containsAddress(uint16_t addr);
	bool writeAddress(uint16_t addr, uint8_t value);
	uint8_t readAddress(uint16_t addr);
	void saveSRAM();
};

} /* namespace proc */

#endif /* BASICROMSECTION_H_ */
