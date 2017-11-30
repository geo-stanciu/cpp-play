#pragma once

#include "LEIBase.h"

class LEIAddress : LEIBase
{
public:
	LEIAddress();
	~LEIAddress();

	char *Line1 = NULL;
	char *City = NULL;
	char *Region = NULL;
	char *Country = NULL;
	char *PostalCode = NULL;

	bool parse(const Poco::JSON::Object::Ptr &obj);

	std::string toString(const std::string &initialIndent = "");
};

