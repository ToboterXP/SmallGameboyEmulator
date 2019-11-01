/*
 * OAMDMA.h
 *
 *  Created on: 30.10.2019
 *      Author: Tobias
 */

#ifndef OAMDMA_H_
#define OAMDMA_H_

#include <memory/MemoryManager.h>

using namespace memory;

namespace misc {

class OAMDMA {
public:
	MemoryManager * memory;
	OAMDMA(MemoryManager * memory);
	void clock();
	virtual ~OAMDMA();
};

} /* namespace ppu */

#endif /* OAMDMA_H_ */
