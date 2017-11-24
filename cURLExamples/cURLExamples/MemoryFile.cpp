#include "stdafx.h"
#include "MemoryFile.h"
#include "StringUtil.h"
#include <assert.h>


MemoryFile::MemoryFile() {
	stream = new MemoryStruct();
}


MemoryFile::~MemoryFile() {
	if (filename)
		free(filename);

	if (stream)
		delete stream;
}
