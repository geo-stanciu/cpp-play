#pragma once

#include <curl/curl.h>
#include "MemoryStruct.h"

enum FTPConnectType {
	FTP_CONNECT_TYPE_FTP,
	FTP_CONNECT_TYPE_SFTP
};

class SFTPRequest {
public:
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

	bool ls(const char *directory, MemoryStruct *dest);
	bool ls(const char *directory, bool list_details, MemoryStruct *dest);
	bool get(const char *directory, const char *filename, MemoryStruct *dest);
	//bool put(const char *url, const char *postdata, MemoryStruct *dest);

private:
	void init(FTPConnectType ftp_type,
			  const char *host,
			  int port,
			  const char *user,
			  const char *password,
			  const char * initial_directory);

	char * normalize_dir(const char *directory, bool assume_home_if_empty);
	void set_login_info();

	CURL *curl = NULL;
	FTPConnectType ftp_type;
	char *base_url = NULL;
	char *userpass = NULL;
	const char *user;
	const char *password;
	const char *initial_directory;
};
