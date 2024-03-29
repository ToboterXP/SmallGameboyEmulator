/*
 * i60_7f.h
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#ifndef I60_7F_H_
#define I60_7F_H_


#include "i60_7f.h"
#include <cstdint>
#include <processor/Processor.h>

namespace proc {

int execute60_7f(uint8_t opcode, Processor * proc) {
	switch (opcode) {
	case 0x60: // ld h,b
		proc->h = proc->b;
		return 1;
	case 0x61: // ld h,c
		proc->h = proc->c;
		return 1;
	case 0x62: //ld h,d
		proc->h = proc->d;
		return 1;
	case 0x63: //ld h,e
		proc->h = proc->e;
		return 1;
	case 0x64: //ld h,h
		return 1;
	case 0x65: //ld h,l
		proc->h = proc->l;
		return 1;
	case 0x66: //ld h,(hl)
		proc->h = proc->memory->readMemory(proc->getHL());
		return 2;
	case 0x67: //ld h,a
		proc->h = proc->a;
		return 1;
	case 0x68: //ld l,b
		proc->l = proc->b;
		return 1;
	case 0x69: //ld l,c
		proc->l = proc->c;
		return 1;
	case 0x6a: //ld l,d
		proc->l = proc->d;
		return 1;
	case 0x6b: //ld l,e
		proc->l = proc->e;
		return 1;
	case 0x6c: //ld l,h
		proc->l = proc->h;
		return 1;
	case 0x6d: //ld l,l
		return 1;
	case 0x6e: //ld l,(hl)
		proc->l = proc->memory->readMemory(proc->getHL());
		return 2;
	case 0x6f: //ld l,a
		proc->l = proc->a;
		return 1;
	case 0x70: // ld (hl),b
		proc->memory->writeMemory(proc->getHL(), proc->b );
		return 2;
	case 0x71: // ld (hl),c
		proc->memory->writeMemory(proc->getHL(), proc->c );
		return 2;
	case 0x72: //ld (hl),d
		proc->memory->writeMemory(proc->getHL(), proc->d );
		return 2;
	case 0x73: //ld (hl),e
		proc->memory->writeMemory(proc->getHL(), proc->e );
		return 2;
	case 0x74: //ld (hl),h
		proc->memory->writeMemory(proc->getHL(), proc->h );
		return 2;
	case 0x75: //ld (hl),l
		proc->memory->writeMemory(proc->getHL(), proc->l );
		return 2;
	case 0x76: //halt
		proc->halt();
		return 1;
	case 0x77: //ld (hl),a
		proc->memory->writeMemory(proc->getHL(), proc->a );
		return 2;
	case 0x78: //ld a,b
		proc->a = proc->b;
		return 1;
	case 0x79: //ld a,c
		proc->a = proc->c;
		return 1;
	case 0x7a: //ld a,d
		proc->a = proc->d;
		return 1;
	case 0x7b: //ld a,e
		proc->a = proc->e;
		return 1;
	case 0x7c: //ld a,h
		proc->a = proc->h;
		return 1;
	case 0x7d: //ld a,l
		proc->a = proc->l;
		return 1;
	case 0x7e: //ld a,(hl)
		proc->a = proc->memory->readMemory(proc->getHL());
		return 2;
	case 0x7f: //ld a,a
		return 1;
	}
	return 0;
}

}

#endif /* I60_7F_H_ */
