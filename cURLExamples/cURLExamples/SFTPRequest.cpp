#include "stdafx.h"
#include "SFTPRequest.h"
#include "StringUtil.h"
#include <assert.h>

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

SFTPRequest::SFTPRequest(FTPConnectType ftp_type,
						 const char *host,
						 const char *user,
						 const char *password,
						 const char * initial_directory) {

	init(ftp_type, host, 22, user, password, initial_directory);
}

SFTPRequest::SFTPRequest(FTPConnectType ftp_type,
						 const char *host,
						 int port,
						 const char *user,
						 const char *password,
						 const char * initial_directory) {

	init(ftp_type, host, port, user, password, initial_directory);
}

SFTPRequest::~SFTPRequest(void) {
	if (curl) {
		curl_easy_cleanup(curl);
		curl = NULL;
	}

	if (base_url)
		free(base_url);

	if (userpass)
		free(userpass);

	curl_global_cleanup();
}

void SFTPRequest::init(FTPConnectType ftp_type,
					   const char *host,
					   int port,
					   const char *user,
					   const char *password,
					   const char * initial_directory) {

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	this->ftp_type = ftp_type;
	this->user = user;
	this->password = password;
	this->initial_directory = initial_directory;

	if (user && password && strlen(user) > 0 && strlen(password) > 0) {
		userpass = strdup_printf("%s:%s", user, password);
	}

	char *init_dir = normalize_dir(initial_directory, true);

	if (ftp_type == FTP_CONNECT_TYPE_FTP)
		base_url = strdup_printf("ftp://%s:%d/%s",
			host ? host : "",
			port,
			init_dir ? init_dir : "");
	else
		base_url = strdup_printf("sftp://%s:%d/%s",
			host ? host : "",
			port,
			init_dir ? init_dir : "");

	if (init_dir)
		free(init_dir);
}

void SFTPRequest::set_login_info() {
	if (userpass) {
		//curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		curl_easy_setopt(curl, CURLOPT_USERPWD, userpass);
	}

	if (ftp_type == FTP_CONNECT_TYPE_FTP)
		curl_easy_setopt(curl, CURLOPT_FTPPORT, "-");
}

char * SFTPRequest::normalize_dir(const char *directory, bool assume_home_if_empty) {
	char *dir = NULL;

	if (directory && strlen(directory) > 0) {
		if (directory[0] == '/')
			dir = strdup_printf("%s", directory + 1);
		else
			dir = strdup_printf("%s", directory);

		size_t len = strlen(dir);

		if (dir[len - 1] != '/') {
			dir = (char *)realloc(dir, (len + 2) * sizeof(char));
			strcat(dir, "/");
		}
	}
	else if (assume_home_if_empty) {
		dir = strdup_printf("~/");
	}

	return dir;
}

bool SFTPRequest::ls(const char *directory, StringArray *filenames) {
	char *url = NULL;
	char *dir = NULL;
	CURLcode res;
	bool ok = false;
	
	assert(filenames != NULL);

	MemoryStruct *dest = new MemoryStruct();
	MemoryStruct *header = new MemoryStruct();

	header->init(true);
	dest->init(true);

	filenames->Clear();

	if (curl) {
		set_login_info();

		/* Define our callback to get called when there's data to be written */
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 1L); // get only filenames

		dir = normalize_dir(directory, true);
		url = strdup_printf("%s%s", base_url ? base_url : "", dir ? dir : "");

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, dest);
		curl_easy_setopt(curl, CURLOPT_WRITEHEADER, header);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			ok = false;

			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}
		else {
			ok = true;
		}

		char * curLine = dest->memory;

		while (curLine) {
			char * nextLine = strchr(curLine, '\n');
			size_t curLineLen = nextLine ? (nextLine - curLine) : strlen(curLine);
			char * file = (char *)malloc((curLineLen + 1) * sizeof(char));

			if (file) {
				memcpy(file, curLine, curLineLen);
				file[curLineLen] = '\0';  // NUL-terminate!

				if (file[curLineLen - 1] == '\r' || file[curLineLen - 1] == '\n') {
					file[curLineLen - 1] = '\0';
				}

				if (strlen(file) > 0 && strcmp(file, ".") != 0 && strcmp(file, "..") != 0)
					filenames->Add(file);
			}
			else {
				printf("malloc error\n");
				return false;
			}

			curLine = nextLine ? (nextLine + 1) : NULL;
		}

		filenames->Sort();

		curl_easy_reset(curl);
	}

	if (dir)
		free(dir);

	if (url)
		free(url);

	if (dest)
		delete dest;

	if (header)
		delete header;

	return ok;
}

bool SFTPRequest::get(const char *directory, const char *filename, MemoryStruct *dest) {
	char *url = NULL;
	char *dir = NULL;
	char *userpass = NULL;
	CURLcode res;
	bool ok = false;
	MemoryStruct *header = new MemoryStruct();

	header->init(true);
	dest->init(true);

	if (curl) {
		set_login_info();

		/* Define our callback to get called when there's data to be written */
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		dir = normalize_dir(directory, true);
		url = strdup_printf("%s%s", base_url ? base_url : "", dir ? dir : "");

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, dest);
		curl_easy_setopt(curl, CURLOPT_WRITEHEADER, header);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			ok = false;

			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		}
		else {
			ok = true;
		}

		curl_easy_reset(curl);
	}

	if (dir)
		free(dir);

	if (url)
		free(url);

	if (header)
		delete header;

	return ok;
}
