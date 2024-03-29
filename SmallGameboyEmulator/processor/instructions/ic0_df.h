/*
 * ic0_df.h
 *
 *  Created on: 14.10.2019
 *      Author: Tobias
 */

#ifndef IC0_DF_H_
#define IC0_DF_H_

#include <cstdint>
#include <processor/Processor.h>
#include "icb00_cbff.h"

namespace proc {
int executeC0_DF(uint8_t opcode, Processor * proc);
}



#endif /* IC0_DF_H_ */
