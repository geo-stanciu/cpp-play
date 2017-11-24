#pragma once
#include "MemoryStruct.h"

class MemoryFile
{
public:
	MemoryFile();
	~MemoryFile();

	char *filename = NULL;
	MemoryStruct *stream = NULL;
};
