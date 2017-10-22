#include "stdafx.h"
#include "HTTPRequest.h"

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

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

bool http_get(const char *url, struct MemoryStruct *dest) {
	CURL *curl;
	CURLcode res;
	bool ok = true;

	if (dest->memory) {
		free(dest->memory);
		dest->memory = NULL;
	}

	/* will be grown as needed by the realloc */
	dest->memory = (char *)malloc(1);
	/* no data at this point */
	dest->size = 0;

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);

		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/7.56.0");

		// skip ssl certificate authentification
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)dest);

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

bool http_post(const char *url, const char *postdata, struct MemoryStruct *dest) {
	CURL *curl;
	CURLcode res;
	bool ok = true;

	if (dest->memory) {
		free(dest->memory);
		dest->memory = NULL;
	}

	/* will be grown as needed by the realloc */
	dest->memory = (char *)malloc(1);
	/* no data at this point */
	dest->size = 0;

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
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)dest);

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
