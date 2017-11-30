#include "stdafx.h"
#include "LEIParser.h"
#include "StringUtil.h"

using namespace std;

using namespace Poco;
using namespace Poco::JSON;
using namespace Poco::Dynamic;

LEIParser::LEIParser() {
}

LEIParser::~LEIParser() {
	if (error_message) free(error_message);
}

bool LEIParser::parseFromJSONString(const string &str, LEIObject &lei) {
	const char *s = str.c_str();
	return parseFromJSONString(s, lei);
}

bool LEIParser::parseFromJSONString(const char *str, LEIObject &lei) {
	string json = str;
	
	Parser parser;
	Var result = parser.parse(json);
	string message = "OK";
	int status_code = 200;

	if (!result.isArray()) {
		// bad LEI !
		Object::Ptr object = result.extract<Object::Ptr>();
		Var msg = object->get("message");
		Var status = object->get("status_code");

		message = msg.convert<string>();
		status_code = status.convert<int>();
	}
	else {
		Poco::JSON::Array::Ptr arr = result.extract<Poco::JSON::Array::Ptr>();
		
		if (arr->size() == 0) {
			message = "empty response";
			status_code = 500;
			goto endparse;
		}

		Object::Ptr object = arr->getObject(0);

		if (!lei.parse(object)) {
			message = "unknown response format";
			status_code = 500;
			goto endparse;
		}
	}

endparse:
	success = status_code == 200;
	error_message = strdup_printf(message.c_str());

	return success;
}
