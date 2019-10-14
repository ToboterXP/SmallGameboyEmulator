/*
 * i20_3f.h
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#ifndef I20_3F_H_
#define I20_3F_H_

#include "i20_3f.h"
#include <processor/Processor.h>

namespace proc {

int execute20_3f(uint8_t opcode, Processor * proc) {
	int8_t jump;
	uint8_t prev;
	uint16_t prev1;
	switch (opcode) {
	case 0x20: //jr nz,r8
		jump = proc->getInstruction8();
		if (!(proc->getFlag(ZERO_FLAG))) {
			proc->pc += jump;
			return 3;
		}
		return 2;
	case 0x21: // ld hl,d16
		proc->setHL(proc->getInstruction16());
		return 3;
	case 0x22: //ld (hl+),a
		proc->memory->writeMemory(proc->getHL(),proc->a);
		proc->setHL(proc->getHL()+1);
		return 2;
	case 0x23: //inc hl
		proc->setHL(proc->getHL()+1);
		return 2;
	case 0x24: //inc h
		prev = proc->h;
		proc->h++;
		proc->setFlag(ZERO_FLAG,proc->h==0);
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,(((prev&0xf)+1)&0x10)==0x10);
		return 1;
	case 0x25: //dec h
		prev = proc->h;
		proc->h--;
		proc->setFlag(ZERO_FLAG,proc->h==0);
		proc->setFlag(SUB_FLAG,1);
		proc->setFlag(HALF_CARRY_FLAG,(((prev&0xf)-1)&0x10)==0x10);
		return 1;
	case 0x26: //ld h,d8
		proc->h = proc->getInstruction8();
		return 2;
	case 0x27: //daa
		if (proc->getFlag(SUB_FLAG)) {
			uint8_t firstDigit = proc->a&0xf;
			uint8_t secondDigit = ((proc->a)>>8) & 0xf;
			if (firstDigit>9){
				firstDigit += 6;
				secondDigit += 1;
			}
			if (secondDigit>9) secondDigit += 6;
			proc->a = firstDigit;
			proc->a &= 0xf;
			proc->a |= secondDigit<<4;
		} else {
			uint8_t firstDigit = proc->a&0xf;
			uint8_t secondDigit = ((proc->a)>>8) & 0xf;
			if (firstDigit>9 || proc->getFlag(HALF_CARRY_FLAG)) firstDigit -= 6;
			if (secondDigit>9 || proc->getFlag(CARRY_FLAG)) secondDigit -= 6;
			proc->a = firstDigit;
			proc->a &= 0xf;
			proc->a |= secondDigit<<4;
		}
		proc->setFlag(CARRY_FLAG,proc->a>0x99);
		proc->setFlag(ZERO_FLAG,proc->a==0);
		proc->setFlag(SUB_FLAG,0);
		return 1;
	case 0x28: //jr z,r8
		jump = proc->getInstruction8();
		if (proc->getFlag(ZERO_FLAG)) {
			proc->pc += jump;
			return 3;
		}
		return 2;
	case 0x29: //add hl,hl
		prev1 = proc->getHL();
		proc->setHL(proc->getHL() + proc->getHL());
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,(((prev1&0xf)+(proc->getHL()&0xf))&0x10)==0x10);
		proc->setFlag(CARRY_FLAG,prev1 > proc->getHL());
		return 2;
	case 0x2a: //ld a,(hl+)
		proc->a = proc->memory->readMemory(proc->getHL());
		proc->setHL(proc->getHL()+1);
		return 2;
	case 0x2b: //dec hl
		proc->setHL(proc->getHL()-1);
		return 2;
	case 0x2c: //inc l
		prev = proc->l;
		proc->l++;
		proc->setFlag(ZERO_FLAG,proc->l==0);
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,(((prev&0xf)+1)&0x10)==0x10);
		return 1;
	case 0x2d: //dec l
		prev = proc->l;
		proc->l--;
		proc->setFlag(ZERO_FLAG,proc->l==0);
		proc->setFlag(SUB_FLAG,1);
		proc->setFlag(HALF_CARRY_FLAG,(((prev&0xf)-1)&0x10)==0x10);
		return 1;
	case 0x2e: //ld l,d8
		proc->l = proc->getInstruction8();
		return 2;
	case 0x2f: //cpl
		proc->a = ~proc->a;
		proc->setFlag(SUB_FLAG,1);
		proc->setFlag(HALF_CARRY_FLAG,1);
		return 1;
	case 0x30: //jr nc,r8
		jump = proc->getInstruction8();
		if (!(proc->getFlag(CARRY_FLAG))) {
			proc->pc += jump;
			return 3;
		}
		return 2;
	case 0x31: //ld sp,d16
		proc->sp = proc->getInstruction16();
		return 3;
	case 0x32: //ld (hl-),a
		proc->memory->writeMemory(proc->getHL(),proc->a);
		proc->setHL(proc->getHL()-1);
		return 2;
	case 0x33: //inc sp
		proc->sp++;
		return 2;
	case 0x34: //inc (hl)
		prev = proc->memory->readMemory(proc->getHL());
		proc->memory->writeMemory(proc->getHL(),prev+1);
		proc->setFlag(ZERO_FLAG,proc->memory->readMemory(proc->getHL())==0);
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,(((prev&0xf)+1)&0x10)==0x10);
		return 3;
	case 0x35: //dec (hl)
		prev = proc->memory->readMemory(proc->getHL());
		proc->memory->writeMemory(proc->getHL(),prev-1);
		proc->setFlag(ZERO_FLAG,proc->memory->readMemory(proc->getHL())==0);
		proc->setFlag(SUB_FLAG,1);
		proc->setFlag(HALF_CARRY_FLAG,(((prev&0xf)-1)&0x10)==0x10);
		return 3;
	case 0x36: //ld (hl),d8
		proc->memory->writeMemory(proc->getHL(),proc->getInstruction8());
		return 3;
	case 0x37: //scf
		proc->setFlag(CARRY_FLAG, 1);
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,0);
		return 1;
	case 0x38: //jr C,r8
		jump = proc->getInstruction8();
		if (proc->getFlag(CARRY_FLAG)) {
			proc->pc += jump;
			return 3;
		}
		return 2;
	case 0x39: //add hl,sp
		prev1 = proc->getHL();
		proc->setHL(proc->getHL() + proc->sp);
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,(((prev1&0xf)+(proc->sp&0xf))&0x10)==0x10);
		proc->setFlag(CARRY_FLAG,prev1 > proc->getHL());
		return 2;
	case 0x3a: //ld a,(hl-)
		proc->a = proc->memory->readMemory(proc->getHL());
		proc->setHL(proc->getHL()-1);
		return 2;
	case 0x3b: //dec sp
		proc->sp--;
		return 2;
	case 0x3c: //inc a
		prev = proc->a;
		proc->a++;
		proc->setFlag(ZERO_FLAG,proc->a==0);
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,(((prev&0xf)+1)&0x10)==0x10);
		return 1;
	case 0x3d: //dec a
		prev = proc->a;
		proc->a++;
		proc->setFlag(ZERO_FLAG,proc->a==0);
		proc->setFlag(SUB_FLAG,1);
		proc->setFlag(HALF_CARRY_FLAG,(((prev&0xf)-1)&0x10)==0x10);
		return 1;
	case 0x3e: //ld a,d8
		proc->a = proc->getInstruction8();
		return 2;
	case 0x3f: //ccf
		proc->setFlag(CARRY_FLAG, !(proc->getFlag(CARRY_FLAG)));
		proc->setFlag(SUB_FLAG,0);
		proc->setFlag(HALF_CARRY_FLAG,0);
		return 1;
	}
	return 0;
}

}
#endif /* I20_3F_H_ */
