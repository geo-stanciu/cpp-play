#include "stdafx.h"
#include "MemoryStruct.h"

MemoryStruct::MemoryStruct(void) {
	memory = NULL;
	size = 0;
}

MemoryStruct::~MemoryStruct(void) {
	if (memory) {
		free(memory);
		memory = NULL;
	}

	size = 0;
}

void MemoryStruct::init() {
	if (memory) {
		free(memory);
		memory = NULL;
	}

	/* will be grown as needed by the realloc */
	memory = (char *)malloc(1);
	/* no data at this point */
	size = 0;
}
