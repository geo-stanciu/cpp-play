#pragma once

#include "LEIBase.h"
#include "LEIAddress.h"
#include "LEILegalAddress.h"
#include "LEIHeadquartersAddress.h"

class LEIEntity : LEIBase
{
public:
	LEIEntity();
	~LEIEntity();

	char *LegalName = NULL;
	LEILegalAddress *LegalAddress = NULL;
	LEIHeadquartersAddress *HeadquartersAddress = NULL;
	char *BusinessRegisterEntityID = NULL;
	char *LegalJurisdiction = NULL;
	char *LegalForm = NULL;
	char *EntityStatus = NULL;

	bool parse(const Poco::JSON::Object::Ptr &obj);

	std::string toString(const std::string &initialIndent = "");
};
