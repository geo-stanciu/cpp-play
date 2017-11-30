#include "stdafx.h"
#include "LEIHeadquartersAddress.h"
#include "LEIParser.h"

using namespace Poco::JSON;
using namespace Poco::Dynamic;

LEIHeadquartersAddress::LEIHeadquartersAddress() {
}


LEIHeadquartersAddress::~LEIHeadquartersAddress() {
}

bool LEIHeadquartersAddress::parse(const Object::Ptr &obj) {
	if (!obj->has("HeadquartersAddress")) return false;

	Var val = obj->get("HeadquartersAddress");
	Object::Ptr object = val.extract<Object::Ptr>();

	if (!LEIAddress::parse(object)) return false;

	return true;
}

std::string LEIHeadquartersAddress::toString(const std::string &initialIndent) {
	std::stringbuf buffer;
	std::ostream os(&buffer);
	os
		<< initialIndent << "HeadquartersAddress: " << std::endl
		<< LEIAddress::toString(initialIndent + "\t");

	return buffer.str();
}
