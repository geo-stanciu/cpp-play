// cURLExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HTTPRequest.h"
#include "SFTPRequest.h"

int main() {
	curl_global_init(CURL_GLOBAL_ALL);

	struct MemoryStruct *mem = MemoryStruct_new();

	//char* url = "http://www.bnro.ro/nbrfxrates.xml";
	/*char *url = "http://www.bvb.ro/Rss/BSENews.ashx";

	if (!http_get(url, mem))
		goto cleaup;

	FILE *f = fopen("d:/f1.xml", "wt");
	if (f) {
		fprintf(f, "%s", mem->memory);
		fclose(f);
	}*/

	/*if (!http_post(url, "", mem))
		goto cleaup;

	f = fopen("d:/f1_post.xml", "wt");
	if (f) {
		fprintf(f, "%s", mem->memory);
		fclose(f);
	}*/

	char *sftp_url = "sftp://192.168.0.108/~/";

	if (!sftp_ls(sftp_url, "geo", "geo", mem)) {
		goto cleaup;
	}

	printf("%s", mem->memory);

cleaup:
	MemoryStruct_cleanup(mem);
	curl_global_cleanup();

    return 0;
}
