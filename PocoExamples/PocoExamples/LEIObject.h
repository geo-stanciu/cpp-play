#pragma once

#include "LEIBase.h"
#include "LEIEntity.h"
#include "LEIRegistration.h"

class LEIObject : LEIBase
{
public:
	LEIObject();
	~LEIObject();

	char *LEI = NULL;
	LEIEntity *Entity = NULL;
	LEIRegistration *Registration = NULL;

	bool parse(const Poco::JSON::Object::Ptr &obj);

	std::string toString(const std::string &initialIndent = "");
};
