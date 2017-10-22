// cURLExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HTTPRequest.h"

int main() {
	curl_global_init(CURL_GLOBAL_ALL);

	struct MemoryStruct mem;
	mem.memory = NULL;

	printf("get rates\n");
	//char* url = "http://www.bnro.ro/nbrfxrates.xml";
	char *url = "http://www.bvb.ro/Rss/BSENews.ashx";

	if (!http_get(url, &mem))
		goto cleaup;

	FILE *f = fopen("d:/f1.xml", "wt");
	if (f) {
		fprintf(f, "%s", mem.memory);
		fclose(f);
	}

	if (!http_post(url, "", &mem))
		goto cleaup;

	f = fopen("d:/f1_post.xml", "wt");
	if (f) {
		fprintf(f, "%s", mem.memory);
		fclose(f);
	}

cleaup:
	if (mem.memory) {
		free(mem.memory);
		mem.memory = NULL;
	}

	curl_global_cleanup();

    return 0;
}
