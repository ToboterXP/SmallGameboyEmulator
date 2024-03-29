/*
 * ia0_bf.h
 *
 *  Created on: 14.10.2019
 *      Author: Tobias
 */

#ifndef IA0_BF_H_
#define IA0_BF_H_


#include "ia0_bf.h"
#include <cstdint>
#include <processor/Processor.h>

namespace proc {

int _and(Processor * proc,uint8_t val) {
	proc->setFlag(SUB_FLAG,0);
	proc->setFlag(HALF_CARRY_FLAG,1);
	proc->setFlag(CARRY_FLAG,0);
	proc->a &=  val;
	proc->setFlag(ZERO_FLAG,proc->a==0);
	return 1;
}

int _xor(Processor * proc,uint8_t val) {
	proc->setFlag(SUB_FLAG,0);
	proc->setFlag(HALF_CARRY_FLAG,0);
	proc->setFlag(CARRY_FLAG,0);
	proc->a ^=  val;
	proc->setFlag(ZERO_FLAG,proc->a==0);
	return 1;
}

int _or(Processor * proc,uint8_t val) {
	proc->setFlag(SUB_FLAG,0);
	proc->setFlag(HALF_CARRY_FLAG,0);
	proc->setFlag(CARRY_FLAG,0);
	proc->a |=  val;
	proc->setFlag(ZERO_FLAG,proc->a==0);
	return 1;
}

int _cp(Processor * proc, uint8_t val) {
	proc->setFlag(SUB_FLAG,1);
	uint8_t prev = proc->a;
	uint8_t res =proc->a - val;
	proc->setFlag(CARRY_FLAG,prev<res);
	proc->setFlag(HALF_CARRY_FLAG,(((prev&0xf)- (val&0xf))&0x10)==0x10);
	proc->setFlag(ZERO_FLAG,res==0);
	return 1;
}

int executeA0_BF(uint8_t opcode,Processor * proc) {
	switch (opcode) {
	case 0xa0: //and b
		return _and(proc,proc->b);
	case 0xa1: //and c
		return _and(proc,proc->c);
	case 0xa2: //and d
		return _and(proc,proc->d);
	case 0xa3: //and e
		return _and(proc,proc->e);
	case 0xa4: //and h
		return _and(proc,proc->h);
	case 0xa5: //and l
		return _and(proc,proc->l);
	case 0xa6: //and (hl)
		return _and(proc,proc->memory->readMemory(proc->getHL()))+1;
	case 0xa7: //and a
		return _and(proc,proc->a);
	case 0xa8: //xor b
		return _xor(proc,proc->b);
	case 0xa9: //xor c
		return _xor(proc,proc->c);
	case 0xaa: //xor d
		return _xor(proc,proc->d);
	case 0xab: //xor e
		return _xor(proc,proc->e);
	case 0xac: //xor h
		return _xor(proc,proc->h);
	case 0xad: //xor l
		return _xor(proc,proc->l);
	case 0xae: //xor (hl)
		return _xor(proc,proc->memory->readMemory(proc->getHL()))+1;
	case 0xaf: //xor a
		return _xor(proc,proc->a);
	case 0xb0: //or b
		return _or(proc,proc->b);
	case 0xb1: //or c
		return _or(proc,proc->c);
	case 0xb2: //or d
		return _or(proc,proc->d);
	case 0xb3: //or e
		return _or(proc,proc->e);
	case 0xb4: //or h
		return _or(proc,proc->h);
	case 0xb5: //or l
		return _or(proc,proc->l);
	case 0xb6: //or (hl)
		return _or(proc,proc->memory->readMemory(proc->getHL()))+1;
	case 0xb7: //or a
		return _or(proc,proc->a);
	case 0xb8: //cp b
		return _cp(proc,proc->b);
	case 0xb9: //cp c
		return _cp(proc,proc->c);
	case 0xba: //cp d
		return _cp(proc,proc->d);
	case 0xbb: //cp e
		return _cp(proc,proc->e);
	case 0xbc: //cp h
		return _cp(proc,proc->h);
	case 0xbd: //cp l
		return _cp(proc,proc->l);
	case 0xbe: //cp (hl)
		return _cp(proc,proc->memory->readMemory(proc->getHL()))+1;
	case 0xbf: //cp a
		return _cp(proc,proc->a);
	}
	return 0;
}
}


#endif /* IA0_BF_H_ */
