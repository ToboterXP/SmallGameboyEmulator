/*
 * APU.h
 *
 *  Created on: 01.12.2019
 *      Author: Tobias
 */

#ifndef APU_H_
#define APU_H_

#include <cstdint>
#include <SDL2/sdl.h>
#include "AudioInterface.h"
#include <memory/MemoryManager.h>

using namespace memory;

namespace audio {

const uint8_t DUTY_CYCLES[] = {1,2,4,6};
class APU {
public:
	//AudioInterface * audio;
	MemoryManager * memory;

	uint16_t lengthTimer = 16384;

	bool c1_enabled = false;
	uint16_t c1_freq = 0;
	int8_t c1_remaining = 0;

	uint8_t c1_sweepTime = 0;
	uint8_t c1_sweepTimer = 0;
	int8_t c1_sweepInc = 0;
	uint8_t c1_sweepShift = 0;

	uint8_t c1_volume = 0;
	int8_t c1_envelopeInc = 0;
	uint8_t c1_envelopeSweep = 0;
	int c1_volumeTimer = 0;

	bool c1_force_reload = false;
	uint8_t c1_duty_count = 0;
	uint8_t c1_last_duty_count = 0;
	uint8_t c1_duty_buffer[32];

	bool c2_enabled = false;
	uint16_t c2_freq = 0;
	uint8_t c2_duty = 0;
	int8_t c2_remaining = 0;

	uint8_t c2_volume = 0;
	int8_t c2_envelopeInc = 0;
	uint8_t c2_envelopeSweep = 0;
	int c2_volumeTimer = 0;

	bool c3_enabled = false;
	int16_t c3_remaining = 0;

	bool c4_enabled = false;
	int16_t c4_remaining = 0;


	APU(MemoryManager * memory);
	virtual ~APU();
	void clockRegisters();
	void clock();
};

} /* namespace audio */

#endif /* APU_H_ */
