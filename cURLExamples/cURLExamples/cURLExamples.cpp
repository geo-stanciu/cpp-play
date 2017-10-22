// cURLExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <curl/curl.h>

bool https_get(const char *url);

int main()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);

	printf("get google.com\n");
	if (!https_get("https://www.google1.ro/"))
		goto cleaup;

	printf("done!\n");

cleaup:
	curl_global_cleanup();

    return 0;
}

bool https_get(const char *url)
{
	CURL *curl;
	CURLcode res;
	bool ok = true;

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);

		// skip ssl certificate authentification
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
		{
			ok = false;

			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	}

	return ok;
}