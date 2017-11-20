#include "stdafx.h"
#include "MemoryStruct.h"

struct MemoryStruct * MemoryStruct_new() {
	struct MemoryStruct *mem = NULL;
	
	mem = (struct MemoryStruct *)malloc(sizeof(struct MemoryStruct));
	mem->memory = NULL;

	return mem;
}

void MemoryStruct_cleanup(struct MemoryStruct *mem) {
	if (mem) {
		if (mem->memory) {
			free(mem->memory);
		}

		free(mem);
		mem = NULL;
	}
}
