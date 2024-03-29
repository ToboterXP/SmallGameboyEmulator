/*
 * APU.cpp
 *
 *  Created on: 01.12.2019
 *      Author: Tobias
 */

#include <audio/APU.h>
#include <chrono>

namespace audio {

APU::APU(MemoryManager * memory) {
	this->memory = memory;
}

APU::~APU() {
	//delete audio;
}

void APU::clockRegisters() {
	//channel 1
	if (memory->lastAccess == 0xff10) {
		memory->lastAccess = 0;
		c1_sweepShift = memory->readMemory(0xff10)&7;
		c1_sweepInc = (memory->readMemory(0xff10)&(1<<3)) ? -1 : 1;
		c1_sweepTime = (memory->readMemory(0xff10)&(7<<4))>>4;
	}

	if (memory->lastAccess==0xff12) {
		memory->lastAccess = 0;
		c1_volume = (memory->readMemory(0xff12)&(15<<4))>>4;
		c1_envelopeInc = (memory->readMemory(0xff12)&(1<<3)) ? 1 : -1;
		c1_envelopeSweep = memory->readMemory(0xff12)&7;
	}

	if (memory->lastAccess == 0xff11) {
		memory->lastAccess = 0;
		if (c1_duty_count<32) {
			c1_duty_buffer[c1_duty_count++] = DUTY_CYCLES[(memory->readMemory(0xff11)&(3<<6))>>6];
		}
	}

	if (((memory->lastAccess == 0xff14) && (memory->readMemory(0xff14)&(1<<7)))) {
		c1_enabled = true;
		c1_remaining = 64-(memory->readMemory(0xff11)&(~(3<<6)));
		if (!(memory->readMemory(0xff14)&(1<<6))) c1_remaining = -1;
		c1_freq = 0;
		c1_freq |= memory->readMemory(0xff13);
		c1_freq |= (memory->readMemory(0xff14)&7)<<8;

		c1_sweepTimer = c1_sweepTime*2;

		c1_volumeTimer = c1_envelopeSweep*4;

		memory->lastAccess = 0;

		memory->writeMemory(0xff26,memory->readMemory(0xff26)|1);
	}

	//channel 2

	if (memory->lastAccess==0xff17) {
		memory->lastAccess = 0;
		c2_volume = (memory->readMemory(0xff17)&(15<<4))>>4;
		c2_envelopeInc = (memory->readMemory(0xff17)&(1<<3)) ? 1 : -1;
		c2_envelopeSweep = memory->readMemory(0xff17)&7;
	}

	if (memory->lastAccess == 0xff16 && c2_enabled) {
		memory->lastAccess = 0;
		c2_duty = DUTY_CYCLES[(memory->readMemory(0xff16)&(3<<6))>>6];
	}

	if (((memory->lastAccess == 0xff19) && (memory->readMemory(0xff19)&(1<<7)))) {
		c2_enabled = true;
		c2_remaining = 64-(memory->readMemory(0xff16)&(~(3<<6)));
		if (!(memory->readMemory(0xff19)&(1<<6))) c2_remaining = -1;
		c2_freq = 0;
		c2_freq |= memory->readMemory(0xff18);
		c2_freq |= (memory->readMemory(0xff19)&7)<<8;

		c2_duty = DUTY_CYCLES[(memory->readMemory(0xff16)&(3<<6))>>6];

		c2_volumeTimer = c2_envelopeSweep*4;

		memory->lastAccess = 0;

		memory->writeMemory(0xff26,memory->readMemory(0xff26)|2);
	}

	//channel 3
	if (((memory->lastAccess == 0xff1e) && (memory->readMemory(0xff1e)&(1<<7)))) {
		c3_enabled = true;
		c3_remaining = 256-memory->readMemory(0xff1b);
		if (!(memory->readMemory(0xff1e)&(1<<6))) c3_remaining = -1;

		memory->lastAccess = 0;

		memory->writeMemory(0xff26,memory->readMemory(0xff26)|4);
	}

	//channel 4
	if (((memory->lastAccess == 0xff23) && (memory->readMemory(0xff23)&(1<<7)))) {
		c4_enabled = true;
		c4_remaining = 64-(memory->readMemory(0xff20)&63);
		if (!(memory->readMemory(0xff23)&(1<<6))) c4_remaining = -1;

		memory->lastAccess = 0;

		memory->writeMemory(0xff26,memory->readMemory(0xff26)|8);
	}
}

void APU::clock() {
	if (!(memory->readMemory(0xff26)&(1<<7))) {
		c1_enabled = false;
		c2_enabled = false;
		c3_enabled = false;
		return;
	}


	if (lengthTimer--<=0) {
		lengthTimer = 16384;

		if (c1_remaining!=-1) {
			if (--c1_remaining==0) {
				c1_enabled = false;
				c1_remaining = -1;
				memory->writeMemory(0xff26,memory->readMemory(0xff26)&(~1));
			}
		}

		if (c1_sweepTime != 0 && c1_enabled) {
			if (--c1_sweepTimer==0) {
				c1_sweepTimer = c1_sweepTime*2;
				c1_freq = c1_freq + c1_sweepInc*(c1_freq>>c1_sweepShift);
				if (c1_freq>=2048) {
					c1_enabled = false;
					memory->writeMemory(0xff26,memory->readMemory(0xff26)&(~1));
				} else {
					c1_force_reload = true;
				}
			}
		}

		if (c1_enabled && c1_envelopeSweep && --c1_volumeTimer==0) {
			c1_volumeTimer = c1_envelopeSweep*4;
			c1_volume += c1_envelopeInc;
			if (c1_volume==0) {
				c1_enabled = false;
				c1_remaining = -1;
				memory->writeMemory(0xff26,memory->readMemory(0xff26)&(~1));
			}
		}

		if (c1_enabled && (c1_force_reload || c1_duty_count>0)) {
			c1_force_reload = false;
			if (c1_duty_count==0) {
				c1_duty_count = c1_last_duty_count;
			} else {
				c1_last_duty_count = c1_duty_count;
			}
			c1_duty_count = 0;
		}

		if (c2_remaining!=-1) {
			if (--c2_remaining==0) {
				c2_enabled = false;
				c2_remaining = -1;
				memory->writeMemory(0xff26,memory->readMemory(0xff26)&(~2));
			}
		}

		if (c2_enabled && c2_envelopeSweep && --c2_volumeTimer==0) {
			c2_volumeTimer = c2_envelopeSweep*4;
			c2_volume += c2_envelopeInc;
			if (c2_volume==0) {
				c2_enabled = false;
				c2_remaining = -1;
				memory->writeMemory(0xff26,memory->readMemory(0xff26)&(~2));
			}
		}

		if (c3_remaining!=-1) {
			if (--c3_remaining==0) {
				c3_enabled = false;
				c3_remaining = -1;
				memory->writeMemory(0xff26,memory->readMemory(0xff26)&(~4));
			}
		}

		if (c4_remaining!=-1) {
			if (--c4_remaining==0) {
				c4_enabled = false;
				c4_remaining = -1;
				memory->writeMemory(0xff26,memory->readMemory(0xff26)&(~8));
			}
		}
	}
}

} /* namespace audio */
