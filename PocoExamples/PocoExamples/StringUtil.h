#pragma once

#include <stdlib.h>
#include <stdarg.h>

char* strdup_vprintf(const char* format, va_list ap);

char* strdup_printf(const char* format, ...);
