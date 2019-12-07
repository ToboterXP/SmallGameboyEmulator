/*
 * Timer.cpp
 *
 *  Created on: 11.11.2019
 *      Author: Tobias
 */

#include <misc/Timer.h>

namespace ppu {

Timer::Timer() {
	// TODO Auto-generated constructor stub

}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::clock(MemoryManager * memory, Processor * proc) {
	if (!(memory->readMemory(0xff07)&0x4)) return;

	if (countdown--==0) {
		countdown = timerFreqs[memory->readMemory(0xff07)&3];
		memory->writeMemory(0xff05,memory->readMemory(0xff05)+1);
		if (memory->readMemory(0xff05)==0) {
			memory->writeMemory(0xff05,memory->readMemory(0xff06));
			proc->triggerInterrupt(TIMER);
		}
	}
}

} /* namespace ppu */
