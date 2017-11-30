#pragma once

#include "LEIBase.h"

class LEIRegistration : LEIBase
{
public:
	LEIRegistration();
	~LEIRegistration();

	char *InitialRegistrationDate = NULL;
	char *LastUpdateDate = NULL;
	char *RegistrationStatus = NULL;
	char *NextRenewalDate = NULL;
	char *ManagingLOU = NULL;
	char *ValidationSources = NULL;

	bool parse(const Poco::JSON::Object::Ptr &obj);
	std::string toString(const std::string &initialIndent = "");
};
