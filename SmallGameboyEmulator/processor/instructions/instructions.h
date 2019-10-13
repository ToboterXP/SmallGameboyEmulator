
#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <cstdint>
#include <processor/Processor.h>
#include "i00_1f.h"
#include "i20_3f.h"
#include "i40_5f.h"
#include "i60_7f.h"

namespace proc {

//returns instruction delay
int executeInstruction(uint8_t opcode,Processor * proc ) {
	if (opcode < 0x20) return execute00_1f(opcode, proc);
	if (opcode < 0x40) return execute20_3f(opcode, proc);
	if (opcode < 0x60) return execute40_5f(opcode, proc);
	if (opcode < 0x80) return execute60_7f(opcode, proc);
	return 0;
}
}

#endif
