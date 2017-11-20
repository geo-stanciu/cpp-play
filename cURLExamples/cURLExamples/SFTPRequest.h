#pragma once

#include <curl/curl.h>
#include "MemoryStruct.h"

enum FTPConnectType {
	FTP_CONNECT_TYPE_FTP,
	FTP_CONNECT_TYPE_SFTP
};

bool sftp_ls(const char *url, char *user, char *password, struct MemoryStruct *dest);
bool sftp_get(const char *url, char *user, char *password, struct MemoryStruct *dest);
//bool sftp_put(const char *url, const char *postdata, struct MemoryStruct *dest);
