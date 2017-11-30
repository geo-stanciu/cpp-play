#include "stdafx.h"
#include "LEIRegistration.h"
#include "StringUtil.h"
#include "LEIParser.h"

using namespace Poco::JSON;
using namespace Poco::Dynamic;

LEIRegistration::LEIRegistration() {
}

LEIRegistration::~LEIRegistration() {
	if (InitialRegistrationDate) free(InitialRegistrationDate);
	if (LastUpdateDate) free(LastUpdateDate);
	if (RegistrationStatus) free(RegistrationStatus);
	if (NextRenewalDate) free(NextRenewalDate);
	if (ManagingLOU) free(ManagingLOU);
	if (ValidationSources) free(ValidationSources);
}

bool LEIRegistration::parse(const Object::Ptr &obj) {
	if (!obj->has("Registration")) return false;

	Var val = obj->get("Registration");
	Object::Ptr object = val.extract<Object::Ptr>();

	if (!getValue(object, "InitialRegistrationDate", &InitialRegistrationDate)) return false;
	if (!getValue(object, "LastUpdateDate", &LastUpdateDate)) return false;
	if (!getValue(object, "RegistrationStatus", &RegistrationStatus)) return false;
	if (!getValue(object, "NextRenewalDate", &NextRenewalDate)) return false;
	if (!getValue(object, "ManagingLOU", &ManagingLOU)) return false;
	if (!getValue(object, "ValidationSources", &ValidationSources)) return false;

	return true;
}

std::string LEIRegistration::toString(const std::string &initialIndent) {
	std::stringbuf buffer;
	std::ostream os(&buffer);
	os
		<< initialIndent << "Registration" << std::endl
		<< initialIndent << "\t" << "InitialRegistrationDate: " << InitialRegistrationDate << std::endl
		<< initialIndent << "\t" << "LastUpdateDate: " << LastUpdateDate << std::endl
		<< initialIndent << "\t" << "RegistrationStatus: " << RegistrationStatus << std::endl
		<< initialIndent << "\t" << "NextRenewalDate: " << NextRenewalDate << std::endl
		<< initialIndent << "\t" << "ManagingLOU: " << ManagingLOU << std::endl
		<< initialIndent << "\t" << "ValidationSources: " << ValidationSources;

	return buffer.str();
}
