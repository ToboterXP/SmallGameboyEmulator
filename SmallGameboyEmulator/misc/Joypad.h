/*
 * Joypad.h
 *
 *  Created on: 21.10.2019
 *      Author: Tobias
 */

#ifndef JOYPAD_H_
#define JOYPAD_H_


#include <memory/MemoryManager.h>
#include <SDL2/sdl.h>

using namespace memory;

namespace misc {

const SDL_Scancode keyMap[] = {
		SDL_SCANCODE_K,
		SDL_SCANCODE_J,
		SDL_SCANCODE_H,
		SDL_SCANCODE_G,
		SDL_SCANCODE_D,
		SDL_SCANCODE_A,
		SDL_SCANCODE_W,
		SDL_SCANCODE_S,
};

class Joypad {
public:
	uint8_t pressedKeys = 0;
	void clock(MemoryManager * memory);
	Joypad();
	virtual ~Joypad();
};

} /* namespace ppu */

#endif /* JOYPAD_H_ */
