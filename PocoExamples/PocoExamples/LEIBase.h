#pragma once

#include "Poco/JSON/Object.h"
#include <sstream>

class LEIBase
{
public:
	LEIBase();
	~LEIBase();

	bool getValue(const Poco::JSON::Object::Ptr &obj, const std::string &prop, char **dest, const std::string &valueTag = "$");
};

