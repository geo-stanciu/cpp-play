// cURLExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HTTPRequest.h"
#include "SFTPRequest.h"

int main() {
	MemoryStruct *mem = new MemoryStruct();
	SFTPRequest *req = NULL;

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

	if (!req->ls("", mem)) {
		goto cleaup;
	}

	//printf("%s", mem->memory);

	int i = 0;
	char * curLine = mem->memory;
	
	while (curLine) {
		char * nextLine = strchr(curLine, '\n');
		size_t curLineLen = nextLine ? (nextLine - curLine) : strlen(curLine);
		char * tempStr = (char *)malloc((curLineLen + 1) * sizeof(char));

		if (tempStr) {
			memcpy(tempStr, curLine, curLineLen);
			tempStr[curLineLen] = '\0';  // NUL-terminate!

			if (tempStr[curLineLen - 1] == '\r' || tempStr[curLineLen - 1] == '\n') {
				tempStr[curLineLen - 1] = '\0';
			}

			printf("line %d: %s\n", ++i, tempStr);

			free(tempStr);
		}
		else {
			printf("malloc error\n");
		}

		curLine = nextLine ? (nextLine + 1) : NULL;
	}

cleaup:
	if (mem)
		delete mem;

	if (req)
		delete req;

    return 0;
}
