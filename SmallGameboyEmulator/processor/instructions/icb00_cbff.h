/*
 * icb00_cbff.h
 *
 *  Created on: 16.10.2019
 *      Author: Tobias
 */

#ifndef ICB00_CBFF_H_
#define ICB00_CBFF_H_

#include <cstdint>
#include <processor/Processor.h>

namespace proc {
int executeCB(uint8_t opcode, Processor * proc);
}



#endif /* ICB00_CBFF_H_ */
