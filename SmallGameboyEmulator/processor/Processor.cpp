/*
 * Processor.cpp
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#include <processor/Processor.h>

namespace proc {

Processor::Processor(MemoryManager * mem) {
	memory = mem;
	a = 1;
	f = 0xb0;
	b = 0;
	c = 0x13;
	d = 0;
	e = 0xd8;
	h = 0x01;
	l = 0x4d;
	sp = 0xfffe;
	pc = 0x100;

	remainingInstructionTime = 0;
}

Processor::~Processor() {
	// TODO Auto-generated destructor stub
}

//virtual 16bit registers
uint16_t Processor::getAF() {
	return (((uint16_t)a)<<8) + (uint16_t)f;
}
void Processor::setAF(uint16_t val) {
	a = val >> 8;
	f = (uint8_t)val;
}
uint16_t Processor::getBC() {
	return (((uint16_t)b)<<8) + (uint16_t)c;
}
void Processor::setBC(uint16_t val) {
	b = val >> 8;
	c = (uint8_t)val;
}
uint16_t Processor::getDE() {
	return (((uint16_t)d)<<8) + (uint16_t)e;
}
void Processor::setDE(uint16_t val) {
	d = val >> 8;
	e = (uint8_t)val;
}
uint16_t Processor::getHL() {
	return (((uint16_t)h)<<8) + (uint16_t)l;
}
void Processor::setHL(uint16_t val) {
	h = val >> 8;
	l = (uint8_t)val;
}

//instruction fetch
uint8_t Processor::getInstruction8() {
	return memory->readMemory(pc++);
}
uint16_t Processor::getInstruction16() {
	uint16_t ret = (uint16_t)(memory->readMemory(pc++));
	ret |= ((uint16_t)(memory->readMemory(pc++))) << 8 ;
	return ret;
}

//stack
void Processor::push8(uint8_t val) {
	memory->writeMemory(--sp,val);
}
uint8_t Processor::pop8() {
	return memory->readMemory(sp++);
}
void Processor::push16(uint16_t val) {
	push8((uint8_t)(val>>8));
	push8((uint8_t)val);
}
uint16_t Processor::pop16() {
	uint16_t ret = 0;
	ret |= ( (uint16_t)pop8())<<8;
	ret |= (uint16_t)pop8();
	return ret;
}

//flags
void Processor::setFlag(uint8_t flag,uint8_t val) {
	f &= ~(1<<flag);
	f |= val<<flag;
}
bool Processor::getFlag(uint8_t flag) {
	return (f & (1<<flag)) > 0;
}

//16-bit memory
void Processor::writeMemory16(uint16_t addr,uint16_t val) {
	memory->writeMemory(addr,(uint8_t)(val>>8));
	memory->writeMemory(addr+1,(uint8_t)val);
}
uint16_t Processor::readMemory16(uint16_t addr) {
	uint16_t ret = 0;
	ret |= ((uint16_t)(memory->readMemory(addr)))<<8;
	ret |= (uint16_t)(memory->readMemory(addr+1));
	return ret;
}

void Processor::clock() {
	if (--remainingInstructionTime<=0) {

	}
}
} /* namespace proc */
