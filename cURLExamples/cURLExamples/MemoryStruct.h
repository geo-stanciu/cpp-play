#pragma once

#include <stdlib.h>

class MemoryStruct {
public:
	MemoryStruct(void);
	~MemoryStruct(void);

	void init();

	char *memory;
	size_t size;
};
