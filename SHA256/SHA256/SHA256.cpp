// SHA256.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SHA256.h"

int main()
{
	char data[] = "Hello World!";
	char* sha256 = SHA256(data);
	printf("%s\n", sha256);
	free(sha256);

	sha256 = SHA256Checksum("d:/test.exe");
	printf("%s\n", sha256);
	free(sha256);

    return 0;
}

