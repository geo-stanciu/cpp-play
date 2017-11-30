#include "stdafx.h"
#include "LEIBase.h"
#include "LEIParser.h"
#include "StringUtil.h"

using namespace std;

using namespace Poco;
using namespace Poco::JSON;
using namespace Poco::Dynamic;

LEIBase::LEIBase() {
}


LEIBase::~LEIBase() {
}

bool LEIBase::getValue(const Poco::JSON::Object::Ptr &obj, const std::string &prop, char **dest, const std::string &valueTag) {
	if (!obj->has(prop))
		return false;

	Var rez = obj->get(prop);
	Object::Ptr object = rez.extract<Object::Ptr>();

	if (!object->has(valueTag))
		return false;

	Var val = object->get(valueTag);
	string sval = val.convert<string>();
	*dest = strdup_printf(sval.c_str());

	return true;
}
