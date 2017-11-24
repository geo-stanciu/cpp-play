#include "stdafx.h"
#include "HTTPRequest.h"

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, MemoryStruct *mem) {
	size_t realsize = size * nmemb;

	mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

bool http_get(const char *url, MemoryStruct *dest) {
	CURL *curl;
	CURLcode res;
	bool ok = true;

	dest->init(true);

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);

		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/7.56.0");

		// skip ssl certificate authentification
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, dest);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			ok = false;

			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	}

	return ok;
}

bool http_post(const char *url, const char *postdata, MemoryStruct *dest) {
	CURL *curl;
	CURLcode res;
	bool ok = true;

	dest->init(true);

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);

		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		if (postdata)
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
		else
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");

		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/7.56.0");

		// skip ssl certificate authentification
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, dest);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			ok = false;

			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	}

	return ok;
}
