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

void MemoryStruct::init(bool make_ready_4_realloc) {
	if (memory) {
		free(memory);
		memory = NULL;
	}

	size = 0;

	if (make_ready_4_realloc) {
		/* will be grown as needed by the realloc */
		memory = (char *)malloc(1);
	}
}
