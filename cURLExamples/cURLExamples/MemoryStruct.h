#pragma once

#include <stdlib.h>

struct MemoryStruct {
	char *memory;
	size_t size;
};

struct MemoryStruct * MemoryStruct_new();
void MemoryStruct_cleanup(struct MemoryStruct *mem);
