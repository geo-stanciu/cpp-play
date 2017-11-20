#include "stdafx.h"
#include "SFTPRequest.h"

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

bool sftp_ls(const char *url, char *user, char *password, struct MemoryStruct *dest) {
	CURL *curl;
	CURLcode res;
	bool ok = true;
	char *userpass = NULL;
	struct MemoryStruct *header = MemoryStruct_new();
	FTPConnectType type = FTP_CONNECT_TYPE_FTP;

	if (dest->memory) {
		free(dest->memory);
		dest->memory = NULL;
	}

	/* will be grown as needed by the realloc */
	dest->memory = (char *)malloc(1);
	/* no data at this point */
	dest->size = 0;

	/* will be grown as needed by the realloc */
	header->memory = (char *)malloc(1);
	/* no data at this point */
	header->size = 0;

	curl = curl_easy_init();

	if (curl) {
		if (user && password) {
			userpass = (char *)malloc((strlen(user) + strlen(password) + 2) * sizeof(char));
			sprintf(userpass, "%s:%s", user, password);

			//curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
			curl_easy_setopt(curl, CURLOPT_USERPWD, userpass);
		}

		/* Define our callback to get called when there's data to be written */
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 1L);

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)dest);
		curl_easy_setopt(curl, CURLOPT_WRITEHEADER, (void *)&header);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		if (strstr(url, "sftp://")) {
			type = FTP_CONNECT_TYPE_SFTP;
		}

		if (type == FTP_CONNECT_TYPE_FTP)
			curl_easy_setopt(curl, CURLOPT_FTPPORT, "-");

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			ok = false;

			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}

		if (userpass)
			free(userpass);

		curl_easy_cleanup(curl);
	}

	MemoryStruct_cleanup(header);

	return ok;
}

bool sftp_get(const char *url, char *user, char *password, struct MemoryStruct *dest) {
	CURL *curl;
	CURLcode res;
	bool ok = true;
	char *userpass = NULL;
	struct MemoryStruct *header = MemoryStruct_new();
	FTPConnectType type = FTP_CONNECT_TYPE_FTP;

	if (dest->memory) {
		free(dest->memory);
		dest->memory = NULL;
	}

	/* will be grown as needed by the realloc */
	dest->memory = (char *)malloc(1);
	/* no data at this point */
	dest->size = 0;

	/* will be grown as needed by the realloc */
	header->memory = (char *)malloc(1);
	/* no data at this point */
	header->size = 0;

	curl = curl_easy_init();

	if (curl) {
		if (user && password) {
			userpass = (char *)malloc((strlen(user) + strlen(password) + 2) * sizeof(char));
			sprintf(userpass, "%s:%s", user, password);

			//curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
			curl_easy_setopt(curl, CURLOPT_USERPWD, userpass);
		}

		/* Define our callback to get called when there's data to be written */
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 1L);

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)dest);
		curl_easy_setopt(curl, CURLOPT_WRITEHEADER, (void *)&header);

		if (strstr(url, "sftp://")) {
			type = FTP_CONNECT_TYPE_SFTP;
		}

		if (type == FTP_CONNECT_TYPE_FTP)
			curl_easy_setopt(curl, CURLOPT_FTPPORT, "-");

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			ok = false;

			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}

		if (userpass)
			free(userpass);

		curl_easy_cleanup(curl);
	}

	MemoryStruct_cleanup(header);

	return ok;
}
