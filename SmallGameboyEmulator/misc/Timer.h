/*
 * Timer.h
 *
 *  Created on: 11.11.2019
 *      Author: Tobias
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <memory/MemoryManager.h>
#include <processor/Processor.h>

using namespace memory;
using namespace proc;

namespace ppu {

const int timerFreqs[] = {
		977,
		15,
		61,
		244
};

class Timer {
public:
	int countdown = 977;
	Timer();
	virtual ~Timer();
	void clock(MemoryManager * memory, Processor * proc);
};

} /* namespace ppu */

#endif /* TIMER_H_ */
