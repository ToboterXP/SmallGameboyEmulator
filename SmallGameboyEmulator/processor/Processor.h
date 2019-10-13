/*
 * Processor.h
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <cstdint>
#include <memory/MemoryManager.h>

using namespace memory;

namespace proc {

//define cpu flags (f) register partition
const uint8_t ZERO_FLAG = 		8;
const uint8_t SUB_FLAG = 		7;
const uint8_t HALF_CARRY_FLAG = 6;
const uint8_t CARRY_FLAG = 		5;

class Processor {
protected:
	int remainingInstructionTime;
public:
	MemoryManager * memory;
	uint8_t a;
	uint8_t f;
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint8_t e;
	uint8_t h;
	uint8_t l;
	uint16_t sp;
	uint16_t pc;

	//virtual 16 bit register
	uint16_t getAF();
	void setAF(uint16_t val);
	uint16_t getBC();
	void setBC(uint16_t val);
	uint16_t getDE();
	void setDE(uint16_t val);
	uint16_t getHL();
	void setHL(uint16_t val);

	//instruction fetch
	uint8_t getInstruction8();
	uint16_t getInstruction16();

	//stack
	void push8(uint8_t val);
	uint8_t pop8();
	void push16(uint16_t val);
	uint16_t pop16();

	//access flags
	void setFlag(uint8_t flag,uint8_t val);
	bool getFlag(uint8_t flag);

	//16-bit memory
	void writeMemory16(uint16_t addr,uint16_t val);
	uint16_t readMemory16(uint16_t addr);

	void clock();


	Processor(MemoryManager * mem);
	virtual ~Processor();
};

} /* namespace proc */

#endif /* PROCESSOR_H_ */