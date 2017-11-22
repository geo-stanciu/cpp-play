// cURLExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HTTPRequest.h"
#include "SFTPRequest.h"

int main() {
	SFTPRequest *req = NULL;
	StringArray files;

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

	req = new SFTPRequest(FTP_CONNECT_TYPE_SFTP, "192.168.0.108", "geo", "geo");

	if (!req->ls("~/sftp_example", &files)) {
		goto cleaup;
	}

	for (int i = 0, n = files.Size(); i < n; i++) {
		printf("%s\n", files[i]);
	}

cleaup:
	if (req)
		delete req;

    return 0;
}
