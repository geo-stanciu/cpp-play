#include "stdafx.h"
#include "LEILegalAddress.h"
#include "LEIParser.h"

using namespace Poco::JSON;
using namespace Poco::Dynamic;

LEILegalAddress::LEILegalAddress() {
}


LEILegalAddress::~LEILegalAddress() {
}

bool LEILegalAddress::parse(const Object::Ptr &obj) {
	if (!obj->has("LegalAddress")) return false;

	Var val = obj->get("LegalAddress");
	Object::Ptr object = val.extract<Object::Ptr>();

	if (!LEIAddress::parse(object)) return false;

	return true;
}

std::string LEILegalAddress::toString(const std::string &initialIndent) {
	std::stringbuf buffer;
	std::ostream os(&buffer);
	os
		<< initialIndent << "LegalAddress: " << std::endl
		<< LEIAddress::toString(initialIndent + "\t");

	return buffer.str();
}
