/*
 * i80_9f.h
 *
 *  Created on: 14.10.2019
 *      Author: Tobias
 */

#ifndef I80_9F_H_
#define I80_9F_H_

#include <cstdint>
#include <processor/Processor.h>

using namespace proc;
using namespace std;

namespace proc {
int execute80_9f(uint8_t opcode, Processor * proc);
}

#endif /* I80_9F_H_ */
