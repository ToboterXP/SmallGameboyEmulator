/*
 * i00_1f.h
 *
 *  Created on: 14.10.2019
 *      Author: Tobias
 */

#ifndef I00_1F_H_
#define I00_1F_H_

#include <cstdint>
#include <processor/Processor.h>

namespace proc {
int execute00_1f(uint8_t opcode, Processor * proc);
}



#endif /* I00_1F_H_ */
