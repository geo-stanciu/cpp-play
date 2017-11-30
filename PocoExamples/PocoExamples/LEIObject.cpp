#include "stdafx.h"
#include "LEIObject.h"
#include "StringUtil.h"

using namespace Poco::JSON;
using namespace Poco::Dynamic;

LEIObject::LEIObject() {
	Entity = new LEIEntity();
	Registration = new LEIRegistration();
}


LEIObject::~LEIObject() {
	if (LEI) free(LEI);
	if (Entity) delete Entity;
	if (Registration) delete Registration;
}

bool LEIObject::parse(const Object::Ptr &obj) {
	if (!getValue(obj, "LEI", &LEI)) return false;
	if (!Entity->parse(obj)) return false;
	if (!Registration->parse(obj)) return false;

	return true;
}

std::string LEIObject::toString(const std::string &initialIndent) {
	std::stringbuf buffer;
	std::ostream os(&buffer);
	os
		<< initialIndent << "LEI: " << LEI << std::endl
		<< initialIndent << Entity->toString(initialIndent) << std::endl
		<< initialIndent << Registration->toString(initialIndent);

	return buffer.str();
}
