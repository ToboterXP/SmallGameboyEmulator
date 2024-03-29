
#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <cstdint>
#include <processor/Processor.h>


namespace proc {

//returns instruction delay
int executeInstruction(uint8_t opcode,Processor * proc );
}

#endif
