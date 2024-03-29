/*
 * ie0_ff.h
 *
 *  Created on: 14.10.2019
 *      Author: Tobias
 */

#ifndef IE0_FF_H_
#define IE0_FF_H_


#include "ie0_ff.h"
#include <cstdint>
#include <cstdio>
#include <processor/Processor.h>

namespace proc {

void _call(Processor * proc, uint16_t addr) {
	proc->push16(proc->pc);
	proc->pc = addr;
}

int executeE0_FF(uint8_t opcode, Processor * proc) {
	uint8_t prev,val,res, addr;
	int8_t b;
	switch (opcode) {
	case 0xe0: //ldh (a8),A
		proc->memory->writeMemory(0xff00 + proc->getInstruction8(),proc->a);
		return 3;
	case 0xe1: //pop hl
		proc->setHL(proc->pop16());
		return 3;
	case 0xe2: //ld (c),a
		proc->memory->writeMemory(0xff00 + proc->c,proc->a);
		return 2;
	case 0xe3: //-
		proc->unknownOpcode();
		return 1;
	case 0xe4: //-
		proc->unknownOpcode();
		return 1;
	case 0xe5: //push hl
		proc->push16(proc->getHL());
		return 4;
	case 0xe6: //and d8
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,1);
		proc->setFlag(CARRY_FLAG,0);
		proc->a &=  proc->getInstruction8();
		proc->setFlag(ZERO_FLAG,proc->a==0);
		return 2;
	case 0xe7: //rst 20h
		_call(proc,0x20);
		return 4;
	case 0xe8: //add sp,r8
		b = proc->getInstruction8();
		proc->sp += b;
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(ZERO_FLAG,0);
		return 4;
	case 0xe9: //jp (hl)
		proc->pc = proc->getHL();
		return 1;
	case 0xea: //ld (a16),a
		proc->memory->writeMemory(proc->getInstruction16(),proc->a);
		return 4;
	case 0xeb: //-
		proc->unknownOpcode();
		return 1;
	case 0xec: //-
		proc->unknownOpcode();
		return 1;
	case 0xed: //-
		proc->unknownOpcode();
		return 1;
	case 0xee: //xor d8
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,0);
		proc->setFlag(CARRY_FLAG,0);
		proc->a ^=  proc->getInstruction8();
		proc->setFlag(ZERO_FLAG,proc->a==0);
		return 2;
	case 0xef: //rst 28h
		_call(proc,0x28);
		return 4;
	case 0xf0: //ldh A,(a8)
		addr = proc->getInstruction8();
		res = proc->memory->readMemory(0xff00+addr);
		proc->a = res;
		return 3;
	case 0xf1: //pop af
		proc->setAF(proc->pop16());
		return 3;
	case 0xf2: //ld a,(c)
		proc->a = proc->memory->readMemory(0xff00+proc->c);
		return 2;
	case 0xf3: //di
		proc->interruptMasterEnable = false;
		return 1;
	case 0xf4: //-
		proc->unknownOpcode();
		return 1;
	case 0xf5: //push af
		proc->push16(proc->getAF());
		return 2;
	case 0xf6: //or d8
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,0);
		proc->setFlag(CARRY_FLAG,0);
		proc->a |=  proc->getInstruction8();
		proc->setFlag(ZERO_FLAG,proc->a==0);
		return 1;
	case 0xf7: //rst 30h
		_call(proc,0x30);
		return 4;
	case 0xf8: //ld hl,sp+r8
		proc->setHL( proc->sp + (int8_t)(proc->getInstruction8()) );
		return 3;
	case 0xf9: //ld sp,hl
		proc->sp = proc->getHL();
		return 2;
	case 0xfa: //ld a,(a16)
		proc->a = proc->memory->readMemory(proc->getInstruction16());
		return 4;
	case 0xfb: //ei
		proc->interruptMasterEnable = true;
		return 1;
	case 0xfc: //-
		proc->unknownOpcode();
		return 1;
	case 0xfd: //-
		proc->unknownOpcode();
		return 1;
	case 0xfe: //cp d8
		proc->setFlag(SUB_FLAG,1);
		prev = proc->a;
		val = proc->getInstruction8();
		res =proc->a - val;
		proc->setFlag(CARRY_FLAG,prev<res);
		proc->setFlag(HALF_CARRY_FLAG,(((prev&0xf)- (val&0xf))&0x10)==0x10);
		proc->setFlag(ZERO_FLAG,res==0);
		return 2;
	case 0xff: //rst 38h
		_call(proc,0x38);
		return 4;
	}
	return 0;
}
}


#endif /* IE0_FF_H_ */
