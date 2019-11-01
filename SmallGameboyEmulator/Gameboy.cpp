/*
 * Gameboy.cpp
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#include "Gameboy.h"
#include <cstdio>
#include <processor/instructions/instructions.h>



Gameboy::Gameboy() {
	log = fopen("log.txt", "w");
	this->memory = new MemoryManager();
	//catch-all ram
	this->memory->romSection = new BasicROMSection("./marioLand.gb");
	this->memory->ramSection = new MemorySection(0x00,0x10000);

	//register init
	for (uint16_t addr=0xff00;addr!=0x0;addr++) {
		memory->writeMemory(addr,0);
	}
	memory->writeMemory(0xff10,0x80);
	memory->writeMemory(0xff11,0xbf);
	memory->writeMemory(0xff12,0xf3);
	memory->writeMemory(0xff14,0xbf);
	memory->writeMemory(0xff16,0x3f);
	memory->writeMemory(0xff19,0xbf);
	memory->writeMemory(0xff1a,0x7f);
	memory->writeMemory(0xff1b,0x7f);
	memory->writeMemory(0xff1c,0x9f);
	memory->writeMemory(0xff1e,0xbf);
	memory->writeMemory(0xff20,0xff);
	memory->writeMemory(0xff23,0xbf);
	memory->writeMemory(0xff24,0x77);
	memory->writeMemory(0xff25,0xf3);
	memory->writeMemory(0xff26,0xf1);
	memory->writeMemory(0xff40,0x91);
	memory->writeMemory(0xff47,0xfc);
	memory->writeMemory(0xff48,0xff);
	memory->writeMemory(0xff49,0xff);

	this->processor = new Processor(this->memory);
	this->ppu = new PPU(memory,processor);
	this->joypad = new Joypad();
	this->oam = new OAMDMA(memory);
}

Gameboy::~Gameboy() {
	delete this->memory;
	delete this->processor;
	delete this->ppu;
	delete this->joypad;
	delete this->oam;
	fclose(log);
}

void Gameboy::clock() {
	ppu->clock();
	if (procCD--<=0) {
		/*if (processor->remainingInstructionTime==1 || processor->halted)
			fprintf(log,"AF=%02X%02X BC=%02X%02X DE=%02X%02X HL=%02X%02X SP=%04X PC=%04X CURR=%02X\n",
					processor->a,
					processor->f,
					processor->b,
					processor->c,
					processor->d,
					processor->e,
					processor->h,
					processor->l,
					processor->sp,
					processor->halted  ? processor->pc-1 :processor->pc,
					memory->readMemory(processor->pc));*/
		if (processor->pc==0xffbc) {
			//memory->printMemory(0x8000,0x9fff);
			fclose(log);
			/*while (ppu->yDraw<153) {
				ppu->clock();
			}*/
			//exit(0);
		}
		processor->clock();
		oam->clock();
		joypad->clock(memory);
		procCD = 3;
	}
}

void Gameboy::test() {
	int i=0;
	while (!(processor->frozen) && !(processor->isDebugging)) {
		clock();
		i++;
	}
	//memory->printMemory(0x8000,0xffff);
}

void Gameboy::debugInstruction(uint8_t opcode) {
	processor->frozen = false;
	processor->halted = false;
	processor->stopped = false;
	processor->a = 1;
	processor->f = 0;
	processor->b = 0xa0;
	processor->c = 3;
	processor->d = 0xa0;
	processor->e = 5;
	processor->h = 0xa0;
	processor->l = 0;
	processor->sp = 0xa000;
	processor->pc = 0x9000;
	memory->writeMemory(0x9000,opcode);
	memory->writeMemory(0x9001,0x05);
	memory->writeMemory(0x9002,0xa0);
	for (int i=0x9ffa;i<0xa00f;i++) memory->writeMemory(i,0);
	memory->writeMemory(0xb000,0xd);
	memory->writeMemory(0xb001,0xe);

	executeInstruction(processor->getInstruction8(),processor);

	printf("Opcode %.2x\n",opcode);
	printf("a=%.2x b=%.2x c=%.2x d=%.2x e=%.2x h=%.2x l=%.2x\nf=%x\n",processor->a,processor->b,processor->c,processor->d,processor->e,processor->h,processor->l,processor->f);
	memory->printMemory(0x9ffa,0xa00f);
	printf("\n\n");
}


