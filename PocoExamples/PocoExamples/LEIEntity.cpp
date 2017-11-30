#include "stdafx.h"
#include "LEIEntity.h"
#include "StringUtil.h"
#include "LEIParser.h"

using namespace Poco::JSON;
using namespace Poco::Dynamic;


LEIEntity::LEIEntity() {
	LegalAddress = new LEILegalAddress();
	HeadquartersAddress = new LEIHeadquartersAddress();
}


LEIEntity::~LEIEntity() {
	if (LegalName) free(LegalName);
	if (LegalAddress) delete LegalAddress;
	if (HeadquartersAddress) delete HeadquartersAddress;
	if (BusinessRegisterEntityID) free(BusinessRegisterEntityID);
	if (LegalJurisdiction) free(LegalJurisdiction);
	if (LegalForm) free(LegalForm);
	if (EntityStatus) free(EntityStatus);
}

bool LEIEntity::parse(const Poco::JSON::Object::Ptr &obj) {
	if (!obj->has("Entity")) return false;

	Var val = obj->get("Entity");
	Object::Ptr object = val.extract<Object::Ptr>();

	if (!getValue(object, "LegalName", &LegalName)) return false;
	if (!LegalAddress->parse(object)) return false;
	if (!HeadquartersAddress->parse(object)) return false;
	if (!getValue(object, "BusinessRegisterEntityID", &BusinessRegisterEntityID, "@register")) return false;
	if (!getValue(object, "LegalJurisdiction", &LegalJurisdiction)) return false;
	if (!getValue(object, "LegalForm", &LegalForm)) return false;
	if (!getValue(object, "EntityStatus", &EntityStatus)) return false;

	return true;
}

std::string LEIEntity::toString(const std::string &initialIndent) {
	std::stringbuf buffer;
	std::ostream os(&buffer);
	os
		<< initialIndent << "Entity: " << std::endl
		<< initialIndent << "\t" << "LegalName: " << LegalName << std::endl
	    << LegalAddress->toString(initialIndent + "\t") << std::endl
	    << HeadquartersAddress->toString(initialIndent + "\t") << std::endl
		<< initialIndent << "\t" << "BusinessRegisterEntityID: " << BusinessRegisterEntityID << std::endl
		<< initialIndent << "\t" << "LegalJurisdiction: " << LegalJurisdiction << std::endl
		<< initialIndent << "\t" << "LegalForm: " << LegalForm << std::endl
		<< initialIndent << "\t" << "EntityStatus: " << EntityStatus;

	return buffer.str();
}
