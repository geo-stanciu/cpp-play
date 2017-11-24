// cURLExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HTTPRequest.h"
#include "SFTPRequest.h"
#include "StringUtil.h"

int main() {
	SFTPRequest *req = NULL;
	MemoryFile *file = new MemoryFile();
	StringArray files;
	char *filepath = NULL;

	/*char* url = "http://www.bnro.ro/nbrfxrates.xml";
	
	if (!http_get(url, mem))
		goto cleaup;

	FILE *f = fopen("d:/f1.xml", "wb");
	if (f) {
		fputs(mem->memory, f);
		fclose(f);
	}*/

	/*char *url = "http://www.bvb.ro/Rss/BSENews.ashx";

	if (!http_post(url, "", mem))
		goto cleaup;

	FILE *f = fopen("d:/f1_post.xml", "wb");
	if (f) {
		fputs(mem->memory, f);
		fclose(f);
	}*/

	req = new SFTPRequest("192.168.0.108", "geo", "geo");

	if (!req->cd("~/sftp_example"))
		goto cleaup;

	if (!req->ls(&files)) {
		goto cleaup;
	}

	for (int i = 0, n = files.size(); i < n; i++) {
		printf("%s\n", files[i]);
	}

	/*
	if (!req->get("f1.txt", file)) {
		goto cleaup;
	}

	filepath = strdup_printf("d:/%s", file->filename);

	FILE *f = fopen(filepath, "wb");
	if (f) {
		fputs(file->stream->memory, f);
		fclose(f);
	}
	*/
cleaup:
	if (filepath)
		free(filepath);

	if (file)
		delete file;

	if (req)
		delete req;

    return 0;
}
