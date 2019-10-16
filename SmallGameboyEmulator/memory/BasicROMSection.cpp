/*
 * BasicROMSection.cpp
 *
 *  Created on: 16.10.2019
 *      Author: Tobias
 */

#include <memory/BasicROMSection.h>
#include <cstdlib>

namespace memory {

BasicROMSection::BasicROMSection(string filename)  : MemorySection(0,2){
	ifstream file;
	file.open(filename,ios::in|ios::binary|ios::ate);
	file.seekg(0,file.end);
	streampos size = file.tellg();
	printf("%s %x %i\n",filename.c_str(),(unsigned int)size,file.fail());
	rom = new uint8_t[size];
	file.seekg(0,ios::beg);
	file.read((char *)rom,size);
	file.close();

	cartridgeType = rom[0x147];
	switch (cartridgeType) {
	case 1:
	case 2:
	case 3:
		romType = MBC1;
		break;
	default:
		romType = NONE;
		break;
	}

	bankOffset = 0x4000;
	ramOffset = 0;
	romMode = 0;

	switch (rom[0x149]) {
	case 0:
		ram = new uint8_t[1];
		break;
	case 1:
		ram = new uint8_t[0x800];
		break;
	case 2:
		ram = new uint8_t[0x2000];
		break;
	case 3:
		ram = new uint8_t[0x8000];
		break;
	case 4:
		ram = new uint8_t[0x20000];
	}
}

BasicROMSection::~BasicROMSection(){
	delete this->rom;
	delete this->ram;
}

bool BasicROMSection::containsAddress(uint16_t addr) {
	return addr<0x8000 || (addr>0xc000 && addr<=0xa000);
}

bool BasicROMSection::writeAddress(uint16_t addr, uint8_t value) {
	if (containsAddress(addr)) {
		if (addr>0x8000) memory[addr-0xa000] = value;

		switch(romType) {
		case MBC1:
			if (addr<0x4000) {
				if (value==0) value = 1;
				bankOffset &= 0x1fff;
				bankOffset |= ((uint64_t)value&0x1f)<<14;
			}
			else if (addr<0x6000) {
				if (romMode==1) {
					bankOffset &= 0x7ffff;
					bankOffset |= ((uint64_t)value&3)<<20;
				} else {
					ramOffset &= 0x1fff;
					ramOffset |= ((uint64_t)value&3)<<13;
				}
			}
			else if(addr<0x8000) {
				romMode = value&1;
			}
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}
uint8_t BasicROMSection::readAddress(uint16_t addr) {
	if (addr>=0xa000) return ram[addr-0xa000+ramOffset];
	if (addr<0x4000) return rom[addr];
	else return rom[bankOffset+addr-0x4000];
}

} /* namespace proc */
