/*
 * instructions.cpp
 *
 *  Created on: 14.10.2019
 *      Author: Tobias
 */

#include "instructions.h"
#include "i00_1f.h"
#include "i20_3f.h"
#include "i40_5f.h"
#include "i60_7f.h"
#include "i80_9f.h"
#include "ia0_bf.h"
#include "ic0_df.h"
#include "ie0_ff.h"


namespace proc {
//returns instruction delay
int executeInstruction(uint8_t opcode,Processor * proc ) {
	if (opcode < 0x20) return execute00_1f(opcode, proc);
	if (opcode < 0x40) return execute20_3f(opcode, proc);
	if (opcode < 0x60) return execute40_5f(opcode, proc);
	if (opcode < 0x80) return execute60_7f(opcode, proc);
	if (opcode < 0xa0) return execute80_9f(opcode, proc);
	if (opcode < 0xc0) return executeA0_BF(opcode, proc);
	if (opcode < 0xe0) return executeC0_DF(opcode, proc);
	return executeE0_FF(opcode,proc);
}
}
