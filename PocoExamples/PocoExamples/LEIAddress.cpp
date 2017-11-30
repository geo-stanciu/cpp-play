#include "stdafx.h"
#include "LEIAddress.h"
#include "StringUtil.h"
#include "LEIParser.h"

using namespace Poco::JSON;
using namespace Poco::Dynamic;

LEIAddress::LEIAddress() {
}

LEIAddress::~LEIAddress() {
	if (Line1) free(Line1);
	if (City) free(City);
	if (Region) free(Region);
	if (Country) free(Country);
	if (PostalCode) free(PostalCode);
}

bool LEIAddress::parse(const Object::Ptr &obj) {
	if (!getValue(obj, "Line1", &Line1)) return false;
	if (!getValue(obj, "City", &City)) return false;
	if (!getValue(obj, "Region", &Region)) return false;
	if (!getValue(obj, "Country", &Country)) return false;
	if (!getValue(obj, "PostalCode", &PostalCode)) return false;

	return true;
}

std::string LEIAddress::toString(const std::string &initialIndent) {
	std::stringbuf buffer;
	std::ostream os(&buffer);
	os
		<< initialIndent << "Line1: " << Line1 << std::endl
		<< initialIndent << "City: " << City << std::endl
		<< initialIndent << "Region: " << Region << std::endl
		<< initialIndent << "Country: " << Country << std::endl
		<< initialIndent << "PostalCode: " << PostalCode;

	return buffer.str();
}
