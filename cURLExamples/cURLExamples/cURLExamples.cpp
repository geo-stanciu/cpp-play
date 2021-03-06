// cURLExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HTTPRequest.h"
#include "SFTPRequest.h"
#include "StringUtil.h"
#include <curl/curl.h>

int main() {
	curl_global_init(CURL_GLOBAL_ALL);

	SFTPRequest *req = NULL;
	MemoryStruct *mem = new MemoryStruct();
	MemoryFile *file = new MemoryFile();
	StringArray files;
	char *filepath = NULL;

	/*char* url = "https://leilookup.gleif.org/api/v1/leirecords?lei=NKY7JRBKJHQQ68KJ6252";

	if (!http_get(url, mem))
		goto cleanup;

	FILE *f = fopen("d:/f1.json", "wb");
	if (f) {
		fputs(mem->memory, f);
		fclose(f);
	}*/

	/*char* url = "http://www.bnro.ro/nbrfxrates.xml";
	
	if (!http_get(url, mem))
		goto cleanup;

	FILE *f = fopen("d:/f1.xml", "wb");
	if (f) {
		fputs(mem->memory, f);
		fclose(f);
	}*/

	/*char *url = "http://www.bvb.ro/Rss/BSENews.ashx";

	if (!http_post(url, "", mem))
		goto cleanup;

	FILE *f = fopen("d:/f1_post.xml", "wb");
	if (f) {
		fputs(mem->memory, f);
		fclose(f);
	}*/

	/*req = new SFTPRequest("192.168.0.108", "geo", "geo");

	if (!req->cd("~/sftp_example"))
		goto cleanup;

	if (!req->ls(&files)) {
		goto cleanup;
	}

	for (int i = 0, n = files.size(); i < n; i++) {
		printf("%s\n", files[i]);
	}*/

	/*
	if (!req->get("f1.txt", file)) {
		goto cleanup;
	}

	filepath = strdup_printf("d:/%s", file->filename);

	FILE *f = fopen(filepath, "wb");
	if (f) {
		fputs(file->stream->memory, f);
		fclose(f);
	}
	*/
cleanup:
	if (filepath)
		free(filepath);

	if (mem)
		delete mem;

	if (file)
		delete file;

	if (req)
		delete req;

	curl_global_cleanup();

    return 0;
}
