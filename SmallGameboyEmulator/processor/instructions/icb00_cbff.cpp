/*
 * icb00_cbff.cpp
 *
 *  Created on: 16.10.2019
 *      Author: Tobias
 */

#include "icb00_cbff.h"
#include <cstdio>

namespace proc {

typedef uint8_t (*opFunction) (uint8_t val, Processor* proc);

uint8_t rlc(uint8_t val,Processor * proc) {
	uint8_t carry = val&0x80;
	proc->setFlag(CARRY_FLAG,carry>>7);
	val = (val<<1)|(carry>>7);
	return val;
}

uint8_t rrc (uint8_t val,Processor * proc) {
	uint8_t carry = val&1;
	proc->setFlag(CARRY_FLAG,carry);
	val = (val>>1)|(carry<<7);
	return val;
}

uint8_t rl(uint8_t val,Processor * proc) {
	uint8_t carry = val&0x80;
	val = (val<<1)|proc->getFlag(CARRY_FLAG);
	proc->setFlag(CARRY_FLAG,carry>>7);
	return val;
}

uint8_t rr(uint8_t val,Processor * proc) {
	uint8_t carry = val&1;
	val = (val>>1)|(proc->getFlag(CARRY_FLAG)<<7);
	proc->setFlag(CARRY_FLAG,carry);
	return val;
}

uint8_t sla(uint8_t val,Processor * proc) {
	proc->setFlag(CARRY_FLAG,val>>7);
	return val<<1;
}

uint8_t sra(uint8_t val,Processor * proc) {
	proc->setFlag(CARRY_FLAG,val&1);
	return (val>>1) | (val&0x80);
}

uint8_t swap(uint8_t val, Processor * proc) {
	uint8_t res = 0;
	res |= (val&0xf)<<4;
	res |= (val&0xf0)>>4;
	proc->setFlag(CARRY_FLAG,0);
	return res;
}

uint8_t srl(uint8_t val,Processor * proc) {
	proc->setFlag(CARRY_FLAG,val&1);
	return val>>1;
}

opFunction operations[] = {
		rlc,
		rrc,
		rl,
		rr,
		sla,
		sra,
		swap,
		srl
};

uint8_t setBit(uint8_t val,uint8_t bit) {
	return val | (1<<bit);
}

uint8_t resetBit(uint8_t val,uint8_t bit) {
	return val & (~(1<<bit));
}

bool getBit(uint8_t val,uint8_t bit) {
	return val&(1<<bit);
}

int executeCB(uint8_t opcode, Processor * proc) {
	uint8_t source = 0;
	switch(opcode%8) {
	case 0:
		source = proc->b;
		break;
	case 1:
		source = proc->c;
		break;
	case 2:
		source = proc->d;
		break;
	case 3:
		source = proc->e;
		break;
	case 4:
		source = proc->h;
		break;
	case 5:
		source = proc->l;
		break;
	case 6:
		source = proc->memory->readMemory(proc->getHL());
		break;
	case 7:
		source = proc->a;
		break;
	}

	uint8_t result = 0;

	if (opcode>=0xc0) { //set *,b
		result = setBit(source,(opcode-0xc0)/8);
	} else if (opcode >= 0x80) { //res *,b
		result = resetBit(source,(opcode-0x80)/8);
	} else if (opcode >=0x40) { //bit *,b
		proc->setFlag(ZERO_FLAG,!getBit(source,(opcode-0x40)/8));
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,1);
		return opcode%8==6 ? 4 :2;
	} else {
		result = operations[opcode/8](source,proc);
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,0);
		proc->setFlag(ZERO_FLAG,result==0);
	}

	switch (opcode%8) {
	case 0:
		proc->b = result;
		break;
	case 1:
		proc->c = result;
		break;
	case 2:
		proc->d = result;
		break;
	case 3:
		proc->e = result;
		break;
	case 4:
		proc->h = result;
		break;
	case 5:
		proc->l = result;
		break;
	case 6:
		proc->memory->writeMemory(proc->getHL(),result);
		break;
	case 7:
		proc->a = result;
		break;
	}
	return opcode%8==6 ? 4 :2;
}

}

