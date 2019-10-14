/*
 * i40_5f.h
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#ifndef I40_5F_H_
#define I40_5F_H_

#include "i40_5f.h"
#include <cstdint>
#include <processor/Processor.h>

namespace proc {

int execute40_5f(uint8_t opcode, Processor * proc) {
	switch (opcode) {
	case 0x40: // ld b,b
		return 1;
	case 0x41: // ld b,c
		proc->b = proc->c;
		return 1;
	case 0x42: //ld b,d
		proc->b = proc->d;
		return 1;
	case 0x43: //ld b,e
		proc->b = proc->e;
		return 1;
	case 0x44: //ld b,h
		proc->b = proc->h;
		return 1;
	case 0x45: //ld b,l
		proc->b = proc->l;
		return 1;
	case 0x46: //ld b,(hl)
		proc->b = proc->memory->readMemory(proc->getHL());
		return 2;
	case 0x47: //ld b,a
		proc->b = proc->a;
		return 1;
	case 0x48: //ld c,b
		proc->c = proc->b;
		return 1;
	case 0x49: //ld c,c
		return 1;
	case 0x4a: //ld c,d
		proc->c = proc->d;
		return 1;
	case 0x4b: //ld c,e
		proc->c = proc->e;
		return 1;
	case 0x4c: //ld c,h
		proc->c = proc->h;
		return 1;
	case 0x4d: //ld c,l
		proc->c = proc->l;
		return 1;
	case 0x4e: //ld c,(hl)
		proc->c = proc->memory->readMemory(proc->getHL());
		return 2;
	case 0x4f: //ld c,a
		proc->c = proc->a;
		return 1;
	case 0x50: // ld d,b
		return 1;
	case 0x51: // ld d,c
		proc->d = proc->c;
		return 1;
	case 0x52: //ld d,d
		return 1;
	case 0x53: //ld d,e
		proc->d = proc->e;
		return 1;
	case 0x54: //ld d,h
		proc->d = proc->h;
		return 1;
	case 0x55: //ld d,l
		proc->d = proc->l;
		return 1;
	case 0x56: //ld d,(hl)
		proc->d = proc->memory->readMemory(proc->getHL());
		return 2;
	case 0x57: //ld d,a
		proc->d = proc->a;
		return 1;
	case 0x58: //ld e,b
		proc->e = proc->b;
		return 1;
	case 0x59: //ld e,c
		proc->e = proc->c;
		return 1;
	case 0x5a: //ld e,d
		proc->e = proc->d;
		return 1;
	case 0x5b: //ld e,e
		return 1;
	case 0x5c: //ld e,h
		proc->e = proc->h;
		return 1;
	case 0x5d: //ld e,l
		proc->e = proc->l;
		return 1;
	case 0x5e: //ld e,(hl)
		proc->e = proc->memory->readMemory(proc->getHL());
		return 2;
	case 0x5f: //ld c,a
		proc->e = proc->a;
		return 1;
	}
	return 0;
}

}

#endif /* I40_5F_H_ */
