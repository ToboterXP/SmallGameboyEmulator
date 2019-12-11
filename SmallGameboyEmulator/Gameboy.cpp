/*
 * Gameboy.cpp
 *
 *  Created on: 13.10.2019
 *      Author: Tobias
 */

#include "Gameboy.h"
#include <cstdio>
#include <chrono>
#include <processor/instructions/instructions.h>

using namespace std::chrono;

Gameboy::Gameboy(string romFile,int screenSize) {
	this->memory = new MemoryManager();

	this->memory->romSection = new BasicROMSection(romFile);
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
	this->ppu = new PPU(memory,processor,screenSize);
	this->joypad = new Joypad();
	this->oam = new OAMDMA(memory);
	this->timer = new Timer();

	this-> apu = new APU(memory);
}

Gameboy::~Gameboy() {
	delete this->memory;
	delete this->processor;
	delete this->ppu;
	delete this->joypad;
	delete this->oam;
	delete this->timer;
	delete this->apu;
}

void Gameboy::clock() {
	ppu->clock();
	timer->clock(memory,processor);

	if (procCD--<=0) {
		procCD = 3;

		processor->clock();
		apu->clockRegisters();
		oam->clock();

		if (memory->lastAccess==0xff00 || ppu->vBlank)
			joypad->clock(memory);
	}
	apu->clock();
}

void Gameboy::run() {
	while (!(processor->frozen)) {
		auto start = steady_clock::now();
		do  {
			clock();
		} while (!ppu->vBlank && !(processor->frozen));

		int time = 0;
		do {
			auto stop = steady_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			time = duration.count();
		} while (time<16742 && !(joypad->speedUp));
		memory->writeMemory(0xff04,memory->readMemory(0xff04)+1);

		if (joypad->exit) return;
	}
	printf("Processor is frozen addr: %.4x opcode: %.2x romBank: %i",processor->pc,memory->readMemory(processor->pc-1),memory->romSection->romBank);
	cout<<endl;
}


