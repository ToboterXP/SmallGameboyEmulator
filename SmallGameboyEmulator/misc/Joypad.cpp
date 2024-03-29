/*
 * Joypad.cpp
 *
 *  Created on: 21.10.2019
 *      Author: Tobias
 */

#include <misc/Joypad.h>
#include <cstdio>

namespace misc {

Joypad::Joypad() {
	// TODO Auto-generated constructor stub

}

Joypad::~Joypad() {
	// TODO Auto-generated destructor stub
}

void Joypad::clock(MemoryManager * memory) {
	SDL_Event event;
	SDL_PumpEvents();
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit = true;
			break;
		case SDL_KEYDOWN:
			for (int i=0;i<8;i++) {
				if (keyMap[i] == event.key.keysym.scancode) {
					pressedKeys |= 1<<i;
					break;
				}
			}
			if (event.key.keysym.scancode==SDL_SCANCODE_P) speedUp = true;
			break;
		case SDL_KEYUP:
			for (int i=0;i<8;i++) {
				if (keyMap[i] == event.key.keysym.scancode) {
					pressedKeys &= ~(1<<i);
					break;
				}
			}
			if (event.key.keysym.scancode==SDL_SCANCODE_P) speedUp = false;
			break;
		}
	}
	switch (memory->readMemory(0xff00)) {
	case 0x10:
		memory->writeMemory(0xff00,0x10+(~(pressedKeys&0xf)));
		break;
	case 0x20:
		memory->writeMemory(0xff00,0x20+(~(pressedKeys>>4)));
		break;
	}

}


} /* namespace ppu */
