#pragma once

#include <curl/curl.h>
#include "MemoryStruct.h"

bool http_get(const char *url, MemoryStruct *dest);
bool http_post(const char *url, const char *postdata, MemoryStruct *dest);
