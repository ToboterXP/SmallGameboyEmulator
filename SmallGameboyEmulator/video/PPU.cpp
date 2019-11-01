/*
 * PPU.cpp
 *
 *  Created on: 17.10.2019
 *      Author: Tobias
 */

#include <video/PPU.h>
#include <cstdio>

namespace ppu {

PPU::PPU(MemoryManager * memory,Processor * proc) {

	this->memory = memory;
	this->proc = proc;
	delay = line_delay;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Small Gameboy Emulator",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			320,
			288,
			0);

	surface = SDL_GetWindowSurface(window);
}

PPU::~PPU() {
	SDL_DestroyWindow(window);
	SDL_FreeSurface(surface);
}

void PPU::drawPixel(uint8_t x, uint8_t y, uint8_t shade) {
	shade &= 3;
	uint8_t colors[] = {255,200,120,0} ;
	uint8_t color = colors[shade];
	SDL_Rect drawPos = {x*2,y*2,2,2};
	SDL_FillRect(surface,&drawPos,SDL_MapRGB(surface->format,color,color,color));
}

void PPU::clock() {
	delay -= 1;
	if (delay<=0) {
		delay += line_delay;
		xDraw =  0;
		yDraw += 1;
		disableSpriteLine = false;

		currentSchedSprite = 0;
		bool highSprites =  memory->readMemory(0xff40)&(1<<2);
		uint8_t spriteOffset = highSprites ? 0 : 8;
		for (uint16_t spriteBase=0xfe00;spriteBase<0xfea0;spriteBase+=4) {
			uint8_t spriteY = memory->readMemory(spriteBase);
			if (yDraw<spriteY-spriteOffset && spriteY-16<=yDraw) {
				scheduledSprites[currentSchedSprite++] = spriteBase;
				if (currentSchedSprite==10) break;
			}
		}
		if (yDraw==143) {
			proc->triggerInterrupt(proc::V_BLANK);
			(this->i)++;
			SDL_UpdateWindowSurface(window);
		}
		if (yDraw>153) {
			yDraw = 0;
		}
		memory->writeMemory(0xff44,yDraw);
		if (yDraw==memory->readMemory(0xff45) && (memory->readMemory(0xff41)&(1<<6))!=0) {
			proc->triggerInterrupt(proc::LCDC);
		}
	}

	if (i%2==0) return;

	if (xDraw<=166) {
		//handle lcdc register
		uint8_t lcdc = memory->readMemory(0xff40);
		if (lcdc&(1<<3))
			bgTileMap = 0x9c00;
		else
			bgTileMap = 0x9800;

		if (lcdc&(1<<4))
			bgTileData = 0x8000;
		else
			bgTileData = 0x8800;

		if (!(lcdc&(1<<7))) {
			yDraw = 0;
			xDraw = 0;
			return;
		}

		bool highSprites = lcdc&(1<<2);
		uint8_t spriteOffset = highSprites ? 0 : 8;

		uint8_t scrollX = memory->readMemory(0xff43);
		uint8_t scrollY = memory->readMemory(0xff42);


		uint8_t spritePixel = 0xff;
		uint8_t currentX = 0xff;
		bool priority = false;
		for (int i=0;i<currentSchedSprite;i++) {
			uint16_t spriteBase = scheduledSprites[i];
			uint8_t spriteY = memory->readMemory(spriteBase);
			uint8_t spriteX = memory->readMemory(spriteBase+1);
			uint8_t tileNr = memory->readMemory(spriteBase+2);
			if (highSprites) tileNr &= ~1;
			uint8_t flags = memory->readMemory(spriteBase+3);
			priority = flags&(1<<7);
			bool yOverlap = (yDraw<spriteY-spriteOffset && spriteY-16<=yDraw);
			bool xOverlap = (xDraw<spriteX && spriteX-8<=xDraw);
			if (xOverlap && yOverlap) {
				if (spriteX>=currentX && spritePixel!=0) {
					continue;
				} else {
					currentX = spriteX;
				}
				if ((spriteY-8)>yDraw) {
					uint8_t x = (xDraw-(spriteX-8))%8;
					if (flags&(1<<5)) x= 7-x;
					uint8_t y = (yDraw-(spriteY-16))%8;
					if (flags&(1<<6)) y = 7-y;
					uint16_t tileAddress = 0x8000+((uint16_t)tileNr)*16;
					uint8_t currentTileL = memory->readMemory(tileAddress+y*2);
					uint8_t currentTileH = memory->readMemory(tileAddress+y*2+1);
					if (x==7) currentTileH<<=1;
					else currentTileH>>=(6-x);
					spritePixel = ((currentTileL>>(7-x))&1)|(currentTileH&2);
				} else {
					tileNr++;
					uint8_t x = (xDraw-(spriteX-8))%8;
					if (flags&(1<<5)) x= 7-x;
					uint8_t y = (yDraw-(spriteY-8))%8;
					if (flags&(1<<6)) y = 7-y;
					uint16_t tileAddress = 0x8000+((uint16_t)tileNr)*16;
					uint8_t currentTileL = memory->readMemory(tileAddress+y*2);
					uint8_t currentTileH = memory->readMemory(tileAddress+y*2+1);
					if (x==7) currentTileH<<=1;
					else currentTileH>>=(6-x);
					spritePixel = ((currentTileL>>(7-x))&1)|(currentTileH&2);
				}
			}
		}

		uint16_t currentTileX = ((xDraw+scrollX)/8)%32;
		uint16_t currentTileY = ((yDraw+scrollY)/8)%32;
		uint16_t tileNumAddr = bgTileMap+currentTileY*32+currentTileX;
		uint16_t tileNumber = memory->readMemory(tileNumAddr);
		uint16_t tileAddress = bgTileData+((uint16_t)tileNumber)*16;

		if (bgTileData == 0x8800) tileAddress = 0x9000+((int8_t)tileNumber)*16;

		uint8_t currentTileL = memory->readMemory(tileAddress+((yDraw+scrollY)%8)*2);
		uint8_t currentTileH = memory->readMemory(tileAddress+((yDraw+scrollY)%8)*2+1);
		if ((xDraw+scrollX)%8==7) currentTileH<<=1;
		else currentTileH>>=(6-(xDraw+scrollX)%8);
		uint8_t currentPixel = ((currentTileL>>(7-(xDraw+scrollX)%8))&1)|(currentTileH&2);

		if (spritePixel != 0xff && ((priority && currentPixel==0) || (!priority && spritePixel!=0))) {
			currentPixel = spritePixel;
		}
		drawPixel(xDraw,yDraw,currentPixel);
		xDraw++;
	}
}

} /* namespace ppu */