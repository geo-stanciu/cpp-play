#include "stdafx.h"
#include "StringUtil.h"
#include <assert.h>

char* strdup_vprintf(const char* format, va_list ap)
{
	va_list ap2;
	int size;
	char* buffer;

	va_copy(ap2, ap);
	size = vsnprintf(NULL, 0, format, ap2) + 1;
	va_end(ap2);

	buffer = (char *)malloc(size + 1);
	assert(buffer != NULL);

	vsnprintf(buffer, size, format, ap);
	return buffer;
}

char* strdup_printf(const char* format, ...)
{
	char* buffer;
	va_list ap;
	va_start(ap, format);
	buffer = strdup_vprintf(format, ap);
	va_end(ap);
	return buffer;
}
