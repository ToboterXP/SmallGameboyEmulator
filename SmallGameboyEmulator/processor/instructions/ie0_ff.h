/*
 * ie0_ff.h
 *
 *  Created on: 14.10.2019
 *      Author: Tobias
 */

#ifndef IE0_FF_H_
#define IE0_FF_H_


#include <cstdint>
#include <processor/Processor.h>

namespace proc {
int executeE0_FF(uint8_t opcode, Processor * proc);
}


#endif /* IE0_FF_H_ */
