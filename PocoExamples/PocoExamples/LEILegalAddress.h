#pragma once

#include "LEIAddress.h"

class LEILegalAddress : LEIAddress
{
public:
	LEILegalAddress();
	~LEILegalAddress();

	bool parse(const Poco::JSON::Object::Ptr &obj);

	std::string toString(const std::string &initialIndent = "");
};

