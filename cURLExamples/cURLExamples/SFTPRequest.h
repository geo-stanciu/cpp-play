#pragma once

#include <curl/curl.h>
#include "MemoryFile.h"
#include "StringArray.h"

enum FTPConnectType {
	FTP_CONNECT_TYPE_FTP,
	FTP_CONNECT_TYPE_SFTP
};

class SFTPRequest {
public:
	SFTPRequest(const char *host,
				const char *user = NULL,
				const char *password = NULL,
				const char *initial_directory = NULL);

	SFTPRequest(const char *host,
				int port,
				const char *user = NULL,
				const char *password = NULL,
				const char *initial_directory = NULL);

	SFTPRequest(FTPConnectType ftp_type,
				const char *host,
				const char *user = NULL,
				const char *password = NULL,
				const char * initial_directory = NULL);

	SFTPRequest(FTPConnectType ftp_type,
				const char *host,
				int port,
				const char *user = NULL,
				const char *password = NULL,
				const char * initial_directory = NULL);

	~SFTPRequest(void);

	bool cd(const char *directory);
	bool ls(StringArray *filenames);
	bool ls(const char *directory, StringArray *filenames);
	bool get(const char *filename, MemoryFile *dest);
	bool get(const char *directory, const char *filename, MemoryFile *dest);
	//bool put(const char *url, const char *postdata, MemoryStruct *dest);

private:
	void init(FTPConnectType ftp_type,
			  const char *host,
			  int port,
			  const char *user,
			  const char *password,
			  const char * initial_directory);

	char * normalize_dir(const char *directory);
	void set_login_info();

	CURL *curl = NULL;
	FTPConnectType ftp_type;
	char *base_url = NULL;
	StringArray *current_path = NULL;
	char *current_directory = NULL;
	char *userpass = NULL;
	const char *user;
	const char *password;
	const char *initial_directory;
};
