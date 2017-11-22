#pragma once

#include <stdlib.h>

class MemoryStruct {
public:
	MemoryStruct(void);
	~MemoryStruct(void);

	void init(bool make_ready_4_realloc = false);

	char *memory;
	size_t size;
};
