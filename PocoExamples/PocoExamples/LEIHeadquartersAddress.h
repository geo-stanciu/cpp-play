#pragma once

#include "LEIAddress.h"

class LEIHeadquartersAddress : LEIAddress
{
public:
	LEIHeadquartersAddress();
	~LEIHeadquartersAddress();

	bool parse(const Poco::JSON::Object::Ptr &obj);

	std::string toString(const std::string &initialIndent = "");
};
